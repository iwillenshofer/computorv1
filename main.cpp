/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:41:22 by iwillens          #+#    #+#             */
/*   Updated: 2023/10/07 14:41:24 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Equation.hpp"

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
        std::cout <<  e.what() << std::endl;
        return (1);
    }
    return (0);
}
