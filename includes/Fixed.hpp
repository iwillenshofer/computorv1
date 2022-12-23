/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 11:21:34 by iwillens          #+#    #+#             */
/*   Updated: 2022/12/20 22:05:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>
# include <vector>
# include <limits>

class Fixed
{
	private:
	long long int					_fixed_point;
	static const int				_fraction = 18;

	public:
	Fixed(void);
	Fixed(int nb);
	Fixed(float nb);
	Fixed(std::string nb);
	Fixed(Fixed const &fixed);
	~Fixed(void);
	Fixed			&operator=(Fixed const &fixed);
	int				getRawBits(void) const;
	void			setRawBits(int const raw);
	int				getFractionSize(void) const;
	uint			getBitMask(void) const;
	float			toFloat(void) const;
	int				toInt(void) const;
	Fixed			operator+(Fixed const &fixed) const;
	Fixed			operator-(Fixed const &fixed) const;
	Fixed			operator*(Fixed const &fixed) const;
	Fixed			operator/(Fixed const &fixed) const;
	bool			operator>(Fixed const &fixed) const;
	bool			operator<(Fixed const &fixed) const;
	bool			operator>=(Fixed const &fixed) const;
	bool			operator<=(Fixed const &fixed) const;
	bool			operator==(Fixed const &fixed) const;
	bool			operator!=(Fixed const &fixed) const;
	Fixed			operator+(int const &fixed) const;
	Fixed			operator-(int const &fixed) const;
	Fixed			operator*(int const &fixed) const;
	Fixed			operator/(int const &fixed) const;
	bool			operator>(int const &fixed) const;
	bool			operator<(int const &fixed) const;
	bool			operator>=(int const &fixed) const;
	bool			operator<=(int const &fixed) const;
	bool			operator==(int const &fixed) const;
	bool			operator!=(int const &fixed) const;
	Fixed			operator+(float const &fixed) const;
	Fixed			operator-(float const &fixed) const;
	Fixed			operator*(float const &fixed) const;
	Fixed			operator/(float const &fixed) const;
	bool			operator>(float const &fixed) const;
	bool			operator<(float const &fixed) const;
	bool			operator>=(float const &fixed) const;
	bool			operator<=(float const &fixed) const;
	bool			operator==(float const &fixed) const;
	bool			operator!=(float const &fixed) const;
	Fixed			operator++();
	Fixed			operator++(int);
	Fixed			operator--();
	Fixed			operator--(int);
    bool 			operator!();


	static void _isvalidfloat(std::string &s);
	std::string _trim(const std::string &s);



	private:
	class InvalidCharacters : public std::exception {
		virtual const char* what() const throw();
	};

	class NotANumber : public std::exception {
		virtual const char* what() const throw();
	};

	class NumberOverflow : public std::exception {
		virtual const char* what() const throw();
	};

	class NumberUnderflow : public std::exception {
		virtual const char* what() const throw();
	};

};

Fixed				&min(Fixed &f1, Fixed &f2);
Fixed				&max(Fixed &f1, Fixed &f2);
Fixed const			&min(Fixed const &f1, Fixed const &f2);
Fixed const			&max(Fixed const &f1, Fixed const &f2);
std::ostream		&operator<<(std::ostream &o, Fixed const & i);

typedef struct	s_float
{
	uint	mantissa: 23;
	uint	exponent: 8;
	uint	signal: 1;
}				t_float;

union			u_float
{
	float	flt;
	t_float	div;
};

#endif
