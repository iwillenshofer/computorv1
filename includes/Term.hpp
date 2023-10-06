#ifndef TERM_HPP
# define TERM_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <iostream>
# include "Double.hpp"

# define LEFT_SIDE_TERM 0
# define RIGHT_SIDE_TERM 1
# define POSITIVE_TERM 0
# define NEGATIVE_TERM 1

class Term
{
	public:
		typedef Double t_coef;
		typedef long long int t_exp;

	private:
		Term();
		t_coef _coefficient;
		t_exp _exponent;
		char _side;
		char _signal;
		std::string _original;

	public:	

		// Constructors
		Term(std::string, char, char);
		Term(const Term &copy);
		
		// Destructor
		~Term();
		
		// Operators
		Term & operator=(const Term &);
		
		// Getters / Setters
		t_coef getSignedCoefficient() const;
		t_coef getCoefficient() const;
		t_exp getExponent() const;
		char getSide() const;
		char getSignal() const;
		std::string getOriginal() const;
		std::string toString(bool = true) const;
		void setSide(char);
		void setSignal(char);
		void setCoefficient(Term::t_coef);
		void setExponent(Term::t_exp);

		// Parser
		void __check_duplicates(std::string &s, char c);
		void __check_exponent(std::string &s);
		void __check_coefficient(std::string &s);
		void __check_op_order(std::string &s);
		void _parse(std::string &);

		template<typename T>
		std::string _to_string(T t) const
		{
			std::ostringstream ss;
			ss << t;
			return ss.str();
		}

		// Exceptions
		class TermInvalid : public std::exception {
			virtual const char* what() const throw();
		};
		
};

// << Operator Overload
std::ostream& operator<<(std::ostream&, const Term&);

#endif