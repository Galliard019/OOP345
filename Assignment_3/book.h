#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <string>
#include <iostream>
#include "mediaItem.h"
#include "settings.h"

namespace seneca
{
	class Book : public MediaItem
	{
		std::string m_author{};
		std::string m_country{};
		double m_price{};
	private:
		Book(const std::string& author, const std::string& title, const std::string& country,
			 unsigned short year, double price, const std::string& summary)
			: MediaItem(title, summary, year),
			  m_author(author), m_country(country), m_price(price)
		{
			trim(m_author);
			trim(m_country);
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
				out << "B | ";
				out << std::left << std::setfill('.');
				out << std::setw(50) << this->getTitle() << " | ";
				out << std::right << std::setfill(' ');
				out << std::setw(2) << this->m_country << " | ";
				out << std::setw(4) << this->getYear() << " | ";
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
				out << this->getTitle() << " [" << this->getYear() << "] [";
				out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
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
			spellChecker(m_author);
			spellChecker(m_title);
			spellChecker(m_summary);
		}


		static Book* createItem(const std::string& strBook) {
        if (strBook.empty() || strBook[0] == '#') {
            throw std::invalid_argument("Not a valid book.");
        }

        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = strBook.find(',');

        while (end != std::string::npos) {
			std::string token = strBook.substr(start, end - start);
			trim(token);
            tokens.push_back(token);
            start = end + 1;
            end = strBook.find(',', start);
        }

		std::string token = strBook.substr(start);
		trim(token);
        tokens.push_back(token);

        if (tokens.size() != 6) {
            throw std::invalid_argument("Not a valid book.");
        }

        double price = std::stod(tokens[3]);
        int year = std::stoi(tokens[4]);

        return new Book(tokens[0], tokens[1], tokens[2], price, year, tokens[5]);
    }
	};
}

#endif
