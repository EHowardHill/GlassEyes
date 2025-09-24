import os
import xml.etree.ElementTree as ET
from PIL import Image
import math


def process_bmp(input_path, output_path):
    # Load the image
    img = Image.open(input_path)

    # Convert to RGB if necessary (to ensure we can work with it)
    if img.mode != "RGB":
        img = img.convert("RGB")

    # Get original dimensions
    orig_width, orig_height = img.size

    # Calculate new canvas size (next multiple of 256 that fits both dimensions)
    max_dim = max(orig_width, orig_height)
    new_size = math.ceil(max_dim / 256) * 256

    # Create new square canvas with white background
    new_img = Image.new("RGB", (new_size, new_size), (0, 0, 0))

    # Paste original image in top-left corner
    new_img.paste(img, (0, 0))

    # Reduce colors to maximum 16 using quantization
    # First convert to P mode (palette mode) with max 16 colors
    quantized = new_img.quantize(colors=16, method=Image.Quantize.MEDIANCUT)

    # Get the palette
    palette_data = quantized.getpalette()

    # Extract RGB values from palette (palette is a flat list of R,G,B values)
    colors = []
    num_colors = min(16, len(palette_data) // 3)
    for i in range(num_colors):
        r = palette_data[i * 3]
        g = palette_data[i * 3 + 1]
        b = palette_data[i * 3 + 2]
        # Calculate luminance for sorting
        luminance = 0.299 * r + 0.587 * g + 0.114 * b
        colors.append((r, g, b, luminance))

    # Sort colors by luminance (darkest to lightest)
    colors.sort(key=lambda x: x[3])

    # Create mapping from old indices to new indices
    old_to_new = {}
    new_palette = []
    for new_idx, (r, g, b, _) in enumerate(colors):
        # Find this color in the original palette
        for old_idx in range(num_colors):
            old_r = palette_data[old_idx * 3]
            old_g = palette_data[old_idx * 3 + 1]
            old_b = palette_data[old_idx * 3 + 2]
            if old_r == r and old_g == g and old_b == b:
                old_to_new[old_idx] = new_idx
                break
        new_palette.extend([r, g, b])

    # Create new image with remapped indices
    remapped_data = []
    for pixel in quantized.getdata():
        remapped_data.append(old_to_new.get(pixel, 0))

    # Create final indexed image
    final_img = Image.new("P", (new_size, new_size))
    final_img.putpalette(new_palette)
    final_img.putdata(remapped_data)

    # Save as BMP without color space information
    # PIL doesn't add color space info by default for BMP files
    final_img.save(output_path, "BMP")


def create_tiled_bmp(png_path, output_path, grid_size, tile_indices, sprite_size=32):
    # Load the PNG spritesheet
    try:
        spritesheet = Image.open(png_path)
    except Exception as e:
        raise ValueError(f"Could not load PNG file: {e}")

    # Calculate number of sprites in the sheet
    sheet_width, sheet_height = spritesheet.size
    if sheet_width != sprite_size:
        raise ValueError(
            f"Spritesheet width ({sheet_width}) doesn't match sprite size ({sprite_size})"
        )

    num_sprites = sheet_height // sprite_size

    # Validate inputs
    grid_width, grid_height = grid_size
    expected_tiles = grid_width * grid_height

    if len(tile_indices) != expected_tiles:
        raise ValueError(
            f"Expected {expected_tiles} tile indices, got {len(tile_indices)}"
        )

    tile_indices = [t if t >= 0 and t <= num_sprites else 0 for t in tile_indices]

    # Create output image
    output_width = grid_width * sprite_size
    output_height = grid_height * sprite_size
    output_image = Image.new("RGB", (output_width, output_height))

    # Place sprites according to indices
    for i, sprite_idx in enumerate(tile_indices):
        # Calculate position in grid
        grid_x = i % grid_width
        grid_y = i // grid_width

        # Calculate pixel position in output
        out_x = grid_x * sprite_size
        out_y = grid_y * sprite_size

        # If index is 0, draw a black square
        if sprite_idx == 0:
            # Create a black tile
            black_tile = Image.new("RGB", (sprite_size, sprite_size), color="black")
            output_image.paste(black_tile, (out_x, out_y))
        else:
            # Extract sprite from spritesheet (adjust for 1-based indexing)
            sprite_y = (sprite_idx - 1) * sprite_size
            sprite = spritesheet.crop(
                (0, sprite_y, sprite_size, sprite_y + sprite_size)
            )

            # Paste sprite to output
            output_image.paste(sprite, (out_x, out_y))

    # Ensure output directory exists
    output_dir = os.path.dirname(output_path)
    if output_dir and not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Save as BMP
    output_image.save(output_path, "BMP")


map_dir = os.path.join("bgs", "maps")
maps = os.listdir(map_dir)

map_data = {}
full_headers = []
map_names = []  # Track all map names for header generation

# Single header template that includes everything
header_template = """// Auto-Generated Map Header
// This file contains all map definitions as inline constexpr

#ifndef GE_MAP_DATA_H
#define GE_MAP_DATA_H

#include "ge_maps.h"
$includes

$definitions

#endif // GE_MAP_DATA_H
"""

for map in maps:
    with open(os.path.join(map_dir, map), "r") as f:
        xml_data = f.read()

    root = ET.fromstring(xml_data)

    map_name = map.replace(".tmx", "")
    map_data[map_name] = {"name": map_name}
    map_names.append(map_name)  # Store map name for header generation

    tileset = root.findall(".//tileset")[0].attrib["source"].replace("..", "bgs")
    with open(tileset, "r") as f:
        tileset_data = f.read()
    tileset_root = ET.fromstring(tileset_data)
    tileset_path = (
        "bgs/tilesets/" + tileset_root.findall(".//image")[0].attrib["source"]
    )

    lbl_blue = (
        int(
            root.find(".//tileset[@source='../tilesets/blue-labels.tsx']").attrib[
                "firstgid"
            ]
        )
        - 1
    )

    # Find all layer elements
    layers = root.findall(".//layer")

    tile_basis = []
    for layer in layers:
        layer_name = layer.get("name")
        data_element = layer.find("data").text.strip()

        width = data_element.split("\n")[0].count(",")
        height = data_element.count("\n") + 1

        map_data[map_name]["width"] = width
        map_data[map_name]["height"] = height
        map_data[map_name][layer_name] = data_element.replace("\n", "\n\t")

        if layer_name in ["colliders", "decor"]:
            list2 = [int(x) for x in data_element.replace("\n", "").split(",")]
            if tile_basis == []:
                tile_basis = [0 for _ in list2]
            tile_basis = [b if b != 0 else a for a, b in zip(tile_basis, list2)]

        elif layer_name in ["characters", "actions", "metadata"]:
            map_data[map_name][layer_name] = ",".join(
                [
                    str(int(x) - lbl_blue if int(x) != 0 else 0)
                    for x in data_element.replace("\n", "").split(",")
                ]
            )

    create_tiled_bmp(
        tileset_path,
        "background_maps/" + map_name + ".bmp",
        [width, height],
        tile_basis,
        sprite_size=32,
    )

    process_bmp(
        "background_maps/" + map_name + ".bmp",
        "graphics/map_" + map_name + ".bmp",
    )

    with open("graphics/map_" + map_name + ".json", "w") as f:
        f.write('{"type": "regular_bg"}')

    img = Image.open("graphics/map_" + map_name + ".bmp")
    raw_width, raw_height = img.size

    map_data[map_name]["raw_width"] = raw_width
    map_data[map_name]["raw_height"] = raw_height

# Template for inline constexpr definitions
template = """
inline constexpr map map_$name = {
    {$width, $height},
    {$raw_width, $raw_height},
    {\n\t$metadata\n    },
    {\n\t$colliders\n    },
    {\n\t$actions\n    },
    {\n\t$characters\n    },
    &bn::regular_bg_items::map_$name};
"""

full_data = []
for key in map_data.keys():
    map = map_data[key]

    if "metadata" not in map.keys():
        map["metadata"] = ""

    new_entry = template
    for elem in map.keys():
        new_entry = new_entry.replace("$" + elem, str(map[elem]))

    full_data.append(new_entry)
    full_headers.append('#include "bn_regular_bg_items_map_' + key + '.h"')

# Generate only the header file with all definitions
includes_dir = "include"

with open(os.path.join(includes_dir, "ge_map_data.h"), "w") as f:
    f.write(
        header_template.replace("$includes", "\n".join(full_headers)).replace(
            "$definitions", "\n".join(full_data)
        )
    )

# No .cpp file needed anymore
