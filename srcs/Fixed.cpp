/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 11:21:31 by iwillens          #+#    #+#             */
/*   Updated: 2022/12/20 22:00:23 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
: _fixed_point(0)
{
	return ;
}

Fixed::Fixed(int nb)
: _fixed_point(nb * (1 << _fraction))
{
	return ;
}

Fixed::Fixed(float n)
: _fixed_point((int)(std::roundf(n * (1 << _fraction))))
{
	return ;
}

std::string Fixed::_trim(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;
    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;
    return std::string(it, rit.base());
}

void Fixed::_isvalidfloat(std::string &s)
{
	bool dot = false;
	bool e = false;


	if (!s.size() || (s.size() == 1 && 
		!(std::isdigit(s[0])) && !(s[0] == '-') && !(s[0] == '+') && !(s[0] == '.')))
		throw Fixed::NotANumber();
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (!(std::isdigit(*it)) && !(*it != 'e') && !(*it != '.')
			&& !(*it != '+') && !(*it != '-'))
			throw Fixed::NotANumber();
		if (*it == '.')
		{
			if (dot || (it + 1 == s.end()) || !(std::isdigit(*(it + 1))))
				throw Fixed::NotANumber();
			if (it + 1 == s.end())
				throw Fixed::NotANumber();
			dot = true;
		}
		else if (*it == 'e')
		{
			if (e || it == s.begin() || !(std::isdigit(*(it - 1))) || (it + 1 == s.end()))
				throw Fixed::NotANumber();
			if (!(std::isdigit(*(it + 1))) && !(*(it + 1) != '+')  && !(*(it + 1) != '+'))
				throw Fixed::NotANumber();
			dot = true;
			e = true;
		}
	}
}


Fixed::Fixed(std::string nb)
{
	float number;
	
	nb = _trim(nb);
	_isvalidfloat(nb);
	number = std::atof(nb.c_str());
	*this = Fixed(float(number));
}

Fixed::Fixed(Fixed const &fixed)
{
	*this = fixed;
}

Fixed::~Fixed()
{
	return ;
}

int				Fixed::getRawBits( void ) const
{
	return (this->_fixed_point);
}

void			Fixed::setRawBits( int const raw )
{
	this->_fixed_point = raw;
}

Fixed			&Fixed::operator=(Fixed const &fixed)
{
	this->setRawBits(fixed.getRawBits());
	return (*this);
}

float			Fixed::toFloat(void) const
{
	return ((float)(this->getRawBits()) / (1 << this->getFractionSize()));
}

int				Fixed::toInt(void) const
{
	return ((int)std::roundf(this->toFloat()));
}

int				Fixed::getFractionSize(void) const
{
	return (this->_fraction);
}

uint			Fixed::getBitMask(void) const
{
	return((1U << this->_fraction) - 1U);
}

Fixed			Fixed::operator+(Fixed const &fixed) const
{
	return (Fixed(this->toFloat() + fixed.toFloat()));
};

Fixed			Fixed::operator-(Fixed const &fixed) const
{
	return (Fixed(this->toFloat() - fixed.toFloat()));
};

Fixed			Fixed::operator*(Fixed const &fixed) const
{
	return (Fixed(this->toFloat() * fixed.toFloat()));
};

Fixed			Fixed::operator/(Fixed const &fixed) const
{
	return (Fixed(this->toFloat() / fixed.toFloat()));
};

bool			Fixed::operator>(Fixed const &fixed) const
{
	return (this->getRawBits() > fixed.getRawBits());
}

bool			Fixed::operator<(Fixed const &fixed) const
{
	return (this->getRawBits() < fixed.getRawBits());
}

bool			Fixed::operator>=(Fixed const &fixed) const
{
	return (this->getRawBits() >= fixed.getRawBits());
}

bool			Fixed::operator<=(Fixed const &fixed) const
{
	return (this->getRawBits() <= fixed.getRawBits());
}

bool			Fixed::operator==(Fixed const &fixed) const
{
	return (this->getRawBits() == fixed.getRawBits());
}

bool			Fixed::operator!=(Fixed const &fixed) const
{
	return (this->getRawBits() != fixed.getRawBits());
}

Fixed			Fixed::operator+(int const &fixed) const
{
	return (*this + Fixed(fixed));
};

Fixed			Fixed::operator-(int const &fixed) const
{
	return (*this - Fixed(fixed));
};

Fixed			Fixed::operator*(int const &fixed) const
{
	return (*this * Fixed(fixed));
};

Fixed			Fixed::operator/(int const &fixed) const
{
	return (*this / Fixed(fixed));
};

bool			Fixed::operator>(int const &fixed) const
{
	return (*this > Fixed(fixed));
}

bool			Fixed::operator<(int const &fixed) const
{
	return (*this < Fixed(fixed));
}

bool			Fixed::operator>=(int const &fixed) const
{
	return (*this >= Fixed(fixed));
}

bool			Fixed::operator<=(int const &fixed) const
{
	return (*this <= Fixed(fixed));
}

bool			Fixed::operator==(int const &fixed) const
{
	return (*this == Fixed(fixed));
}

bool			Fixed::operator!=(int const &fixed) const
{
	return (*this != Fixed(fixed));
}

Fixed			Fixed::operator+(float const &fixed) const
{
	return (*this + Fixed(fixed));
};

Fixed			Fixed::operator-(float const &fixed) const
{
	return (*this - Fixed(fixed));
};

Fixed			Fixed::operator*(float const &fixed) const
{
	return (*this * Fixed(fixed));
};

Fixed			Fixed::operator/(float const &fixed) const
{
	return (*this / Fixed(fixed));
};

bool			Fixed::operator>(float const &fixed) const
{
	return (*this > Fixed(fixed));
}

bool			Fixed::operator<(float const &fixed) const
{
	return (*this < Fixed(fixed));
}

bool			Fixed::operator>=(float const &fixed) const
{
	return (*this >= Fixed(fixed));
}

bool			Fixed::operator<=(float const &fixed) const
{
	return (*this <= Fixed(fixed));
}

bool			Fixed::operator==(float const &fixed) const
{
	return (*this == Fixed(fixed));
}

bool			Fixed::operator!=(float const &fixed) const
{
	return (*this != Fixed(fixed));
}

Fixed			Fixed::operator++(void)
{
	this->_fixed_point++;
	return(*this);
}

Fixed			Fixed::operator++(int)
{
	Fixed	fixed(*this);

	this->_fixed_point++;
	return(fixed);
}

Fixed			Fixed::operator--(void)
{
	this->_fixed_point--;
	return(*this);
}

Fixed			Fixed::operator--(int)
{
	Fixed	fixed(*this);

	this->_fixed_point--;
	return(fixed);
}

   bool Fixed::operator!()
    {
		return (*this == 0);
    }

Fixed			&min(Fixed &f1, Fixed &f2)
{
	return (f1 > f2 ? f2 : f1);
}

Fixed			&max(Fixed &f1, Fixed &f2)
{
	return (f1 > f2 ? f1 : f2);
}

Fixed const		&min(Fixed const &f1, Fixed const &f2)
{
	return (f1 > f2 ? f2 : f1);
}

Fixed const		&max(Fixed const &f1, Fixed const &f2)
{
	return (f1 > f2 ? f1 : f2);
}

std::ostream	&operator<<(std::ostream &o, Fixed const & i)
{
	return (o << i.toFloat());
}

const char * Fixed::InvalidCharacters::what() const throw()
{
	return "There are invalid characters in this number";
}

const char * Fixed::NotANumber::what() const throw()
{
	return "Not a Number";
}

const char * Fixed::NumberOverflow::what() const throw()
{
	return "Number Overflow";
}

const char * Fixed::NumberUnderflow::what() const throw()
{
	return "Number Underflow";
}
