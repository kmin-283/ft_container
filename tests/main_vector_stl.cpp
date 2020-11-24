/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector_stl.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 10:06:39 by kmin              #+#    #+#             */
/*   Updated: 2020/11/24 21:35:34 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ofstream out1("./result/stl", std::ios_base::out);

    out1 << "stlvector testing" << std::endl;
    out1 << std::endl;


    std::vector<int> first;                                // empty vector of ints
    std::vector<int> second (4,100);                       // four ints with value 100
    std::vector<int> third (second.begin(),second.end());  // iterating through second
    std::vector<int> fourth (third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    out1 << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    std::vector<int> foo (3,1);
    std::vector<int> bar (5,2);

    bar = foo;
    foo = std::vector<int>();

    out1 << "Size of foo: " << int(foo.size()) << '\n';
    out1 << "Size of bar: " << int(bar.size()) << '\n';
    std::vector<int> myvector;

  // set some content in the vector:

    out1 << "maxsize testing" << std::endl;
    out1 << std::endl;
    for (int i=0; i<100; i++) myvector.push_back(i);

    out1 << "size: " << myvector.size() << "\n";
    out1 << "capacity: " << myvector.capacity() << "\n";
    out1 << "max_size: " << myvector.max_size() << "\n";

    out1 << "resize testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector2;

  // set some initial content:
    for (int i=1;i<10;i++) myvector2.push_back(i);

    myvector2.resize(5);
    myvector2.resize(8,100);
    myvector2.resize(12);

    out1 << "myvector2 contains:";
    for (unsigned int i=0;i<myvector2.size();i++)
        out1 << ' ' << myvector2[i];
    out1 << '\n';

    out1 << "capacity testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector3;

  // set some content in the vector:
    for (int i=0; i<100; i++) myvector3.push_back(i);

    out1 << "size: " << (int) myvector3.size() << '\n';
    out1 << "capacity: " << (int) myvector3.capacity() << '\n';
    out1 << "max_size: " << (int) myvector3.max_size() << '\n';

    out1 << "empty testing" << std::endl;
    out1 << std::endl;


    std::vector<int> myvector4;
    int sum (0);

    for (int i=1;i<=10;i++) myvector4.push_back(i);

    while (!myvector4.empty())
    {
        sum += myvector4.back();
        myvector4.pop_back();
    }

    out1 << "total: " << sum << '\n';

    out1 << "reserve testing" << std::endl;
    out1 << std::endl;

    std::vector<int>::size_type sz;

    std::vector<int> foo2;
    sz = foo2.capacity();
    out1 << "making foo2 grow:\n";
    for (int i=0; i<100; ++i) {
        foo2.push_back(i);
        if (sz!=foo2.capacity()) {
        sz = foo2.capacity();
        out1 << "capacity changed: " << sz << '\n';
        }
    }

    std::vector<int> bar2;
    sz = bar2.capacity();
    bar2.reserve(200);   // this is the only difference with foo above
    out1 << "making bar2 grow:\n";
    for (int i=0; i<200; ++i) {
        bar2.push_back(i);
        if (sz!=bar2.capacity()) {
        sz = bar2.capacity();
        out1 << "capacity changed: " << sz << '\n';
        }
    }

    out1 << "operator[] testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector5 (10);   // 10 zero-initialized elements

    std::vector<int>::size_type sz5 = myvector5.size();

    // assign some values:
    for (unsigned i=0; i<sz5; i++) myvector5[i]=i;

    // reverse vector using operator[]:
    for (unsigned i=0; i<sz5/2; i++)
    {
        int temp;
        temp = myvector5[sz5-1-i];
        myvector5[sz5-1-i]=myvector5[i];
        myvector5[i]=temp;
    }

    out1 << "myvector5 contains:";
    for (unsigned i=0; i<sz5; i++)
        out1 << ' ' << myvector5[i];
    out1 << '\n';


    out1 << "at testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector8 (10);   // 10 zero-initialized ints

  // assign some values:
    for (unsigned i=0; i<myvector8.size(); i++)
        myvector8.at(i)=i;

    out1 << "myvector8 contains:";
    for (unsigned i=0; i<myvector8.size(); i++)
        out1 << ' ' << myvector8.at(i);
    out1 << '\n';

    out1 << "front testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector7;

    myvector7.push_back(78);
    myvector7.push_back(16);

    // now front equals 78, and back 16

    myvector7.front() -= myvector7.back();

    out1 << "myvector7.front() is now " << myvector7.front() << '\n';

    out1 << "back testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector9;

    myvector9.push_back(10);

    while (myvector9.back() != 0)
    {
        myvector9.push_back ( myvector9.back() -1 );
    }

    out1 << "myvector9 contains:";
    for (unsigned i=0; i<myvector9.size() ; i++)
        out1 << ' ' << myvector9[i];
    out1 << '\n';


    out1 << "assign testing" << std::endl;
    out1 << std::endl;

    std::vector<int> first10;
    std::vector<int> second10;
    std::vector<int> third10;

    first10.assign (7,100);             // 7 ints with a value of 100

    std::vector<int>::iterator it;
    it=first10.begin()+1;

    second10.assign (it,first10.end()-1); // the 5 central values of first10

    int myints10[] = {1776,7,4};
    third10.assign (myints10,myints10+3);   // assigning from array.

    out1 << "Size of first10: " << int (first10.size()) << '\n';
    out1 << "Size of second10: " << int (second10.size()) << '\n';
    out1 << "Size of third10: " << int (third10.size()) << '\n';

    out1 << "push_back testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector11;

    out1 << "Please enter some integers (enter 0 to end):\n";

    for (int i=0;i<1000;++i)
        myvector11.push_back(i*i);

    out1 << "myvector11 stores " << int(myvector11.size()) << " numbers.\n";

    out1 << "pop_back testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector12;
    int sum12 (0);
    myvector12.push_back (100);
    myvector12.push_back (200);
    myvector12.push_back (300);

    while (!myvector12.empty())
    {
        sum12+=myvector12.back();
        myvector12.pop_back();
    }

    out1 << "The elements of myvector12 add up to " << sum12 << '\n';


    out1 << "insert testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector13 (3,100);
    std::vector<int>::iterator it13;

    it13 = myvector13.begin();
    it13 = myvector13.insert ( it13 , 200 );

    myvector13.insert (it13,2,300);

    // "it13" no longer valid, get a new one:
    it13 = myvector13.begin();

    std::vector<int> anothervector (2,400);
    myvector13.insert (it13+2,anothervector.begin(),anothervector.end());

    int myarray [] = { 501,502,503 };
    myvector13.insert (myvector13.begin(), myarray, myarray+3);

    out1 << "myvector13 contains:";
    for (it13=myvector13.begin(); it13<myvector13.end(); it13++)
        out1 << ' ' << *it13;
    out1 << '\n';

    out1 << "erase testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector14;

  // set some values (from 1 to 10)
    for (int i=1; i<=10; i++) myvector14.push_back(i);

    // erase the 6th element
    myvector14.erase (myvector14.begin()+5);

    // erase the first 3 elements:
    myvector14.erase (myvector14.begin(),myvector14.begin()+3);

    out1 << "myvector14 contains:";
    for (unsigned i=0; i<myvector14.size(); ++i)
        out1 << ' ' << myvector14[i];
    out1 << '\n';

    out1 << "swap testing" << std::endl;
    out1 << std::endl;

    std::vector<int> foo15 (3,100);   // three ints with a value of 100
    std::vector<int> bar15 (5,200);   // five ints with a value of 200

    foo15.swap(bar15);

    out1 << "foo15 contains:";
    for (unsigned i=0; i<foo15.size(); i++)
        out1 << ' ' << foo15[i];
    out1 << '\n';

    out1 << "bar15 contains:";
    for (unsigned i=0; i<bar15.size(); i++)
        out1 << ' ' << bar15[i];
    out1 << '\n';


    out1 << "clear testing" << std::endl;
    out1 << std::endl;

    std::vector<int> myvector16;
    myvector16.push_back (100);
    myvector16.push_back (200);
    myvector16.push_back (300);

    out1 << "myvector16 contains:";
    for (unsigned i=0; i<myvector16.size(); i++)
        out1 << ' ' << myvector16[i];
    out1 << '\n';

    out1 << "relational operator testing" << std::endl;
    out1 << std::endl;

    std::vector<int> foo17 (3,100);   // three ints with a value of 100
    std::vector<int> bar17 (2,200);   // two ints with a value of 200

    if (foo17==bar17) out1 << "foo17 and bar17 are equal\n";
    if (foo17!=bar17) out1 << "foo17 and bar17 are not equal\n";
    if (foo17< bar17) out1 << "foo17 is less than bar17\n";
    if (foo17> bar17) out1 << "foo17 is greater than bar17\n";
    if (foo17<=bar17) out1 << "foo17 is less than or equal to bar17\n";
    if (foo17>=bar17) out1 << "foo17 is greater than or equal to bar17\n";


    out1.close();

    return (0);
}