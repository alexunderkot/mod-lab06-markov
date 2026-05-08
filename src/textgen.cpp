//Copyright 2026 Alexunderkot
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <random>
#include "../include/textgen.h"

void textgen(int Npref, int MaxGen,
    map<prefix, vector<string>> statetab, string *textout) {
    prefix p;
    p = statetab.begin()->first;

    *textout += p.front() + " " + p.back() + " ";

    unsigned int seed = 100;

    for (int i = 1; i < MaxGen; i++) {
        int r = rand_r(&seed) % statetab[p].size();
        *textout += statetab[p][r] + " " + (i % 4 == 0 ? "\n" : "");
        p.push_back(statetab[p][r]);
        p.pop_front();
    }
}
