#include "Term.hpp"

// Constructors
Term::Term()
{
	_coefficient = 0;
	_exponent = 0;
	_side = LEFT_SIDE_TERM;
	_signal = POSITIVE_TERM;
	std::cout << "\e[0;33mDefault Constructor called of Term\e[0m" << std::endl;
}

Term::Term(std::string s, char signal = POSITIVE_TERM, char side = LEFT_SIDE_TERM)
:_side(side), _signal(signal), _original(s)
{
	this->_parse(s);
//	std::cout << *this << std::endl;
}

Term::Term(const Term &copy)
{
	_coefficient = copy.getCoefficient();
	_exponent = copy.getExponent();
	_side = copy.getSide();
	_signal = copy.getSignal();
	_original = copy.getOriginal();
}

// Destructor
Term::~Term()
{
//	std::cout << "\e[0;31mDestructor called of Term\e[0m" << std::endl;
}


// Operators
Term & Term::operator=(const Term &assign)
{
	_coefficient = assign.getCoefficient();
	_exponent = assign.getExponent();
	_side = assign.getSide();
	_signal = assign.getSignal();
	_original = assign.getOriginal();
	return *this;
}


// Getters / Setters

Term::t_coef Term::getCoefficient() const
{
	return _coefficient;
}

Term::t_exp Term::getExponent() const
{
	return _exponent;
}

char Term::getSignal() const
{
	return _signal;
}

char Term::getSide() const
{
	return _side;
}

void Term::setSide(char c)
{
	this->_side = c;	
}

void Term::setSignal(char c)
{
	this->_signal = c;	
}

void Term::setCoefficient(Term::t_coef c)
{
	this->_coefficient = c;	
}

void Term::setExponent(Term::t_exp c)
{
	this->_exponent = c;	
}

std::string Term::getOriginal() const
{
	return _original;
}

std::string Term::toString(bool show_positive_sign) const
{
	std::string s;
	
	if (this->getSignal() == NEGATIVE_TERM || show_positive_sign)
		s += (this->getSignal() == POSITIVE_TERM ? "+ " : "- ");
	s += this->_to_string<t_coef>(this->getCoefficient());
	if (!(this->getExponent()) && !(this->getCoefficient()) && this->getOriginal() == "0" && this->getSide() == RIGHT_SIDE_TERM)
		return (s + " ");
	s += " * X ^ ";
	s += this->_to_string<t_exp>(this->getExponent()) + " ";
	return (s);
}

/*
** Parser
*/

void Term::__check_duplicates(std::string &s, char c)
{
	int count = 0;
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		if (*it == c) count++;
	if (count > 1)
		throw Term::TermInvalid();
}

void Term::__check_exponent(std::string &s)
{
	size_t pos = s.find('^');
	std::string exp;
	std::stringstream ss;
	t_exp number = 0;

	if (pos == 0 || pos == s.length() - 1)
		throw Term::TermInvalid();
	if (pos == std::string::npos && s.find('X') != std::string::npos)
		_exponent = 1;
	else if (pos == std::string::npos)
		_exponent = 0;
	else
	{
		exp = s.substr(++pos);
      	ss << exp;
		ss >> number;
		if (!(exp.length()) || ss.good() || (number == 0 && exp[0] != '0'))
			throw Term::TermInvalid();
		_exponent = number;
	}
}

void Term::__check_coefficient(std::string &s)
{
	size_t pos = s.find_first_of("*^");
	std::string coef;
	std::stringstream ss;
	t_coef number = 0;

	if (pos == 0 || pos == s.length() - 1)
		throw Term::TermInvalid();
	coef = s.substr(0, pos);
	number = coef;
	if (!(coef.length()) || (number == 0 && coef[0] != '0'))
		throw Term::TermInvalid();
	_coefficient = number;
}


void Term::__check_op_order(std::string &s)
{
	size_t exp = s.find('^');
	size_t multi = s.find('*');
	size_t var = s.find('X');
	bool bexp = s.find('^') != std::string::npos;
	bool bmulti = s.find('*') != std::string::npos;
	bool bvar = s.find('X') != std::string::npos;
	if (bexp && bmulti && bvar && !(exp > var && var > multi))
		throw Term::TermInvalid();
	else if (!bvar && (bmulti || bexp))
		throw Term::TermInvalid();
	else if (bvar && bmulti && (multi != var - 1))
		throw Term::TermInvalid();
	else if (bvar && bexp && (exp != var + 1))
		throw Term::TermInvalid();
}


void Term::_parse(std::string &s)
{
	__check_duplicates(s, 'X');
	__check_duplicates(s, '^');
	__check_duplicates(s, '*');
	__check_exponent(s);
	__check_coefficient(s);
	__check_op_order(s);

}

// Exceptions
const char * Term::TermInvalid::what() const throw()
{
	return "Invalid Term";
}

// <<
std::ostream& operator<<(std::ostream& o, const Term& term)
{
	o << "\e[0;35m";
    o << "[" << term.getOriginal() << "] ";
	o << "\e[0;32m";
	o << term.toString();
	o << "\e[0m";
	o << (term.getSide() == RIGHT_SIDE_TERM ? 'R' : 'L');
    return o;
}