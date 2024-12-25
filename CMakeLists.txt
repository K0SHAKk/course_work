cmake_minimum_required(VERSION 3.10)
project(ParallelSort)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем поддержку OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    add_compile_options(${OpenMP_CXX_FLAGS})
    link_libraries(${OpenMP_CXX_LIBRARIES})
endif()

# Указываем исполняемый файл
add_executable(ParallelSort main.cpp)

# Линковка с OpenMP
target_link_libraries(ParallelSort PUBLIC OpenMP::OpenMP_CXX)