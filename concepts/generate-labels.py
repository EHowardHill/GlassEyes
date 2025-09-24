from PIL import Image, ImageDraw, ImageFont

# Constants
sprite_size = 32
num_sprites = 2048
total_height = num_sprites * sprite_size
background_color = (128, 0, 0)
text_color = "white"
font_size = 10
output_file = "spritesheet.png"

# Create a new image with the specified dimensions and background color
img = Image.new('RGB', (sprite_size, total_height), color=background_color)

# Load the font
try:
    font = ImageFont.truetype("arial.ttf", font_size)
except IOError:
    print("Arial font not found. Using default font.")
    font = ImageFont.load_default()

# Create ImageDraw object
draw = ImageDraw.Draw(img)

# Generate and draw text for each sprite
for i in range(num_sprites):
    text = str(i + 1)
    # Calculate the centered position for the text
    position = (sprite_size // 2, i * sprite_size + sprite_size // 2)
    # Draw the text with anchor 'mm' to center it
    draw.text(position, text, fill=text_color, font=font, anchor="mm")

# Save the image
img.save(output_file)
print(f"Spritesheet generated: {output_file}")