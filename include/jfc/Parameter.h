#ifndef _JFC_COMMAND_TREE_PARAMETER_H_
#define _JFC_COMMAND_TREE_PARAMETER_H_

#include <string>
#include <iosfwd>

/// \desc base class for all parameter types, used for collections
class Parameter
{
    friend std::ostream &operator<< (std::ostream &, const Parameter &);

protected:
    virtual std::string toString() const = 0;
};

#endif