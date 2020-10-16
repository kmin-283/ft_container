/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/16 21:01:12 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "List/List.hpp"
// #include <iostream>

int main()
{
    ft::list<int> lst;
    if (lst.empty())
        std::cout << "lst is empty" << std::endl;
    std::cout << lst.front() << std::endl;
    lst.push_back(12);
    lst.push_back(122);
    lst.push_front(1);
    lst.push_front(1549);
    std::cout << lst.front() << std::endl;
    lst.push_back(13);
    lst.push_back(17);
    std::cout << lst.front() << std::endl;
    std::cout << lst.back() << std::endl;
    std::cout << "======================" << std::endl;
    if (lst.empty())
        std::cout << "lst is empty" << std::endl;
    for (ft::list<int>::iterator iter = lst.begin(); iter != lst.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;
    ft::list<int> lst2(lst);
    for (ft::list<int>::iterator iter = lst2.begin(); iter != lst2.end(); iter++)
         std::cout << *iter << std::endl;
    return (0);
}