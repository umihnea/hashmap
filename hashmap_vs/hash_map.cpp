#include "stdafx.h"
#include "hash_map.h"

HashMap::HashMap(int initial_capacity) {
	capacity = initial_capacity;
	slots = new Node[this->capacity];
	size = 0;
}

HashMap::~HashMap() {
	delete[] slots;
}

void HashMap::add(std::string key, int value) {
	if (size == capacity)
		throw HashTableIsFull();

	int hash_value = hash(key);
	int pos = h(hash_value, 0);
	int i = 0;

	for (;!slots[pos].is_empty(); pos = h(hash_value, i++)) {
		if (slots[pos].key == key) {
			slots[pos].value = value;
			return;
		}
	}
	slots[pos].key = key;
	slots[pos].value = value;
	size++;
}

int HashMap::remove(std::string key) {

	int saved = -1;

	int hash_value = hash(key);
	int pos = h(hash_value, 0);
	int i = 0;

	while (slots[pos].key != key) pos = h(hash_value, i++);

	saved = slots[pos].value;
	slots[pos].key.clear();
	slots[pos].value = 0;

	// re-hash all keys in the same cluster
	pos = h(hash_value, i++);
	while (!slots[pos].is_empty()) {
		std::string k{ slots[pos].key };
		int v = slots[pos].value;

		slots[pos].key.clear();
		slots[pos].value = 0;
		size--;

		add(k, v);

		pos = h(hash_value, i++);
	}

	size--;
	return saved;
}

int HashMap::search(std::string key)
{
	int counter = 0;

	int hash_value = hash(key);
	int pos = 0;
	int i = 0;

	//std::cout << "searching for " << key << " with hash " << hash(key) << "\n";

	for (int i = 0, pos = h(hash(key), 0); !slots[pos].is_empty() && counter < 2*capacity; pos = h(hash(key), ++i), counter++) {
		//std::cout << "computed position pos=" << pos << " where key=" << slots[pos].key << "\n";
		if (slots[pos].key == key) {
			//std::cout << "found " << key << " at "<< pos <<"\n";
			return slots[pos].value;
		}
	}
	//std::cout << "could not find.\n";
	return -1;
}

/* Iterator functions */

bool HashMap::valid() {
	return (current_position >= 0 && current_position < capacity);
}

void HashMap::next() {
	int next_position = current_position - 1;

	while (0 <= next_position && slots[next_position].is_empty())
		next_position--;

	current_position = next_position;
}

Node HashMap::get_current() {
	std::string k = slots[current_position].key;
	int v = slots[current_position].value;
	return Node(k, v);
}

/* Others */

int HashMap::hash(std::string key = "") {
	if (key.empty()) return 0;
	int hash_value = 0;
	for (const char &x : key)
		hash_value += (int)(x);
	return hash_value % capacity;
}

int HashMap::h(int hash_value, int i) {
	return (hash_value + 13*i + 17*i*i) % capacity;
}

void debug_print(HashMap &hash_map) {
	std::cout << "{";
	for (int i = 0; i < hash_map.capacity; i++) {
		std::cout << "(`" << hash_map.slots[i].key << "`: " << hash_map.slots[i].value << ")";
		if (i < hash_map.capacity - 1) std::cout << ", ";
	}
	std::cout << "}\n";
}

