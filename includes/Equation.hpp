#ifndef EQUATION_HPP
# define EQUATION_HPP

# include <iostream>
# include <string>
# include <vector>
# include "Term.hpp"

class Equation
{
	private:
		typedef Term::t_coef	t_coef;
		std::string _original;
		int	_degree;
		static const std::string _valid_chars;
		static const std::string _parser_chars;
		std::vector<Term> _terms;

	public:
		// Constructors
		Equation();
		Equation(std::string s);
		Equation(const Equation &copy);
		
		// Destructor
		~Equation();
		
		// Operators
		Equation & operator=(const Equation &assign);



		/*
		** Checkers
		*/

		bool ___is_valid_char(char &c) const;

		void __ck_invalid_characters(std::string &s);

		void __ck_double_equal(std::string &s) const;

		void __ck_double_spaces(std::string &s);

		void _check_equation(std::string &s);


		/*
		** Parse
		*/

		void __prs_add_term(std::string value, char token, char side);

		void _parse(std::string s);

		void _print(void);

		std::size_t __prs_findnext(std::string &s, std::size_t pos) const;

		/*
		** Steps
		*/
		void __remove_empty_coef(int i);
		void __insert_missing_term(int i);
		void _switch_rightside(void);
		static bool __sort_fn(Term &t1, Term &t2);
		void _sort();
		bool __chk_equal_exp();
		void __sum_terms(Term &t1, Term &t2);
		void _reduce();




		/*
		** Solve
		*/
		void _check_degree(void);
		void _check_multiple_solutions(void);

		void __baskhara(t_coef a, t_coef b, t_coef discriminant);
		t_coef __discriminant(t_coef a, t_coef b, t_coef c);
		void _solve_quadratic(void);
		void _solve_linear(void);
		void _solve(void);

		// Exceptions
		class EquationInvalid : public std::exception {
			virtual const char* what() const throw();
		};
		class InvalidCharacters : public std::exception {
			virtual const char* what() const throw();
		};
		class InvalidDegree : public std::exception {
			virtual const char* what() const throw();
		};
		class MultipleSolutions : public std::exception {
			virtual const char* what() const throw();
		};

		class NoSolutions : public std::exception {
			virtual const char* what() const throw();
		};
};

#endif