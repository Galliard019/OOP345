#include "team.h"

namespace seneca {

    void Team::resize(size_t newCap) {
            Character** temp = new Character*[newCap]{};
            for (size_t i = 0; i < m_size; ++i)
                temp[i] = m_members[i];
            delete[] m_members;
            m_members = temp;
            m_capacity = newCap;
        }

        void Team::clear() {
            for (size_t i = 0; i < m_size; ++i)
                delete m_members[i];
            delete[] m_members;
            m_members = nullptr;
            m_size = 0;
            m_capacity = 0;
        }

        Team::Team(const char* name) : m_name(name) {}

        // Rule of 5
        Team::Team(const Team& other) : m_name(other.m_name), m_size(other.m_size), m_capacity(other.m_capacity) {
            m_members = new Character*[m_capacity]{};
            for (size_t i = 0; i < m_size; ++i)
                m_members[i] = other.m_members[i]->clone();
        }

        Team& Team::operator=(const Team& other) {
            if (this != &other) {
                clear();
                m_name = other.m_name;
                m_size = other.m_size;
                m_capacity = other.m_capacity;
                m_members = new Character*[m_capacity]{};
                for (size_t i = 0; i < m_size; ++i)
                    m_members[i] = other.m_members[i]->clone();
            }
            return *this;
        }

        Team::Team(Team&& other) noexcept
            : m_name(std::move(other.m_name)), m_members(other.m_members),
              m_size(other.m_size), m_capacity(other.m_capacity) {
            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        Team& Team::operator=(Team&& other) noexcept {
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

        Team::~Team() {
            clear();
        }

        void Team::addMember(const Character* c) {
            // Check for duplicate name
            for (size_t i = 0; i < m_size; ++i)
                if (m_members[i]->getName() == c->getName())
                    return;
            if (m_size == m_capacity)
                resize(m_capacity == 0 ? 2 : m_capacity * 2);
            m_members[m_size++] = c->clone();
        }

        void Team::removeMember(const std::string& name) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_members[i]->getName() == name) {
                    delete m_members[i];
                    for (size_t j = i; j < m_size - 1; ++j)
                        m_members[j] = m_members[j + 1];
                    --m_size;
                    m_members[m_size] = nullptr;
                    break;
                }
            }
        }

        Character* Team::operator[](size_t idx) const {
            if (idx < m_size)
                return m_members[idx];
            return nullptr;
        }

        void Team::showMembers() const {
            if (m_size == 0) {
                std::cout << "No team." << std::endl;
                return;
            }
            std::cout << "[Team] " << m_name << std::endl;
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << "    " << (i + 1) << ": " << *m_members[i] << std::endl;
            }
        }

}