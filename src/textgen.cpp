//Copyright 2026 Alexunderkot
#include "../include/textgen.h"
#include <string>
#include <vector>
#include <map>

void textgen(int Npref, int MaxGen, 
    map<prefix, vector<string>> statetab, string *textout) {
    prefix p;
    p = statetab.begin()->first;

    *textout += p.front() + " " + p.back() + " ";

    for (int i = 1; i < MaxGen; i++) {
        int r = rand() % statetab[p].size();
        *textout += statetab[p][r] + " " + (i % 4 == 0 ? "\n" : "");
        p.push_back(statetab[p][r]);
        p.pop_front();
    }
}
