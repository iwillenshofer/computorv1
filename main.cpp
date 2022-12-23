# include "Equation.hpp"

int main (int argc, char *argv[])
{
    try
    { 
        if (argc != 2)
            throw std::invalid_argument("Invalid number of arguments");
        Equation eq(argv[1]);
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return (1);
    }
    return (0);
}
