/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/22 11:13:42 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "List/List.hpp"
// #include <iostream>
bool single_digit(const int &value) { return (value < 10); }
bool same_integral_part(double first, double second)
{
    return (int(first)==int(second));
}
// a predicate implemented as a class:
struct is_odd
{
    bool operator()(const int &value) { return (value % 2) == 1; }
};
int main()
{
    int myints[] = {1, 15, 15, 36, 7, 1, 17, 20, 39, 4, 1, 1, 15, 15, 15, 1};
    std::list<int> stdlist(myints, myints + 16);
    ft::list<int> mylist(myints, myints + 16);
    mylist.unique(same_integral_part);
    for (ft::list<int>::iterator iter = mylist.begin(); iter != mylist.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;    
    stdlist.unique(same_integral_part);
    for (std::list<int>::iterator iter = stdlist.begin(); iter != stdlist.end(); iter++)
        std::cout << *iter << std::endl;
    // mylist.remove(1);
    // std::cout << mylist.size() << std::endl;
    // std::cout << "======================" << std::endl;
    // ft::list<int> cplst(mylist);
    // cplst.remove_if(is_odd());
    // for (ft::list<int>::iterator iter = cplst.begin(); iter != cplst.end(); iter++)
    //     std::cout << *iter << std::endl;
    // std::cout << "======================" << std::endl;
    // // std::cout << "======================" << std::endl;
    // second.assign(first.begin(),first.end());
    // std::cout << second.size() << std::endl;
    // for (std::list<int>::iterator iter = second.begin(); iter != second.end(); iter++)
    //     std::cout << *iter << std::endl;
    return (0);
}