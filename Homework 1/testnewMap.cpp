#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

// To test a Map from string to double, leave the following line commented out;
// to test a Map from int to string, remove the "//".
//#define INT_TO_STRING

#ifdef INT_TO_STRING

const KeyType DUMMY_KEY = 9876543;
const ValueType DUMMY_VALUE = "Ouch";
const KeyType NO_SUCH_KEY = 42;
const KeyType KEY1 = 123456789;
const ValueType VALUE1 = "Wow!";
const ValueType VALUE2 = "wow1";
const ValueType VALUE3 = "wow2";
const ValueType VALUE4 = "wow3";
const KeyType KEY2 = 111;
const ValueType VALUE5 = "wow4";
const KeyType KEY3 = 222;
const ValueType NULLVALUE = "";

#else // assume string to double

const KeyType DUMMY_KEY = "hello";
const ValueType DUMMY_VALUE = -1234.5;
const KeyType NO_SUCH_KEY = "abc";
const KeyType KEY1 = "xyz";
const ValueType VALUE1 = 9876.5;
const ValueType VALUE2 = 123.45;
const ValueType VALUE3 = 321;
const ValueType VALUE4 = 123;
const KeyType KEY2 = "lol";
const ValueType VALUE5 = 415;
const KeyType KEY3 = "def";
const ValueType NULLVALUE = 0;

#endif

//To test all functions of Map.cpp
/*int main()
{
Map m;  // maps strings to doubles
assert(m.empty());
ValueType v = DUMMY_VALUE;
assert(!m.get(NO_SUCH_KEY, v) && v == DUMMY_VALUE); // v unchanged by get failure
m.insert(KEY1, VALUE1);
//m contains KEY1: VALUE1
assert(!m.insert(KEY1, VALUE4));
assert(m.size() == 1 && !m.empty());
KeyType k = DUMMY_KEY;
assert(m.get(0, k, v) && k == KEY1 &&  v == VALUE1);
ValueType q = NULLVALUE;
assert(m.update(KEY1, VALUE2) && m.get(KEY1, q) && q == VALUE2);
//m contains KEY1: VALUE2
assert(!m.update(NO_SUCH_KEY, VALUE2));
ValueType c = NULLVALUE;
assert(m.insertOrUpdate(NO_SUCH_KEY, VALUE3) && m.get(NO_SUCH_KEY, c) && c == VALUE3);
//m contains KEY1:VALUE2, NO_SUCH_KEY:VALUE3
assert(m.insertOrUpdate(NO_SUCH_KEY, VALUE4) && m.get(NO_SUCH_KEY, c) && c == VALUE4);
//m contains KEY1:VALUE2, NO_SUCH_KEY:VALUE4

Map m2;
m2.insert(KEY2, VALUE5);
//m2 contains KEY2:VALUE5
m.swap(m2);
//m contains KEY2:VALUE5
//m2 contains KEY1:VALUE2, NO_SUCH_KEY:VALUE4
assert(m2.contains(KEY1) && m2.contains(NO_SUCH_KEY) && m.size() == 1);

assert(m2.contains(NO_SUCH_KEY) && !m.contains(KEY3));
assert(m2.erase(KEY1) && m2.erase(NO_SUCH_KEY));
//m2 contains
assert(!m2.erase(KEY1));
assert(!m2.get(10, k, c) && k == KEY1 && c == VALUE4);

Map m3 = m;
assert(m.contains(KEY2) && m.size() == 1);
m3 = m2;
assert(m3.size() == 0);
cerr << "Passed all tests" << endl;
}*/