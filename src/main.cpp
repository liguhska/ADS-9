// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

void printPermutations(const std::vector<char>& elements) {
	PMTree tree(elements);
	auto perms = getAllPerms(tree);

	std::cout << "All permutations for [";
	for (char c : elements) {
		std::cout << c << " ";
	}
	std::cout << "] (" << perms.size() << " total):\n";

	for (const auto& perm : perms) {
		for (char c : perm) {
			std::cout << c;
		}
		std::cout << " ";
	}
	std::cout << "\n\n";
}

void runExperiment(int max_n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	for (int n = 1; n <= max_n; ++n)
	{
		std::vector<char> elements;
		for (int i = 0; i < n; ++i)
		{
			elements.push_back('1' + i);
		}

		auto start = std::chrono::high_resolution_clock::now();
		PMTree tree(elements);
		auto end = std::chrono::high_resolution_clock::now();
		auto build_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		start = std::chrono::high_resolution_clock::now();
		auto all_perms = getAllPerms(tree);
		end = std::chrono::high_resolution_clock::now();
		auto all_perms_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		const int num_tests = 10;
		std::vector<int> test_nums(num_tests);
		std::uniform_int_distribution<> distr(1, all_perms.size());
		for (int i = 0; i < num_tests; ++i) {
			test_nums[i] = distr(gen);
		}

		start = std::chrono::high_resolution_clock::now();
		for (int num : test_nums) {
			auto perm = getPerm1(tree, num);
		}
		end = std::chrono::high_resolution_clock::now();
		auto get_perm1_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		start = std::chrono::high_resolution_clock::now();
		for (int num : test_nums) {
			auto perm = getPerm2(tree, num);
		}

		end = std::chrono::high_resolution_clock::now();
		auto get_perm2_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		std::cout << n << "\t" << all_perms.size() << "\t\t" << all_perms_time << "\t\t\t" << get_perm1_time << "\t\t" << get_perm2_time << "\n";
	}
}

int main() {
	std::vector<char> elements = { '1', '3', '5', '7' };
	PMTree tree(elements);

	auto perms = getAllPerms(tree);
	for (int i = 0; i < 5 && i < perms.size(); ++i) {
		for (char c : perms[i]) {
			std::cout << c;
		}
		std::cout << " ";
	}
	std::cout << "\n\n";

	std::cout << "permutation 1: ";
	auto perm1 = getPerm1(tree, 1);
	for (char c : perm1) std::cout << c;
	std::cout << "\n";

	std::cout << "permutation 2: ";
	auto perm2 = getPerm2(tree, 2);
	for (char c : perm2) std::cout << c;
	std::cout << "\n";

	runExperiment(8);
	return 0;
}
