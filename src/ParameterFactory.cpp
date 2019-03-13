#include <jfc/ParameterFactory.h>
#include <jfc/LongOptionWithValue.h>
#include <jfc/OptionList.h>
#include <jfc/Positional.h>

ParameterFactory::factory_method_output_type ParameterFactory::factoryMethod(const std::string &aRawArg)
{
    const auto size = aRawArg.size();

    if (!size) throw std::runtime_error("arg cannot be zero length");

    if (aRawArg.front() == '-') 
    {
        if (size == 1) throw std::runtime_error("optionlist prefix \"-\" must be followed by at least one additional character (representing an option)");

        if (aRawArg[1] == '-')
        {
            if (size == 2) throw std::runtime_error("long option prefex \"--\" must be followed by at least one additional character (representing a long option)");

            static const int PREFIX_LENGTH = 2; // "--"

            if (auto nameValueDelimiterIndex = aRawArg.find("="); nameValueDelimiterIndex != std::string::npos) //long option with value
            {
                if (nameValueDelimiterIndex != aRawArg.rfind("=")) throw std::runtime_error("a long option was provided with multiple name:value delimiters(\"=\"). a long option must have a name and may contain a single value, delimited by a single \"=\"");

                static const int DELIMITER_LENGTH = 1; // "-"

                std::string name  = aRawArg.substr(0 + PREFIX_LENGTH, nameValueDelimiterIndex - PREFIX_LENGTH);
                std::string value = aRawArg.substr(nameValueDelimiterIndex + DELIMITER_LENGTH);

                if (!name.size())  throw std::runtime_error("a long option with value's name must be at least a single characer long!");
                if (!value.size()) throw std::runtime_error("a long option with value's value must be at least a single character long!");

                return ParameterFactory::factory_method_output_type(new LongOptionWithValue(name, value), ConcreteType::LongOptionWithValue);
            }
            else
            {
                std::string name = aRawArg.substr(0 + PREFIX_LENGTH);

                if (!name.size()) throw std::runtime_error("a long option's name must be at least a single character long!");

                return ParameterFactory::factory_method_output_type(new LongOption(name), ConcreteType::LongOption);
            }
        }
        else
        {
            OptionList::option_collection_type options;

            for (OptionList::option_collection_type::size_type i = 1; i < aRawArg.size(); ++i) options.push_back(aRawArg[i]);

            return ParameterFactory::factory_method_output_type(new OptionList(options), ConcreteType::OptionList);
        }
    }
    else
    {
        return ParameterFactory::factory_method_output_type(new Positional(aRawArg), ConcreteType::Positional);
    }

    throw std::runtime_error("The commandline argument did not match the format of any parameter type that the parameterfactory can produce!");
}
