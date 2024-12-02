#Lent this code from the ThreePP project test cmake
function(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE threepp Catch2::Catch2WithMain autoShapeSortingLib opencv_core opencv_highgui opencv_imgproc)
    target_include_directories(${name} PRIVATE "${PROJECT_SOURCE_DIR}/include")
    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_subdirectory(integrated_glfw_tests)


add_test_executable(opencv_detection_tests)
add_test_executable(grid_tests)


