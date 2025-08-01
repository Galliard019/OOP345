#include "LineManager.h"
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

namespace seneca {

LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) 
{
    std::ifstream input(file);
    if (!input) 
    {
        throw std::runtime_error("Failed to open " + file);
    }

    Utilities util;
    std::string line;
    bool more = false;
    size_t next_pos = 0;

    std::vector<std::pair<std::string, std::string>> links;

    while (std::getline(input, line)) 
    {
        next_pos = 0;
        more = true;
        std::string ws1 = util.extractToken(line, next_pos, more);
        std::string ws2 = more ? util.extractToken(line, next_pos, more) : "";

        links.emplace_back(ws1, ws2);
    }

    for (const auto& [current, next] : links) 
    {
        auto curr_ws = std::find_if(stations.begin(), stations.end(),
            [&](Workstation* w) { return w->getItemName() == current; });

        auto next_ws = std::find_if(stations.begin(), stations.end(),
            [&](Workstation* w) { return w->getItemName() == next; });

        if (curr_ws != stations.end()) 
        {
            (*curr_ws)->setNextStation(next_ws != stations.end() ? *next_ws : nullptr);
            m_activeLine.push_back(*curr_ws);
        }
    }

    m_firstStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* w) 
    {
        return std::none_of(stations.begin(), stations.end(), [&](Workstation* other) 
        {
            return other->getNextStation() == w;
        });
    });

    m_cntCustomerOrder = g_pending.size();
}

void LineManager::reorderStations() 
{
    std::vector<Workstation*> orderedLine;
    Workstation* current = m_firstStation;

    while (current) 
    {
        orderedLine.push_back(current);
        current = current->getNextStation();
    }

    m_activeLine = std::move(orderedLine);
}

bool LineManager::run(std::ostream& os) 
{
    static size_t iteration = 0;
    ++iteration;
    os << "Line Manager Iteration: " << iteration << std::endl;

    if (!g_pending.empty()) 
    {
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }

    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) 
    {
        ws->fill(os);
    });

    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) 
    {
        ws->attemptToMoveOrder();
    });

    return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
}

void LineManager::display(std::ostream& os) const 
{
    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) 
    {
        ws->display(os);
    });
}

}
