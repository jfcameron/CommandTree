#include <jfc/OptionList.h>
#include <jfc/ParameterFactory.h>
#include <jfc/ParameterList.h>
#include <jfc/Positional.h>

/// \desc returns a weak_ptr to a longoptionwithvalue with the provided name if such a longoption exists in the list. returns a null weak ptr if it does not
std::weak_ptr<LongOptionWithValue> ParameterList::getLongOptionWithValue(const std::string &aLongOptionWithValue) const
{
    for (const auto param : m_Parameters) if (const auto p = std::dynamic_pointer_cast<LongOptionWithValue>(param))
    {
        if (aLongOptionWithValue == p->getName()) return p;
    }

    return {};
}

/// \desc indicates whether or not the list contains a long option with the given name
bool ParameterList::containsLongOption(const std::string &aLongOption) const
{
    for (const auto param : m_Parameters) if (const auto p = std::dynamic_pointer_cast<LongOption>(param))
    {
        if (aLongOption == p->getName()) return true;
    }

    return false;
}

/// \desc indicates whether or not any option list in the parameter list contains the given option
bool ParameterList::containsOption(const char aOption) const
{
    for (const auto param : m_Parameters) if (const auto p = std::dynamic_pointer_cast<OptionList>(param))
    {
        for (const auto option : *p)
        {
            if (aOption == option) return true;
        }
    }

    return false;
}

/// \desc indicates whether or not the parameter list contains a positional with the given name
bool ParameterList::containsPositional(const std::string &aPositional) const
{
    for (const auto param : m_Parameters) if (const auto p = std::dynamic_pointer_cast<Positional>(param))
    {
        if (aPositional == p->getName()) return true;
    }

    return false;
}

/// \desc ptr to beginning of list data
ParameterList::iterator ParameterList::begin() 
{ 
    return m_Parameters.begin(); 
}

/// \desc const ptr to beginning of list data
ParameterList::const_iterator ParameterList::begin() const 
{ 
    return m_Parameters.begin(); 
}

/// \desc ptr to end of list data
ParameterList::iterator ParameterList::end() 
{ 
    return m_Parameters.end(); 
}

/// \desc const ptr to end of list data
ParameterList::const_iterator ParameterList::end() const 
{ 
    return m_Parameters.end(); 
}

/// \desc number of parameters contained in the list
ParameterList::size_type ParameterList::size() const 
{ 
    return m_Parameters.size(); 
}

/// \brief access param at aIndex in param list
/// \warn throws invalid_argument if aIndex is out of bounds of the array
ParameterList::parameter_ptr_type ParameterList::at(const size_type &aIndex) const
{
    if (aIndex >= size()) throw std::invalid_argument("index is out of range");

    return m_Parameters.at(aIndex);
}

/// \brief sugar for at method
ParameterList::parameter_ptr_type ParameterList::operator[](const size_type &aIndex) const 
{ 
    return at(aIndex); 
}

/// \desc Construct out of raw args (vec of strings)
ParameterList::ParameterList(const std::vector<std::string> &rargs)
{
    ParameterFactory factory;

    ///TODO add a reserve

    for (std::vector<std::string>::size_type i = 1; i < rargs.size(); ++i) 
    {
        const auto factoryOutput = factory.factoryMethod(rargs[i]);

        m_Parameters.push_back(std::get<0>(factoryOutput));
    }
}

/// \desc convenience ctor with paramlist that matches standard main() signature defined in C++ standards
ParameterList::ParameterList(int argc, char* argv[])
: ParameterList(std::vector<std::string>(argv, argv + argc))
{}

ParameterList::ParameterList(parameter_collection_type::const_iterator begin, parameter_collection_type::const_iterator end)
: m_Parameters(begin, end)
{}
