# Glimpse
Glimpse is a minimal CLI image viewer — open images directly from your terminal.

## Supported Formats
- PNG
- JPG / JPEG
- PPM (P6 binary)

## Dependencies
- SDL2
- SDL2_image
- CMake 3.16+

## Building
```bash
cmake -B build
cmake --build build
```

## Usage
```bash
./build/image_viewer [COMMAND] [IMAGE_PATH]
```

### Commands
| Command | Description |
|---------|-------------|
| `view`  | Opens the image in a window |
| `check` | Prints info about the image (format, size, path) |
| `help`  | Prints usage information |

### Examples
```bash
./build/image_viewer view ~/Pictures/photo.png
./build/image_viewer check ~/Pictures/photo.jpg
```
