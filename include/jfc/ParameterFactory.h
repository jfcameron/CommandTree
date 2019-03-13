#ifndef _COMMAND_TREE_PARAMETER_FACTORY_H_
#define _COMMAND_TREE_PARAMETER_FACTORY_H_

#include <jfc/Parameter.h>

#include <tuple>
#include <memory>
#include <string>

/// \desc used to construct parameters when the concrete type can only be determined at runtime
class ParameterFactory
{
public:
    enum class ConcreteType
    {
        LongOptionWithValue,
        LongOption,
        OptionList,
        Positional
    };

    using factory_method_output_type = std::tuple<std::shared_ptr<Parameter>, ConcreteType>;

    /// \desc returns bundle containing a shared ptr to a parameter and an enum indicating the concrete type instantiated. 
    /// the concrete type of the pointee depends on the nature of the raw argment provided
    /// \warn throws exceptions if the rawarg is badly formed
    /// \warn throws an exception if the provided raw argument does not match the format of any of the parameter types the factory can produce
    factory_method_output_type factoryMethod(const std::string &aRawArg);
};

#endif
