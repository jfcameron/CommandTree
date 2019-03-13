//cr me 2019

//
#include <jfc/Command.h>

// STL
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string> 
#include <tuple>
#include <vector>

/*// POSIX 
#include <sys/stat.h>

/// \todo move to filesystem_bridge.h?
namespace jfc
{
    /// \desc makes a directory in the current directory
    void mkdir(const std::string &aDirectory)
    {
        if (const int dir_err = ::mkdir(aDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); dir_err == -1) 
            throw std::runtime_error(std::string("Could not make directory \"").append(aDirectory).append("\"!"));
    }
    
    /// \desc prompts user for input, processes the raw input and produces an instance of a user-defined type for consumption.
    /// \param aMessage message to display before blocking for input
    /// \param aVisitor function wrapper that may modify (massage/sanitize) and or validate (throw if bad) the string retrieved from the user before returning an instance of T.
    template<class userdata_type>
    userdata_type promptUser(const std::string &aMessage, const std::function<userdata_type(std::string &aInput)> aVisitor)
    {
        std::cout << aMessage << std::endl;

        std::string input;
        std::cin >> input;

        return aVisitor(input);
    }
}*/
// ======================================================================================================================================================================================================

int main(int argc, char **argv)
{
    Command root("git",
        "a neato utility for managing source code",
        [](ParameterList params, const Command *const aParent)
        {
            return EXIT_SUCCESS;
        },
        {
            Command("status",
                "Show the working tree status",
                [](ParameterList aParams, const Command *const aParent)
                {
                    return EXIT_SUCCESS;
                },
                {
                }
            ),
            Command("show",
                "Show various types of objects",
                [](ParameterList aParams, const Command *const aParent)
                {
                    return EXIT_SUCCESS;
                },
                {
                }
            ),
            Command("log",
                "Show commit logs",
                [](ParameterList aParams, const Command *const aParent)
                {
                    return EXIT_SUCCESS;
                },
                {
                }
            ),
            Command("remote",
                "list all remotes by name",
                [](ParameterList aParams, const Command *const aParent)
                {
                    return EXIT_SUCCESS;
                },
                {
                    Command("get-url",
                        "print the url of a given remote",
                        [](ParameterList aParams, const Command *const aParent)
                        {
                            return EXIT_SUCCESS;
                        },
                        {
                        }
                    ),
                }
            ),
        }
    );

    root(argc, argv);

    return 0;
}
