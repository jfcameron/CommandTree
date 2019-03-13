#include <jfc/Command.h>
#include <jfc/Positional.h>
#include <jfc/ParameterList.h>

#include <iostream>
#include <sstream>

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

    // handle help. works but i think its inappropriate thsi work is doen inline. sohuld be mapped
    if (m_ParameterList.containsOption('h'))
    {
        if (m_pParent)
        {
            std::cout 
                << m_Name << ":" << std::endl
                << m_Brief << std::endl
                << std::endl;

            if (m_Commands.size())
            {
                std::cout << "subcommands: " << std::endl;

                for (const auto command : m_Commands)
                {
                    std::cout << /*" " +*/ command.first << std::endl;
                }
            }

            return EXIT_SUCCESS;
        }
        else
        {
            const auto *const pRoot = [this] // Break out to member level (possibly static?) function: getRootCommand
            {
                const auto *pCommand = this;

                while (pCommand->m_pParent) pCommand = pCommand->m_pParent;

                return pCommand;
            }();

            std::function<void (const Command *, const int, int &, std::vector<std::pair<std::string, std::string>>&)> visitDescendants = [&](const Command *pCurrentCommand, const int depth, int &maxWidth, std::vector<std::pair<std::string, std::string>> &nodeNameDescriptionPairs) // wrap in member level (nonstatic) function: visitDescendants(pNode, maxDepth, pVisitorFunction) and depth (currentdepth) should be hidden from user.
            {   
                auto currentCommandName = pCurrentCommand->m_Name;

                currentCommandName.insert(currentCommandName.begin(), depth, ' ');

                nodeNameDescriptionPairs.push_back({currentCommandName, pCurrentCommand->m_Brief});

                const auto currentWidth = currentCommandName.size();

                maxWidth = currentWidth > maxWidth ? currentWidth : maxWidth;
                
                for (const auto command : pCurrentCommand->m_Commands) visitDescendants(&command.second, 1 + depth, maxWidth, nodeNameDescriptionPairs);
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
            
            std::stringstream helpHeaderStream; helpHeaderStream
            << std::string().append(maxLineWidth, '*') << std::endl
            
            << "author: " << "joeyjoey" << std::endl
            << "build date: " << "09/09/1999" << std::endl
            << "hash: " << "72382a74f55698ec4e7ed634545157ad6c9f51f4" << std::endl
            << "remote: " << "https://github.com/ThisIsATest/Blimblamblar" << std::endl
            << std::string().append(maxLineWidth, '*') << std::endl
            << "-h on root to display this message." << std::endl 
            << "-h after any subcommand to get more info on that specific subcommand." << std::endl
            << std::string().append(maxLineWidth, '*') << std::endl;

            std::cout << helpHeaderStream.str() << treestream.str() << std::endl;

            return EXIT_SUCCESS;
        }
    }

    return m_UserMain(m_ParameterList, this);
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

Command::Command(const std::string &aName, const std::string &aBrief,  const behaviour_type &aBehaviour, const std::vector<Command> &aCommands)
: m_Name(aName)
, m_Brief(aBrief)
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
