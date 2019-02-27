#include "stdafx.h"
#include "unit_tests.h"
#include "hash_map.h"
#include <cassert>
#include <vector>

void test_all() {
	test_add();
	test_remove();
	test_search();
	test_iterator();
}

void test_add() {
	HashMap map;
	std::vector<std::string> lst = { "This", "is", "a", "test", "for", "the", "add", "operation." };

	for (const std::string& x : lst)	// add
		map.add(x);

	for (const std::string& x : lst)	// update
		map.add(x, 200);

	assert(map.get_size() == lst.size());

	try {
		map.add("An", 150);
		map.add("exception", 300);
		map.add("occurs.", 300);
	} catch (HashTableIsFull& htif) {
		std::cout << htif.what() << "\n";
	}
}

void test_remove() {
	std::vector<std::string> lst = { "aaa", "abc", "bca", "cba", "xyz", "xzy", "zyx", "zzz", "qwe", "wqe", "ewq" };
	HashMap map(2 * lst.size());

	for (auto x : lst) map.add(x, 150);
	assert(map.get_size() == lst.size());

	assert(map.remove("abc") == 150);
	assert(map.remove("xyz") == 150);
	assert(map.remove("qwe") == 150);
	assert(map.get_size() == lst.size() - 3);

	//assert(map.search("cba") == 150);
	//assert(map.search("xzy") == 150);
	//assert(map.search("yzx") == -1);

	//debug_print(map);
}

void test_search() {
	std::vector<std::string> lst = { "aaa", "abc", "bca", "cba", "xyz", "xzy", "zyx", "zzz", "qwe", "wqe", "ewq" };

	HashMap map(2 * lst.size());

	for (auto x : lst)
		map.add(x, 100);

	//for (auto x : lst) {
	//	int v = map.search(x);
	//	assert(v == 100);
	//}

	assert(map.search("123") == -1);
	assert(map.search("xxy") == -1);
	assert(map.search("a1b2") == -1);

	map.remove("aaa");
	assert(map.search("aaa") == -1);
}

void test_iterator() {
	std::vector<std::string> lst = { "This", "is", "a", "test", "for", "the", "iterator", "operations." };
	HashMap map(2 * lst.size());

	for (const std::string& x : lst)
		map.add(x);
	
	debug_print(map);

	std::cout << "List of keys: ";
	map.iterator_init();
	while (map.valid()) {
		std::cout << "`" << map.get_current().key << "` ";
		map.next();
	}

	std::cout << "\n";
}