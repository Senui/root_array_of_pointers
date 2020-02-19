project(ClassDefInlineTest)
cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

find_package(ROOT REQUIRED COMPONENTS Core Gui)
include(${ROOT_USE_FILE})

set(DICT_FILE "foo_dict")

REFLEX_GENERATE_DICTIONARY(${DICT_FILE} "inline_vector.h" SELECTION "selection.xml")

add_executable(foo main.cc ${DICT_FILE})
target_link_libraries(foo ${ROOT_LIBRARIES})
