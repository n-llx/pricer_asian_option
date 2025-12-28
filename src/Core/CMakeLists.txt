add_library(Core
    Instruments/Payoff.cpp
    Math/StochasticModel.cpp
    Math/HestonModel.cpp
    Pricing/MonteCarloPricer.cpp
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add OpenMP if available (used in original code)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Core PUBLIC OpenMP::OpenMP_CXX)
endif()
