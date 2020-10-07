cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(sfml-lab-1.1)

add_executable(00 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(00 PUBLIC cxx_std_17)
target_compile_definitions(00 PRIVATE SFML_STATIC)

target_link_libraries(00 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
