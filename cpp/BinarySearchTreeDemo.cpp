#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include "BinarySearchTree.h"

using BinarySearchTree = tree::BinarySearchTree<int, std::string>;

int main(int argc, char** argv) {
    BinarySearchTree bst;
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
 
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(v.begin(), v.end(), g);

    fmt::print("{}\n\n", fmt::join(v, " "));

    size_t cnt = 0;
    for (auto key : v) {
        bst.insert(key, std::to_string(key));
        std::ofstream os(fmt::format("tree_{}.dot", cnt ++));
        os << bst.visualize() << '\n';
        os.close();
    }

    std::shuffle(v.begin(), v.end(), g);
    fmt::print("{}\n\n", fmt::join(v, " "));

    for (auto key : v) {
        bst.remove(key);
        std::ofstream os(fmt::format("tree_{}.dot", cnt ++));
        os << bst.visualize() << '\n';
        os.close();
    }

    return 0;
}