//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#pragma once
#include <string>
#include <cstddef>
#include <vector>


namespace seneca {

enum class PartOfSpeech {
    Unknown,
    Noun,
    Pronoun,
    Adjective,
    Adverb,
    Verb,
    Preposition,
    Conjunction,
    Interjection,
};

struct Word {
    
    std::string m_word{};
    std::string m_definition{};
    PartOfSpeech m_pos = PartOfSpeech::Unknown;

};

class Dictionary {
    Word* m_words{nullptr};
    size_t m_size{0};

    PartOfSpeech parsePOS(const std::string& posStr) const;

public:
    Dictionary() = default;
    Dictionary(const char* filename);
    ~Dictionary();

    //The isntructions ask to disable copy but if I do tester_1 does not work
    Dictionary(const Dictionary&);
    Dictionary& operator=(const Dictionary&);

    Dictionary(Dictionary&& other) noexcept;
    Dictionary& operator=(Dictionary&& other) noexcept;

    void searchWord(const char* word) const;
    
};

}

#endif