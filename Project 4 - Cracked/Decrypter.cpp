#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class DecrypterImpl
{
public:
	DecrypterImpl();
	~DecrypterImpl();
	bool load(string filename);
	vector<string> crack(const string& ciphertext);
private:
	void crackHelper(string ciphertextmessage, vector<string>& output);
	WordList* m_wordList;
	Translator* m_translator;
	Tokenizer* m_tokenizer;
};

DecrypterImpl::DecrypterImpl()
{
	m_wordList = new WordList();
	m_translator = new Translator();
	m_tokenizer = new Tokenizer(" ,;:.!()[]{}-\"#$%^&");
}

DecrypterImpl::~DecrypterImpl()
{
	delete m_wordList;
	delete m_translator;
	delete m_tokenizer;
}

bool DecrypterImpl::load(string filename)
{
	return m_wordList->loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	vector<string> possibleTranslations;
	crackHelper(ciphertext, possibleTranslations);
	return possibleTranslations;
}

void DecrypterImpl::crackHelper(string ciphertextmessage, vector<string>& output)
{
	vector<string> m_cipherWords = m_tokenizer->tokenize(ciphertextmessage);

	//2. find the word with the most unknown characters													
	vector<string>::iterator it3 = m_cipherWords.begin();
	string longestWord = "";
	int numMostUnknown = 0;
	while (it3 != m_cipherWords.end())
	{
		string temp = m_translator->getTranslation(*it3);
		int numUnknown = 0;
		//loop through the characters in each word
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] == '?')
				numUnknown++;
		}
		if (numUnknown > numMostUnknown)
		{
			longestWord = (*it3);
			numMostUnknown = numUnknown;
		}
			
		it3++;
	}


	//3. get the translation based on the current mapping table
	string currTranslationOfWord = m_translator->getTranslation(longestWord);

	//4. return the vector of possible words that fit the ciphertext
	vector<string> candidates = m_wordList->findCandidates(longestWord, currTranslationOfWord);

	//5. if vector is empty, throw away the current mapping table
	if (candidates.size() == 0)
	{
		m_translator->popMapping();
		return;
	}

	//6. loop through the candidates
	vector<string>::iterator it = candidates.begin();
	while (it != candidates.end())
	{
		string candidateWord = *it;
		//tru if should push a new mapping, false if not
		bool pushpop = true;
		//loop through the characters of the chosen word
		for (int i = 0; i < longestWord.size(); i++)
		{
			//if the letter in current translation is not the same as that in candidateword AND translation is not a ?
			if (tolower(currTranslationOfWord[i]) != tolower(candidateWord[i]) && currTranslationOfWord[i] != '?')
			{
				m_translator->popMapping();
				pushpop = false;
				break;
			}
		}

		if (pushpop)
		{
			bool b = m_translator->pushMapping(longestWord, (*it));
			if(!b)
			{
				it++;
				continue;
			}
		}
		else
		{
			it++;
			continue;
		}


		//translate entire cipherword
		vector<string> tempcipherwords;
		vector<string>::iterator it2 = m_cipherWords.begin();
		while (it2 != m_cipherWords.end())
		{
			//cout << m_translator->getTranslation(*it2) << endl;
			tempcipherwords.push_back(m_translator->getTranslation((*it2)));
			it2++;
		}

		//check each newly translated cipherword
		bool notComplete = false;
		bool wrongMapping = false;
		it2 = tempcipherwords.begin();
		while (it2 != tempcipherwords.end())
		{
			bool hasQMark = false;
			for (int i = 0; i < (*it2).size(); i++)
			{
				if ((*it2)[i] == '?')
				{
					hasQMark = true;
					notComplete = true;
					break;
				}
			}

			if (!hasQMark)
			{
				//search wordlist to see if it contains the word
				if (!m_wordList->contains((*it2)))
				{
					//if not, mapping must be wrong
					m_translator->popMapping();
					wrongMapping = true;
					break;
				}
			}
			it2++;
		}
		
		//make a new ciphertext string
		
		if (!wrongMapping)
		{
			string newCipherText = m_translator->getTranslation(ciphertextmessage);
			if (notComplete)
			{
				crackHelper(ciphertextmessage, output);
			}
			else
			{
				output.push_back(newCipherText);
				it++;
				continue;
			}
		}
		
		
		it++;
	}

	m_translator->popMapping();
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
