#ifndef _JFC_COMMAND_TREE_PARAMETERLIST_H
#define _JFC_COMMAND_TREE_PARAMETERLIST_H

#include <jfc/Parameter.h>
#include <jfc/LongOptionWithValue.h>

#include <memory>
#include <vector>
#include <iosfwd>

/// \desc abstraction for reading and manipulating commandline parameters
class ParameterList
{
public:
    using parameter_ptr_type = std::shared_ptr<Parameter>;
    using parameter_collection_type = std::vector<parameter_ptr_type>;

    using const_iterator = parameter_collection_type::const_iterator;
    using iterator = parameter_collection_type::iterator;
    using size_type = parameter_collection_type::size_type;

private:
    parameter_collection_type m_Parameters = {}; //<! representation of the parameter list strongly typed, in order

public:
    /// \desc returns a weak_ptr to a longoptionwithvalue with the provided name if such a longoption exists in the list. returns a null weak ptr if it does not
    std::weak_ptr<LongOptionWithValue> getLongOptionWithValue(const std::string &aLongOptionWithValue) const;

    /// \desc indicates whether or not the list contains a long option with the given name
    bool containsLongOption(const std::string &aLongOption) const;

    /// \desc indicates whether or not any option list in the parameter list contains the given option
    bool containsOption(const char aOption) const;

    /// \desc indicates whether or not the parameter list contains a positional with the given name
    bool containsPositional(const std::string &aPositional) const;

    /// \desc ptr to beginning of list data
    iterator begin();

    /// \desc const ptr to beginning of list data
    const_iterator begin() const;
    
    /// \desc ptr to end of list data
    iterator end();

    /// \desc const ptr to end of list data
    const_iterator end() const;

    /// \desc number of parameters contained in the list
    size_type size() const;

    /// \brief access param at aIndex in param list
    /// \warn throws invalid_argument if aIndex is out of bounds of the array
    parameter_ptr_type at(const size_type &aIndex) const;

    /// \brief sugar for at method
    parameter_ptr_type operator[](const size_type &aIndex) const;

    /// \desc Construct out of raw args (vec of strings)
    ParameterList(const std::vector<std::string> &rargs);

    /// \desc convenience ctor with paramlist that matches standard main() signature defined in C++ standards
    ParameterList(int argc, char* argv[]);

    ParameterList(parameter_collection_type::const_iterator begin, parameter_collection_type::const_iterator end);
};

#endif
