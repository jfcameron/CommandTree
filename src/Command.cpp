#include <jfc/Command.h>
#include <jfc/Positional.h>
#include <jfc/ParameterList.h>

#include <iostream>
#include <sstream>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

/*#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"*/

/*std::string ApplyColor(std::string &aColor, std::string &aString)
{
    aString.insert(0, "\x1B[31m").insert(aString.size(), "\x1B[0m");

    return aString;
}
std::string ApplyColor(std::string &&aColor, std::string &&aString)
{
    return ApplyColor(aColor, aString);
}

std::string Red(std::string &aString)
{
    ApplyColor(std::string(RED), aString);
}
std::string Red(std::string &&aString)
{
    Red(aString);
}*/


void Command::printHelp()
{
    const auto *const pRoot = this;

    std::function<void (const Command *, const int, int &, std::vector<std::pair<std::string, std::string>>&)> visitDescendants = [&](const Command *pCurrentCommand, int depth, int &maxWidth, std::vector<std::pair<std::string, std::string>> &nodeNameDescriptionPairs) // wrap in member level (nonstatic) function: visitDescendants(pNode, maxDepth, pVisitorFunction) and depth (currentdepth) should be hidden from user.
    {   
        auto currentCommandName = pCurrentCommand->m_Name;

        currentCommandName.insert(currentCommandName.begin(), depth, ' ');

        nodeNameDescriptionPairs.push_back({currentCommandName, pCurrentCommand->m_Brief});

        depth++;

        const auto currentWidth = currentCommandName.size();

        maxWidth = currentWidth > maxWidth ? currentWidth : maxWidth;
        
        for (const auto command : pCurrentCommand->m_Commands) visitDescendants(&command.second, depth, maxWidth, nodeNameDescriptionPairs);
    };

    //these alloc proves beyond user experience why this work must be wrapped.
    int maxwidth = 0; 

    std::vector<std::pair<std::string, std::string>> nodeNameDescriptionPairs;

    visitDescendants(pRoot, 0, maxwidth, nodeNameDescriptionPairs); //todo: hide the second param, this should be wrapped. user has no buisness assigning "the current depth" (the initial depth will never not be zero)

    std::string::size_type maxLineWidth = 0;

    std::stringstream treestream;

    for (const auto &nodeNameDescription : nodeNameDescriptionPairs)
    {
        std::string buffer = nodeNameDescription.first;

        buffer += " ";

        for (int i = 0; i < (maxwidth - static_cast<int>(nodeNameDescription.first.size())); ++i) buffer += " ";

        buffer += nodeNameDescription.second;

        treestream << buffer << std::endl;

        maxLineWidth = buffer.size() > maxLineWidth ? buffer.size() : maxLineWidth;
    }
    
    std::cout << m_Description;

    if (nodeNameDescriptionPairs.size()) 
    {
        std::cout << std::endl << std::endl << treestream.str();
    }

    std::cout << std::endl;
}

void Command::onError(const ParameterList &aParams, Command *const pParent)
{
    std::cout << /*Red(*/"error:"/*)*/ << " unrecognized argument[s] for " + m_Name << std::endl;

    printHelp();
}

int Command::main(const ParameterList &aParams, Command *const pParent)
{
    m_pParent = pParent;
    m_ParameterList = aParams;

    for (ParameterList::size_type i = 0; i < aParams.size(); ++i)
    {
        const auto &param = aParams[i];

        if (const auto pPositional = std::dynamic_pointer_cast<Positional>(param))
        {
            if (auto command = m_Commands.find(pPositional->getName()); command != m_Commands.end())
            {
                auto subarrayParams = ParameterList(aParams.begin() + i + 1, aParams.end());

                m_ParameterList = ParameterList(aParams.begin(), aParams.begin() + i);

                return command->second(subarrayParams, this);
            }
        }
    }

    if (m_ParameterList.containsOption('h'))
    {
        printHelp();

        return EXIT_SUCCESS;
    }

    auto returnValue = m_UserMain(m_ParameterList, this);

    if (returnValue == EXIT_FAILURE) onError(aParams, pParent);

    return returnValue;
}

std::string Command::getName() const
{
    return m_Name;
}

int Command::operator()(const ParameterList &aParams, Command *const pParent)
{
    return main(aParams, pParent);
}

int Command::operator()(int argc, char* argv[])
{
    return (*this)(ParameterList(argc, argv), nullptr);
}

Command::Command(const std::string &aName, const std::string &aBrief, const std::string &aDescription,  const behaviour_type &aBehaviour, const std::vector<Command> &aCommands)
: m_Name(aName)
, m_Brief(aBrief)
, m_Description(aDescription)
, m_UserMain(aBehaviour)
, m_Commands([&aCommands]()
{
    std::map<std::string, Command> buffer;

    for (const auto &command : aCommands)
    {
        buffer.insert({command.m_Name, command});
    }

    return buffer;
}())
{}
