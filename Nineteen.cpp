#include <fstream>
#include <iostream>
#include <exception>
#include <map>
#include <set>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <functional>
#include <dlfcn.h>

using namespace std;
typedef vector<string> (*fun1)(char *file);
typedef vector<pair<string, int>> (*fun2)(vector<string> &words);
fun1 extract_words;
fun2 top25;

void load_plugins() {
    ifstream config;
    stringstream data;
    config.open("./config.ini", ios_base::in);
    data << config.rdbuf();
    string word;
	int i = 0;
    void *handle[10];
    while (data >> word) {
    	if(word.find(".so") != string::npos) {
		//cout << "lib: " << word << endl;
		handle[i] = dlopen(word.c_str(), RTLD_NOW);
		i++;
	}
    }
	void *handle1;
	void *handle2;
	*(void**)(&extract_words) = dlsym(handle[0],"extract_words");
	*(void**)(&top25) = dlsym(handle[1],"top25");
}

int main(int argc, char **argv)
{
	vector<string> words;
	vector<pair <string, int> > word_freqs;
	if(argc > 2 || argc == 1) {
		cout << "Error: Only accept one argument!" << endl;
		return -1;
	}
	load_plugins();
	words = extract_words(argv[1]);
	word_freqs = top25(words);
     	int i = 0;
    	for (vector<pair<string, int>>::iterator it = word_freqs.begin(); it != word_freqs.end() && i < 25; ++it)
    	{
           cout << it->first <<" - "<< it->second << endl;
           i++;
    	}
	return 0;
}

