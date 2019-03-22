#ifndef _JFC_COMMAND_LOGGING_H
#define _JFC_COMMAND_LOGGING_H

void log(std::ostringstream &stringStream)
{
    //m_LoggingBehaviourCallback(stringStre am.str());
    std::cout << stringStream.str() << "\n";
}

template<typename First, typename ...Rest>
void log(std::ostringstream &stringStream, First &&first, Rest &&...rest)
{
    stringStream << first;
    log(stringStream, std::forward<Rest>(rest)...);
}

template<typename First, typename ...Rest>
void log(First &&first, Rest &&...rest)
{
    std::ostringstream stringStream;
    stringStream << first;
    
    log(stringStream, std::forward<Rest>(rest)...);
}

#endif
