#include <jfc/OptionList.h>

#include <sstream>

std::string OptionList::toString() const
{
    std::stringstream s;
    s
    << "{ "
    << "type: OptionList, "
    << "options: ["
    << [&]()
    {
        std::string buffer;

        for (const auto &option : m_Options) buffer += option;

        return buffer;
    }()
    << "]}";

    return s.str();
}

OptionList::option_collection_type::iterator OptionList::begin() 
{ 
    return m_Options.begin(); 
}

OptionList::option_collection_type::const_iterator OptionList::begin() const 
{ 
    return m_Options.begin(); 
}

OptionList::option_collection_type::iterator OptionList::end() 
{ 
    return m_Options.end(); 
}

OptionList::option_collection_type::const_iterator OptionList::end() const 
{ 
    return m_Options.end(); 
}    

OptionList::option_collection_type::size_type OptionList::size() const 
{ 
    return m_Options.size(); 
}

OptionList::OptionList(const option_collection_type &aOptions)
: m_Options(aOptions)
{}
