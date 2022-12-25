/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Double.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 11:21:34 by iwillens          #+#    #+#             */
/*   Updated: 2022/12/20 22:05:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_HPP
# define DOUBLE_HPP

# include <iostream>
# include <limits>
# include <cstdlib>

class Double
{
	private:
	typedef double					type;
	typedef const double			const_type;

	type							_dbl;

	public:
	Double(void);
	Double(int nb);
	Double(float nb);
	Double(type n);
	Double(std::string nb);
	Double(Double const &dbl);
	~Double(void);
	Double			&operator=(Double const &dbl);
	Double			operator+(Double const &dbl) const;
	Double			operator-(Double const &dbl) const;
	Double			operator*(Double const &dbl) const;
	Double			operator/(Double const &dbl) const;
	bool			operator>(Double const &dbl) const;
	bool			operator<(Double const &dbl) const;
	bool			operator>=(Double const &dbl) const;
	bool			operator<=(Double const &dbl) const;
	bool			operator==(Double const &dbl) const;
	bool			operator!=(Double const &dbl) const;
	Double			operator+(int const &dbl) const;
	Double			operator-(int const &dbl) const;
	Double			operator*(int const &dbl) const;
	Double			operator/(int const &dbl) const;
	bool			operator>(int const &dbl) const;
	bool			operator<(int const &dbl) const;
	bool			operator>=(int const &dbl) const;
	bool			operator<=(int const &dbl) const;
	bool			operator==(int const &dbl) const;
	bool			operator!=(int const &dbl) const;
	Double			operator+(float const &dbl) const;
	Double			operator-(float const &dbl) const;
	Double			operator*(float const &dbl) const;
	Double			operator/(float const &dbl) const;
	bool			operator>(float const &dbl) const;
	bool			operator<(float const &dbl) const;
	bool			operator>=(float const &dbl) const;
	bool			operator<=(float const &dbl) const;
	bool			operator==(float const &dbl) const;
	bool			operator!=(float const &dbl) const;
	Double			operator+(type const &dbl) const;
	Double			operator-(type const &dbl) const;
	Double			operator*(type const &dbl) const;
	Double			operator/(type const &dbl) const;
	bool			operator>(type const &dbl) const;
	bool			operator<(type const &dbl) const;
	bool			operator>=(type const &dbl) const;
	bool			operator<=(type const &dbl) const;
	bool			operator==(type const &dbl) const;
	bool			operator!=(type const &dbl) const;
	Double			operator+(std::string const &dbl) const;
	Double			operator-(std::string const &dbl) const;
	Double			operator*(std::string const &dbl) const;
	Double			operator/(std::string const &dbl) const;
	bool			operator>(std::string const &dbl) const;
	bool			operator<(std::string const &dbl) const;
	bool			operator>=(std::string const &dbl) const;
	bool			operator<=(std::string const &dbl) const;
	bool			operator==(std::string const &dbl) const;
	bool			operator!=(std::string const &dbl) const;




	Double			operator++();
	Double			operator++(int);
	Double			operator--();
	Double			operator--(int);
    bool 			operator!();


	static void _isvalidfloat(std::string &s);
	std::string _trim(const std::string &s);
	type _str_to_double(std::string &nb);
	const_type &value() const;
	void _check_overflow(type &v) const;
	Double sqrt();

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

Double				&min(Double &f1, Double &f2);
Double				&max(Double &f1, Double &f2);
Double const			&min(Double const &f1, Double const &f2);
Double const			&max(Double const &f1, Double const &f2);
std::ostream		&operator<<(std::ostream &o, Double const & i);

#endif
