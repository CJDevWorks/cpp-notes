cmake_minimum_required(VERSION 3.5)
project(cpp_notes)

SET (BOOST_ROOT "/opt/local/include/boost")
SET (Boost_DIR "/opt/local/include/boost")
set(CMAKE_CXX_FLAGS "-std=c++14")

find_package(Boost REQUIRED regex date_time system filesystem thread graph program_options)
include_directories(${Boost_INCLUDE_DIR})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_SOURCE_DIR "/Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file( GLOB SOURCES *.cpp */*.cpp )

foreach (testsourcefile ${SOURCES})
    #get_filename_component(dir_exe ${testsourcefile} NAME_WE)
    string (REPLACE ${CMAKE_SOURCE_DIR}/ "" dir_exe11 ${testsourcefile})
    string (REPLACE ".cpp" "" dir_exe1 ${dir_exe11})
    string (REPLACE "/" "_" dir_exe ${dir_exe1})
    add_executable(${dir_exe}  ${testsourcefile})
endforeach(testsourcefile ${SOURCES})
