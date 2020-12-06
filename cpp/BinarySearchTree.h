#pragma once

#include "BinaryTree.h"

namespace tree {
template <typename Key, typename Value>
class BinarySearchTree : public BinaryTree<Key, Value> {
protected:
  using Node = typename BinaryTree<Key, Value>::Node;

public:
  BinarySearchTree() : BinaryTree<Key, Value>() {};
  BinarySearchTree(const Key &key, const Value &value)
      : BinaryTree<Key, Value>(key, value) {}

  void insert(const Key &key, const Value &value,
              bool overwrite_if_exists = true) override {
    if (this->root)
      insert(this->root, key, value, overwrite_if_exists);
    else {
      this->root = new Node(key, value);
    }
  }

  std::optional<Value> find(const Key &key) const override {
    return (this->root ? find(this->root, key) : std::nullopt);
  }

  bool remove(const Key &key) override {
    return (this->root ? remove(this->root, key) : false);
  }

protected:
  bool remove(Node *&subtree, const Key &key) {
    if (subtree->key == key) {
      auto prev = subtree;
      if (auto ptr = subtree->left) {
        while (ptr->right) {
          prev = ptr;
          ptr = ptr->right;
        }
        subtree->key = ptr->key;
        subtree->value = ptr->value;
        if (prev == subtree) {
            prev->left = ptr->left;
        } else  {
            prev->right = ptr->left;
        }
        delete ptr;
      } else if (auto ptr = subtree->right) {
        while (ptr->left) {
          prev = ptr;
          ptr = ptr->left;
        }
        subtree->key = ptr->key;
        subtree->value = ptr->value;
        if (prev == subtree) {
            prev->right = ptr->right;
        } else {
            prev->left = ptr->right;
        }
        delete ptr;
      } else {
        delete subtree;
        subtree = nullptr;
      }
      return true;
    } else if (key < subtree->key) {
      return (subtree->left ? remove(subtree->left, key) : false);
    } else {
      return (subtree->right ? remove(subtree->right, key) : false);
    }
  }
  std::optional<Value> find(Node *subtree, const Key &key) const {
    if (subtree->key == key) {
      return subtree->value;
    }
    if (key < subtree->key) {
      return (subtree->left ? find(subtree->left, key) : std::nullopt);
    } else {
      return (subtree->right ? find(subtree->right, key) : std::nullopt);
    }
  }
  void insert(Node *subtree, const Key &key, const Value &value,
              bool overwrite_if_exists = true) {
    if (key < subtree->key) {
      if (subtree->left) {
        insert(subtree->left, key, value, overwrite_if_exists);
      } else {
        subtree->left = new Node(key, value);
      }
    } else if (key == subtree->key) {
      if (overwrite_if_exists) {
        subtree->value = value;
      }
    } else {
      if (subtree->right) {
        insert(subtree->right, key, value, overwrite_if_exists);
      } else {
        subtree->right = new Node(key, value);
      }
    }
  }
};
} // namespace tree