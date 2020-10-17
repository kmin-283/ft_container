/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/17 19:07:52 by kmin             ###   ########.fr       */
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
    if (lst.empty())
        std::cout << "lst is empty" << std::endl;
    for (ft::list<int>::iterator iter = lst.begin(); iter != lst.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;
    ft::list<int> lst2(lst);
    for (ft::list<int>::iterator iter = lst2.begin(); iter != lst2.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;
    ft::list<int> lst3(10);
    for (ft::list<int>::iterator iter = lst3.begin(); iter != lst3.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;
    ft::list<int> lst4(10, 5);
    for (ft::list<int>::iterator iter = lst4.begin(); iter != lst4.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;
    ft::list<int> lst5 = lst;
    for (ft::list<int>::iterator iter = lst5.begin(); iter != lst5.end(); iter++)
        std::cout << *iter << std::endl;
    lst5.pop_back();
    std::cout << "pop! " << lst5.size() << std::endl;
    std::cout << "======================" << std::endl;
    ft::list<int> stdlst(10, 10);
    for (ft::list<int>::iterator iter = stdlst.begin(); iter != stdlst.end(); iter++)
        std::cout << *iter << std::endl;
    stdlst.resize(5, 1);
    std::cout << "======================" << std::endl;
    for (ft::list<int>::iterator iter = stdlst.begin(); iter != stdlst.end(); iter++)
        std::cout << *iter << std::endl;
    stdlst.resize(10, 1);
    std::cout << "======================" << std::endl;
    for (ft::list<int>::iterator iter = stdlst.begin(); iter != stdlst.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;
    ft::list<int> lst6;
    std::cout << lst6.size() << std::endl;
    lst6.resize(7,100);
    std::cout << lst6.size() << std::endl;
    for (ft::list<int>::iterator iter = lst6.begin(); iter != lst6.end(); iter++)
        std::cout << *iter << std::endl;
    lst6.assign(10,200);
    std::cout << lst6.size() << std::endl;
    for (ft::list<int>::iterator iter = lst6.begin(); iter != lst6.end(); iter++)
        std::cout << *iter << std::endl;
    
    return (0);
}