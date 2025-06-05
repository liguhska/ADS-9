// Copyright 2022 NNTU-CS

#include <algorithm>
#include <stdexcept>
#include  "tree.h"

size_t PMTree::factorial(size_t n) const {
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

PMTree::PMTree(const std::vector<char>& elements) {
	if (elements.empty()) {
		root = nullptr;
		total_permutations = 0;
		return;
	}

	total_permutations = factorial(elements.size());

	root = std::make_shared<node>('\0');
	buildTree(root, elements);
}

void PMTree::buildTree(std::shared_ptr<node> parent, const std::vector<char>& remaining) {
	if (remaining.empty()) {
		return;
	}

	std::vector<char> sorted_remaining = remaining;
	std::sort(sorted_remaining.begin(), sorted_remaining.end());

	for (char elem : sorted_remaining) {
		auto child = std::make_shared<node>(elem);
		parent->children.push_back(child);

		std::vector<char> new_remaining;
		for (char e : sorted_remaining) {
			if (e != elem) {
				new_remaining.push_back(e);
			}
		}

		buildTree(child, new_remaining);
	}
}

void collectPerms(std::shared_ptr<PMTree::node> root, std::vector<char>& current, std::vector<std::vector<char>>& result) {
	if (root->value != '\0') {
		current.push_back(root->value);
	}

	if (root->children.empty()) {
		result.push_back(current);
	} else {
		for (const auto& child : root->children) {
			collectPerms(child, current, result);
		}
	}

	if (root->value != '\0') {
		current.pop_back();
	}
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
	std::vector<std::vector<char>> result;
	if (!tree.getRoot()) {
		return result;
	}

	std::vector<char> current;
	collectPerms(tree.getRoot(), current, result);
	return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
	if (num < 1 || static_cast<size_t>(num) > tree.getTotalPermutations()) {
		return {};
	}

	auto all_perms = getAllPerms(tree);
	return all_perms[num - 1];
}

bool findPermByNum(std::shared_ptr<PMTree::node> root, int& remaining, std::vector<char>& result, int target_num) {
	if (root->value != '\0') {
		result.push_back(root->value);
	}

	if (root->children.empty()) {
		remaining++;
		if (remaining == target_num) {
			return true;
		}
	} else {
		for (const auto& child : root->children) {
			if (findPermByNum(child, remaining, result, target_num)) {
				return true;
			}
		}
	}

	if (root->value != '\0') {
		result.pop_back();
	}
	return false;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
	if (num < 1 || static_cast<size_t>(num) > tree.getTotalPermutations() || !tree.getRoot()) {
		return {};
	}

	std::vector<char> result;
	int counter = 0;
	findPermByNum(tree.getRoot(), counter, result, num);
	return result;
}
