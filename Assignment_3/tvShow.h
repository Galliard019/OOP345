#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <list>
#include "mediaItem.h"


namespace seneca
{
	class TvShow : public MediaItem
	{

        struct TvEpisode
        {
            std::string m_show{}; //const TvShow*
            unsigned short m_numberOverall{};
            unsigned short m_season{};
            unsigned short m_numberInSeason{};
            std::string m_airDate{};
            unsigned int m_length{};
            std::string m_title{};
            std::string m_summary{};

            TvEpisode(const std::string& show, unsigned short numberOverall,
                unsigned short season, unsigned short numberInSeason,
                const std::string& airDate, unsigned int length,
                const std::string& title, const std::string& summary = "")
                : m_show(show), m_numberOverall(numberOverall),
                  m_season(season), m_numberInSeason(numberInSeason),
                  m_airDate(airDate), m_length(length),
                  m_title(title), m_summary(summary) {}
        };

		std::string m_id{};
        std::vector<TvEpisode*> m_episodes;

	private:
		TvShow(std::string id, const std::string& title, unsigned short year,
            const std::string& summary, std::vector<TvEpisode*> episodes = {})
			: MediaItem(title, summary, year),
                m_id(id), m_episodes(std::move(episodes))
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
                out << "S | ";
                out << std::left << std::setfill('.');
                out << std::setw(50) << this->getTitle() << " | ";
                out << std::right << std::setfill(' ');
                out << std::setw(2) << this->m_episodes.size() << " | ";
                out << std::setw(4) << this->getYear() << " | ";
                out << std::left;
                if (g_settings.m_maxSummaryWidth > -1)
                {
                    if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                        out << this->getSummary();
                    else
                        out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
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
                for (auto& item : m_episodes)
                {
                    out << std::setfill('0') << std::right;
                    out << "    " << 'S' << std::setw(2) << item->m_season
                        << 'E' << std::setw(2) << item->m_numberInSeason << ' ';
                    if (item->m_title != "")
                    {
                        out << item->m_title << '\n';
                    }
                        
                    else
                    {
                        out << "Episode " << item->m_numberOverall << '\n';
                    }
                        

                    pos = 0;
                    while (pos < item->m_summary.size())
                    {
                        out << "            " << item->m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                        pos += g_settings.m_maxSummaryWidth - 8;
                    }
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


		static TvShow* createItem(const std::string& strTvShow) 
        {
        if (strTvShow.empty() || strTvShow[0] == '#') 
        {
            throw std::invalid_argument("Not a valid show.");
        }

        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = strTvShow.find(',');

        while (end != std::string::npos) 
        {
            std::string token = strTvShow.substr(start, end - start);
		    trim(token);
            tokens.push_back(token);
            start = end + 1;
            end = strTvShow.find(',', start);
        }
        std::string token = strTvShow.substr(start);
		trim(token);
        tokens.push_back(token);

        if (tokens.size() != 6) {
            throw std::invalid_argument("Not a valid show.");
        }

        long id = std::stol(tokens[0]);
        int year = std::stoi(tokens[2]);

        return new TvShow(tokens[0], tokens[1], year, tokens[3]);
    }

    
void addEpisode(TvEpisode* ep) {
}


    template<typename Collection_t>
    static void addEpisode(Collection_t& col, const std::string& strEpisode) 
    {
        if (strEpisode.empty() || strEpisode[0] == '#') 
        {
            throw std::invalid_argument("Not a valid episode.");
        }

        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = strEpisode.find(',');

        while (end != std::string::npos) 
        {
            std::string token = strEpisode.substr(start, end - start);
		    trim(token);
            tokens.push_back(token);
            start = end + 1;
            end = strEpisode.find(',', start);
        }
        std::string token = strEpisode.substr(start);
		trim(token);
        tokens.push_back(token);

        if (tokens.size() < 8) 
        {
            throw std::invalid_argument("Not a valid episode.");
        }

        std::string& id = tokens[0]; //const TvShow*
        unsigned short epNumber = std::stoi(tokens[1]);
        unsigned short seasonNumber = (tokens[2].empty() ? 1 : std::stoi(tokens[2]));
        unsigned short epInSeason = std::stoi(tokens[3]);
        const std::string& airDate = tokens[4];
        unsigned int length = std::stoi(tokens[5]);
        const std::string& title = tokens[6];
        const std::string& summary = tokens[7];

        TvEpisode* ep = new TvEpisode(id, epNumber, seasonNumber, epInSeason, airDate, length, title, summary);

        auto it = std::find_if(col.begin(), col.end(), [=](MediaItem* item) {
            auto* show = dynamic_cast<TvShow*>(item);
            return show && show->m_id == id;
        });

        if (it != col.end()) 
        {
            auto* show = dynamic_cast<TvShow*>(*it);
            show->addEpisode(ep);
        } 
        
        else 
        {
            delete ep;
            throw std::runtime_error("TV Show ID not found.");
        }
    }

    double getEpisodeAverageLength() const 
    {
        if (m_episodes.empty()) 
        {
            return 0.0;

        } 
        int total = std::accumulate(m_episodes.begin(), m_episodes.end(), 0, [](int sum, TvEpisode* ep) 
            {
                return sum + ep->m_length;
            }
        );

        return static_cast<double>(total) / m_episodes.size();
    }


    std::list<std::string> getLongEpisodes() const 
    {
        std::list<std::string> result;

        std::for_each(m_episodes.begin(), m_episodes.end(), [=, &result](TvEpisode* ep) {
            if (ep->m_length >= 3600)
            {
                result.push_back(ep->m_title);
            }
        });

        return result;
    }

    auto begin() { return m_episodes.begin(); }
    auto end() { return m_episodes.end(); }
    auto begin() const { return m_episodes.begin(); }
    auto end() const { return m_episodes.end(); }

	};
}

#endif
