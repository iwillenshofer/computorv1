#include "Equation.hpp"

const std::string Equation::_valid_chars = "0123456789 X+-=.^*";
const std::string Equation::_parser_chars = "=+-";


// Constructors
Equation::Equation()
{
	std::cout << "\e[0;33mDefault Constructor called of Equation\e[0m" << std::endl;
}

Equation::Equation(std::string s)
:_original(s)
{
	std::cout << "Starting equation: " << this->_original << std::endl;
	this->_check_equation(this->_original);
	this->_parse(this->_original);
	this->_check_degree();
	this->_print();
	this->_switch_rightside();
	this->_sort();
	this->_reduce();
	this->_solve();
}

Equation::Equation(const Equation &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of Equation\e[0m" << std::endl;
}


// Destructor
Equation::~Equation()
{
	_terms.clear();
}


// Operators
Equation & Equation::operator=(const Equation &assign)
{
	(void) assign;
	return *this;
}

/*
** Checkers
*/

bool Equation::___is_valid_char(char &c) const
{
	for(std::string::const_iterator vit = Equation::_valid_chars.begin(); vit != Equation::_valid_chars.end(); vit++)
	{
		if (*vit == c)
			return (true);
	}
	return (false);
}

void Equation::__ck_invalid_characters(std::string &s)
{
	for(std::string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (*it == 'x') {*it = 'X';}
		if (!(this->___is_valid_char(*it)))
			throw Equation::InvalidCharacters();
	}
}

void Equation::__ck_double_equal(std::string &s) const
{
	int count = 0;
	for(std::string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (*it == '=')
			count++;
	}
	if (count != 1)
		throw Equation::EquationInvalid();
}

void Equation::__ck_double_spaces(std::string &s)
{
	std::size_t double_space = s.find(" ");
	while (double_space != std::string::npos)
	{
		s.erase(double_space, 1);
		double_space = s.find(" ");
	}
	if (!(s.length()))
		throw Equation::EquationInvalid();
}

void Equation::_check_equation(std::string &s)
{
	this->__ck_double_spaces(s);
	this->__ck_double_equal(s);
	this->__ck_invalid_characters(s);
}

void Equation::_check_degree(void)
{
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end(); it++)
	{
		if (it->getExponent() >= 3)
			throw Equation::InvalidDegree();
	}
}

/*
** Parse
*/

void Equation::__prs_add_term(std::string value, char token, char side)
{
	char signal = POSITIVE_TERM;
	
	if (token == '-')
		signal = NEGATIVE_TERM;
	try
	{
		_terms.push_back(Term(value, signal, side));
	}
	catch (std::exception &e)
	{
		this->_terms.clear();
		throw;
	}
}

void Equation::_parse(std::string s)
{
	std::size_t pos = 0;
	char token = '\0';
	std::string value = "";
	char side = LEFT_SIDE_TERM;

	while ((pos = s.find_first_of(_parser_chars)) != std::string::npos) {
		value = s.substr(0, pos);
		__prs_add_term(value, token, side);
		token = s[pos];
		if (token == '=')
		{
			side = RIGHT_SIDE_TERM;
			token = '\0';
		}
		s.erase(0, pos + 1);
	}
	__prs_add_term(s, token, side);
}

void Equation::_print(void) {
	bool right_side = false;
	bool show_pos_sign = false;
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end(); it++)
	{
		if (it->getSide() == RIGHT_SIDE_TERM && !right_side)
		{
			std::cout << "= ";
			right_side = true;
			show_pos_sign = false;
		}
		std::cout << it->toString(show_pos_sign);
		show_pos_sign = true;
	}
	std::cout << std::endl;
}

/*
** Steps
*/

void Equation::_switch_rightside(void)
{
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end(); it++)
	{
		if (it->getSide() == RIGHT_SIDE_TERM)
		{
			it->setSide(LEFT_SIDE_TERM);
			it->setSignal((it->getSignal() == NEGATIVE_TERM ? POSITIVE_TERM : NEGATIVE_TERM));
		}
	}
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end();)
	{
		if(it->getExponent() == 0 && it->getCoefficient() == 0) 
			it = _terms.erase(it);
		else 
			++it;
	}
	_terms.push_back(Term("0", POSITIVE_TERM, RIGHT_SIDE_TERM));
	_print();
}

bool Equation::__sort_fn(Term &t1, Term &t2)
{
    return (t1.getExponent() < t2.getExponent());
}

void Equation::_sort()
{
	std::sort(_terms.begin(), _terms.end() - 1, Equation::__sort_fn);
	_print();
}

bool Equation::__chk_equal_exp()
{
	int count = 0;
	
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end(); it++)
		if (it->getSide() == LEFT_SIDE_TERM) count++;
	if (count <= 1)
		return (false);
	for (int i = 0; i < count - 1; i++)
	{
		if (_terms[i].getSide() == LEFT_SIDE_TERM && _terms[i + 1].getSide() == LEFT_SIDE_TERM && _terms[i].getExponent() == _terms[i + 1].getExponent())
			return (true);
	}
	return (false);
}

void Equation::__sum_terms(Term &t1, Term &t2)
{
	if (t1.getSignal() == t2.getSignal())
		t1.setCoefficient(t1.getCoefficient() + t2.getCoefficient());
	else if (t1.getCoefficient() < t2.getCoefficient())
	{
		t1.setSignal(t2.getSignal());
		t1.setCoefficient(t2.getCoefficient() - t1.getCoefficient());
	}
	else
		t1.setCoefficient(t1.getCoefficient() - t2.getCoefficient());
}

void Equation::_reduce()
{
	while (__chk_equal_exp())
	{
		for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end() - 1; it++)
		{
			if (it->getExponent() == (it + 1)->getExponent())
			{
				__sum_terms(*it, *(it + 1));
				_terms.erase(it + 1);
				break;
			}
		}
	}
	_print();
	if (_terms.size() && _terms[_terms.size() - 2].getExponent() == 2 && _terms[_terms.size() - 2].getCoefficient() == 0)
	{
		if (_terms.size() == 2)
			_terms[_terms.size() - 2].setExponent(0);
		else
			_terms.erase(_terms.begin());
		_print();
	}	
}

void Equation::_solve()
{
	
}

// Errors
const char * Equation::EquationInvalid::what() const throw()
{
	return "This equation is invalid";
}

const char * Equation::InvalidCharacters::what() const throw()
{
	return "There are invalid characters in this equation";
}

const char * Equation::InvalidDegree::what() const throw()
{
	return "Equations of the third degree or higher cannot be solved";
}
