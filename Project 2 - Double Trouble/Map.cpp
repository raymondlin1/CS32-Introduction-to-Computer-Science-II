#include "Map.h"

Map::Map()
{
	head = nullptr;
	numElements = 0;
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
	if (size() == 0)	//if no elements in linked list
	{
		KeyValuePair *n = new KeyValuePair(key, value);
		head = n;
		n->next = nullptr;
		n->prev = nullptr;
		numElements++;
		return true;
	}
	else
	{
		KeyValuePair *p;
		p = head;
		while (p != nullptr && p->next != nullptr)	//loop through the list and if the key is already in the list, return false
		{
			if (p != nullptr && key == p->key)
				return false;
			p = p->next;
		}
		if (p != nullptr && key == p->key)
			return false;

		//if key is not in the list, create a new KeyValuePair and add it to end of list
		KeyValuePair *n = new KeyValuePair(key, value);
		p->next = n;
		n->prev = p;
		n->next = nullptr;
		numElements++;
		return true;
	}
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	KeyValuePair *p;
	p = head;
	if (p == nullptr)	//if there are no elements in the linked list
	{
		//create a new KeyValuePair and make it the first element of the list
		KeyValuePair *n = new KeyValuePair(key, value);
		head = n;
		n->next = nullptr;
		n->prev = nullptr;
		numElements++;
		return true;
	}
	else
	{
		//loop through the list
		while (p->next != nullptr)
		{
			//if key is in the list, change its value and return true
			if (p != nullptr && key == p->key)
			{
				p->value = value;
				return true;
			}
			p = p->next;
		}
		//if key is not in list, create a new KeyValuePair and add it to the end of the list
		KeyValuePair *n = new KeyValuePair(key, value);
		p->next = n;
		n->prev = p;
		n->next = nullptr;
		numElements++;
		return true;
	}
}

bool Map::erase(const KeyType& key)
{
	//can't erase if there are no elements to erase
	if (numElements == 0)
	{
		return false;
	}
	//if first element is the one to be erased, set head to the second element and delete the first
	else if (head->key == key)
	{
		KeyValuePair *p = head;
		head = p->next;
		delete p;
		numElements--;
		return true;
	}
	//if element to be erased is not first element, find it
	else
	{
		KeyValuePair *p = head;
		while (p != nullptr)
		{
			//if found, set next pointer to the element after the target element. delete the target
			if (p->next != nullptr && p->next->key == key)
			{
				break;
			}
			p = p->next;
		}

		if (p != nullptr)
		{
			KeyValuePair *toKill = p->next;
			p->next = toKill->next;
			p->next->prev = p;
			delete toKill;
			numElements--;
			return true;
		}
		return false;
	}
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	//loop through the list to find the key
	KeyValuePair *p = head;
	while (p->next != nullptr)
	{
		//if found, update the value
		if (p != nullptr && p->key == key)
		{
			p->value = value;
			return true;
		}
		p = p->next;
	}
	//last element
	if (p != nullptr && p->key == key)
	{
		p->value = value;
		return true;
	}
	return false;
}

bool Map::contains(const KeyType& key) const
{
	//loop through the list to find the target element
	KeyValuePair *p = head;
	while (p->next != nullptr)
	{
		//if found, return true
		if (p != nullptr && p->key == key)
		{
			return true;
		}
		p = p->next;
	}
	if (p != nullptr && p->key == key)
	{
		return true;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	//loop through the list to find the target 
	KeyValuePair *p = head;
	while (p->next != nullptr)
	{
		//if found, change the parameter
		if (p != nullptr && p->key == key)
		{
			value = p->value;
			return true;
		}
		p = p->next;
	}
	if (p != nullptr && p->key == key)
	{
		value = p->value;
		return true;
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	//check to see if i is a valid index
	int index = 0;
	if (i >= 0 && i < size())
	{
		//loop through the list to find the element at index i
		KeyValuePair *p = head;
		while (index < i && p->next != nullptr)
		{
			p = p->next;
			index++;
		}
		//change the parameters after found
		key = p->key;
		value = p->value;
		return true;
	}
	return false;
}

void Map::swap(Map& other)
{
	//swap the two private data members of Map class: KeyValuePair *head and int numElements
	KeyValuePair *temp = head;
	head = other.head;
	other.head = temp;

	int temp2 = numElements;
	numElements = other.numElements;
	other.numElements = temp2;
}

Map::~Map()		//destructor
{
	//loop through the list 
	KeyValuePair* p = head;

	while (p != nullptr)
	{
		//save the pointer to the next element and delete the current element
		KeyValuePair *temp = p->next;
		delete p;
		numElements--;
		p = temp;
	}
	head = nullptr;
}

Map::Map(const Map &other)
{
	numElements = other.numElements;
	//if the other map is empty, head is a nullptr
	if (other.size() == 0)
	{
		head = nullptr;
	}
	//if not empty, head points to new KeyValuePair
	else
	{
		head = new KeyValuePair(other.head->key, other.head->value);
		KeyValuePair *p = head;
		KeyValuePair *otherP = other.head;
		//loop through other map and duplicate each node
		while (otherP->next != nullptr)
		{
			p->next = new KeyValuePair(otherP->next->key, otherP->next->value);
			p->next->prev = p;
			p = p->next;
			otherP = otherP->next;
		}
	}
	
}

Map &Map::operator=(const Map &other)
{
	if (&other == this)
		return(*this);

	this->~Map();
	numElements = other.numElements;
	//if the other map is empty, head is a nullptr
	if (other.size() == 0 && other.head == nullptr)
	{
		head = nullptr;
	}
	//if not empty, head points to new KeyValuePair
	else
	{
		head = new KeyValuePair(other.head->key, other.head->value);
		KeyValuePair *p = head;
		KeyValuePair *otherP = other.head->next;
		//loop through other map and duplicate each node
		while (otherP != nullptr)
		{
			p->next = new KeyValuePair(otherP->key, otherP->value);
			p->next->prev = p;
			p = p->next;
			otherP = otherP->next;
		}
	}
	return(*this);
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
	//make a temp Map
	Map tempRes = result;

	//destruct result
	tempRes.~Map();
	//if m1 is empty, result is m2
	if (m1.size() == 0)
	{
		//if m2 is also empty, result doesn't change
		if (m2.size() == 0)
		{
			tempRes.swap(result);
			return true;
		}
		tempRes = m2;
		tempRes.swap(result);
		return true;
	}
	//if m2 is empty, result is m1
	else if (m2.size() == 0)
	{
		tempRes = m1;
		tempRes.swap(result);
		return true;
	}
	//loop through both linked lists
	else
	{
		bool returnVal = true;
		//loop through the first map and add all elements to result
		for (int i = 0; i < m1.size(); i++)
		{
			KeyType k1;
			ValueType v1;
			m1.get(i, k1, v1);
			tempRes.insert(k1, v1);
		}
		for (int j = 0; j < m2.size(); j++)
		{
			KeyType k2;
			ValueType v2;
			m2.get(j, k2, v2);
			//check if key is already in result
			if (tempRes.contains(k2))
			{
				//if key is already in result and the corresponding key in m2 has a different value, remove it from result and set returnval to false
				ValueType temp;
				tempRes.get(k2, temp);
				if (temp != v2)
				{
					tempRes.erase(k2);
					returnVal = false;
				}
			}
			//if result doesn't contain the key, add it
			else
			{
				tempRes.insert(k2, v2);
			}
		}
		tempRes.swap(result);
		return returnVal;
	}
	
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
	//create a temp Map and assign m1 to it
	Map temp = m1;

	KeyType k;
	ValueType v;
	//loop through m2, and if found any keys that also appear in m2, delete them
	for (int i = 0; i < m2.size(); i++)
	{
		m2.get(i, k, v);
		if (temp.contains(k))
			temp.erase(k);
	}
	temp.swap(result);
}