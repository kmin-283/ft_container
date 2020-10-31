/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/29 16:25:56 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include "../List/List.hpp"

bool single_digit(const int &value) { return (value < 10); }
bool same_integral_part(double first, double second)
{
    return (int(first) == int(second));
}
// a predicate implemented as a class:
struct is_odd
{
    bool operator()(const int &value) { return (value % 2) == 1; }
};

bool mycomparison(double first, double second)
{
    return (int(first) < int(second));
}
int main()
{
    // ############ //
    // splice test  //
    // ############ //
    ft::list<int> mylist1, mylist2;
    ft::list<int>::iterator it;

    for (int i=1; i<=4; ++i)
        mylist1.push_back(i);      // mylist1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        mylist2.push_back(i*10);   // mylist2: 10 20 30
    it = mylist1.begin();
    ++it;
                            // points to 2
    mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
                                    // mylist2 (empty)
                                    // "it" still points to 2 (the 5th element)
    std::cout << "first splice = mylist1 contains:";
    for (ft::list<int>::iterator itt = mylist1.begin(); itt!=mylist1.end(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "first splice = mylist2 contains:";
    for (ft::list<int>::iterator itt = mylist2.begin(); itt!=mylist2.end(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';

    std::cout << "first splice = mylist1 contains reverse:";
    for (ft::list<int>::reverse_iterator itt = mylist1.rbegin(); itt!=mylist1.rend(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "first splice = mylist2 contains reverse:";
    for (ft::list<int>::reverse_iterator itt = mylist2.rbegin(); itt!=mylist2.rend(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';

    mylist2.splice (mylist2.begin(),mylist1, it);
                                    // mylist1: 1 10 20 30 3 4
                                    // mylist2: 2
                                    // "it" is now invalid.
    std::cout << "second splice = mylist1 contains:";
    for (ft::list<int>::iterator itt = mylist1.begin(); itt!=mylist1.end(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "second splice = mylist2 contains:";
    for (ft::list<int>::iterator itt = mylist2.begin(); itt!=mylist2.end(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "second splice = mylist1 contains reverse:";
    for (ft::list<int>::reverse_iterator itt = mylist1.rbegin(); itt!=mylist1.rend(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "second splice = mylist2 contains reverse:";
    for (ft::list<int>::reverse_iterator itt = mylist2.rbegin(); itt!=mylist2.rend(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    it = mylist1.begin();
    it++;
    it++;
    it++;           // "it" points now to 30
    mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
                                    // mylist1: 30 3 4 1 10 20

    std::cout << "third splice = mylist1 contains:";
    for (ft::list<int>::iterator itt = mylist1.begin(); itt!=mylist1.end(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "third splice = mylist2 contains:";
    for (ft::list<int>::iterator itt = mylist2.begin(); itt!=mylist2.end(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "third splice = mylist1 contains reverse:";
    for (ft::list<int>::reverse_iterator itt = mylist1.rbegin(); itt!=mylist1.rend(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "third splice = mylist2 contains reverse:";
    for (ft::list<int>::reverse_iterator itt = mylist2.rbegin(); itt!=mylist2.rend(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';

    // ############ //
    // merge test   //
    // ############ //
    ft::list<double> first, second;

    first.push_back(3.1);
    first.push_back(2.2);
    first.push_back(2.9);

    second.push_back(3.7);
    second.push_back(7.1);
    second.push_back(1.4);

    first.sort();
    second.sort();

    first.merge(second);
    std::cout << "first contains:";
    for (ft::list<double>::iterator it = first.begin(); it != first.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    // (second is now empty)
    std::cout << "second contains:";
    for (ft::list<double>::iterator it = second.begin(); it != second.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    second.push_back(2.1);

    first.merge(second, mycomparison);
    first.sort();
    std::cout << "first contains:";
    for (ft::list<double>::iterator it = first.begin(); it != first.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    std::cout << "second contains:";
    for (ft::list<double>::iterator it = second.begin(); it != second.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    // // ############ //
    // // reverse test   //
    // // ############ //
    first.reverse();
    std::cout << "reverse first contains:";
    for (ft::list<double>::iterator it = first.begin(); it != first.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    std::cout << "reverse first contains:";
    for (ft::list<double>::reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    while (1)
        ;
    return (0);
}