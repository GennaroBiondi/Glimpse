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

## Installing
```bash
cmake --build build --target glimpse-install                      # Install to ~/local/bin
cmake --build build --target glimpse-install-release              # Install to ~/local/bin, optimized
cmake --build build --target glimpse-install-system               # Install to /usr/local/bin
cmake --build build --target glimpse-install-system-release       # Install to /usr/local/bin, optimized
```

## Usage
```bash
glimpse [COMMAND] [IMAGE_PATH]
```

### Commands
| Command | Description |
|---------|-------------|
| `view`  | Opens the image in a window |
| `check` | Prints info about the image (format, size, path) |
| `help`  | Prints usage information |

### Examples
```bash
glimpse view ~/Pictures/photo.png
glimpse check ~/Pictures/photo.jpg
```
