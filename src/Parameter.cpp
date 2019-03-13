#include <jfc/Parameter.h>

#include <iostream>

std::ostream &operator<< (std::ostream &s, const Parameter &a)
{
    return s << a.toString();
}
