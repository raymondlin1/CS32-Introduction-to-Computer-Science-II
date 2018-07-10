// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
///*
template<typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(double maxLoadFactor = 0.5);
	~MyHash();
	void reset();
	void associate(const KeyType& key, const ValueType& value);
	int getNumItems() const;
	double getLoadFactor() const;

	// for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	// for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
	}

	// C++11 syntax for preventing copying and assignment
	MyHash(const MyHash&) = delete;
	MyHash& operator=(const MyHash&) = delete;

private:
	struct Node
	{
		ValueType value;
		KeyType key;
		Node* next;
	};
	Node** m_buckets;
	double m_maxLoadFactor;
	int m_numItems;
	int m_numBuckets;
};

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
{
	m_numBuckets = 100;
	m_numItems = 0;
	m_buckets = new Node*[m_numBuckets];

	//make all pointers point to null
	for (int i = 0; i < m_numBuckets; i++)
	{
		m_buckets[i] = nullptr;
	}

	//set the load factor
	if (maxLoadFactor <= 0)
		m_maxLoadFactor = 0.5;
	else if (maxLoadFactor > 2.0)
		m_maxLoadFactor = 2.0;
	else
		m_maxLoadFactor = maxLoadFactor;

}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
	//loop through all the buckets
	for (int i = 0; i < m_numBuckets; i++)
	{
		//if it's not a nullptr, delete it
		if (m_buckets[i] != nullptr)
		{
			Node *p;
			p = m_buckets[i];
			while (p != nullptr)
			{
				Node *n = p->next;
				delete p;
				p = n;
			}
		}
	}
	delete[] m_buckets;
	m_buckets = nullptr;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
	if (m_buckets == nullptr)
		return;

	//loop through all the buckets
	for (int i = 0; i < m_numBuckets; i++)
	{
		//if it's not a nullptr, delete it
		if (m_buckets[i] != nullptr)
		{
			Node *p;
			p = m_buckets[i];
			while (p != nullptr)
			{
				Node *n = p->next;
				delete p;
				p = n;
			}
		}
	}
	delete[] m_buckets;

	m_numBuckets = 100;
	m_buckets = new Node*[m_numBuckets];

	for (int i = 0; i < m_numBuckets; i++)
	{
		m_buckets[i] = nullptr;
	}
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType &key, const ValueType &value)
{
	unsigned int hasher(const KeyType& k);
	ValueType* v = find(key);
	if (v != nullptr)
	{
		*v = value;
	}
	else
	{
		m_numItems++;
		if (getLoadFactor() > m_maxLoadFactor)
		{
			int newNumBuckets = 2 * m_numBuckets;

			//new array with all nullptrs
			Node** temp = new Node*[newNumBuckets];
			for (int i = 0; i < newNumBuckets; i++)
			{
				temp[i] = nullptr;
			}

			//transfer all items from old array to new
			for (int j = 0; j < m_numBuckets; j++)
			{
				if (m_buckets[j] != nullptr)
				{
					int bucket = hasher(m_buckets[j]->key) % newNumBuckets;

					temp[bucket] = new Node;
					temp[bucket]->value = m_buckets[j]->value;
					temp[bucket]->key = m_buckets[j]->key;
					temp[bucket]->next = nullptr;

					delete m_buckets[j];
				}
			}
			delete [] m_buckets;
			m_buckets = temp;
			m_numBuckets = newNumBuckets;
		}

		//get the bucket that key hashes to
		//unsigned int ::hash(const KeyType& k);
		
		unsigned int bucket = hasher(key) % m_numBuckets;
		Node* n = new Node;
		n->value = value;
		n->key = key;
		n->next = nullptr;
		if (m_buckets[bucket] == nullptr)
		{
			m_buckets[bucket] = n;
		}
		else
		{
			Node* p = m_buckets[bucket];
			n->next = p;
			m_buckets[bucket] = n;
		}
	}
	
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
	double load = static_cast<double>(getNumItems())/static_cast<double>(m_numBuckets);
	return load;
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
	return m_numItems;
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
	//find the bucket with the matching key
	unsigned int hasher(const KeyType& k);
	unsigned int bucket = hasher(key) % m_numBuckets;

	Node* p = m_buckets[bucket];
	while (p != nullptr)
	{
		if (p->key == key)
		{
			ValueType* v = &(p->value);
			if (v != nullptr)
				return v;
		}
		p = p->next;
	}
	return nullptr;
}
//*/
/*
#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED

#include <unordered_map>  // YOU MUST NOT USE THIS HEADER IN CODE YOU TURN IN
#include <algorithm>

// In accordance with the spec, YOU MUST NOT TURN IN THIS CLASS TEMPLATE,
// since you are not allowed to use any STL containers, and this
// implementation uses std::unordered_map.

// This code is deliberately obfuscated.

// If you can not get your own MyHash class template working, you may use
// this one during development in order to let you proceed with implementing
// the other classes for this project; you can then go back to working on
// fixing your own MyHash class template.

template<typename KeyType, typename ValueType>
class MyHash
{
public:
	MyHash(const MyHash&) = delete;
	MyHash& operator=(const MyHash&) = delete;
	using O = KeyType; using maxloadfactor = float; using O10 = int; void reset() {
		maxloadfactor max_1oad_factor = l01.max_load_factor(); l01.clear(); l01.
			max_load_factor(max_1oad_factor); l01.rehash(doub1e + doub1e);
	}using String =
		double; using l0 = ValueType; using l1O = O10 const; MyHash(String d0uble = doub1e / 10) :
		l01(doub1e + doub1e) {
		l01.max_load_factor(std::min<maxloadfactor>(doub1e / 5 / 5,
			std::max<maxloadfactor>((double)doub1e / (doub1e + doub1e), d0uble)));
	}using l10 = O
		const; using Const = MyHash<O, l0>; String getLoadFactor()const {
		return l01.
			load_factor();
	}using ll0 = l0 const; O10 getNumItems()const {
		return l01.size(
		);
	}using l00 = Const const; void associate(l10&Using, ll0&first) {
		l01[Using] =
			first;
	}using l1 = std::unordered_map<O, l0>; ll0*find(l10&l11)const {
		auto first(l01.
			find(l11)); return(first != l01.end() ? &first->second : 0);
	}l0*find(l10&l01) {
		return(
			l0*)(*(l00*)(this)).find(l01);
	}private:static l1O doub1e{ 50 }; l1 l01;
};

#endif // MYHASH_INCLUDED
*/