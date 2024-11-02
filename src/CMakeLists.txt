add_library(SceneriesLib geoGeneration.cpp)
add_library(GridManagerLib gridManager.cpp)


target_include_directories(SceneriesLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(GridManagerLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SceneriesLib PRIVATE threepp::threepp)

