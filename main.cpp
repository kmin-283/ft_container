/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/22 15:58:50 by kmin             ###   ########.fr       */
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
    int myints[] = {1, 2, 3, 4, 5, 6};
    int myints2[] = {11, 12, 13, 15, 16, 17};
    // std::list<int> stdlist(myints, myints + 16);
    ft::list<int> mylist(myints, myints + 6);
    ft::list<int> mylist2(myints2, myints2 + 6);
    std::list<int> stdlist(myints, myints + 6);
    std::list<int> stdlist2(myints2, myints2 + 6);
    
    // mylist.unique(same_integral_part);
    // for (ft::list<int>::iterator iter = mylist.begin(); iter != mylist.end(); iter++)
    //     std::cout << *iter << std::endl;
    // std::cout << "======================" << std::endl;    
    // stdlist.unique(same_integral_part);
    // for (std::list<int>::iterator iter = stdlist.begin(); iter != stdlist.end(); iter++)
    //     std::cout << *iter << std::endl;
    // std::cout << "======================" << std::endl;
    std::cout << "======================" << std::endl;
    ft::list<int>::iterator it2 = mylist2.begin();
    ++it2;
    std::list<int>::iterator it = stdlist2.begin();
    ++it;
    stdlist.splice(stdlist.begin(), stdlist2, it);
    for (std::list<int>::iterator iter = stdlist.begin(); iter != stdlist.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;

    for (std::list<int>::iterator iter = stdlist2.begin(); iter != stdlist2.end(); iter++)
        std::cout << *iter << std::endl;
    stdlist.splice(stdlist.begin(), stdlist2);
    std::cout << "======================" << std::endl;

    for (std::list<int>::iterator iter = stdlist.begin(); iter != stdlist.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;

    mylist.splice(mylist.begin(), mylist2, it2);
    for (ft::list<int>::iterator iter = mylist.begin(); iter != mylist.end(); iter++)
        std::cout << *iter << std::endl;
    std::cout << "======================" << std::endl;

    for (ft::list<int>::iterator iter = mylist2.begin(); iter != mylist2.end(); iter++)
        std::cout << *iter << std::endl;    
    std::cout << "======================" << std::endl;

    mylist.splice(mylist.begin(), mylist2);
    for (ft::list<int>::iterator iter = mylist.begin(); iter != mylist.end(); iter++)
        std::cout << *iter << std::endl; 
    std::cout << "======================" << std::endl;

    // double mydouble[] = {1.1, -3.79, 4.6,28.7,147.9,-75.4};
    // std::list<double> first(mydouble + 3, mydouble + 6);
    // std::list<double> second(mydouble, mydouble + 3);
    // first.merge(second);
    // for (std::list<double>::iterator iter = first.begin(); iter != first.end(); iter++)
    //     std::cout << *iter << std::endl;
    // second.clear();
    // std::cout << "======================" << std::endl;    
    // for (std::list<double>::iterator iter = first.begin(); iter != first.end(); iter++)
    //     std::cout << *iter << std::endl;


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