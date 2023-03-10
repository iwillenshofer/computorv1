#include "Equation.hpp"

const std::string Equation::_valid_chars = "0123456789 X+-=.^*";
const std::string Equation::_parser_chars = "=+-";


// Constructors
Equation::Equation()
:_original(""), _degree(-1)
{
	std::cout << "\e[0;33mDefault Constructor called of Equation\e[0m" << std::endl;
}

Equation::Equation(std::string s)
:_original(s), _degree(-1)
{
	this->_check_equation(this->_original);
	this->_parse(this->_original);
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
		if (pos != 0 || (s != _original) || s[0] == '=')
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

//clears highest degree with zero coef
void Equation::__remove_empty_coef(int i)
{
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end(); it++)
	{
		if (it->getSide() == LEFT_SIDE_TERM && it->getExponent() == i &&
			(it + 1)->getSide() == RIGHT_SIDE_TERM && it->getCoefficient() == 0.0)
			_terms.erase(it);
	}
}

//add equations for all degrees
void Equation::__insert_missing_term(int i)
{
	std::string term("0*X^");
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end(); it++)
	{
		if (it->getSide() == LEFT_SIDE_TERM && it->getExponent() > i)
		{
			term.push_back((i + '0'));
			_terms.insert(it, Term(term , POSITIVE_TERM, LEFT_SIDE_TERM));	
			return ;
		}
		else if (it->getExponent() == i)
			return ;
	}
}



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
	if (!(_terms.size()))
		_terms.push_back(Term("0", POSITIVE_TERM, LEFT_SIDE_TERM));
	_terms.push_back(Term("0", POSITIVE_TERM, RIGHT_SIDE_TERM));
}

bool Equation::__sort_fn(Term &t1, Term &t2)
{
    return (t1.getExponent() < t2.getExponent());
}

void Equation::_sort()
{
	std::sort(_terms.begin(), _terms.end() - 1, Equation::__sort_fn);
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
	__insert_missing_term(1);
	__insert_missing_term(0);
	__remove_empty_coef(2);
	__remove_empty_coef(1);
	std::cout << "Reduced Equation: ";
	_print();
}

void Equation::_check_degree(void)
{
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end(); it++)
	{
		if (it->getSide() == LEFT_SIDE_TERM && it->getExponent() > _degree && it->getCoefficient() != 0.0)
			_degree = it->getExponent();
	}
	std::cout << "Polynomial degree: ";
	if (_degree == -1)
		std::cout << "undefined";
	else
		std::cout << _degree;
	std::cout << std::endl;


	if (_degree >= 3)
		throw Equation::InvalidDegree();
}

void Equation::_check_multiple_solutions()
{
	for (std::vector<Term>::iterator it = _terms.begin(); it != _terms.end(); it++)
	{
		if (it->getSide() == LEFT_SIDE_TERM && it->getCoefficient() > 0.0)
			return;
	}
	throw Equation::MultipleSolutions();
}

Equation::t_coef Equation::__discriminant(t_coef a, t_coef b, t_coef c)
{
	t_coef res = (b * b) - (t_coef(4.0) * a * c);
	return (res);
}

void Equation::__baskhara(t_coef a, t_coef b, t_coef discriminant)
{
	t_coef x1;
	t_coef x2;
	t_coef x1b;
	t_coef x2b;

	if (discriminant > 0.0)
	{
		x1 = ((b * -1.0) - discriminant.sqrt()) / (a * 2.0);
		x2 = ((b * -1.0) + discriminant.sqrt()) / (a * 2.0);
		std::cout << x1 << std::endl << x2 << std::endl;
	}
	else if (discriminant == 0.0)
	{
		x1 = ((b * -1.0)) / (a * 2.0);
		std::cout << x1 << std::endl;
	}
	else
	{
		x1 = (b * -1.0  / (a * 2.0));
		x2 = discriminant.sqrt() / (a * 2.0);
		std::cout << x1 << " + " << x2 << "i" << std::endl;
		std::cout << x1 << " - " << x2 << "i" << std::endl;
	}
}

void Equation::_solve_quadratic(void)
{
	t_coef a = _terms[2].getSignedCoefficient();
	t_coef b = _terms[1].getSignedCoefficient();
	t_coef c = _terms[0].getSignedCoefficient();
	t_coef discriminant = __discriminant(a, b, c);

	if (discriminant > 0.0)
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
	else if (discriminant == 0.0)
		std::cout << "Discriminant is zero, the only solution is:" << std::endl;
	else
		std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
	__baskhara(a, b, discriminant);
}

void Equation::_solve_linear(void)
{
	Double res;

	res = _terms[0].getCoefficient() / _terms[1].getCoefficient();
	if (_terms[0].getSignal() == _terms[1].getSignal())
		res = res * -1.0;
	std::cout << "Solution:" << std::endl << res << std::endl;
}

void Equation::_solve(void)
{
	this->_check_degree();
	this->_check_multiple_solutions();
	if (_degree == 0)
		throw Equation::NoSolutions();
	else if (_degree == 1)
		_solve_linear();
	else if (_degree == 2)
		_solve_quadratic();
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
	return "The polynomial degree is strictly greater than 2, I can't solve.";
}

const char * Equation::MultipleSolutions::what() const throw()
{
	return "Any real number is a solution.";
}

const char * Equation::NoSolutions::what() const throw()
{
	return "There are no solutions for this equation.";
}