#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <string>
#include <iostream>
#include "character.h"

namespace seneca
{
    /// <summary>
    /// Guild class manages a collection of Character pointers (aggregation).
    /// </summary>
    class Guild
    {
        std::string m_name{};
        Character** m_members{nullptr};
        size_t m_size{0};
        size_t m_capacity{0};

        void resize(size_t newCap);

        void clear();

    public:
        Guild() = default;

        Guild(const char* name);

        // Rule of 5
        Guild(const Guild& other);
        Guild& operator=(const Guild& other);

        Guild(Guild&& other) noexcept;

        Guild& operator=(Guild&& other) noexcept;

        ~Guild();

        void addMember(Character* c);

        void removeMember(const std::string& name);

        Character* operator[](size_t idx) const;

        void showMembers() const;
    };
}

#endif