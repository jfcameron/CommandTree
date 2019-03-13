#include <jfc/LongOption.h>

#include <sstream>

std::string LongOption::toString() const
{
    std::stringstream s;
    s
    << "{ " 
    << "type: " << "\"LongOption\", "
    << "name: " << "\"" << m_Name << "\" " 
    << "}";

    return s.str();
}

void LongOption::setName(const std::string &aName) 
{ 
    m_Name = aName; 
}

std::string LongOption::getName() const 
{ 
    return m_Name; 
}

LongOption::LongOption(const std::string &aName)
: m_Name(aName)
{}