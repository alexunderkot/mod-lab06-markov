//Copyright 2026 Alexunderkot

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <vector>
#include <string>
#include <map>
#include <deque>

using std::string;
using std::vector;
using std::map;
using std::deque;

typedef deque<string> prefix;

void textgen(int Npref, int MaxGen, map<prefix,
    vector<string>> statetab, string *textout);

#endif // INCLUDE_TEXTGEN_H_
