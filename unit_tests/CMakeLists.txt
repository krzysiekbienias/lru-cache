find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(lru_cache_tests
        test_lru_cache_linked_list.cpp
        test_lru_cache_deque.cpp
)

set_target_properties(lru_cache_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(lru_cache_tests PRIVATE
        core_lib
        GTest::gtest
        GTest::gtest_main
)

gtest_discover_tests(lru_cache_tests)
