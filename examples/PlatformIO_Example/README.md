# PlatformIO Example for ESP32 Configurable Streambuf

This is a complete PlatformIO project demonstrating the usage of the ESP32 Configurable Streambuf library.

## Features Demonstrated

- Multiple output functions (Serial, custom log, file simulation)
- Dynamic adding and removing of output functions
- Lambda function as output handler
- Performance testing
- Real-time logging in main loop

## How to Use

1. Open this folder in PlatformIO IDE or VSCode with PlatformIO extension
2. Build and upload to your ESP32 board
3. Open Serial Monitor at 115200 baud

## Expected Output

The example will demonstrate:
- Messages going to multiple outputs simultaneously
- Dynamic removal of specific outputs
- Uppercase transformation using lambda
- Performance metrics
- Continuous logging every 5 seconds

## Configuration

The `platformio.ini` is configured to use the library from the parent directory. To use the published version from GitHub, uncomment the `lib_deps` line and comment out `lib_extra_dirs`.