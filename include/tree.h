// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>

class PMTree {
 public:
  struct node {
    char value;
    std::vector<std::shared_ptr<node>> children;
    explicit node(char val) : value(val) {}
  };

  explicit PMTree(const std::vector<char>& elements);
  ~PMTree() = default;

  std::shared_ptr<node> getRoot() const { return root; }
  size_t getTotalPermutations() const { return total_permutations; }

 private:
  std::shared_ptr<node> root;
  size_t total_permutations;

  void buildTree(std::shared_ptr<node> parent,
const std::vector<char>& remaining);
  size_t factorial(size_t n) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
