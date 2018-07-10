// Map.cpp : Defines the entry point for the console application.
//
#include <string>

using KeyType = std::string; using ValueType = double;

#ifndef MAP_H
#define MAP_H

const int DEFAULT_MAX_ITEMS = 250;

class Map
{
public:
	Map();         // Create an empty map (i.e., one with no key/value pairs)

	bool empty() const;  // Return true if the map is empty, otherwise false.

	int size() const;    // Return the number of key/value pairs in the map.

	bool insert(const KeyType& key, const ValueType& value);
	// If key is not equal to any key currently in the map, and if the
	// key/value pair can be added to the map, then do so and return true.
	// Otherwise, make no change to the map and return false (indicating
	// that either the key is already in the map, or the map has a fixed
	// capacity and is full).

	bool update(const KeyType& key, const ValueType& value);
	// If key is equal to a key currently in the map, then make that key no
	// longer map to the value it currently maps to, but instead map to
	// the value of the second parameter; return true in this case.
	// Otherwise, make no change to the map and return false.

	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	// If key is equal to a key currently in the map, then make that key no
	// longer map to the value it currently maps to, but instead map to
	// the value of the second parameter; return true in this case.
	// If key is not equal to any key currently in the map and if the
	// key/value pair can be added to the map, then do so and return true.
	// Otherwise, make no change to the map and return false (indicating
	// that the key is not already in the map and the map has a fixed
	// capacity and is full).

	bool erase(const KeyType& key);
	// If key is equal to a key currently in the map, remove the key/value
	// pair with that key from the map and return true.  Otherwise, make
	// no change to the map and return false.

	bool contains(const KeyType& key) const;
	// Return true if key is equal to a key currently in the map, otherwise
	// false.

	bool get(const KeyType& key, ValueType& value) const;
	// If key is equal to a key currently in the map, set value to the
	// value in the map that that key maps to, and return true.  Otherwise,
	// make no change to the value parameter of this function and return
	// false.

	bool get(int i, KeyType& key, ValueType& value) const;
	// If 0 <= i < size(), copy into the key and value parameters the
	// key and value of one of the key/value pairs in the map and return
	// true.  Otherwise, leave the key and value parameters unchanged and
	// return false.  (See below for details about this function.)

	void swap(Map& other);
	// Exchange the contents of this map with the other one.

	~Map();
	//destructor

	Map(const Map &other);
	//copy constructor

	Map &operator=(const Map &other);
	//assignment operator

private:
	struct KeyValuePair {
		KeyValuePair(KeyType a, ValueType b)
		{
			key = a;
			value = b;
			next = nullptr;
			prev = nullptr;
		}
		KeyValuePair()
		{
			next = nullptr;
			prev = nullptr;
		}
		KeyType key;
		ValueType value;
		KeyValuePair *next;
		KeyValuePair *prev;
	};
	KeyValuePair *head;
	int numElements;
};

bool combine(const Map& m1, const Map& m2, Map& result);
// if a key is in m1, m2 or both (and values are the same), add it to result. Return true when finished
// if a key is in both m1 and m2 but the values are different, don't add it to 
// result and continue combining. Then return false
// DO NOT assume result to be empty

void subtract(const Map& m1, const Map& m2, Map& result);
// result must contain all keys that appear in m1 but not m2
// DO NOT assume result to be empty

#endif // !MAP_H