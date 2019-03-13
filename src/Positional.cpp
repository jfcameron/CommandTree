#include <jfc/Positional.h>

#include <sstream>

std::string Positional::toString() const
{
    std::stringstream s;
    s
    << "{ "
    << "type: " << "\"Positional\", "
    << "name: "
    << "\"" << m_Name << "\""
    << " }";

    return s.str();
}

std::string Positional::getName() 
{ 
    return m_Name; 
};

Positional::Positional(const std::string &aName)
: m_Name(aName)
{}
