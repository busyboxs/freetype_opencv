cmake_minimum_required(VERSION 3.15)
project(OpenCVUnicode)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Freetype REQUIRED)
message(STATUS "Freetype library status")
message(STATUS "    ${FREETYPE_INCLUDE_DIRS}")
message(STATUS "    ${FREETYPE_INCLUDE_DIR_ft2build}")
message(STATUS "    ${FREETYPE_INCLUDE_DIR_freetype2}")
include_directories(${FREETYPE_INCLUDE_DIRS})

set(SRC
    main.cpp
    CvxFont.cpp
    Chinese_test.cpp
    Japanese_test.cpp
    Symbol_test.cpp)

add_executable(OpenCVUnicode ${SRC})
target_link_libraries(OpenCVUnicode ${OpenCV_LIBS})
target_link_libraries(OpenCVUnicode ${FREETYPE_LIBRARIES})