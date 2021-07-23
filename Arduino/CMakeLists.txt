cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME CSGO_Arduino)

set(${PROJECT_NAME}_BOARD leonardo)
#set(ARDUINO_CPU)
project(${PROJECT_NAME})

# Define additional source and header files or default arduino sketch files
set(${PROJECT_NAME}_SRCS
        Helpers/arrays.h
        Helpers/bytes.h
        Helpers/definitions.h
        Helpers/global.h
        Helpers/utils.h
        )
#set(${PROJECT_NAME}_HDRS)

### Additional static libraries to include in the target.
#set(${PROJECT_NAME}_LIBS)

### Main sketch file
set(${PROJECT_NAME}_SKETCH csgo_arduino.ino)

### Add project directories into the build
#add_subdirectory()

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

### Additional Arduino libraries to include in the target.
set(${PROJECT_NAME}_ARDLIBS EEPROM HID Keyboard Mouse)

# For nested library sources replace ${LIB_NAME} with library name for each library
#set(_RECURSE true)
set(HID_RECURSE true)
set(Keyboard_RECURSE true)
set(Mouse_RECURSE true)

#### Additional settings for programmer. From programmers.txt
set(${PROJECT_NAME}_PROGRAMMER avrispmkii)
set(${PROJECT_NAME}_PORT COM13)
set(leonardo.upload.speed 128000)

## Verbose build process
#set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME})

print_board_list()
print_programmer_list()
