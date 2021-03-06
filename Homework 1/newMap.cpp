#include "newMap.h"

Map::Map(int n)
{
	map = new KeyValuePair[n];
	numElements = 0;
	maxElements = n;
}

Map::Map()
{
	map = new KeyValuePair[DEFAULT_MAX_ITEMS];
	numElements = 0;
	maxElements = DEFAULT_MAX_ITEMS;
}

bool Map::empty() const
{
	if (numElements == 0)
		return true;

	return false;
}

int Map::size() const
{
	return numElements;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (numElements >= maxElements)
		return false;

	if (!contains(key))
	{
		map[numElements] = KeyValuePair(key, value);
		numElements++;
		return true;
	}
	return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < numElements; i++)
	{
		if (key == map[i].key)
		{
			map[i].value = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (update(key, value))
	{
		return true;
	}
	else
	{
		ValueType temp = value;
		if (insert(key, temp))
		{
			return true;
		}
		return false;
	}
}

bool Map::erase(const KeyType& key)
{
	for (int i = 0; i < numElements; i++)
	{
		if (key == map[i].key)
		{
			for (int j = i; j < numElements - 1; j++)
			{
				map[i].key = map[i + 1].key;
				map[i].value = map[i + 1].value;
			}
			numElements--;
			return true;
		}
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int i = 0; i < numElements; i++)
	{
		if (key == map[i].key)
		{
			value = map[i].value;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < size() && i >= 0)
	{
		key = map[i].key;
		value = map[i].value;
		return true;
	}
	return false;
}

void Map::swap(Map& other)
{
	int larger;
	if (other.maxElements > maxElements)
		larger = other.maxElements;
	else
		larger = maxElements;

	for (int i = 0; i < maxElements; i++)
	{
		KeyValuePair temp = map[i];
		map[i] = other.map[i];
		other.map[i] = temp;
	}

	int temp1 = other.numElements;
	other.numElements = numElements;
	numElements = temp1;

	int temp2 = other.maxElements;
	other.maxElements = maxElements;
	maxElements = temp2;
}

bool Map::contains(const KeyType& key) const
{
	for (int i = 0; i < numElements; i++)
	{
		if (key == map[i].key)
			return true;
	}

	return false;
}

Map::~Map()
{
	delete[] map;
}

Map::Map(const Map &src)
{
	map = new KeyValuePair[src.maxElements];
	maxElements = src.maxElements;
	numElements = src.numElements;

}

Map &Map::operator=(const Map &src)
{
	if (&src == this)
	{
		return(*this);
	}
	delete[] map;
	numElements = src.numElements;
	maxElements = src.maxElements;
	map = new KeyValuePair[maxElements];
	for (int i = 0; i < maxElements; i++)
	{
		map[i] = src.map[i];
	}
	return(*this);
}