#ifndef _JFC_COMMAND_TREE_OPTION_LIST_H_
#define _JFC_COMMAND_TREE_OPTION_LIST_H_

#include <jfc/Parameter.h>

#include <vector>
#include <string>

/// \desc an option list is a parameter which represents an array of single char options. an option is present or is not. the form is e.g: "-a", "-ab", "-abc", etc.
class OptionList : public Parameter 
{
public:
    using option_collection_type = std::vector<char>;

private:
    option_collection_type m_Options;

protected:
    virtual std::string toString() const override;

public:
    option_collection_type::iterator begin();

    option_collection_type::const_iterator begin() const;

    option_collection_type::iterator end();

    option_collection_type::const_iterator end() const;

    option_collection_type::size_type size() const;

    OptionList(const option_collection_type &aOptions);
};

#endif
