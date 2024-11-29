#Lent this code from the ThreePP project test cmake
function(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE threepp Catch2::Catch2WithMain autoShapeSortingLib ${OpenCV_LIBS})
    target_include_directories(${name} PRIVATE "${PROJECT_SOURCE_DIR}/include")
    add_test(NAME ${name} COMMAND ${name})
    #target_compile_definitions(${name} PRIVATE DATA_FOLDER="${PROJECT_SOURCE_DIR}/data")
endfunction()


add_test_executable(tests)
add_test_executable(grid_tests)