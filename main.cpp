/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/24 18:35:26 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "List/List.hpp"

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
    // ft::list<int> mylist1, mylist2;
    // ft::list<int>::iterator it;

    // for (int i=1; i<=4; ++i)
    //     mylist1.push_back(i);      // mylist1: 1 2 3 4

    // for (int i=1; i<=3; ++i)
    //     mylist2.push_back(i*10);   // mylist2: 10 20 30
    // it = mylist1.begin();
    // ++it;
    //                         // points to 2
    // mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
    //                                 // mylist2 (empty)
    //                                 // "it" still points to 2 (the 5th element)
    // std::cout << "mylist1 contains:";
    // for (ft::list<int>::iterator itt = mylist1.begin(); itt!=mylist1.end(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';
    // std::cout << "mylist2 contains:";
    // for (ft::list<int>::iterator itt = mylist2.begin(); itt!=mylist2.end(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';

    // std::cout << "mylist1 contains reverse:";
    // for (ft::list<int>::reverse_iterator itt = mylist1.rbegin(); itt!=mylist1.rend(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';
    // std::cout << "mylist2 contains reverse:";
    // for (ft::list<int>::reverse_iterator itt = mylist2.rbegin(); itt!=mylist2.rend(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';      
              
    // mylist2.splice (mylist2.begin(),mylist1, it);
    //                                 // mylist1: 1 10 20 30 3 4
    //                                 // mylist2: 2
    //                                 // "it" is now invalid.
    // std::cout << "mylist1 contains:";
    // for (ft::list<int>::iterator itt = mylist1.begin(); itt!=mylist1.end(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';
    // std::cout << "mylist2 contains:";
    // for (ft::list<int>::iterator itt = mylist2.begin(); itt!=mylist2.end(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';
    // std::cout << "mylist1 contains reverse:";
    // for (ft::list<int>::reverse_iterator itt = mylist1.rbegin(); itt!=mylist1.rend(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';
    // std::cout << "mylist2 contains reverse:";
    // for (ft::list<int>::reverse_iterator itt = mylist2.rbegin(); itt!=mylist2.rend(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';    
    // it = mylist1.begin();
    // it++;
    // it++;
    // it++;           // "it" points now to 30
    // mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
    //                                 // mylist1: 30 3 4 1 10 20
    // std::cout << "mylist1 contains:";
    
    // for (ft::list<int>::iterator itt = mylist1.begin(); itt!=mylist1.end(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';
    // std::cout << "mylist2 contains:";
    // for (ft::list<int>::iterator itt = mylist2.begin(); itt!=mylist2.end(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';
    // std::cout << "mylist1 contains reverse:";
    // for (ft::list<int>::reverse_iterator itt = mylist1.rbegin(); itt!=mylist1.rend(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n';
    // std::cout << "mylist2 contains reverse:";
    // for (ft::list<int>::reverse_iterator itt = mylist2.rbegin(); itt!=mylist2.rend(); ++itt)
    //     std::cout << ' ' << *itt;
    // std::cout << '\n'; 

    ft::list<int> s1,s2;
    for (int i=1; i<=4; ++i)
        s1.push_back(i);      // mylist1: 1 2 3 4
    for (int i=1; i<=3; ++i)
        s2.push_back(i*10);
    ft::list<int>::iterator it = s2.begin();
    ft::list<int>::iterator it2 = s2.begin();
    it2++;
    it2++;
    s1.splice(s1.begin(), s2, it, s2.end());
    for (ft::list<int>::iterator itt = s1.begin(); itt!=s1.end(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    std::cout << "mylist2 contains:";
    for (ft::list<int>::iterator itt = s2.begin(); itt!=s2.end(); ++itt)
        std::cout << ' ' << *itt;
    std::cout << '\n';
    return (0);
}