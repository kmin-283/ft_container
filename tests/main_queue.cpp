/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:40:19 by kmin              #+#    #+#             */
/*   Updated: 2020/11/22 22:10:07 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Queue/queue.hpp"
#include <queue>
#include <fstream>

int main()
{
    std::ofstream out1("./result/my", std::ios_base::out);
    std::ofstream out2("./result/stl", std::ios_base::out);

    out1 << "myqueue testing" << std::endl;
    out1 << std::endl;

    ft::vector<int> myvector(2, 200); // vector with 2 elements

    ft::queue<int> myfirst; // empty queue

    ft::queue<int, ft::vector<int> > mythird; // empty queue using vector
    ft::queue<int, ft::vector<int> > myfourth(myvector);

    out1 << "size of first: " << myfirst.size() << '\n';
    out1 << "size of third: " << mythird.size() << '\n';
    out1 << "size of fourth: " << myfourth.size() << '\n';

    out1 << "=======================================================\n";

    out1 << "empty testing" << std::endl;
    out1 << std::endl;

    ft::queue<int> myqueue;
    int mysum (0);

    for (int i=1;i<=10;i++) myqueue.push(i);

    while (!myqueue.empty())
    {
        mysum += myqueue.front();
        myqueue.pop();
    }

    out1 << "total: " << mysum << '\n';
    out1 << "=======================================================\n";

    out1 << "front testing" << std::endl;
    out1 << std::endl;

    ft::queue<int> myqueue2;

    myqueue2.push(77);
    myqueue2.push(16);

    myqueue2.front() -= myqueue2.back();    // 77-16=61

    out1 << "myqueue.front() is now " << myqueue2.front() << '\n';


    out1 << "=======================================================\n";
    
    out1 << "back testing" << std::endl;
    out1 << std::endl;
    
    ft::queue<int> myqueue2_1;

    myqueue2_1.push(12);
    myqueue2_1.push(75);   // this is now the back

    myqueue2_1.back() -= myqueue2_1.front();

    out1 << "myqueue.back() is now " << myqueue2_1.back() << '\n';

    out1 << "=======================================================\n";

    out1 << "push testing" << std::endl;
    out1 << std::endl;

    ft::queue<int> myqueue3;

    for (int i=0;i<1000;++i)
    {
        myqueue3.push (i);
    }
    out1 << "myqueue contains: ";
    while (!myqueue3.empty())
    {
        out1 << ' ' << myqueue3.front();
        myqueue3.pop();
    }
    out1 << '\n';
    out1 << "myqueue is empty : ";
    while (!myqueue3.empty())
    {
        out1 << ' ' << myqueue3.front();
        myqueue3.pop();
    }
    out1 << '\n';
    
    out1 << "=======================================================\n";
    
    out1.close();







    out2 << "STLqueue testing" << std::endl;
    out2 << std::endl;

    std::vector<int> stlvector(2, 200); // vector with 2 elements

    std::queue<int> stlfirst; // empty queue

    std::queue<int, std::vector<int> > stlthird; // empty queue using vector
    std::queue<int, std::vector<int> > stlfourth(stlvector);

    out2 << "size of first: " << stlfirst.size() << '\n';
    out2 << "size of third: " << stlthird.size() << '\n';
    out2 << "size of fourth: " << stlfourth.size() << '\n';

    out2 << "=======================================================\n";


    out2 << "empty testing" << std::endl;
    out2 << std::endl;

    std::queue<int> stlqueue;
    int stlsum (0);

    for (int i=1;i<=10;i++) stlqueue.push(i);

    while (!stlqueue.empty())
    {
        stlsum += stlqueue.front();
        stlqueue.pop();
    }

    out2 << "total: " << stlsum << '\n';
    out2 << "=======================================================\n";

    out2 << "front testing" << std::endl;
    out2 << std::endl;

    std::queue<int> stlqueue2;

    stlqueue2.push(77);
    stlqueue2.push(16);

    stlqueue2.front() -= stlqueue2.back();    // 77-16=61

    out2 << "myqueue.front() is now " << stlqueue2.front() << '\n';


    out2 << "=======================================================\n";


    out2 << "back testing" << std::endl;
    out2 << std::endl;
    
    ft::queue<int> stlqueue2_1;

    stlqueue2_1.push(12);
    stlqueue2_1.push(75);   // this is now the back

    stlqueue2_1.back() -= stlqueue2_1.front();

    out2 << "myqueue.back() is now " << stlqueue2_1.back() << '\n';

    out2 << "=======================================================\n";


    
    out2 << "push testing" << std::endl;
    out2 << std::endl;

    std::queue<int> stlqueue3;

    std::cout << "Please enter some integers (enter 0 to end):\n";

    for (int i=0;i<1000;++i)
    {
        stlqueue3.push (i);
    }

    out2 << "myqueue contains: ";
    while (!stlqueue3.empty())
    {
        out2 << ' ' << stlqueue3.front();
        stlqueue3.pop();
    }
    out2 << '\n';
    out2 << "myqueue is empty : ";
    while (!stlqueue3.empty())
    {
        out2 << ' ' << stlqueue3.front();
        stlqueue3.pop();
    }
    out2 << '\n';

    out2 << "=======================================================\n";

    out2.close();

    return (0);
}