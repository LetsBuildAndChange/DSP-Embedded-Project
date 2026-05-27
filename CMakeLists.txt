cmake_minimum_required(VERSION 3.16)

project(rpi_embedded_dsp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)
pkg_check_modules(FFTW REQUIRED fftw3)

add_executable(rpi_dsp
    src/main.cpp
    src/dsp.cpp
)

target_include_directories(rpi_dsp PRIVATE
    include
    ${PORTAUDIO_INCLUDE_DIRS}
    ${FFTW_INCLUDE_DIRS}
)

target_link_libraries(rpi_dsp PRIVATE
    ${PORTAUDIO_LIBRARIES}
    ${FFTW_LIBRARIES}
    atomic
)

target_compile_options(rpi_dsp PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    ${PORTAUDIO_CFLAGS_OTHER}
    ${FFTW_CFLAGS_OTHER}
)