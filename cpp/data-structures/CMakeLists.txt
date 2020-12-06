cmake_minimum_required(VERSION 3.0)

project(tree)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

add_executable(bst_demo BinarySearchTreeDemo.cpp)
target_link_libraries(bst_demo fmt)

enable_testing()

find_package(GTest REQUIRED)

add_executable(bst_test BinarySearchTreeTest.cpp BinaryTree.h BinarySearchTree.h)
target_link_libraries(bst_test GTest::GTest GTest::Main)
add_test(NAME bst_test COMMAND bst_test)