add_executable(PricerAdapter adapter.cpp)

target_link_libraries(PricerAdapter PRIVATE Core)

# Use the headers we downloaded in Server/include (json.hpp)
target_include_directories(PricerAdapter PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/Core
    ${CMAKE_SOURCE_DIR}/src/Server/include
)

# Preserve legacy CLI if needed, but for now Adapter is the main focus
# add_executable(PricerCLI main.cpp) 
# target_link_libraries(PricerCLI PRIVATE Core)
