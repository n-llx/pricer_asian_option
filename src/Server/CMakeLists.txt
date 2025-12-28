add_executable(PricerServer main.cpp)

target_link_libraries(PricerServer PRIVATE Core ws2_32 wsock32)

target_include_directories(PricerServer PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(PricerServer PRIVATE _WIN32_WINNT=0x0601)
