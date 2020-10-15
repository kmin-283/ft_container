/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/12 18:09:29 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "List/List.hpp"
#include <iostream>

int main()
{
    ft::list<int> lst;
    std::list<int> lst2;
    lst.push_back(1);
    std::cout << lst.front() << std::endl;
    lst.push_back(12);
    std::cout << lst.front() << std::endl;
    lst.push_back(13);
    lst.push_back(17);
    std::cout << lst.front() << std::endl;
    std::cout << lst.back() << std::endl;
    
    lst2.push_back(1);
    std::cout << lst2.front() << std::endl;
    lst2.push_back(12);
    std::cout << lst2.front() << std::endl;
    lst2.push_back(13);
    std::cout << lst2.front() << std::endl;
    std::cout << lst2.back() << std::endl;
    

    return (0);
}