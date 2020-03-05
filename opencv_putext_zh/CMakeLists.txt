cmake_minimum_required(VERSION 3.10)
project(opencvtextzh)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
message("  ${OpenCV_INCLUDE_DIRS}")
message("  ${OpenCV_LIBS}")
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Freetype REQUIRED)
message("  ${FREETYPE_INCLUDE_DIRS}")
message("  ${FREETYPE_LIBRARIES}")
include_directories(${Freetype_DIR})

add_executable(opencvtest opencvtest.cpp CvxFont.cpp Chinese_Test.cpp Japanese_test.cpp symbol_test.cpp)
target_link_libraries(opencvtest ${OpenCV_LIBS})
target_link_libraries(opencvtest ${FREETYPE_LIBRARIES})
