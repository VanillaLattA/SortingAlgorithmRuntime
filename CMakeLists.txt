cmake_minimum_required(VERSION 3.5)
project(SortingAlgs)
set(CMAKE_CXX_STANDARD 11)

set(EXE1_NAME sortedverification)
set(EXE2_NAME consistentresultverification)
set(EXE3_NAME timealgorithms)

add_library(SortingAlgs STATIC
        insertionsort.h insertionsort.cpp
        mergesort.h mergesort.cpp
        quicksort.h quicksort.cpp)
target_include_directories(SortingAlgs PUBLIC .)
target_compile_options(SortingAlgs PRIVATE -Wall -Wextra -Werror)

add_library(Json STATIC json.hpp)
set_target_properties(Json PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Json PUBLIC .)
target_compile_options(Json PRIVATE -Wall -Wextra -Werror)

add_library(CSV STATIC CSV.h CSV.cpp)
target_include_directories(CSV PUBLIC .)
target_link_libraries(CSV PUBLIC Json SortingAlgs)
target_compile_options(CSV PRIVATE -Wall -Wextra -Werror)

add_executable(${EXE1_NAME} sortedverification.cxx)
target_link_libraries(${EXE1_NAME} PRIVATE Json)
target_compile_options(${EXE1_NAME} PRIVATE -Wall -Wextra -Werror)

add_executable(${EXE2_NAME} consistentresultverification.cxx)
target_link_libraries(${EXE2_NAME} PRIVATE Json)
target_compile_options(${EXE2_NAME} PRIVATE -Wall -Wextra -Werror)

add_executable(${EXE3_NAME} timealgorithms.cxx)
target_link_libraries(${EXE3_NAME} PRIVATE CSV)
target_compile_options(${EXE3_NAME} PRIVATE -Wall -Wextra -Werror)

add_executable(CreateData createdata.cxx)
target_link_libraries(CreateData PRIVATE Json SortingAlgs)
target_compile_options(CreateData PRIVATE -Wall -Wextra -Werror)
