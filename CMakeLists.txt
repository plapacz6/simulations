cmake_minimum_required(VERSION 3.19)
project("collisions_1D")

find_package(SFML 2.5 COMPONENTS graphics window system network audio REQUIRED)

LIST(APPEND my_targets
    collisions_1D
    collisions_1Dv2_demo
)

add_library(collisions_1Dv2 STATIC collisions_1Dv2.cpp)
target_compile_options(collisions_1Dv2 PUBLIC -g -Wall -Wextra)
target_include_directories(collisions_1Dv2 PUBLIC ".")

foreach(my_target IN LISTS my_targets)
add_executable("${my_target}" "${my_target}.cpp")
    target_compile_options("${my_target}" PRIVATE -g3 -Wall)
    target_link_libraries("${my_target}"
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio 
        sfml-network 
        # sfml-music
    )    
endforeach(my_target IN LISTS my_targets)

target_link_libraries(collisions_1Dv2_demo 
    collisions_1Dv2
)

add_subdirectory(tests)
