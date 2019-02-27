#pragma once
#include <string>
#include <iostream>
#include <exception>

struct Node {
	std::string key;
	int value;

	Node() : key{}, value{ 0 } {}
	Node(std::string k, int v) : key{ k }, value{ v } {}

	bool is_empty() { return key.empty(); }
};

class HashMap {
private:
	int size;
	int capacity;
	Node* slots;

	int current_position = 0;

public:
	explicit HashMap(int initial_capacity = 10);
	~HashMap();

	void add(std::string key, int value = 0);
	int remove(std::string key);
	int search(std::string key);

	int get_size() { return size; }

	/* Iterator functions */
	void iterator_init() { current_position = capacity - 1; }
	bool valid();
	void next();
	Node get_current();

	friend void debug_print(HashMap &hash_map);

private:
	int hash(std::string key);
	int h(int h, int i);
};

class HashTableIsFull : public std::exception {
public:
	const char *what() const throw () {
		return "Hash table has reached full capacity.";
	}
};