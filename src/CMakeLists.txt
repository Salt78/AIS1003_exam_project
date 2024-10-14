
add_library(SceneriesLib scenery.cpp)



target_include_directories(SceneriesLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SceneriesLib PRIVATE threepp::threepp)