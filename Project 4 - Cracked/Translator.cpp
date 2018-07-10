#include "provided.h"
#include <string>
#include <iostream>
#include <cctype>
#include <unordered_map>
using namespace std;

class TranslatorImpl
{
public:
	TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
	vector<unordered_map<char, char>> m_charMaps; 
	unordered_map<char, char> m_currMap;
	int m_top = 0;
};

TranslatorImpl::TranslatorImpl()
{
	unordered_map<char, char> temp;
	for (int j = 0; j < 26; j++)
	{
		temp.insert(pair<char, char>(65 + j, '?'));
	}
	
	m_charMaps.push_back(temp);
	m_currMap = m_charMaps[m_top];
	m_top++;
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	if (ciphertext.size() != plaintext.size())
		return false;

	//set up the temp map
	unordered_map<char, char> temp;
	temp = m_charMaps[m_top - 1];

	//associate the values
	for (int i = 0; i < ciphertext.size(); i++)
	{
		if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
			return false;
		if (temp[toupper(ciphertext[i])] != '?' && temp[toupper(ciphertext[i])] != toupper(plaintext[i]))
			return false;
		else if(temp[toupper(ciphertext[i])] == '?' || temp[toupper(ciphertext[i])] == toupper(plaintext[i]))
			temp[toupper(ciphertext[i])] = toupper(plaintext[i]);
	}
	
	//if values are repeated, wrong mapping
	for (char c = 65; c < 91; c++)
	{
		char plaintextLetter1 = temp[c];
		for (char j = c; j < 91; j++)
		{
			char plaintextLetter2 = temp[j];
			if (plaintextLetter1 == plaintextLetter2 && c != j && plaintextLetter1 != '?' && plaintextLetter2 != '?')
			{
				//value is repeated
				return false;
			}
		}
	}
	

	m_charMaps.push_back(temp);
	m_currMap = m_charMaps.back();
	m_top++;
    return true; 
}

bool TranslatorImpl::popMapping()
{
	if (m_charMaps.size() <= 1)
		return false;
	else
	{
		m_charMaps.pop_back();
		m_top--;
		m_currMap = m_charMaps.back();
		//test: print out values of latest map
		/*for (char c = 'A'; c <= 'Z'; c++)
		{
			cout << c << " " << m_currMap[c] << endl;
		}
		*/
		return true;
	}
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	
	string translation = "";
	for (int i = 0; i < ciphertext.size(); i++)
	{
		if (isalpha(ciphertext[i]))
		{
			char cipher = toupper(ciphertext[i]);
			unordered_map<char, char>::const_iterator it = m_currMap.find(cipher);
			//cout << get<1>(*it) << endl;
			if (get<1>(*it) == '?')
				translation += "?";
			else
			{
				if (isupper(ciphertext[i]))
					translation += get<1>(*it);
				else
					translation += tolower(get<1>(*it));
			}
		}
		else
		{
			translation += ciphertext[i];
		}
	}
    return translation; 
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
