cmake_minimum_required(VERSION 3.19)
project("collisions_1D")

enable_testing()

find_package(GTest REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system network audio REQUIRED)

LIST(APPEND my_tests_targets
    test_collisions_1Dv2
)

foreach(my_target IN LISTS my_tests_targets)
add_executable("${my_target}" "${my_target}.cpp")
    target_compile_options("${my_target}" PRIVATE -g3 -Wall -Wextra)
    target_link_libraries("${my_target}"
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio 
        sfml-network 
        # sfml-music
        GTest::gtest_main
        collisions_1Dv2
    )    
    add_test("${my_target}_runner" "${my_target}")
endforeach(my_target IN LISTS my_targets)
