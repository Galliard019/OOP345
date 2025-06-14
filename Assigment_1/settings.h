//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#pragma once
#include <string>

namespace seneca {

struct Settings {
    bool m_show_all = false;
    bool m_verbose = false;
    std::string m_time_units = "nanoseconds";
};

extern Settings g_settings;

}

#endif