//cr me 2019

//
#include <jfc/Command.h>
#include <jfc/Positional.h>

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

#include <sstream>

std::string git_status_description = R"V0G0N(usage: git status [<options>] [--] <pathspec>...

    -v, --verbose         be verbose
    -s, --short           show status concisely
    -b, --branch          show branch information
    --porcelain[=<version>]
                          machine-readable output
    --long                show status in long format (default)
    -z, --null            terminate entries with NUL
    -u, --untracked-files[=<mode>]
                          show untracked files, optional modes: all, normal, no. (Default: all)
    --ignored             show ignored files
    --ignore-submodules[=<when>]
                          ignore changes to submodules, optional when: all, dirty, untracked. (Default: all)
    --column[=<style>]    list untracked files in columns)V0G0N"
;

std::string git_remote_description = R"V0G0N(usage: git remote [-v | --verbose]
   or: git remote add [-t <branch>] [-m <master>] [-f] [--tags | --no-tags] [--mirror=<fetch|push>] <name> <url>
   or: git remote rename <old> <new>
   or: git remote remove <name>
   or: git remote set-head <name> (-a | --auto | -d | --delete | <branch>)
   or: git remote [-v | --verbose] show [-n] <name>
   or: git remote prune [-n | --dry-run] <name>
   or: git remote [-v | --verbose] update [-p | --prune] [(<group> | <remote>)...]
   or: git remote set-branches [--add] <name> <branch>...
   or: git remote get-url [--push] [--all] <name>
   or: git remote set-url [--push] <name> <newurl> [<oldurl>]
   or: git remote set-url --add <name> <newurl>
   or: git remote set-url --delete <name> <url>

    -v, --verbose         be verbose; must be placed before a subcommand)V0G0N"
;

std::string git_show_description = R"V0G0N(git show -h
usage: git log [<options>] [<revision-range>] [[--] <path>...]
   or: git show [<options>] <object>...

    -q, --quiet           suppress diff output
    --source              show source
    --use-mailmap         Use mail map file
    --decorate[=...]      decorate options
    -L <n,m:file>         Process line range n,m in file, counting from 1)V0G0N"
;

class Palette
{
public:
    void applyColor(std::string &aString);
};

#include <jfc/Logging.h>

int main(int argc, char **argv)
{
    log("blar");

    Command root("git",
        "a neato utility for managing source code",
        []()
        {
            std::stringstream ss;
            ss
                << "author: " << "jfcameron <jf.cameron@gmail.com>" << std::endl
                << "build date: " << "Tue Mar 12 21:20:30 2019 -0400" << std::endl
                << "hash: " << "e44acd23bd3d1fcd844823d1a4d514b5d8bcd7e9" << std::endl
                << "remote: " << "git://github.com/jfcameron/CommandTree.git" << std::endl 
                << std::endl
                << "This is not git, this is just a demo usage of commandtree lib";

            return ss.str();
        }(),
        [](ParameterList params, const Command *const aParent)
        {
            return EXIT_SUCCESS;
        },
        {
            Command("status",
                "Show the working tree status", git_status_description,
                [](ParameterList aParams, const Command *const aParent)
                {
                    return EXIT_FAILURE;
                },
                {
                }
            ),
            Command("show",
                "Show various types of objects", git_show_description,
                [](ParameterList aParams, const Command *const aParent)
                {
                    return EXIT_SUCCESS;
                },
                {
                }
            ),
            Command("log",
                "Show commit logs",
                "usage is likethis and that and blahblah\ngoobagooba",
                [](ParameterList aParams, const Command *const aParent)
                {
                    return EXIT_SUCCESS;
                },
                {
                }
            ),
            Command("remote",
                "list all remotes by name", git_remote_description,
                [](ParameterList aParams, const Command *const aParent)
                {
                    return EXIT_SUCCESS;
                },
                {
                    Command("get-url",
                        "print the url of a given remote",
                        "usage is likethis and that and blahblah\ngoobagooba",
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

    return root(argc, argv);
}
