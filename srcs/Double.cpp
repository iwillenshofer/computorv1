/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Double.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 11:21:31 by iwillens          #+#    #+#             */
/*   Updated: 2023/10/07 15:25:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Double.hpp"

Double::Double(void)
: _dbl(0)
{
	return ;
}

Double::Double(int n)
: _dbl(static_cast<type>(n))
{
	return ;
}

Double::Double(float n)
: _dbl(static_cast<type>(n))
{
	return ;
}

Double::Double(type n)
: _dbl(n)
{
	return ;
}

std::string Double::_trim(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;
    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;
    return std::string(it, rit.base());
}

void Double::_isvalidfloat(std::string &s)
{
	bool dot = false;
	bool e = false;


	if (!s.size() || (s.size() == 1 && 
		!(std::isdigit(s[0])) && !(s[0] == '-') && !(s[0] == '+') && !(s[0] == '.')))
		throw Double::NotANumber();
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (!(std::isdigit(*it)) && !(*it != 'e') && !(*it != '.')
			&& !(*it != '+') && !(*it != '-'))
			throw Double::NotANumber();
		if (*it == '.')
		{
			if (dot || (it + 1 == s.end()) || !(std::isdigit(*(it + 1))))
				throw Double::NotANumber();
			if (it + 1 == s.end())
				throw Double::NotANumber();
			dot = true;
		}
		else if (*it == 'e')
		{
			if (e || it == s.begin() || !(std::isdigit(*(it - 1))) || (it + 1 == s.end()))
				throw Double::NotANumber();
			if (!(std::isdigit(*(it + 1))) && !(*(it + 1) != '+')  && !(*(it + 1) != '+'))
				throw Double::NotANumber();
			dot = true;
			e = true;
		}
	}
}

/*
** converts string to double
*/
Double::type Double::_str_to_double(std::string &nb)
{
	type number;
	char *endp;
	const char *s = nb.c_str();

	number = strtod(s, &endp);
	if (s != endp && *endp =='\0')
	{
		if (number == std::numeric_limits<type>::infinity())
			throw Double::NumberOverflow();
		else if (number == -std::numeric_limits<type>::infinity())
			throw Double::NumberUnderflow();
		return (number);
	}
	throw Double::NotANumber();
}

Double::Double(std::string nb)
{
	type number;
	
	nb = _trim(nb);
	_isvalidfloat(nb);
	number = _str_to_double(nb);
	*this = Double(number);
}

Double::Double(Double const &dbl)
{
	*this = dbl;
}

Double::~Double()
{
	return ;
}

Double			&Double::operator=(Double const &dbl)
{
	this->_dbl = dbl._dbl;
	return (*this);
}

void Double::_check_overflow(type &v) const
{
	if ((v != v) ||
		v == std::numeric_limits<type>::max() ||
		v == std::numeric_limits<type>::min() ||
		v == -std::numeric_limits<type>::infinity() ||
		v == std::numeric_limits<type>::infinity())
		throw Double::NumberOverflow();
}

Double			Double::operator+(Double const &dbl) const
{
	type ret = this->_dbl + dbl._dbl;
	_check_overflow(ret);
	return (ret);
};

Double			Double::operator-(Double const &dbl) const
{
	type ret = this->_dbl - dbl._dbl;
	_check_overflow(ret);
	return (ret);
};

Double			Double::operator*(Double const &dbl) const
{
	type ret = this->_dbl * dbl._dbl;
	_check_overflow(ret);
	return (ret);
};

Double			Double::operator/(Double const &dbl) const
{
	type ret = this->_dbl / dbl._dbl;
	_check_overflow(ret);
	return (ret);
};

bool			Double::operator>(Double const &dbl) const
{
	return (this->_dbl > dbl._dbl);
}

bool			Double::operator<(Double const &dbl) const
{
	return (this->_dbl < dbl._dbl);
}

bool			Double::operator>=(Double const &dbl) const
{
	return (this->_dbl >= dbl._dbl);
}

bool			Double::operator<=(Double const &dbl) const
{
	return (this->_dbl <= dbl._dbl);
}

bool			Double::operator==(Double const &dbl) const
{
	return (this->_dbl == dbl._dbl);
}

bool			Double::operator!=(Double const &dbl) const
{
	return (this->_dbl != dbl._dbl);
}

Double			Double::operator+(int const &dbl) const
{
	return (*this + Double(dbl));
};

Double			Double::operator-(int const &dbl) const
{
	return (*this - Double(dbl));
};

Double			Double::operator*(int const &dbl) const
{
	return (*this * Double(dbl));
};

Double			Double::operator/(int const &dbl) const
{
	return (*this / Double(dbl));
};

bool			Double::operator>(int const &dbl) const
{
	return (*this > Double(dbl));
}

bool			Double::operator<(int const &dbl) const
{
	return (*this < Double(dbl));
}

bool			Double::operator>=(int const &dbl) const
{
	return (*this >= Double(dbl));
}

bool			Double::operator<=(int const &dbl) const
{
	return (*this <= Double(dbl));
}

bool			Double::operator==(int const &dbl) const
{
	return (*this == Double(dbl));
}

bool			Double::operator!=(int const &dbl) const
{
	return (*this != Double(dbl));
}

Double			Double::operator+(float const &dbl) const
{
	return (*this + Double(dbl));
};

Double			Double::operator-(float const &dbl) const
{
	return (*this - Double(dbl));
};

Double			Double::operator*(float const &dbl) const
{
	return (*this * Double(dbl));
};

Double			Double::operator/(float const &dbl) const
{
	return (*this / Double(dbl));
};

bool			Double::operator>(float const &dbl) const
{
	return (*this > Double(dbl));
}

bool			Double::operator<(float const &dbl) const
{
	return (*this < Double(dbl));
}

bool			Double::operator>=(float const &dbl) const
{
	return (*this >= Double(dbl));
}

bool			Double::operator<=(float const &dbl) const
{
	return (*this <= Double(dbl));
}

bool			Double::operator==(float const &dbl) const
{
	return (*this == Double(dbl));
}

bool			Double::operator!=(float const &dbl) const
{
	return (*this != Double(dbl));
}


Double			Double::operator+(type const &dbl) const
{
	return (*this + Double(dbl));
};

Double			Double::operator-(type const &dbl) const
{
	return (*this - Double(dbl));
};

Double			Double::operator*(type const &dbl) const
{
	return (*this * Double(dbl));
};

Double			Double::operator/(type const &dbl) const
{
	return (*this / Double(dbl));
};

bool			Double::operator>(type const &dbl) const
{
	return (*this > Double(dbl));
}

bool			Double::operator<(type const &dbl) const
{
	return (*this < Double(dbl));
}

bool			Double::operator>=(type const &dbl) const
{
	return (*this >= Double(dbl));
}

bool			Double::operator<=(type const &dbl) const
{
	return (*this <= Double(dbl));
}

bool			Double::operator==(type const &dbl) const
{
	return (*this == Double(dbl));
}

bool			Double::operator!=(type const &dbl) const
{
	return (*this != Double(dbl));
}

Double			Double::operator+(std::string const &dbl) const
{
	return (*this + Double(dbl));
};

Double			Double::operator-(std::string const &dbl) const
{
	return (*this - Double(dbl));
};

Double			Double::operator*(std::string const &dbl) const
{
	return (*this * Double(dbl));
};

Double			Double::operator/(std::string const &dbl) const
{
	return (*this / Double(dbl));
};

bool			Double::operator>(std::string const &dbl) const
{
	return (*this > Double(dbl));
}

bool			Double::operator<(std::string const &dbl) const
{
	return (*this < Double(dbl));
}

bool			Double::operator>=(std::string const &dbl) const
{
	return (*this >= Double(dbl));
}

bool			Double::operator<=(std::string const &dbl) const
{
	return (*this <= Double(dbl));
}

bool			Double::operator==(std::string const &dbl) const
{
	return (*this == Double(dbl));
}

bool			Double::operator!=(std::string const &dbl) const
{
	return (*this != Double(dbl));
}


Double			Double::operator++(void)
{
	this->_dbl++;
	return(*this);
}

Double			Double::operator++(int)
{
	Double	dbl(*this);

	this->_dbl++;
	return(dbl);
}

Double			Double::operator--(void)
{
	this->_dbl--;
	return(*this);
}

Double			Double::operator--(int)
{
	Double	dbl(*this);

	this->_dbl--;
	return(dbl);
}

bool Double::operator!()
{
	return (*this == 0);
}

Double::const_type &Double::value() const
{
	return (this->_dbl);
}

Double Double::sqrt()
{
	type precision = 0.00000001;
	type sqrt = 1.0;
	type dbl = std::abs(_dbl);

	if (dbl == 0.0)
		return (0.0);
	while (std::abs(dbl / sqrt - sqrt) > precision)
		sqrt = (sqrt + dbl / sqrt) / 2.0;
	return (sqrt);
}

std::ostream	&operator<<(std::ostream &o, Double const & i)
{
    std::stringstream ss;
    std::string str;
	size_t dot;

	o << str;

    ss << std::fixed << std::setprecision(6) << i.value();
	str = ss.str();
	dot = str.find('.');
	if (dot != std::string::npos)
	{
		while (*(str.rbegin()) == '0')
			str.pop_back();
		if (*(str.rbegin()) == '.')
			str.pop_back();
	}
	if (str == "-0")
		return (o << "0");	
	return (o << str);
}

const char * Double::InvalidCharacters::what() const throw()
{
	return "There are invalid characters in this number";
}

const char * Double::NotANumber::what() const throw()
{
	return "Not a Number";
}

const char * Double::NumberOverflow::what() const throw()
{
	return "Number Overflow";
}

const char * Double::NumberUnderflow::what() const throw()
{
	return "Number Underflow";
}
