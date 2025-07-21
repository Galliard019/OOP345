#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <string>
#include <iostream>
#include "mediaItem.h"
#include "settings.h"

namespace seneca
{
	class Movie : public MediaItem
	{
	private:
		Movie(const std::string& title, unsigned short year, const std::string& summary)
			: MediaItem(title, summary, year)
		{
            
		}
	protected:
		static void trim(std::string& str)
		{
			size_t i = 0u;
			for (i = 0u; i < str.length() && str[i] == ' '; ++i);
			str = str.substr(i);

			for (i = str.length(); i > 0 && str[i - 1] == ' '; --i);
			str = str.substr(0, i);
		}
	public:
		void display(std::ostream& out) const override
        {
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                {
                    out << this->getSummary();
                }
                    
                else
                {
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
                }
                    
            }
            else 
            {
                out << this->getSummary();
                out << std::endl;
            }
            
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
            << std::setfill(' ') << '\n';
        }
}

		template<typename Functor_t>
		void fixSpelling(Functor_t& spellChecker)
		{
			spellChecker(m_title);
			spellChecker(m_summary);
		}


		static Movie* createItem(const std::string& strMovie) {
        if (strMovie.empty() || strMovie[0] == '#') {
            throw std::invalid_argument("Not a valid movie.");
        }

        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = strMovie.find(',');

        while (end != std::string::npos) {
            std::string token = strMovie.substr(start, end - start);
		    trim(token);
            tokens.push_back(token);
            start = end + 1;
            end = strMovie.find(',', start);
        }

        std::string token = strMovie.substr(start);
		trim(token);
        tokens.push_back(token);

        if (tokens.size() != 6) {
            throw std::invalid_argument("Not a valid movie.");
        }

        int year = std::stoi(tokens[1]);

        return new Movie(tokens[0], year, tokens[2]);
    }
	};
}

#endif
