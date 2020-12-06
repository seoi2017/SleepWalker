cmake_minimum_required(VERSION 3.16)

project(matrix)

include_directories(./inc /home/invrise/OpenBLAS/include/)

link_directories(/home/invrise/OpenBLAS/lib/)

aux_source_directory(./src DIR_SRC)

add_compile_options(-Wall -Ofast -std=c++17)

add_executable(main ${DIR_SRC})

target_link_libraries(main pthread openblas)