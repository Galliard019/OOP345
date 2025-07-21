//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 15/06/2025


#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <string>
#include <iostream>
#include "character.h"

namespace seneca
{
    // Team class manages a collection of Character pointers (composition).
    class Team
    {
        std::string m_name{};
        Character** m_members{nullptr};
        size_t m_size{0};
        size_t m_capacity{0};

        void resize(size_t newCap);

        void clear();

    public:
        Team() = default;

        Team(const char* name);

        // Rule of 5
        Team(const Team& other);

        Team& operator=(const Team& other);

        Team(Team&& other) noexcept;

        Team& operator=(Team&& other) noexcept;

        ~Team();

        void addMember(const Character* c);

        void removeMember(const std::string& name);

        Character* operator[](size_t idx) const;

        void showMembers() const;
    };
}

#endif