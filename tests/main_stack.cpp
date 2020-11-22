/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:38 by kmin              #+#    #+#             */
/*   Updated: 2020/11/22 21:38:29 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../Vector/vector.hpp"
#include <vector>
#include <stack>
#include <fstream>
#include "../Stack/stack.hpp"

int main()
{
    std::ofstream out1("./result/my", std::ios_base::out);
    std::ofstream out2("./result/stl", std::ios_base::out);

    out1 << "mystack testing" << std::endl;
    out1 << std::endl;

    ft::vector<int> myvector(2, 200); // vector with 2 elements

    ft::stack<int> myfirst; // empty stack

    ft::stack<int, ft::vector<int> > mythird; // empty stack using vector
    ft::stack<int, ft::vector<int> > myfourth(myvector);

    out1 << "size of first: " << myfirst.size() << '\n';
    out1 << "size of third: " << mythird.size() << '\n';
    out1 << "size of fourth: " << myfourth.size() << '\n';

    out1 << "=======================================================\n";

    out1 << "empty testing" << std::endl;
    out1 << std::endl;

    ft::stack<int> mystack;
    int mysum(0);

    for (int i = 1; i <= 10; i++)
        mystack.push(i);

    while (!mystack.empty())
    {
        mysum += mystack.top();
        mystack.pop();
    }

    out1 << "total: " << mysum << '\n';
    out1 << "=======================================================\n";

    out1 << "top testing" << std::endl;
    out1 << std::endl;

    ft::stack<int> mystack2;

    mystack2.push(10);
    mystack2.push(20);

    mystack2.top() -= 5;

    out1 << "mystack.top() is now " << mystack2.top() << '\n';
    out1 << "=======================================================\n";
    
    out1 << "push testing" << std::endl;
    out1 << std::endl;

    ft::stack<int> mystack3;

    for (int i=0; i<1000; ++i) mystack3.push(i);

    out1 << "Popping out elements...";
    while (!mystack3.empty())
    {
        out1 << ' ' << mystack3.top();
        mystack3.pop();
    }
    out1 << '\n';
    
    out1 << "=======================================================\n";
    
    out1 << "pop testing" << std::endl;
    out1 << std::endl;



    ft::stack<int> mystack4;

    for (int i=0; i<5; ++i) mystack4.push(i);

    out1 << "Popping out elements...";
    while (!mystack4.empty())
    {
        out1 << ' ' << mystack4.top();
        mystack4.pop();
    }
    out1 << '\n';
    out1.close();







    out2 << "STLstack testing" << std::endl;
    out2 << std::endl;

    std::vector<int> stlvector(2, 200); // vector with 2 elements

    std::stack<int> stlfirst; // empty stack

    std::stack<int, std::vector<int> > stlthird; // empty stack using vector
    std::stack<int, std::vector<int> > stlfourth(stlvector);

    out2 << "size of first: " << stlfirst.size() << '\n';
    out2 << "size of third: " << stlthird.size() << '\n';
    out2 << "size of fourth: " << stlfourth.size() << '\n';

    out2 << "=======================================================\n";


    out2 << "empty testing" << std::endl;
    out2 << std::endl;

    std::stack<int> stlstack;
    int stlsum(0);

    for (int i = 1; i <= 10; i++)
        stlstack.push(i);

    while (!stlstack.empty())
    {
        stlsum += stlstack.top();
        stlstack.pop();
    }

    out2 << "total: " << stlsum << '\n';
    out2 << "=======================================================\n";

    out2 << "top testing" << std::endl;
    out2 << std::endl;

    std::stack<int> stlstack2;

    stlstack2.push(10);
    stlstack2.push(20);

    stlstack2.top() -= 5;

    out2 << "mystack.top() is now " << stlstack2.top() << '\n';

    out2 << "=======================================================\n";
    
    out2 << "push testing" << std::endl;
    out2 << std::endl;

    std::stack<int> stlstack3;

    for (int i=0; i<1000; ++i) stlstack3.push(i);

    out2 << "Popping out elements...";
    while (!stlstack3.empty())
    {
        out2 << ' ' << stlstack3.top();
        stlstack3.pop();
    }
    out2 << '\n';

    out2 << "=======================================================\n";
    
    out2 << "pop testing" << std::endl;
    out2 << std::endl;



    std::stack<int> stlstack4;

    for (int i=0; i<5; ++i) stlstack4.push(i);

    out2 << "Popping out elements...";
    while (!stlstack4.empty())
    {
        out2 << ' ' << stlstack4.top();
        stlstack4.pop();
    }
    out2 << '\n';
    out2.close();

    return (0);
}