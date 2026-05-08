//Copyright 2026 Alexunderkot
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include "../include/textgen.h"

using std::string;
using std::vector;
using std::map;
using std::deque;

int main(int argc, char const *argv[]) {
    const int NPREF = 2;                 // количество слов в префиксе
    const int MAXGEN = 1250;             // объем текста на выходе
    const string READFROM = "input.txt"; // путь до входного файла
    const string WRITEIN = "../result/gen.txt"; // путь до выходного файла

    srand(time(nullptr));
    std::ifstream file(READFROM);
    std::string word;
    string text;

    typedef deque<string> prefix;         // очередь префиксов
    map<prefix, vector<string>> statetab; // префикс-суффиксы
    prefix curPrefix;

    for (int i = 0; i < NPREF && file >> word; i++) {
        curPrefix.push_back(word);
    }

    while (file >> word) {
        statetab[curPrefix].push_back(word);
        curPrefix.push_back(word);
        curPrefix.pop_front();
    }

    //отправляем ограничения файл и первые два слова для генерации
    textgen(NPREF, MAXGEN, statetab, &text);

    std::ofstream fileout(WRITEIN);
    fileout << text;

    return 0;
}
