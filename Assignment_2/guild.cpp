#include "guild.h"

namespace seneca {

    void Guild::resize(size_t newCap) {
            Character** temp = new Character*[newCap]{};
            for (size_t i = 0; i < m_size; ++i)
                temp[i] = m_members[i];
            delete[] m_members;
            m_members = temp;
            m_capacity = newCap;
        }

        void Guild::clear() {
            delete[] m_members;
            m_members = nullptr;
            m_size = 0;
            m_capacity = 0;
        }

        Guild::Guild(const char* name) : m_name(name) {}

        Guild::Guild(const Guild& other)
        : m_name(other.m_name), m_members(nullptr), m_size(other.m_size), 
        m_capacity(other.m_capacity) {
            if (m_size > 0) {
                m_members = new Character*[m_capacity]{};
                for (size_t i = 0; i < m_size; ++i)
                    m_members[i] = other.m_members[i]; 
            }
        }
        
        Guild& Guild::operator=(const Guild& other) {
            if (this != &other) {
            clear();
            m_name = other.m_name;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            if (m_size > 0) {
                m_members = new Character*[m_capacity]{};
                for (size_t i = 0; i < m_size; ++i)
                    m_members[i] = other.m_members[i]; // shallow copy, or clone if needed
            } else {
                m_members = nullptr;
            }
        }
        return *this;
        }

        Guild::Guild(Guild&& other) noexcept
            : m_name(std::move(other.m_name)), m_members(other.m_members),
              m_size(other.m_size), m_capacity(other.m_capacity) {
            
                other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        Guild& Guild::operator=(Guild&& other) noexcept {
            if (this != &other) {
                clear();
                m_name = std::move(other.m_name);
                m_members = other.m_members;
                m_size = other.m_size;
                m_capacity = other.m_capacity;
                other.m_members = nullptr;
                other.m_size = 0;
                other.m_capacity = 0;
            }
            return *this;
        }

        Guild::~Guild() {
            clear();
        }

        void Guild::addMember(Character* c) {
            // Check for duplicate pointer (identity)
            for (size_t i = 0; i < m_size; ++i)
                if (m_members[i] == c)
                    return;
            if (m_size == m_capacity)
                resize(m_capacity == 0 ? 2 : m_capacity * 2);
            m_members[m_size++] = c;
            c->setHealthMax(c->getHealthMax() + 300);
        }

        void Guild::removeMember(const std::string& name) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_members[i]->getName() == name) {
                    m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
                    for (size_t j = i; j < m_size - 1; ++j)
                        m_members[j] = m_members[j + 1];
                    --m_size;
                    m_members[m_size] = nullptr;
                    break;
                }
            }
        }

        Character* Guild::operator[](size_t idx) const {
            if (idx < m_size)
                return m_members[idx];
            return nullptr;
        }

        void Guild::showMembers() const {
            if (m_size == 0) {
                std::cout << "No guild." << std::endl;
                return;
            }
            std::cout << "[Guild] " << m_name << std::endl;
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << "    " << (i + 1) << ": " << *m_members[i] << std::endl;
            }
        }

};