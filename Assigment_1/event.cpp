//Name: Joao Marcos Freire de Castro
//Seneca ID: 173962234
//Seneca e-mail: jmfreire-de-castro@myseneca.ca
//Date: 30/05/2025

#include "event.h"
#include "settings.h"
#include <iomanip>


namespace seneca {

std::ostream& operator<<(std::ostream& ostr, const Event& ev) {
    
    static size_t counter = 1;
    int width = 11;
    double value = static_cast<double>(ev.m_duration.count());
    std::string units = g_settings.m_time_units;

    if (units == "seconds") {
        width = 2;
        value /= 1'000'000'000.0;
    } else if (units == "milliseconds") {
        width = 5;
        value /= 1'000'000.0;
    } else if (units == "microseconds") {
        width = 8;
        value /= 1'000.0;
    } else { // nanoseconds
        width = 11;
    }

    ostr << std::right << std::setw(2) << counter << ": "
         << std::right << std::setw(40) << ev.m_name << " -> "
         << std::right << std::setw(width)
         << std::fixed << std::setprecision((units == "seconds") ? 0 : 0)
         << static_cast<long long>(value)
         << " " << units << std::endl;
    ++counter;
    
    
    return ostr;
}

}
