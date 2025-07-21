#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <iostream>
#include "mediaItem.h"

namespace seneca
{

class Collection 
{
    std::string m_name;
    std::vector<MediaItem*> m_items;
    void (*m_observer)(const Collection&, const MediaItem&) = nullptr;

public:
    Collection(const std::string& name) : m_name(name) {}

    Collection(const Collection&) = delete;
    Collection& operator=(const Collection&) = delete;
    Collection(Collection&&) = delete;
    Collection& operator=(Collection&&) = delete;

    ~Collection() 
    {
        for (auto item : m_items) 
        {
            delete item;
        }
    }

    const std::string& name() const 
    {
        return m_name;
    }

    size_t size() const 
    {
        return m_items.size();
    }

    void setObserver(void (*observer)(const Collection&, const MediaItem&)) 
    {
        m_observer = observer;
    }

    Collection& operator+=(MediaItem* item) 
    {
        auto found = std::find_if(m_items.begin(), m_items.end(),
            [item](const MediaItem* existing) {
                return existing->getTitle() == item->getTitle();
            });

        if (found == m_items.end()) 
        {
            m_items.push_back(item);
            if (m_observer) 
            {
                m_observer(*this, *item);
            }
        } 
        else 
        {
            delete item;
        }
        return *this;
    }

    MediaItem* operator[](size_t idx) const 
    {
        if (idx >= m_items.size()) 
        {
            throw std::out_of_range("Bad index [" + std::to_string(idx) +
                "]. Collection has [" + std::to_string(m_items.size()) + "] items.");
        }
        return m_items[idx];
    }

    MediaItem* operator[](const std::string& title) const 
    {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [title](const MediaItem* item) 
            {
                return item->getTitle() == title;
            });
        return (it != m_items.end()) ? *it : nullptr;
    }

    void removeQuotes() {
        std::for_each(m_items.begin(), m_items.end(),
            [](MediaItem* item) {
                auto trim = [](std::string str) -> std::string 
                {
                    if (!str.empty() && str.front() == '"') str.erase(0, 1);
                    if (!str.empty() && str.back() == '"') str.pop_back();
                    return str;
                };
                item->setTitle(trim(item->getTitle()));
                item->setSummary(trim(item->getSummary()));
            });
    }

    void sort(const std::string& field) 
    {
        if (field == "title") 
        {
            std::sort(m_items.begin(), m_items.end(),
                [](const MediaItem* a, const MediaItem* b) 
                {
                    return a->getTitle() < b->getTitle();
                });
        } 
        else if (field == "summary") 
        {
            std::sort(m_items.begin(), m_items.end(),
                [](const MediaItem* a, const MediaItem* b) 
                {
                    return a->getSummary() < b->getSummary();
                });
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Collection& col) 
    {
        std::for_each(col.m_items.begin(), col.m_items.end(),
            [&os](const MediaItem* item) 
            {
                os << *item;
            });
        return os;
    }

auto begin() { return m_items.begin(); }
auto end() { return m_items.end(); }
auto begin() const { return m_items.begin(); }
auto end() const { return m_items.end(); }

};

}


#endif
