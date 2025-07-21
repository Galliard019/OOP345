//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 15/06/2025


#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"

namespace seneca
{
    /// Templated character base class for health management.
    template <typename T>
    class CharacterTpl : public Character
    {
        int m_healthMax{};
        T m_health{};
    public:

        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_healthMax(healthMax), m_health() {
                m_health = healthMax;
            }

        /// Reduces health by dmg. Prints defeat or remaining health.
        void takeDamage(int dmg) override {
            m_health -= dmg;
            if (getHealth() <= 0) {
                m_health = 0;
                std::cout << "    " << getName() << " has been defeated!" << std::endl;
            } else {
                std::cout << "    " << getName() << " took " << dmg << " damage, "
                          << getHealth() << " health remaining." << std::endl;
            }
        }

        int getHealth() const override { return static_cast<int>(m_health); }
        int getHealthMax() const override { return m_healthMax; }

        void setHealth(int health) override { m_health = health; }
        void setHealthMax(int health) override {
            m_healthMax = health;
            m_health = health;
        }
    };
}

#endif