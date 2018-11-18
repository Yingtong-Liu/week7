#include <fstream>
#include <iostream>
#include <exception>
#include <map>
#include <set>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <functional>

extern "C" {
using namespace std;
void Frequencies(vector<string> words, vector<pair <string, int> > &word_freqs) {
    map<string, int> word_freqs_helper;
    for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
        ++word_freqs_helper[*it];
    }
    
    for (map<string, int>::iterator it = word_freqs_helper.begin(); it != word_freqs_helper.end(); ++it) {
        word_freqs.push_back(*it);
    } 
}

void Sort(vector<pair <string, int> > &word_freqs) {
    typedef function<bool(pair<string, int>, pair<string, int>)> Comparator; 
	Comparator compFunctor =
			[](pair<string, int> elem1, pair<string, int> elem2)
			{
				return elem1.second > elem2.second;
			};
 
	set<pair<string, int>, Comparator> sortedWords(
			word_freqs.begin(), word_freqs.end(), compFunctor);
			
	word_freqs.clear();
	
    for (set<pair<string, int>, Comparator>::iterator it = sortedWords.begin(); it != sortedWords.end(); ++it)
    {
           word_freqs.push_back(*it);
    }
}

vector<pair <string, int> > top25(vector<string> &words)
{
	vector<pair <string, int> > word_freqs;
	Frequencies(words, word_freqs);
        Sort(word_freqs);
	return word_freqs;
}
}
