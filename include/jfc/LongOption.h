#ifndef _JFC_COMMAND_TREE_LONG_OPTION_H_
#define _JFC_COMMAND_TREE_LONG_OPTION_H_

#include <jfc/Parameter.h>

/// \desc models a word param prefixed with "--". a longoption itself carries no value, but within the context of a parameter list, it is present in the list or it is not.
class LongOption : public Parameter 
{
    std::string m_Name;

protected:
    virtual std::string toString() const override;

    void setName(const std::string &aName);

public:
    std::string getName() const;

    LongOption(const std::string &aName);
};



#endif
