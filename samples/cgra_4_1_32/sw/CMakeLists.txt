cmake_minimum_required(VERSION 2.8)

project(main)

set(CMAKE_CXX_STANDARD 11)

include_directories("${CMAKE_PREFIX_PATH}/include" "${CMAKE_SOURCE_DIR}/include")

find_library(LIB_OPAE NAMES opae-c REQUIRED)
find_library(LIB_OPAE_ASE NAMES opae-c-ase REQUIRED)
find_library(LIB_UUID NAMES uuid REQUIRED)
find_library(LIB_MPF NAMES MPF REQUIRED)
find_library(LIB_FDAM NAMES fdam REQUIRED)
find_library(LIB_JSONCPP NAMES jsoncpp REQUIRED)
find_library(LIB_READY NAMES ready REQUIRED)
find_library(LIB_READY_ASE NAMES ready_ase REQUIRED)


file(GLOB CPP_SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB H_SRCS ${CMAKE_SOURCE_DIR}/include/*.h)

add_executable(main_ase ${CPP_SRCS} ${H_SRCS})
add_executable(main ${CPP_SRCS} ${H_SRCS})

target_link_libraries(main_ase ${LIB_READY_ASE} ${LIB_FDAM} ${LIB_OPAE_ASE} ${LIB_UUID} ${LIB_MPF} ${LIB_JSONCPP})
target_link_libraries(main ${LIB_READY} ${LIB_FDAM} ${LIB_OPAE} ${LIB_UUID} ${LIB_MPF} ${LIB_JSONCPP})
