#ifndef _JFC_COMMAND_TREE_COMMAND_H
#define _JFC_COMMAND_TREE_COMMAND_H

#include <jfc/ParameterList.h> //#include "ParameterList.h"

#include <string>
#include <map>
#include <functional>

/// \desc a unit of behaviour. May contain sub commands.
class Command
{
public:
    using command_collection_type = std::map<std::string, Command>;

    /// \desc user defined main is provided with a list of params and a pointer to the parent command
    using behaviour_type = std::function<int(ParameterList, const Command *const)>; 

private:
    /// \desc child commands
    std::map<std::string, Command> m_Commands;

    /// \desc name of this command
    std::string m_Name;

    /// \desc very short description of this command. should be a single, short sentence. should not include returns.
    std::string m_Brief;

    /// \desc user defined behaviour of this command
    behaviour_type m_UserMain;

    /// \desc parameters associated with this command
    ParameterList m_ParameterList = {{}}; // TOOD think about this. I dont like to default construct this. What does it model in a default state?: Nothing.it is a zombie

    /// \desc parent command of this command
    Command *m_pParent = nullptr;

    int main(const ParameterList &aParams, Command *const pParent);

public:
    std::string getName() const;

    /// \desc invokes command with typed parameters
    int operator()(const ParameterList &aParams, Command *const pParent);

    /// \desc invokes command with standard C++ commandline parameters. 
    /// Convenience overload, to allow the user to pass standard C++ commandline args (argc, argv) directly to a root command, without forcing user to manipulate the args themselves.
    int operator()(int argc, char* argv[]);

    Command(const std::string &aName, const std::string &aBrief,  const behaviour_type &aBehaviour, const std::vector<Command> &aCommands);
};

#endif
