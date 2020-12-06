#pragma once

#include <fmt/format.h>

#include <optional>
#include <string>
#include <vector>

// TODO: add augment field??
namespace tree {

template <typename Key, typename Value>
class BinaryTree {
 protected:
  struct Node {
    Key key;
    Value value;
    Node* left;
    Node* right;
    Node() = default;
    Node(const Key& key, const Value& value)
        : Node(key, value, nullptr, nullptr) {}
    Node(const Key& key, const Value& value, Node* left, Node* right)
        : key(key), value(value), left(left), right(right) {}
  };

 public:
  BinaryTree() : root(nullptr){};
  BinaryTree(const Key& key, const Value& value) : root(new Node(key, value)) {}

  virtual ~BinaryTree() {
    if (root) destory(root);
  }

  virtual void insert(const Key& key, const Value& value,
                      bool overwrite_if_exists = true) = 0;
  virtual bool remove(const Key& key) = 0;
  virtual std::optional<Value> find(const Key& key) const = 0;

  virtual std::string visualize() const {
    if (!root) return "";
    std::vector<std::string> nodes, edges;
    size_t count = 0;
    visualize(root, count, nodes, edges);
    return fmt::format("{0}\n{1}\n{2}\n{3}{4}{5}\n", "digraph g {",
                       "node [shape = record,height=.1];",
                       fmt::join(nodes, "\n"), (edges.empty() ? "" : "\n\n"),
                       fmt::join(edges, "\n"), "}");
  }

 private:
  void visualize(Node* subtree, size_t& count, std::vector<std::string>& nodes,
                 std::vector<std::string>& edges) const {
    auto countp = count;
    nodes.push_back(fmt::format(
        "node{countp}[label = \"<f0> |<f1> {key} : {value}|<f2> \"]",
        fmt::arg("countp", countp), fmt::arg("key", subtree->key),
        fmt::arg("value", subtree->value)));
    if (subtree->left) {
      edges.push_back(fmt::format(
          "\"node{countp}\":f0 -> \"node{countlc}\":f1;",
          fmt::arg("countp", countp), fmt::arg("countlc", ++count)));
      visualize(subtree->left, count, nodes, edges);
    }
    if (subtree->right) {
      edges.push_back(fmt::format(
          "\"node{countp}\":f2 -> \"node{countrc}\":f1;",
          fmt::arg("countp", countp), fmt::arg("countrc", ++count)));
      visualize(subtree->right, count, nodes, edges);
    }
  }

 protected:
  void destory(Node*& subtree) {
    if (subtree->left) {
      destory(subtree->left);
      subtree->left = nullptr;
    }
    if (subtree->right) {
      destory(subtree->right);
      subtree->right = nullptr;
    }
    delete subtree;
    subtree = nullptr;
  }
  Node* root;
};
}  // namespace tree