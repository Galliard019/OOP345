#include "CustomerOrder.h"
#include "Utilities.h"
#include "Station.h"
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <vector>

namespace seneca {

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() : m_cntItem(0), m_lstItem(nullptr) {}

CustomerOrder::CustomerOrder(const std::string& record) 
{
    Utilities util;
    size_t next_pos = 0;
    bool more = true;
    std::vector<std::string> tokens;

    while (more) 
    {
        tokens.push_back(util.extractToken(record, next_pos, more));
    }

    if (tokens.size() < 3) 
    {
        throw std::runtime_error("Invalid record: not enough fields.");
    }

    m_name = tokens[0];
    m_product = tokens[1];
    m_cntItem = tokens.size() - 2;

    m_lstItem = new Item*[m_cntItem];
    for (size_t i = 0; i < m_cntItem; ++i) 
    {
        m_lstItem[i] = new Item(tokens[i + 2]);
    }

    if (util.getFieldWidth() > m_widthField) 
    {
        m_widthField = util.getFieldWidth();
    }
}

CustomerOrder::CustomerOrder(const CustomerOrder& other) 
{
    throw std::runtime_error("Cannot make copies.");
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept 
{
    *this = std::move(other);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept 
{
    if (this != &other) 
    {
        if (m_lstItem) 
        {
            for (size_t i = 0; i < m_cntItem; ++i) 
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
        }

        m_name = std::move(other.m_name);
        m_product = std::move(other.m_product);
        m_cntItem = other.m_cntItem;
        m_lstItem = other.m_lstItem;

        other.m_cntItem = 0;
        other.m_lstItem = nullptr;
    }
    return *this;
}

CustomerOrder::~CustomerOrder() 
{
    for (size_t i = 0; i < m_cntItem; ++i) 
    {
        delete m_lstItem[i];
    }
    delete[] m_lstItem;
}

bool CustomerOrder::isOrderFilled() const 
{
    for (size_t i = 0; i < m_cntItem; ++i) 
    {
        if (!m_lstItem[i]->m_isFilled) 
        {
            return false;
        }
    }
    return true;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const 
{
    bool found = false;
    for (size_t i = 0; i < m_cntItem; ++i) 
    {
        if (m_lstItem[i]->m_itemName == itemName) 
        {
            if (!m_lstItem[i]->m_isFilled) 
            {
                found = true;
            }
        }
    }
    return found;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) 
{
    for (size_t i = 0; i < m_cntItem; ++i) 
    {
        if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) 
        {
            if (station.getQuantity() > 0) 
            {
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                station.updateQuantity();
                os << "    Filled " << m_name << ", " << m_product
                   << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            } 
            else 
            {
                os << "    Unable to fill " << m_name << ", " << m_product
                   << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
            break;
        }
    }
}

void CustomerOrder::display(std::ostream& os) const 
{
    os << m_name << " - " << m_product << std::endl;
    for (size_t i = 0; i < m_cntItem; ++i) 
    {
        os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
        os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName;
        os << " - ";
        os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
    }
}

}
