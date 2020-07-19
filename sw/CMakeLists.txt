cmake_minimum_required(VERSION 2.8)

project(ready)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

include_directories("${CMAKE_PREFIX_PATH}/include" "${CMAKE_SOURCE_DIR}/include")

find_library(LIB_OPAE NAMES opae-c REQUIRED)
find_library(LIB_OPAE_ASE NAMES opae-c-ase REQUIRED)
find_library(LIB_UUID NAMES uuid REQUIRED)
find_library(LIB_MPF NAMES MPF REQUIRED)
find_library(LIB_FDAM NAMES fdam REQUIRED)
find_library(LIB_JSONCPP NAMES jsoncpp REQUIRED)

file(GLOB_RECURSE CPP_SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE H_SRCS ${CMAKE_SOURCE_DIR}/include/*.h)

add_library(ready SHARED ${CPP_SRCS} ${H_SRCS})
add_library(ready_ase SHARED ${CPP_SRCS} ${H_SRCS})

target_link_libraries(ready ${LIB_FDAM} ${LIB_OPAE} ${LIB_UUID} ${LIB_MPF} ${LIB_JSONCPP})
target_link_libraries(ready_ase ${LIB_FDAM} ${LIB_OPAE_ASE} ${LIB_UUID} ${LIB_MPF} ${LIB_JSONCPP})

get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)
if ("${LIB64}" STREQUAL "TRUE")
    set(LIB_DIR "lib64")
else()
    set(LIB_DIR "lib")
endif()

install(
    TARGETS ready ready_ase
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${LIB_DIR}
    ARCHIVE DESTINATION ${LIB_DIR}
    )
        
install(FILES ${H_SRCS} DESTINATION include/ready)

