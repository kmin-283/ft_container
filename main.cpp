/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/19 17:01:54 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <list>
#include <vector>
// #include "List/List.hpp"
#include "Vector/vector.hpp"
#include <iostream>

int main()
{
    ft::vector<int> vec;
    std::vector<int> stdvec(4,100);
    stdvec.insert(--stdvec.end(),1);
    for (int i = 0; i < 5; i++)
    {
        std::cout << stdvec[i] << std::endl;
    }
    return (0);
}