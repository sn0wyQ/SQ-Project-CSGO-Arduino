cmake_minimum_required(VERSION 3.19)
project(PC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR_PLATFORM x86)

set(SOURCES
        Arduino/arduino.cpp
        Arrays/arrays.cpp
        Global/global.cpp
        Memory/memory.cpp
        SDK/Entity/LocalPlayer/local_player.cpp
        SDK/Entity/entity.cpp
        SDK/EntityList/entity_list.cpp
        Timer/timer.cpp
        Utils/utils.cpp
        dump.h
        )

add_executable(PC main.cpp ${SOURCES})
target_include_directories(PC PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
