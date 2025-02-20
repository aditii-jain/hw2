#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <set>
#include "util.h"

using namespace std;

std::string convToLower(std::string src) {
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

std::set<std::string> parseStringToWords(std::string rawWords) {
    set<string> words;

    // Convert to lowercase
    rawWords = convToLower(rawWords);

    // Replace punctuation with spaces
    for (char &c : rawWords) {
        if (ispunct(c)) {
            c = ' ';
        }
    }

    // Use stringstream to extract words
    stringstream ss(rawWords);
    string word;
    
    while (ss >> word) {
        if (word.size() >= 2) {  // Only add words with 2 or more characters
            words.insert(word);
        }
    }

    return words; // Return the set
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}