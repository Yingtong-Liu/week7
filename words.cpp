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
/* Just a helper function */
int isNotAlphaNum(char c)
{
        return !isalnum(c);
}

void  FilterCharsAndNormalize(stringstream &data) {
    string ss;
    ss = data.str();
    replace_if(ss.begin(), ss.end(), isNotAlphaNum, ' ');
    transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
    data.str(ss);
    //cout << "After: " << data.str() << endl;
}

void Scan(stringstream &data, vector<string> &words) {
    string word;
    while (data >> word) {
    //    cout << word << endl;
        words.push_back(word);
    }
}

void RemoveStopWords(vector<string> &words) {
    //cout << "RemoveStopWords" << endl;
    ifstream input1;
    vector<string> stopWords;
	input1.open ("../stop_words.txt", ios_base::in);
	if (input1.is_open())
	{
	    stopWords.clear();
        string line;
        getline(input1,line);
        stringstream stops(line);
        string stop;
        while (getline(stops, stop, ',' ))
        {
            //cout << "stop: " << stop <<endl;
            stopWords.push_back(stop);
        }
        for(char i = 'a'; i < 'a' + 26; i++) {
            string alphabet(1, i);
            //cout << "stop: " << alphabet <<endl;
            stopWords.push_back(alphabet);
        }

        input1.close();
    } else
	{
		cout << "Error: can't open stop_words.txt file" << endl;
	}
	
	for (vector<string>::iterator it = words.begin(); it != words.end(); ++it) {
        if((find(stopWords.begin(), stopWords.end(), *it) != stopWords.end())) {
                words.erase(it);
                it--;
        }
        //cout << *it << endl;
    }
}

vector<string> extract_words(char *file) {
    ifstream input;
    stringstream data;
    vector<string> words;
    input.open(file, ios_base::in);
    //cout << "extract_words" << endl;
    if (input.fail()) {
       	cout << "Open " << file << " failed" << endl;
       	exit(0);
     }
     data << input.rdbuf();
     input.close();
     FilterCharsAndNormalize(data);
     Scan(data, words);
     RemoveStopWords(words);
     return words; 
}
}
