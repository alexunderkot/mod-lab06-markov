// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include "../include/textgen.h"


using std::string;
using std::vector;
using std::map;
using std::deque;
using std::ofstream;
using std::ifstream;

// Создание таблицы как в main
void SetUpFunc(string filePath, map<prefix, vector<string>>& statetab,
     prefix& firstWords, int NPREF) {
    std::ifstream file(filePath);
    string word;
    prefix curPrefix;

    for (int i = 0; i < NPREF && file >> word; i++) {
        curPrefix.push_back(word);
        firstWords.push_back(word);
    }

    while (file >> word) {
        statetab[curPrefix].push_back(word);
        curPrefix.push_back(word);
        curPrefix.pop_front();
    }
}


TEST(task1, testPrefix1) {
    const string file = "test_prefix.txt";
    const int NPREF = 3;
    map<prefix, vector<string>> statetab;
    prefix firstWords;

    ofstream testFile(file);
    testFile << "один два три четыре пять";
    testFile.close();

    SetUpFunc(file, statetab, firstWords, NPREF);

    EXPECT_EQ(firstWords.size(), NPREF);
    EXPECT_EQ(firstWords[0], "один");
    EXPECT_EQ(firstWords[1], "два");
    EXPECT_EQ(firstWords[2], "три");
}

TEST(task1, testPrefix2) {
    const string file = "test_prefix.txt";
    const int NPREF = 5;
    map<prefix, vector<string>> statetab;
    prefix firstWords;

    ofstream testFile(file);
    testFile << "один два три четыре пять";
    testFile.close();

    SetUpFunc(file, statetab, firstWords, NPREF);

    EXPECT_EQ(firstWords.size(), NPREF);
    EXPECT_EQ(firstWords[0], "один");
    EXPECT_EQ(firstWords[1], "два");
    EXPECT_EQ(firstWords[2], "три");
    EXPECT_EQ(firstWords[3], "четыре");
    EXPECT_EQ(firstWords[4], "пять");
}

TEST(task2, testSuffix1) {
    const string file = "test_prefix.txt";
    const int NPREF = 2;
    map<prefix, vector<string>> statetab;
    prefix firstWords;

    ofstream testFile(file);
    testFile << "один два три четыре пять";
    testFile.close();

    SetUpFunc(file, statetab, firstWords, NPREF);


    EXPECT_EQ(3, statetab.size());
    EXPECT_EQ(1, statetab[firstWords].size());
}

TEST(task2, testSuffix2) {
    const string file = "test_prefix.txt";
    const int NPREF = 2;
    map<prefix, vector<string>> statetab;
    prefix firstWords;

    ofstream testFile(file);
    testFile << "даже буква и символ и слово";
    testFile.close();

    SetUpFunc(file, statetab, firstWords, NPREF);

    EXPECT_EQ(4, statetab.size());
    EXPECT_EQ(1, statetab[firstWords].size());
}

TEST(task2, prefixSuffixMultiple) {
    const string file = "test_ps2.txt";
    const int NPREF = 2;
    map<prefix, vector<string>> statetab;
    prefix firstWords;

    ofstream testFile(file);
    testFile << "кот сидел тут кот сидел там";
    testFile.close();

    SetUpFunc(file, statetab, firstWords, NPREF);

    prefix p;
    p.push_back("кот");
    p.push_back("сидел");

    EXPECT_EQ(2, statetab[p].size());
    EXPECT_EQ("тут", statetab[p][0]);
    EXPECT_EQ("там", statetab[p][1]);
}

TEST(task3, singleSuffix) {
    map<prefix, vector<string>> statetab;
    prefix p;
    p.push_back("один");
    p.push_back("два");
    statetab[p].push_back("три");
    prefix p2;
    p2.push_back("два");
    p2.push_back("три");
    statetab[p2].push_back("четыре");

    string textout = "";
    textgen(2, 2, statetab, &textout);

    EXPECT_NE(textout.find("три"), string::npos);
}

TEST(task4, multiSuffix1) {
    map<prefix, vector<string>> statetab;
    prefix p1;
    p1.push_back("один");
    p1.push_back("два");
    statetab[p1].push_back("три");
    statetab[p1].push_back("четыре");

    prefix p2;
    p2.push_back("два");
    p2.push_back("три");
    statetab[p2].push_back("пять");

    prefix p3;
    p3.push_back("два");
    p3.push_back("четыре");
    statetab[p3].push_back("пять");

    string textout = "";
    srand(100);
    for (int i = 0; i < 1000; i++) {
        textgen(2, 2, statetab, &textout);
    }

    EXPECT_NE(textout.find("три"), string::npos);
    EXPECT_NE(textout.find("четыре"), string::npos);
}

TEST(task4, multiSuffix2) {
    map<prefix, vector<string>> statetab;
    prefix p;
    p.push_back("1");
    p.push_back("2");
    statetab[p].push_back("один");
    statetab[p].push_back("два");
    statetab[p].push_back("три");
    statetab[p].push_back("четыре");
    statetab[p].push_back("пять");
    statetab[p].push_back("шесть");
    statetab[p].push_back("семь");
    statetab[p].push_back("восемь");
    vector<string> suffixes = {"один", "два", "три",
        "четыре", "пять", "шесть", "семь", "восемь"};

    for (auto& s : suffixes) {
        prefix p2;
        p2.push_back("2");
        p2.push_back(s);
        statetab[p2].push_back("один");
    }

    string textout = "";
    srand(100);
    for (int i = 0; i < 1000; i++) {
        textout = "";
        textgen(2, 2, statetab, &textout);
    }

    bool hasAny = false;
    for (auto& s : suffixes) {
        if (textout.find(s) != string::npos) {
            hasAny = true;
            break;
        }
    }
    EXPECT_TRUE(hasAny);
}

TEST(task5, textNotEmpty) {
    map<prefix, vector<string>> statetab;
    prefix p;
    p.push_back("слово");
    p.push_back("другое");
    statetab[p].push_back("третье");

    string textout = "";
    textgen(2, 1, statetab, &textout);

    EXPECT_FALSE(textout.empty());
}

TEST(task5, textLength1) {
    ifstream file("mod-lab06-markov/test/testText2.txt");
    string word;
    string text;

    map<prefix, vector<string>> statetab;
    prefix curPrefix;

    for (int i = 0; i < 2 && file >> word; i++) {
        curPrefix.push_back(word);
    }

    while (file >> word) {
        statetab[curPrefix].push_back(word);
        curPrefix.push_back(word);
        curPrefix.pop_front();
    }

    string textout = "";
    textgen(2, 500, statetab, &textout);

    bool isWord;
    int wordCount = 0;
    for (char c : textout) {
        if (c == '\n' || c == ' ') {
            isWord = false;
        } else {
            if (!isWord) {
                isWord = true;
                wordCount += 1;
            }
        }
    }

    EXPECT_GE(wordCount, 500);
}

TEST(task5, textLength2) {
    ifstream file("mod-lab06-markov/test/testText2.txt");
    string word;
    string text;

    map<prefix, vector<string>> statetab;
    prefix curPrefix;

    for (int i = 0; i < 2 && file >> word; i++) {
        curPrefix.push_back(word);
    }

    while (file >> word) {
        statetab[curPrefix].push_back(word);
        curPrefix.push_back(word);
        curPrefix.pop_front();
    }

    string textout = "";
    textgen(2, 30, statetab, &textout);

    bool isWord;
    int wordCount = 0;
    for (char c : textout) {
        if (c == '\n' || c == ' ') {
            isWord = false;
        } else {
            if (!isWord) {
                isWord = true;
                wordCount += 1;
            }
        }
    }

    EXPECT_GE(wordCount, 30);
}
