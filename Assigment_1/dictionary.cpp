//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>


namespace seneca {

Dictionary::~Dictionary() {
    
    delete[] m_words;
    m_words = nullptr;

}

Dictionary::Dictionary(Dictionary&& other) noexcept

    : m_words(other.m_words), m_size(other.m_size) {
      other.m_words = nullptr;
      other.m_size = 0;

}

Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
    
    if (this != &other) {
        delete[] m_words;
        m_words = other.m_words;
        m_size = other.m_size;
        other.m_words = nullptr;
        other.m_size = 0;
    
    }
    
    return *this;
}

PartOfSpeech Dictionary::parsePOS(const std::string& posStr) const {
    
    if (posStr == "n." || posStr == "n. pl.") return PartOfSpeech::Noun;
    if (posStr == "adv.") return PartOfSpeech::Adverb;
    if (posStr == "a.") return PartOfSpeech::Adjective;
    if (posStr == "v." || posStr == "v. i." || posStr == "v. t." || posStr == "v. t. & i.") return PartOfSpeech::Verb;
    if (posStr == "prep.") return PartOfSpeech::Preposition;
    if (posStr == "pron.") return PartOfSpeech::Pronoun;
    if (posStr == "conj.") return PartOfSpeech::Conjunction;
    if (posStr == "interj.") return PartOfSpeech::Interjection;
    
    return PartOfSpeech::Unknown;
}

Dictionary::Dictionary(const char* filename) {
    
    std::ifstream file(filename);
    if (!file) {
        m_words = nullptr;
        m_size = 0;
    
        return;
    }

    std::vector<Word> tempWords;
    std::string line;
    while (std::getline(file, line)) {
        size_t firstComma = line.find(',');
        if (firstComma == std::string::npos) continue;
        size_t secondComma = line.find(',', firstComma + 1);
        if (secondComma == std::string::npos) continue;

        std::string word = line.substr(0, firstComma);
        std::string pos = line.substr(firstComma + 1, secondComma - firstComma - 1);
        std::string def = line.substr(secondComma + 1);

        // This is for removing possible leading and trailing whitespace (if this is causing problems comment it out)
        word.erase(0, word.find_first_not_of(" \t\r\n"));
        word.erase(word.find_last_not_of(" \t\r\n") + 1);
        pos.erase(0, pos.find_first_not_of(" \t\r\n"));
        pos.erase(pos.find_last_not_of(" \t\r\n") + 1);
        def.erase(0, def.find_first_not_of(" \t\r\n"));
        def.erase(def.find_last_not_of(" \t\r\n") + 1);

        tempWords.push_back({word, def, parsePOS(pos)});
    }

    m_size = tempWords.size();
    m_words = new Word[m_size];
    for (size_t i = 0; i < m_size; ++i) {
        m_words[i] = std::move(tempWords[i]);
    }
    
    //std::cout << "[Dictionary] Loaded " << m_size << " words from file: " << filename << std::endl;
}

static std::string posToString(PartOfSpeech pos) {
    
    switch (pos) {
        case PartOfSpeech::Noun: return "noun";
        case PartOfSpeech::Pronoun: return "pronoun";
        case PartOfSpeech::Adjective: return "adjective";
        case PartOfSpeech::Adverb: return "adverb";
        case PartOfSpeech::Verb: return "verb";
        case PartOfSpeech::Preposition: return "preposition";
        case PartOfSpeech::Conjunction: return "conjunction";
        case PartOfSpeech::Interjection: return "interjection";
    
        default: return "";
    }
}

void Dictionary::searchWord(const char* word) const {
    std::string target(word);
    bool found = false;
    size_t count = 0;
    for (size_t i = 0; i < m_size; ++i) {
        if (m_words[i].m_word == target) {
            found = true;
            std::ostringstream oss;
            if (count == 0) {
                oss << m_words[i].m_word;
            } else {
                oss << std::setw(m_words[i].m_word.size()) << " ";
            }
            if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                oss << " - (" << posToString(m_words[i].m_pos) << ")";
            } else {
                oss << " -";
            }
            oss << " " << m_words[i].m_definition << std::endl;
            std::cout << oss.str();
            ++count;
            if (!g_settings.m_show_all) break;
        }
    }
    
    if (!found) {
        std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
    }
}

Dictionary::Dictionary(const Dictionary& other)
    
    : m_words(nullptr), m_size(other.m_size) {
    if (other.m_words && other.m_size > 0) {
        m_words = new Word[m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_words[i] = other.m_words[i];
        }
    
    }
}

Dictionary& Dictionary::operator=(const Dictionary& other) {
    
    if (this != &other) {
        delete[] m_words;
        m_size = other.m_size;
        m_words = nullptr;
        if (other.m_words && m_size > 0) {
            m_words = new Word[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_words[i] = other.m_words[i];
            }
        }
    }

    return *this;
}

}
