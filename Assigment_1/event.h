//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#pragma once
#include <string>
#include <chrono>
#include <iostream>


namespace seneca {

class Event {
    std::string m_name{};
    std::chrono::nanoseconds m_duration{0};

public:
    Event() = default;
    Event(const char* name, const std::chrono::nanoseconds& duration)
        : m_name(name), m_duration(duration) {}

    friend std::ostream& operator<<(std::ostream& os, const Event& ev);
};

}

#endif