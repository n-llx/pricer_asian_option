xadd_executable(UnitTests test_main.cpp)

target_link_libraries(UnitTests PRIVATE GTest::gtest_main Core)

target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/src/Core)

include(GoogleTest)
gtest_discover_tests(UnitTests)
