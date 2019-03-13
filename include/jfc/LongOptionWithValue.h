#ifndef _JFC_COMMAND_TREE_LONGOPTIONWITHVALUE_H_
#define _JFC_COMMAND_TREE_LONGOPTIONWITHVALUE_H_

#include <jfc/LongOption.h>

/// \desc models a longoption that carries a value; think of it as a key:value pair. the form is --longoptionname=longoptionvalue
class LongOptionWithValue : public LongOption 
{
    std::string m_Value;

protected:
    virtual std::string toString() const override;

public:
    std::string getValue();

    LongOptionWithValue(const std::string &aName, const std::string &aValue);
};

#endif
