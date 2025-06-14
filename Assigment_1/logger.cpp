//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#include "logger.h"


namespace seneca {

Logger::~Logger() {
    
    delete[] m_events;
    m_events = nullptr;

}

Logger::Logger(Logger&& other) noexcept
    
    : m_events(other.m_events), m_size(other.m_size), m_capacity(other.m_capacity) {
    other.m_events = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;

}

Logger& Logger::operator=(Logger&& other) noexcept {
    
    if (this != &other) {
        delete[] m_events;
        m_events = other.m_events;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_events = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    
    return *this;
}

void Logger::addEvent(const Event& event) {
    
    if (m_size == m_capacity) {
        size_t new_capacity = m_capacity ? m_capacity * 2 : 2;
        Event* new_events = new Event[new_capacity];
        for (size_t i = 0; i < m_size; ++i)
            new_events[i] = std::move(m_events[i]);
        delete[] m_events;
        m_events = new_events;
        m_capacity = new_capacity;
    }
    m_events[m_size++] = event;
}

std::ostream& operator<<(std::ostream& ostr, const Logger& logger) {
    
    for (size_t i = 0; i < logger.m_size; ++i)
        ostr << logger.m_events[i];
    
    
    return ostr;
}

}
