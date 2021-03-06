#include "stdafx.h"
#include "unit_tests.h"
#include "hash_map.h"
#include <iostream>
#include <fstream>
#define TESTING

void parse_file(HashMap&);
void query_loop(HashMap&);

int main()
{
#ifdef TESTING
	test_all();
#endif

	//HashMap map(2 * 1000);
	//parse_file(map);
	//query_loop(map);

	system("pause");
	return 0;
}

void parse_file(HashMap& map) {
	std::ifstream f;
	f.open("bulk.txt");
	if (!f.is_open()) {
		std::cerr << "Could not open file.\n";
		return;
	}
	std::string word{};
	while (f >> word) {
		int current_count = map.search(word);
		if (current_count != -1) {
			map.add(word, current_count + 1);
			continue;
		}
		map.add(word, 1);
	}
}

void query_loop(HashMap& map) {
	for (;;) {
		std::string search_term{};
		std::cout << "Search for:";
		std::cin >> search_term;

		if (search_term == "exit")
			return;

		if (search_term.empty()) {
			std::cout << "Search term is empty.\n";
			continue;
		}
		int frequency = map.search(search_term);
		if (frequency == -1) {
			std::cout << "This term has not been found.\n";
			continue;
		}
		std::cout << "`" << search_term << "` appears " << frequency << " times.\n";
	}
}
