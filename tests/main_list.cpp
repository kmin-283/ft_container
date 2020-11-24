/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/11/25 01:48:02 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "../List/List.hpp"

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }


bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
    bool operator() (const int& value) { return (value%2)==1; }
};

bool same_integral_part (double first, double second)
{ return ( (int)first==(int)second ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (std::fabs(first-second)<5.0); }
};

bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

int main()
{
    std::ofstream out1("./result/my", std::ios_base::out);
    std::ofstream out2("./result/stl", std::ios_base::out);

    out1 << "mylist testing" << std::endl;
    out1 << std::endl;

    ft::list<int> myfirst;                                // empty list of ints
    ft::list<int> mysecond (4,100);                       // four ints with value 100
    ft::list<int> mythird (mysecond.begin(),mysecond.end());  // iterating through second
    ft::list<int> myfourth (mythird);                       // a copy of third

    // // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    ft::list<int> myfifth (myints, myints + sizeof(myints) / sizeof(int) );

    out1 << "The contents of fifth are: ";
    for (ft::list<int>::iterator it = myfifth.begin(); it != myfifth.end(); it++)
        out1 << *it << ' ';

    out1 << '\n';

    for (ft::list<int>::iterator it = myfirst.begin(); it != myfirst.end(); ++it)
        out1 << *it << " ";
    out1 << std::endl;

    for (ft::list<int>::reverse_iterator it = myfirst.rbegin(); it != myfirst.rend(); ++it)
        out1 << *it << " ";
    out1 << std::endl;

    if (myfourth == mythird)
        out1 << "fourth and thrid are same\n";
    if (myfirst != mysecond)
        out1 << "first and second are different\n";
    if (myfirst < mysecond)
        out1 << "first is are smaller than second\n";
    if (myfirst > mysecond)
        out1 << "first is larger than second\n";
    if (myfirst >= mysecond)
        out1 << "first is greater than or equal to second\n";
    if (myfirst <= mysecond)
        out1 << "first is smaller than or equal to second\n";


    ft::list<int> first (3);      // list of 3 zero-initialized ints
    ft::list<int> second (5);     // list of 5 zero-initialized ints
    
    second = first;
    first = ft::list<int>();

    out1 << "Size of first: " << int (first.size()) << '\n';
    out1 << "Size of second: " << int (second.size()) << '\n';


    out1 << "empty testing" << std::endl;
    out1 << std::endl;

    ft::list<int> myylist;
    int mysum (0);

    for (int i=1;i<=10;++i) myylist.push_back(i);

    while (!myylist.empty())
    {
        mysum += myylist.front();
        myylist.pop_front();
    }

    out1 << "total: " << mysum << '\n';

    out1 << "empty testing" << std::endl;
    out1 << std::endl;

    ft::list<int> myints3;
    out1 << "0. size: " << myints3.size() << '\n';

    for (int i=0; i<100; i++)
        myints3.push_back(i);
    out1 << "1. size: " << myints3.size() << '\n';

    myints3.insert (myints3.begin(),10,100);
    out1 << "2. size: " << myints3.size() << '\n';

    myints3.pop_back();
    out1 << "3. size: " << myints3.size() << '\n';

    out1 << "max_size and resize testing" << std::endl;
    out1 << std::endl;

    unsigned int myi = 10;
    ft::list<int> mylist4;

    if (myi<mylist4.max_size())
    {
        out1 << "before size" << mylist4.size() << std::endl;
        mylist4.resize(myi);
        out1 << "after size" << mylist4.size() << std::endl;
    }
    else out1 << "That size exceeds the limit.\n";

    out1 << "front and back testing" << std::endl;
    out1 << std::endl;

    ft::list<int> mylist5;

    mylist5.push_back(77);
    mylist5.push_back(22);

    // now front equals 77, and back 22

    mylist5.front() -= mylist5.back();

    out1 << "mylist.front() is now " << mylist5.front() << '\n';

    mylist5.push_back(10);

    while (mylist5.back() != 0)
    {
        mylist5.push_back ( mylist5.back() -1 );
    }

    out1 << "mylist contains:";
    for (ft::list<int>::iterator it=mylist5.begin(); it!=mylist5.end() ; ++it)
        out1 << ' ' << *it;

    out1 << '\n';

    out1 << "assign testing" << std::endl;
    out1 << std::endl;

    ft::list<int> myfirst6;
    ft::list<int> mysecond6;

    myfirst6.assign (7,100);                      // 7 ints with value 100

    mysecond6.assign (myfirst6.begin(),myfirst6.end()); // a copy of myfirst6

    int myints6[]={1776,7,4};
    myfirst6.assign (myints6,myints6+3);            // assigning from array

    out1 << "Size of first: " << int (myfirst6.size()) << '\n';
    out1 << "Size of second: " << int (mysecond6.size()) << '\n';

    out1 << "push_front and push_back and pop_front and pop_back testing" << std::endl;
    out1 << std::endl;

    ft::list<int> mylist7 (2,100);         // two ints with a value of 100
    mylist7.push_front (200);
    mylist7.push_front (300);

    out1 << "mylist contains:";
    for (ft::list<int>::iterator it=mylist7.begin(); it!=mylist7.end(); ++it)
        out1 << ' ' << *it;

    out1 << '\n';

    mylist7.push_back(400);
    mylist7.push_back(500);

    for (ft::list<int>::reverse_iterator it=mylist7.rbegin(); it!=mylist7.rend(); ++it)
        out1 << ' ' << *it;

    out1 << '\n';

    out1 << "Popping out the elements in mylist:";
    while (!mylist7.empty())
    {
        out1 << ' ' << mylist7.front();
        mylist7.pop_front();
    }
    for (int i=0;i<50; ++i)
    {
        mylist7.push_back(i*i*i);
        mylist7.push_front(i*i);
    }
    for (ft::list<int>::reverse_iterator it=mylist7.rbegin(); it!=mylist7.rend(); ++it)
        out1 << ' ' << *it;

    out1 << '\n';
    while (!mylist7.empty())
    {
        mylist7.pop_back();
    }

    out1 << "insert testing" << std::endl;
    out1 << std::endl;

    ft::list<int> mylist8;
    ft::list<int>::iterator myit8;

    // set some inmyit8ial values:
    for (int i=1; i<=5; ++i) mylist8.push_back(i); // 1 2 3 4 5

    myit8 = mylist8.begin();
    ++myit8;       // myit8 points now to number 2           ^

    mylist8.insert (myit8,10);                        // 1 10 2 3 4 5

    // "myit8" still points to number 2                      ^
    mylist8.insert (myit8,2,20);                      // 1 10 20 20 2 3 4 5

    --myit8;       // myit8 points now to the second 20            ^
                                                    // 1 10 20 30 30 20 2 3 4 5
                                                    //               ^

    std::vector<int> myvec (15, 123);
    std::vector<int>::iterator myvit = myvec.begin();
    mylist8.insert(mylist8.begin(), myvit, myvec.end());
    
    out1 << "mylist contains:";
    for (myit8=mylist8.begin(); myit8!=mylist8.end(); ++myit8)
        out1 << ' ' << *myit8;
    out1 << '\n';

    out1 << "erase testing" << std::endl;
    out1 << std::endl;

    ft::list<int> mylist9;
    ft::list<int>::iterator it19,it29;

    // set some values:
    for (int i=1; i<10; ++i) mylist9.push_back(i*10);

                                // 10 20 30 40 50 60 70 80 90
    it19 = it29 = mylist9.begin(); // ^^
    ++it19;                      //    ^              ^

    it19 = mylist9.erase (it19);   // 10 30 40 50 60 70 80 90
                                //    ^           ^

    it29 = mylist9.erase (it29);   // 10 30 40 50 60 80 90
                                //    ^           ^

    ++it19;                      //       ^        ^
    --it29;                      //       ^     ^

    mylist9.erase (it19,it29);     // 10 30 60 80 90
                                //        ^

    out1 << "mylist contains:";
    for (it19=mylist9.begin(); it19!=mylist9.end(); ++it19)
        out1 << ' ' << *it19;
    out1 << '\n';

    out1 << "splice testing" << std::endl;
    out1 << std::endl;

    ft::list<int> mylist10, mylist210;
    ft::list<int>::iterator myit10;

    // set some initial values:
    for (int i=1; i<=4; ++i)
        mylist10.push_back(i);      // mylist10: 1 2 3 4

    for (int i=1; i<=3; ++i)
        mylist210.push_back(i*10);   // mylist210: 10 20 30

    myit10 = mylist10.begin();
    ++myit10;                         // points to 2

    mylist10.splice (myit10, mylist210); // mylist10: 1 10 20 30 2 3 4
    //                                 // mylist210 (empty)
    //                                 // "myit10" still points to 2 (the 5th element)
                                            
    mylist210.splice (mylist210.begin(),mylist10, myit10);
    //                                 // mylist10: 1 10 20 30 3 4
    //                                 // mylist210: 2
    //                                 // "myit10" is now invalid.
    myit10 = mylist10.begin();
    ++myit10;
    ++myit10;
    ++myit10;

    mylist10.splice ( mylist10.begin(), mylist10, myit10, mylist10.end());
    //                                 // mylist1: 30 3 4 1 10 20
    mylist10.swap(mylist210);
    out1 << "mylist1 contains:";
    for (myit10=mylist10.begin(); myit10!=mylist10.end(); ++myit10)
        out1 << ' ' << *myit10;
    out1 << '\n';

    out1 << "mylist2 contains:";
    for (myit10=mylist210.begin(); myit10!=mylist210.end(); ++myit10)
        out1 << ' ' << *myit10;
    out1 << '\n';

    out1 << "remove testing" << std::endl;
    out1 << std::endl;

    int myints11[]= {17,89,7,89,89,14,89};
    ft::list<int> mylist11 (myints11,myints11+4);

    mylist11.remove(89);

    out1 << "mylist contains:";
    for (ft::list<int>::iterator it=mylist11.begin(); it!=mylist11.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "remove_if testing" << std::endl;
    out1 << std::endl;

    int myints12[]= {15,36,7,17,20,39,4,1};
    ft::list<int> mylist12 (myints12,myints12+8);   // 15 36 7 17 20 39 4 1

    mylist12.remove_if (single_digit);           // 15 36 17 20 39

    mylist12.remove_if (is_odd());               // 36 20

    out1 << "mylist contains:";
    for (ft::list<int>::iterator it=mylist12.begin(); it!=mylist12.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "unique testing" << std::endl;
    out1 << std::endl;

    double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                        12.77, 73.35, 72.25, 15.3,  72.25 };
    ft::list<double> mylist13 (mydoubles,mydoubles+10);
    
    mylist13.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
                                // 15.3,  72.25, 72.25, 73.0,  73.35
    

    mylist13.unique();           //  2.72,  3.14, 12.15, 12.77
                                // 15.3,  72.25, 73.0,  73.35
    
    mylist13.unique (same_integral_part);  //  2.72,  3.14, 12.15
                                        // 15.3,  72.25, 73.0

    mylist13.unique (is_near());           //  2.72, 12.15, 72.25

    out1 << "mylist contains:";
    for (ft::list<double>::iterator it=mylist13.begin(); it!=mylist13.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "merge testing" << std::endl;
    out1 << std::endl;

    ft::list<double> myfirst14, mysecond14;

    myfirst14.push_back (3.1);
    myfirst14.push_back (2.2);
    myfirst14.push_back (2.9);

    mysecond14.push_back (3.7);
    mysecond14.push_back (7.1);
    mysecond14.push_back (1.4);

    myfirst14.sort();
    mysecond14.sort();

    myfirst14.merge(mysecond14);

    // (mysecond14 is now empty)

    mysecond14.push_back (2.1);

    myfirst14.merge(mysecond14,mycomparison);

    out1 << "first contains:";
    for (ft::list<double>::iterator it=myfirst14.begin(); it!=myfirst14.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "sort testing" << std::endl;
    out1 << std::endl;

    ft::list<std::string> mylist15;
    ft::list<std::string>::iterator it15;
    mylist15.push_back ("one");
    mylist15.push_back ("two");
    mylist15.push_back ("Three");

    mylist15.sort();

    out1 << "mylist contains:";
    for (it15=mylist15.begin(); it15!=mylist15.end(); ++it15)
        out1 << ' ' << *it15;
    out1 << '\n';

    mylist15.sort(compare_nocase);

    out1 << "mylist contains:";
    for (it15=mylist15.begin(); it15!=mylist15.end(); ++it15)
        out1 << ' ' << *it15;
    out1 << '\n';

    mylist15.reverse();

    for (it15=mylist15.begin(); it15!=mylist15.end(); ++it15)
        out1 << ' ' << *it15;
    out1 << '\n';

    out1.close();
    /////////////////////////////////////////////////////////////////////////////////////
    
    out2 << "stllist testing" << std::endl;
    out2 << std::endl;

    std::list<int> stlfirst;                                // empty list of ints
    std::list<int> stlsecond (4,100);                       // four ints with value 100
    std::list<int> stlthird (stlsecond.begin(),stlsecond.end());  // iterating through second
    std::list<int> stlfourth (stlthird);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int stlints[] = {16,2,77,29};
    std::list<int> stlfifth (stlints, stlints + sizeof(stlints) / sizeof(int) );

    out2 << "The contents of fifth are: ";
    for (std::list<int>::iterator it = stlfifth.begin(); it != stlfifth.end(); it++)
        out2 << *it << ' ';
    out2 << '\n';

    for (std::list<int>::iterator it = stlfirst.begin(); it != stlfirst.end(); ++it)
        out2 << *it << " ";
    out2 << std::endl;

    for (std::list<int>::reverse_iterator it = stlfirst.rbegin(); it != stlfirst.rend(); ++it)
        out2 << *it << " ";
    out2 << std::endl;

    if (stlfourth == stlthird)
        out2 << "fourth and thrid are same\n";
    if (stlfirst != stlsecond)
        out2 << "first and second are different\n";
    if (stlfirst < stlsecond)
        out2 << "first is are smaller than second\n";
    if (stlfirst > stlsecond)
        out2 << "first is larger than second\n";
    if (stlfirst >= stlsecond)
        out2 << "first is greater than or equal to second\n";
    if (stlfirst <= stlsecond)
        out2 << "first is smaller than or equal to second\n";

    std::list<int> stlfirst2 (3);      // list of 3 zero-initialized ints
    std::list<int> stlsecond2 (5);     // list of 5 zero-initialized ints

    stlsecond2 = stlfirst2;
    stlfirst2 = std::list<int>();

    out2 << "Size of first: " << int (stlfirst2.size()) << '\n';
    out2 << "Size of second: " << int (stlsecond2.size()) << '\n';

    out2 << "empty testing" << std::endl;
    out2 << std::endl;

    std::list<int> stlllist;
    int stllsum (0);

    for (int i=1;i<=10;++i) stlllist.push_back(i);

    while (!stlllist.empty())
    {
        stllsum += stlllist.front();
        stlllist.pop_front();
    }

    out2 << "total: " << stllsum << '\n';

    out2 << "empty testing" << std::endl;
    out2 << std::endl;

    std::list<int> stlints3;
    out2 << "0. size: " << stlints3.size() << '\n';

    for (int i=0; i<100; i++) stlints3.push_back(i);
    out2 << "1. size: " << stlints3.size() << '\n';

    stlints3.insert (stlints3.begin(),10,100);
    out2 << "2. size: " << stlints3.size() << '\n';

    stlints3.pop_back();
    out2 << "3. size: " << stlints3.size() << '\n';

    out2 << "max_size and resize testing" << std::endl;
    out2 << std::endl;

    unsigned int stli = 10;
    ft::list<int> stllist4;

    if (stli<stllist4.max_size())
    {
        out2 << "before size" << stllist4.size() << std::endl;
        stllist4.resize(stli);
        out2 << "after size" << stllist4.size() << std::endl;
    }
    else out2 << "That size exceeds the limit.\n";

    out2 << "front and back testing" << std::endl;
    out2 << std::endl;

    ft::list<int> stllist5;

    stllist5.push_back(77);
    stllist5.push_back(22);

    // now front equals 77, and back 22

    stllist5.front() -= stllist5.back();

    out2 << "mylist.front() is now " << stllist5.front() << '\n';

    stllist5.push_back(10);

    while (stllist5.back() != 0)
    {
        stllist5.push_back ( stllist5.back() -1 );
    }

    out2 << "mylist contains:";
    for (ft::list<int>::iterator it=stllist5.begin(); it!=stllist5.end() ; ++it)
        out2 << ' ' << *it;

    out2 << '\n';

    out2 << "assign testing" << std::endl;
    out2 << std::endl;

    std::list<int> stlfirst6;
    std::list<int> stlsecond6;

    stlfirst6.assign (7,100);                      // 7 ints with value 100

    stlsecond6.assign (stlfirst6.begin(),stlfirst6.end()); // a copy of stlfirst6

    int stlints6[]={1776,7,4};
    stlfirst6.assign (stlints6,stlints6+3);            // assigning from array

    out2 << "Size of first: " << int (stlfirst6.size()) << '\n';
    out2 << "Size of second: " << int (stlsecond6.size()) << '\n';

    out2 << "push_front and push_back and pop_front and pop_back testing" << std::endl;
    out2 << std::endl;

    std::list<int> stllist7 (2,100);         // two ints with a value of 100
    stllist7.push_front (200);
    stllist7.push_front (300);

    out2 << "mylist contains:";
    for (std::list<int>::iterator it=stllist7.begin(); it!=stllist7.end(); ++it)
        out2 << ' ' << *it;

    out2 << '\n';

    stllist7.push_back(400);
    stllist7.push_back(500);

    for (std::list<int>::reverse_iterator it=stllist7.rbegin(); it!=stllist7.rend(); ++it)
        out2 << ' ' << *it;

    out2 << '\n';

    out2 << "Popping out the elements in mylist:";
    while (!stllist7.empty())
    {
        out2 << ' ' << stllist7.front();
        stllist7.pop_front();
    }

    for (int i=0;i<50; ++i)
    {
        stllist7.push_back(i*i*i);
        stllist7.push_front(i*i);
    }
    for (std::list<int>::reverse_iterator it=stllist7.rbegin(); it!=stllist7.rend(); ++it)
        out2 << ' ' << *it;

    out2 << '\n';
    while (!stllist7.empty())
    {
        stllist7.pop_back();
    }

    out2 << "insert testing" << std::endl;
    out2 << std::endl;

    std::list<int> stllist8;
    std::list<int>::iterator stlit8;

    // set some inmyit8ial values:
    for (int i=1; i<=5; ++i) stllist8.push_back(i); // 1 2 3 4 5

    stlit8 = stllist8.begin();
    ++stlit8;       // stlit8 points now to number 2           ^

    stllist8.insert (stlit8,10);                        // 1 10 2 3 4 5

    // "stlit8" still points to number 2                      ^
    stllist8.insert (stlit8,2,20);                      // 1 10 20 20 2 3 4 5

    --stlit8;       // stlit8 points now to the second 20            ^

                                                    // 1 10 20 30 30 20 2 3 4 5
                                                    //               ^

    std::vector<int> stlvec (15, 123);
    std::vector<int>::iterator stlvit = stlvec.begin();
    
    stllist8.insert(stllist8.begin(), stlvit, stlvec.end());


    out2 << "mylist contains:";
    for (stlit8=stllist8.begin(); stlit8!=stllist8.end(); ++stlit8)
        out2 << ' ' << *stlit8;
    out2 << '\n';

    out2 << "erase testing" << std::endl;
    out2 << std::endl;

    std::list<int> stllist9;
    std::list<int>::iterator stlit19,stlit29;

    // set some values:
    for (int i=1; i<10; ++i) stllist9.push_back(i*10);

                                // 10 20 30 40 50 60 70 80 90
    stlit19 = stlit29 = stllist9.begin(); // ^^
    ++stlit19;                      //    ^              ^

    stlit19 = stllist9.erase (stlit19);   // 10 30 40 50 60 70 80 90
                                //    ^           ^

    stlit29 = stllist9.erase (stlit29);   // 10 30 40 50 60 80 90
                                //    ^           ^

    ++stlit19;                      //       ^        ^
    --stlit29;                      //       ^     ^

    stllist9.erase (stlit19,stlit29);     // 10 30 60 80 90
                                //        ^

    out2 << "mylist contains:";
    for (stlit19=stllist9.begin(); stlit19!=stllist9.end(); ++stlit19)
        out2 << ' ' << *stlit19;
    out2 << '\n';


    out2 << "splice testing" << std::endl;
    out2 << std::endl;

    std::list<int> stllist10, stllist210;
    std::list<int>::iterator stlit10;

    // set some initial values:
    for (int i=1; i<=4; ++i)
        stllist10.push_back(i);      // stllist10: 1 2 3 4

    for (int i=1; i<=3; ++i)
        stllist210.push_back(i*10);   // stllist210: 10 20 30

    stlit10 = stllist10.begin();
    ++stlit10;                         // points to 2

    stllist10.splice (stlit10, stllist210); // stllist10: 1 10 20 30 2 3 4
                                    // stllist210 (empty)
                                    // "stlit10" still points to 2 (the 5th element)
                                            
    stllist210.splice (stllist210.begin(),stllist10, stlit10);
                                    // stllist10: 1 10 20 30 3 4
                                    // stllist210: 2
                                    // "stlit10" is now invalid.
    stlit10 = stllist10.begin();
    ++stlit10;
    ++stlit10;
    ++stlit10;
    stllist10.splice ( stllist10.begin(), stllist10, stlit10, stllist10.end());
    //                                 // mylist1: 30 3 4 1 10 20
    stllist10.swap(stllist210);
    out2 << "mylist1 contains:";
    for (stlit10=stllist10.begin(); stlit10!=stllist10.end(); ++stlit10)
        out2 << ' ' << *stlit10;
    out2 << '\n';

    out2 << "mylist2 contains:";
    for (stlit10=stllist210.begin(); stlit10!=stllist210.end(); ++stlit10)
        out2 << ' ' << *stlit10;
    out2 << '\n';

    out2 << "remove testing" << std::endl;
    out2 << std::endl;

    int stlints11[]= {17,89,7,89,89,14,89};
    std::list<int> stllist11 (stlints11,stlints11+4);

    stllist11.remove(89);

    out2 << "mylist contains:";
    for (std::list<int>::iterator it=stllist11.begin(); it!=stllist11.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';

    out2 << "remove_if testing" << std::endl;
    out2 << std::endl;

    int stlints12[]= {15,36,7,17,20,39,4,1};
    std::list<int> stllist12 (stlints12,stlints12+8);   // 15 36 7 17 20 39 4 1

    stllist12.remove_if (single_digit);           // 15 36 17 20 39

    stllist12.remove_if (is_odd());               // 36 20

    out2 << "mylist contains:";
    for (std::list<int>::iterator it=stllist12.begin(); it!=stllist12.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';


    out2 << "unique testing" << std::endl;
    out2 << std::endl;

    double stldoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                        12.77, 73.35, 72.25, 15.3,  72.25 };
    std::list<double> stllist13 (stldoubles,stldoubles+10);
    
    stllist13.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
                                // 15.3,  72.25, 72.25, 73.0,  73.35

    stllist13.unique();           //  2.72,  3.14, 12.15, 12.77
                                // 15.3,  72.25, 73.0,  73.35

    stllist13.unique (same_integral_part);  //  2.72,  3.14, 12.15
                                        // 15.3,  72.25, 73.0

    stllist13.unique (is_near());           //  2.72, 12.15, 72.25

    out2 << "mylist contains:";
    for (std::list<double>::iterator it=stllist13.begin(); it!=stllist13.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';


    out2 << "merge testing" << std::endl;
    out2 << std::endl;

    std::list<double> stlfirst14, stlsecond14;

    stlfirst14.push_back (3.1);
    stlfirst14.push_back (2.2);
    stlfirst14.push_back (2.9);

    stlsecond14.push_back (3.7);
    stlsecond14.push_back (7.1);
    stlsecond14.push_back (1.4);

    stlfirst14.sort();
    stlsecond14.sort();

    stlfirst14.merge(stlsecond14);

    // (stlsecond14 is now empty)

    stlsecond14.push_back (2.1);

    stlfirst14.merge(stlsecond14,mycomparison);

    out2 << "first contains:";
    for (std::list<double>::iterator it=stlfirst14.begin(); it!=stlfirst14.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';


    out2 << "sort testing" << std::endl;
    out2 << std::endl;

    std::list<std::string> stllist15;
    std::list<std::string>::iterator stl15;
    stllist15.push_back ("one");
    stllist15.push_back ("two");
    stllist15.push_back ("Three");

    stllist15.sort();

    out2 << "mylist contains:";
    for (stl15=stllist15.begin(); stl15!=stllist15.end(); ++stl15)
        out2 << ' ' << *stl15;
    out2 << '\n';

    stllist15.sort(compare_nocase);

    out2 << "mylist contains:";
    for (stl15=stllist15.begin(); stl15!=stllist15.end(); ++stl15)
        out2 << ' ' << *stl15;
    out2 << '\n';

    stllist15.reverse();

    for (stl15=stllist15.begin(); stl15!=stllist15.end(); ++stl15)
        out2 << ' ' << *stl15;
    out2 << '\n';

    out2.close();
    return (0);
}