import os
import xml.etree.ElementTree as ET
from PIL import Image
import math
import json
import hashlib

# Define the magic pink color for transparency
TRANSPARENT_PINK = (255, 0, 255)


# Process existing BMPs without JSON files
graphics_dir = "graphics"
if os.path.exists(graphics_dir):
    for filename in os.listdir(graphics_dir):
        if filename.lower().endswith(".bmp"):
            bmp_path = os.path.join(graphics_dir, filename)
            json_filename = filename[:-4] + ".json"
            json_path = os.path.join(graphics_dir, json_filename)

            # Check if JSON already exists
            if not os.path.exists(json_path):
                # Open BMP to get dimensions
                try:
                    img = Image.open(bmp_path)
                    width, height = img.size
                    img.close()

                    # Create appropriate JSON based on width
                    if width <= 64:
                        json_content = {"type": "sprite", "height": width}
                    else:
                        json_content = {"type": "regular_bg"}

                    # Write JSON file
                    with open(json_path, "w") as f:
                        json.dump(json_content, f, indent=4)

                    print(f"Created {json_filename} for {filename}")
                except Exception as e:
                    print(f"Error processing {filename}: {e}")


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

    # Create new square canvas with black background
    # The quantizer will pick up the pink from the image
    new_img = Image.new("RGB", (new_size, new_size), (0, 0, 0))

    # Paste original image in top-left corner
    new_img.paste(img, (0, 0))

    # Reduce colors to maximum 16 using quantization
    # First convert to P mode (palette mode) with max 16 colors
    quantized = new_img.quantize(colors=16, method=Image.Quantize.MEDIANCUT)

    # Get the palette
    palette_data = quantized.getpalette()

    # Extract RGB values from palette (palette is a flat list of R,G,B values)
    raw_colors = []
    num_colors = min(16, len(palette_data) // 3)
    for i in range(num_colors):
        r = palette_data[i * 3]
        g = palette_data[i * 3 + 1]
        b = palette_data[i * 3 + 2]
        # Calculate luminance for sorting
        luminance = 0.299 * r + 0.587 * g + 0.114 * b
        raw_colors.append((r, g, b, luminance))

    # --- New Palette Sorting Logic ---
    # Find pink and separate it from other colors
    pink_color_data = None
    other_colors = []

    for r, g, b, luminance in raw_colors:
        if (r, g, b) == TRANSPARENT_PINK:
            if pink_color_data is None:  # Only grab the first instance
                pink_color_data = (r, g, b, luminance)
        else:
            other_colors.append((r, g, b, luminance))

    # Sort *other* colors by luminance
    other_colors.sort(key=lambda x: x[3])

    # Create the new sorted color list, forcing pink to be at index 0
    sorted_colors = []

    # Add pink at index 0
    if pink_color_data:
        sorted_colors.append(pink_color_data)
    else:
        # Pink wasn't in the image, force it in at index 0
        # Use 0 for luminance, it doesn't matter
        sorted_colors.append(
            (TRANSPARENT_PINK[0], TRANSPARENT_PINK[1], TRANSPARENT_PINK[2], 0)
        )
        # If we were already at 16, remove the last (brightest) one
        if len(other_colors) >= 16:
            other_colors.pop()

    # Add the rest of the colors
    sorted_colors.extend(other_colors)

    # Ensure we are still at max 16 colors
    sorted_colors = sorted_colors[:16]

    # --- New Remapping Logic ---

    # Build the new flat palette list
    new_palette = []
    # This map stores (R,G,B) -> new_index
    color_to_new_index = {}

    for new_idx, (r, g, b, _) in enumerate(sorted_colors):
        new_palette.extend([r, g, b])
        if (r, g, b) not in color_to_new_index:
            color_to_new_index[(r, g, b)] = new_idx

    # Fill the rest of the palette with black if less than 16 colors
    while len(new_palette) < 16 * 3:
        new_palette.extend([0, 0, 0])

    # Build a map from the OLD palette index to the NEW palette index
    old_index_to_new_index = {}
    for old_idx in range(num_colors):
        old_r = palette_data[old_idx * 3]
        old_g = palette_data[old_idx * 3 + 1]
        old_b = palette_data[old_idx * 3 + 2]

        # Find the new index for this old color
        # Default to 0 (pink) if its color was removed (e.g., > 16 colors)
        new_idx = color_to_new_index.get((old_r, old_g, old_b), 0)
        old_index_to_new_index[old_idx] = new_idx

    # Create new image with remapped indices
    remapped_data = []
    for pixel_old_idx in quantized.getdata():
        remapped_data.append(old_index_to_new_index.get(pixel_old_idx, 0))

    # Create final indexed image
    final_img = Image.new("P", (new_size, new_size))
    final_img.putpalette(new_palette)
    final_img.putdata(remapped_data)

    # Save as BMP without color space information
    final_img.save(output_path, "BMP")


def create_tiled_bmp(png_path, output_path, grid_size, tile_indices, sprite_size=32):
    # Load the PNG spritesheet, ensuring it's RGBA
    try:
        spritesheet = Image.open(png_path).convert("RGBA")
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

    # Create an RGBA canvas with a solid OPAQUE PINK background
    # TRANSPARENT_PINK + (255,) -> (255, 0, 255, 255)
    output_image = Image.new(
        "RGBA", (output_width, output_height), TRANSPARENT_PINK + (255,)
    )

    # Place sprites according to indices
    for i, sprite_idx in enumerate(tile_indices):
        # Only paste non-empty tiles. Empty tiles (idx 0) will remain pink.
        if sprite_idx != 0:
            # Calculate position in grid
            grid_x = i % grid_width
            grid_y = i // grid_width

            # Calculate pixel position in output
            out_x = grid_x * sprite_size
            out_y = grid_y * sprite_size

            # Extract sprite from spritesheet (adjust for 1-based indexing)
            sprite_y = (sprite_idx - 1) * sprite_size
            sprite = spritesheet.crop(
                (0, sprite_y, sprite_size, sprite_y + sprite_size)
            )

            # Paste sprite to output, using its own alpha channel as a mask.
            # Transparent pixels in the sprite will not be pasted,
            # revealing the pink background.
            output_image.paste(sprite, (out_x, out_y), mask=sprite)

    # Ensure output directory exists
    output_dir = os.path.dirname(output_path)
    if output_dir and not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # Save as BMP, converting from RGBA to RGB first.
    # This flattens the image, preserving the pink background.
    output_image.convert("RGB").save(output_path, "BMP")

map_dir = os.path.join("bgs", "maps")
maps = os.listdir(map_dir)

map_data = {}
header_includes = set() # Changed to a set to handle duplicates automatically
map_names = []  
image_registry = {} # Stores hash -> {name, width, height}

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
    if not map.endswith(".tmx"):
        continue

    with open(os.path.join(map_dir, map), "r") as f:
        xml_data = f.read()

    root = ET.fromstring(xml_data)

    map_name = map.replace(".tmx", "")
    map_data[map_name] = {"name": map_name}
    map_names.append(map_name)

    tileset = root.findall(".//tileset")[0].attrib["source"].replace("..", "bgs")
    with open(tileset, "r") as f:
        tileset_data = f.read()
    tileset_root = ET.fromstring(tileset_data)
    tileset_path = (
        "bgs/tilesets/" + tileset_root.findall(".//image")[0].attrib["source"]
    )

    try:
        lbl_blue = (
            int(root.find(".//tileset[@source='../tilesets/blue-labels.tsx']").attrib["firstgid"]) - 1
        )
    except:
        print(f"Error: Blue labels missing in {map}")
        exit(1)

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

    # Create the temporary BMP for this map
    temp_bmp_path = "background_maps/" + map_name + ".bmp"
    create_tiled_bmp(
        tileset_path,
        temp_bmp_path,
        [width, height],
        tile_basis,
        sprite_size=32,
    )

    # Calculate Hash of the raw tiled image
    with open(temp_bmp_path, "rb") as f:
        img_bytes = f.read()
        img_hash = hashlib.md5(img_bytes).hexdigest()

    # Deduplication Logic
    if img_hash in image_registry:
        # We have seen this image before!
        source_info = image_registry[img_hash]
        graphics_name = source_info['name']
        
        map_data[map_name]["raw_width"] = source_info['width']
        map_data[map_name]["raw_height"] = source_info['height']
        map_data[map_name]["graphics_name"] = graphics_name
        
        print(f"Skipping image gen for {map_name} (Duplicate of {graphics_name})")
    else:
        # New image
        graphics_name = map_name
        
        process_bmp(
            temp_bmp_path,
            "graphics/map_" + map_name + ".bmp",
        )

        with open("graphics/map_" + map_name + ".json", "w") as f:
            f.write('{"type": "regular_bg"}')

        # Get final dimensions
        img = Image.open("graphics/map_" + map_name + ".bmp")
        raw_width, raw_height = img.size
        
        map_data[map_name]["raw_width"] = raw_width
        map_data[map_name]["raw_height"] = raw_height
        map_data[map_name]["graphics_name"] = graphics_name
        
        # Add to registry
        image_registry[img_hash] = {
            'name': map_name,
            'width': raw_width,
            'height': raw_height
        }
        print(f"Created graphics for {map_name}")

# Template updated to use $graphics_name
template = """
inline constexpr map map_$name = {
    {$width, $height},
    {$raw_width, $raw_height},
    {
    $metadata
    },
    {
    $colliders
    },
    {
    $actions
    },
    {
    $characters
    },
    &bn::regular_bg_items::map_$graphics_name};
"""

full_data = []
sorted_keys = sorted(map_data.keys()) # Sort for consistent output

for key in sorted_keys:
    map_info = map_data[key]
    print(f'> linking "{key}" -> graphics: "{map_info["graphics_name"]}"')

    if "metadata" not in map_info.keys():
        map_info["metadata"] = ""

    new_entry = template
    for elem in map_info.keys():
        new_entry = new_entry.replace("$" + elem, str(map_info[elem]))

    full_data.append(new_entry)
    
    # Add to set (handles duplicates automatically)
    header_includes.add('#include "bn_regular_bg_items_map_' + map_info["graphics_name"] + '.h"')

# Generate header file
includes_dir = "include"

# Sort includes for stable file generation
sorted_includes = sorted(list(header_includes))

with open(os.path.join(includes_dir, "ge_map_data.h"), "w") as f:
    f.write(
        header_template.replace("$includes", "\n".join(sorted_includes)).replace(
            "$definitions", "\n".join(full_data)
        )
    )