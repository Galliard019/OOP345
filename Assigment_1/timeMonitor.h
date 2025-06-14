//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#pragma once
#include <chrono>
#include <string>
#include "event.h"


namespace seneca {

class TimeMonitor {
    std::string m_eventName{};
    std::chrono::steady_clock::time_point m_startTime{};

public:
    void startEvent(const char* name);
    Event stopEvent();
};

}

#endif