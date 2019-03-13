#ifndef _JFC_COMMAND_TREE_POSITIONAL_H_
#define _JFC_COMMAND_TREE_POSITIONAL_H_

#include <jfc/Parameter.h>

#include <string>

/// \desc models a parameter that is a single word.
class Positional : public Parameter
{
    std::string m_Name;

protected:
    virtual std::string toString() const override;

public:
    std::string getName();

    Positional(const std::string &aName);
};

#endif
 