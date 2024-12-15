cmake_minimum_required(VERSION 3.0)

#set(CMAKE_C_COMPILER "vc4-elf-gcc")
set(CMAKE_ASM_COMPILER "vc4-elf-as")
set(CMAKE_CXX_COMPILER "vc4-elf-g++")
set(OBJCOPY "vc4-elf-objcopy")
set(OBJCOPY_ARGS -O binary)
set(CMAKE_CXX_FLAGS "-nostdlib -fno-rtti -fno-exceptions -ffreestanding -O2")
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(ROOT_DIR ${CMAKE_BINARY_DIR}/..)
set(LINKSCRIPT_PATH ${ROOT_DIR}/link.ld)
set(DIR_INCLUDE ${CMAKE_SOURCE_DIR}/inc)

project(videore
        ASM
        CXX
)
# Make -rdynamic go away.
#set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_EXECUTABLE_SUFFIX .elf)

add_executable(videore
        entry.s
        Main.cpp
)
add_library(core
        inc/dev/crystall/Aux.cpp
        inc/dev/crystall/Gpio.cpp
        inc/Console.cpp
        inc/Console.hpp
        inc/String.hpp
        inc/String.cpp
        inc/Memory.hpp
        inc/Memory.cpp
        inc/Runtime.cpp
        inc/Iterator.hpp
        inc/Core.cpp
        inc/Core.hpp
)
target_link_libraries(videore core -T ${LINKSCRIPT_PATH})
target_include_directories(videore PRIVATE ${DIR_INCLUDE})
target_include_directories(core PRIVATE ${DIR_INCLUDE})

# Extract raw binary from the target executable.
add_custom_command(
        TARGET videore
        POST_BUILD
        COMMAND ${OBJCOPY} ${OBJCOPY_ARGS} $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin
)