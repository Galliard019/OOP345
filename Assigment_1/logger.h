//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#pragma once
#include "event.h"
#include <cstddef>
#include <iostream>


namespace seneca {

class Logger {
    Event* m_events{nullptr};
    size_t m_size{0};
    size_t m_capacity{0};

public:
    Logger() = default;
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&& other) noexcept;
    Logger& operator=(Logger&& other) noexcept;

    void addEvent(const Event& event);

    friend std::ostream& operator<<(std::ostream& ostr, const Logger& logger);
};

}

#endif