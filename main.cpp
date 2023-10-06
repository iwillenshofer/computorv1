# include "Equation.hpp"
# include <vector>

void tests()
{
	std::vector<std::string>v;

//	v.push_back("5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0");
//	v.push_back("5 * X^0 + 4 * X^1 = 4 * X^0");
//	v.push_back("8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0");
//	v.push_back("5 * X^0 = 5 * X^0");
//	v.push_back("4 * X^0 = 8 * X^0");
//	v.push_back("5 * X^0 = 4 * X^0 + 7 * X^1");
//	v.push_back("5 * X^0 + 13 * X^1 + 3 * X^2 = 1 * X^0 + 1 * X^1");
//	v.push_back("6 * X^0 + 11 * X^1 + 5 * X^2 = 1 * X^0 + 1 * X^1");
//	v.push_back("5 * X^0 + 3 * X^1 + 3 * X^2 = 1 * X^0 + 0 * X^1");
//	v.push_back("3* x^2 - 4 *X^1 = 0");
//	v.push_back("3* x^2 - 4 *X^0 = 0");
//	v.push_back("3* x^2 = 0");
	v.push_back("0* x^2 + 3* x^1 = 0");
//	v.push_back("1* x^2 - 4 * x^1 + 6.25 * X^0 = 0");
//	v.push_back("6x2+7x2-3=0");

	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		try
		{ 
			std::cout << "Equation: " << *it << std::endl;
			Equation eq(*it);
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

}

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
