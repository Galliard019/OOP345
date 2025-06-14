//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#include "timeMonitor.h"


namespace seneca {

void TimeMonitor::startEvent(const char* name) {
    
    m_eventName = name;
    m_startTime = std::chrono::steady_clock::now();

}

Event TimeMonitor::stopEvent() {
    
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime);
    
    
    return Event(m_eventName.c_str(), duration);
}

}