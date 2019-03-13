#include <jfc/LongOptionWithValue.h>

#include <sstream>

std::string LongOptionWithValue::toString() const
{
    std::stringstream s;
    s
    << "{ "
    << "type: " << "\"LongOptionWithValue\", "
    << "name: "  << "\"" << getName() << "\" "
    << "value: " << "\"" << m_Value   << "\" "
    << "}";

    return s.str();
}

std::string LongOptionWithValue::getValue()
{
    return m_Value;
}

LongOptionWithValue::LongOptionWithValue(const std::string &aName, const std::string &aValue)
: LongOption(aName)
, m_Value(aValue)
{}
