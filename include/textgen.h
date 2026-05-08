#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <vector>
#include <string>
#include <map>
#include <deque>

using namespace std;

typedef deque<string> prefix;

void textgen(int Npref, int MaxGen, map<prefix, 
    vector<string>> statetab, string *textout);

#endif // TEXTGEN_H