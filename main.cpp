/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/23 14:00:30 by kmin             ###   ########.fr       */
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
    ft::list<int> mylist1, mylist2;
    ft::list<int>::iterator it;

  // set some initial values:
    for (int i=1; i<=4; ++i)
        mylist1.push_back(i);      // mylist1: 1 2 3 4
    for (ft::list<int>::iterator it = mylist1.begin(); it != mylist1.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;    
    mylist1.push_front(7);

    ft::list<int>::iterator itt = mylist1.begin();
    ++itt;
    std::cout << *itt << std::endl;
    mylist1.insert(itt, 7705);
    for (ft::list<int>::reverse_iterator it = mylist1.rbegin(); it != mylist1.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    // for (ft::list<int>::reverse_iterator it = mylist1.rbegin(); it != mylist1.rend(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;
    // std::cout << "=====================================" << std::endl;
    // for (int i=1; i<=3; ++i)
    //     mylist2.push_back(i*10);   // mylist2: 10 20 30
    // mylist2.push_front(70);    
    // for (ft::list<int>::iterator it = mylist2.begin(); it != mylist2.end(); ++it)
    //     std::cout << *it << " ";


    // std::cout << std::endl; 
    // it = mylist1.begin();
    // it++;
    // ++it;                         // points to 2
    // // mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
    //                         // mylist2 (empty)
    //                         // "it" still points to 2 (the 5th element)
    // mylist2.splice (mylist2.begin(),mylist1, it);
    //                         // mylist1: 1 10 20 30 3 4
    //                         // mylist2: 2
    //                         // "it" is now invalid.
    // it = mylist1.begin();
    // ++it;           // "it" points now to 30
    // ++it;
    // ++it;

    // // mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
    // std::cout << "mylist1 contains:";
    // for (it=mylist1.begin(); it != mylist1.end(); ++it)
    //     std::cout << ' ' << *it;
    // std::cout << '\n';

    // std::cout << "mylist2 contains:";
    // for (it = mylist2.begin(); it != mylist2.end(); ++it)
    //     std::cout << ' ' << *it;
    // std::cout << '\n';
    return (0);
}