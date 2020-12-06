#include <gtest/gtest.h>
#include <string>

#include "BinarySearchTree.h"

using BinarySearchTree = tree::BinarySearchTree<int, std::string>;

TEST(BinarySearchTest, ConstructorWorks) {
    BinarySearchTree bst;
    BinarySearchTree bst2(100, "root");
}

TEST(BinarySearchTest, InsertWorks) {
    BinarySearchTree bst;
    bst.insert(1, "1");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}