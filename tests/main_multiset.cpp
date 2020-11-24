/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_multiset.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:23:56 by kmin              #+#    #+#             */
/*   Updated: 2020/11/24 11:17:32 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <set>
#include "../MultiSet/multiset.hpp"

bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const int &lhs, const int &rhs) const
    {
        return lhs < rhs;
    }
};

int main()
{
    std::ofstream out1("./result/my", std::ios_base::out);
    std::ofstream out2("./result/stl", std::ios_base::out);

    out1 << "mystack testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myfirst;                           // empty multiset of ints

    int myints[]= {10,10,20,30,30,40,50};
    ft::multiset<int> mysecond (myints,myints+7);        // range

    ft::multiset<int> mythird (mysecond);                  // a copy of second

    ft::multiset<int> myfourth (mysecond.begin(), mysecond.end());  // iterator ctor.

    ft::multiset<int,classcomp> myfifth;                 // class as Compare

    bool(*myfn_pt)(int,int) = fncomp;
    ft::multiset<int,bool(*)(int,int)> mysixth (myfn_pt);  // function pointer as Compare

    for (ft::multiset<int>::iterator it = mysecond.begin(); it != mysecond.end(); ++it)
        out1 << *it << " ";
    out1 << std::endl;

    for (ft::multiset<int>::reverse_iterator it = mysecond.rbegin(); it != mysecond.rend(); ++it)
        out1 << *it << " ";
    out1 << std::endl;

    out1 << "assign operator testing" << std::endl;
    out1 << std::endl;

    int myints2[]={ 12,82,37,64,15 };
    ft::multiset<int> myfirst2 (myints2,myints2+5);   // multiset with 5 ints
    ft::multiset<int> mysecond2;                    // empty multiset

    mysecond2 = myfirst2;                          // now mysecond2 contains the 5 ints
    myfirst2 = ft::multiset<int>();                 // and first is empty

    out1 << "Size of first: " << int (myfirst2.size()) << '\n';
    out1 << "Size of second: " << int (mysecond2.size()) << '\n';

    out1 << "begin and end and rbegin and rend testing" << std::endl;
    out1 << std::endl;

    int myints3[] = {75,23,65,42,13};
    ft::multiset<int> myset (myints3,myints3+5);

    out1 << "myset contains:";
    for (ft::multiset<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';
    out1 << "myset contains:";
    for (ft::multiset<int>::reverse_iterator it=myset.rbegin(); it!=myset.rend(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "empty testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset2;

    myset2.insert(20);
    myset2.insert(30);
    myset2.insert(10);

    out1 << "myset contains:";
    while (!myset2.empty())
    {
        out1 << ' ' << *myset2.begin();
        myset2.erase(myset2.begin());
    }
    out1 << '\n';

    out1 << "size testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myints4;
    out1 << "0. size: " << myints4.size() << '\n';

    for (int i=0; i<100; ++i) myints4.insert(i);
    out1 << "1. size: " << myints4.size() << '\n';

    myints4.insert (100);
    out1 << "2. size: " << myints4.size() << '\n';

    myints4.erase(5);
    out1 << "3. size: " << myints4.size() << '\n';

    out1 << "max_size testing" << std::endl;
    out1 << std::endl;

    int myi;
    ft::multiset<int> myset5;

    if (myset5.max_size()>1000)
    {
        for (myi=0; myi<1000; myi++) myset5.insert(myi);
        out1 << "The multiset contains 1000 elements.\n";
    }
    else out1 << "The multiset could not hold 1000 elements.\n";

    out1 << "insert testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myymultiset;
    ft::multiset<int>::iterator myyit;

    // set some inmyyitial values:
    for (int i=1; i<=501; i++) myymultiset.insert(i*10);  // 10 20 30 40 50

    myyit=myymultiset.insert(25);

    myyit=myymultiset.insert (myyit,27);    // max efficiency inserting
    myyit=myymultiset.insert (myyit,29);    // max efficiency inserting
    myyit=myymultiset.insert (myyit,24);    // no max efficiency inserting (24<29)

    int myyyints[]= {5,5,5,5,1,0,10,15,8,10,15};
    myymultiset.insert (myyyints,myyyints+11);

    out1 << "mymultiset contains:";
    for (myyit=myymultiset.begin(); myyit!=myymultiset.end(); ++myyit)
        out1 << ' ' << *myyit;
    out1 << '\n';

    out1 << "erase testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset7;
    ft::multiset<int>::iterator myit7;

    // insert some values:
    for (int i=1; i<10; i++) myset7.insert(i*10);  // 10 20 30 40 50 60 70 80 90

    myit7 = myset7.begin();
    ++myit7;                                         // "myit7" points now to 20

    myset7.erase (myit7);

    myset7.erase (40);

    myit7 = myset7.find (60);
    myset7.erase (myit7, myset7.end());

    out1 << "myset contains:";
    for (myit7=myset7.begin(); myit7!=myset7.end(); ++myit7)
        out1 << ' ' << *myit7;
    out1 << '\n';

    out1 << "swap testing" << std::endl;
    out1 << std::endl;

    int myints8[]={12,75,10,32,20,25};
    ft::multiset<int> myfirst8 (myints8,myints8+3);     // 10,12,75
    ft::multiset<int> mysecond8 (myints8+3,myints8+6);  // 20,25,32

    myfirst8.swap(mysecond8);

    out1 << "first contains:";
    for (ft::multiset<int>::iterator it=myfirst8.begin(); it!=myfirst8.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "second contains:";
    for (ft::multiset<int>::iterator it=mysecond8.begin(); it!=mysecond8.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "clear testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset10;

    myset10.insert (100);
    myset10.insert (200);
    myset10.insert (300);

    out1 << "myset contains:";
    for (ft::multiset<int>::iterator it=myset10.begin(); it!=myset10.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    myset10.clear();
    myset10.insert (1101);
    myset10.insert (2202);

    out1 << "myset contains:";
    for (ft::multiset<int>::iterator it=myset10.begin(); it!=myset10.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "key_comp testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset11;
    int highest;

    ft::multiset<int>::key_compare mycomp11 = myset11.key_comp();

    for (int i=0; i<=5; i++) myset11.insert(i);

    out1 << "myset contains:";

    highest=*myset11.rbegin();
    ft::multiset<int>::iterator myit11=myset11.begin();
    do {
        out1 << ' ' << *myit11;
    } while ( mycomp11(*(++myit11),highest) );

    out1 << '\n';

    out1 << "value_comp testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset12;

    ft::multiset<int>::value_compare mycomp12 = myset12.value_comp();

    for (int i=0; i<=5; i++) myset12.insert(i);

    out1 << "myset contains:";

    int highest12=*myset12.rbegin();
    ft::multiset<int>::iterator myit12=myset12.begin();
    do {
        out1 << ' ' << *myit12;
    } while ( mycomp12(*(++myit12),highest12) );

    out1 << '\n';

    out1 << "find testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset13;
    ft::multiset<int>::iterator myit13;

    // multiset some initial values:
    for (int i=1; i<=5; i++) myset13.insert(i*10);    // multiset: 10 20 30 40 50

    myit13=myset13.find(20);
    myset13.erase (myit13);
    myset13.erase (myset13.find(40));

    out1 << "myset contains:";
    for (myit13=myset13.begin(); myit13!=myset13.end(); ++myit13)
        out1 << ' ' << *myit13;
    out1 << '\n';

    out1 << "count testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset14;

  // multiset some initial values:
    for (int i=1; i<5; ++i) myset14.insert(i*3);    // multiset: 3 6 9 12

    for (int i=0; i<10; ++i)
    {
        out1 << i;
        if (myset14.count(i)!=0)
        out1 << " is an element of myset.\n";
        else
        out1 << " is not an element of myset.\n";
    }

    out1 << "lower_bound testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset15;
    ft::multiset<int>::iterator myitlow,myitup;

    for (int i=1; i<10; i++) myset15.insert(i*10); // 10 20 30 40 50 60 70 80 90

    myitlow=myset15.lower_bound (30);                //       ^
    myitup=myset15.upper_bound (60);                 //                   ^

    myset15.erase(myitlow,myitup);                     // 10 20 70 80 90

    out1 << "myset contains:";
    for (ft::multiset<int>::iterator it=myset15.begin(); it!=myset15.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "upper_bound testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset16;
    ft::multiset<int>::iterator itlow16,itup16;

    for (int i=1; i<10; i++) myset16.insert(i*10); // 10 20 30 40 50 60 70 80 90

    itlow16=myset16.lower_bound (30);                //       ^
    itup16=myset16.upper_bound (60);                 //                   ^

    myset16.erase(itlow16,itup16);                     // 10 20 70 80 90

    out1 << "myset contains:";
    for (ft::multiset<int>::iterator it=myset16.begin(); it!=myset16.end(); ++it)
        out1 << ' ' << *it;
    out1 << '\n';

    out1 << "equal_range testing" << std::endl;
    out1 << std::endl;

    ft::multiset<int> myset17;

    for (int i=1; i<=5; i++) myset17.insert(i*10);   // myset17: 10 20 30 40 50

    std::pair<ft::multiset<int>::const_iterator,ft::multiset<int>::const_iterator> ret;
    ret = myset17.equal_range(30);

    out1 << "the lower bound points to: " << *ret.first << '\n';
    out1 << "the upper bound points to: " << *ret.second << '\n';

    out1.close();


    ///////////////////////////////////////////////////////////////////////////////////

    out2 << "stlstack testing" << std::endl;
    out2 << std::endl;



    std::multiset<int> stlfirst;                           // empty multiset of ints

    int stlints[]= {10,10,20,30,30,40,50};
    std::multiset<int> stlsecond (stlints,stlints+7);        // range

    std::multiset<int> stlthird (stlsecond);                  // a copy of second

    std::multiset<int> stlfourth (stlsecond.begin(), stlsecond.end());  // iterator ctor.

    std::multiset<int,classcomp> stlfifth;                 // class as Compare

    bool(*stlfn_pt)(int,int) = fncomp;
    std::multiset<int,bool(*)(int,int)> stlsixth (stlfn_pt);  // function pointer as Compare

    for (std::multiset<int>::iterator it = stlsecond.begin(); it != stlsecond.end(); ++it)
        out2 << *it << " ";
    out2 << std::endl;

    for (std::multiset<int>::reverse_iterator it = stlsecond.rbegin(); it != stlsecond.rend(); ++it)
        out2 << *it << " ";
    out2 << std::endl;
    

    out2 << "assign operator testing" << std::endl;
    out2 << std::endl;

    int stlints2[]={ 12,82,37,64,15 };
    std::multiset<int> stlfirst2 (stlints2,stlints2+5);   // multiset with 5 ints
    std::multiset<int> stlsecond2;                    // empty multiset

    stlsecond2 = stlfirst2;                          // now stlsecond2 contains the 5 ints
    stlfirst2 = std::multiset<int>();                 // and first is empty

    out2 << "Size of first: " << int (stlfirst2.size()) << '\n';
    out2 << "Size of second: " << int (stlsecond2.size()) << '\n';

    out2 << "begin and end and rbegin and rend testing" << std::endl;
    out2 << std::endl;

    int stlints3[] = {75,23,65,42,13};
    std::multiset<int> stlset (stlints3,stlints3+5);

    out2 << "myset contains:";
    for (std::multiset<int>::iterator it=stlset.begin(); it!=stlset.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';
    out2 << "myset contains:";
    for (std::multiset<int>::reverse_iterator it=stlset.rbegin(); it!=stlset.rend(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';

    out2 << "empty testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset2;

    stlset2.insert(20);
    stlset2.insert(30);
    stlset2.insert(10);

    out2 << "myset contains:";
    while (!stlset2.empty())
    {
        out2 << ' ' << *stlset2.begin();
        stlset2.erase(stlset2.begin());
    }
    out2 << '\n';

    out2 << "size testing" << std::endl;
    out2 << std::endl;

    ft::multiset<int> stlints4;
    out2 << "0. size: " << stlints4.size() << '\n';

    for (int i=0; i<100; ++i) stlints4.insert(i);
    out2 << "1. size: " << stlints4.size() << '\n';

    stlints4.insert (100);
    out2 << "2. size: " << stlints4.size() << '\n';

    stlints4.erase(5);
    out2 << "3. size: " << stlints4.size() << '\n';


    out2 << "max_size testing" << std::endl;
    out2 << std::endl;

    int stli;
    std::multiset<int> stlset5;

    if (stlset5.max_size()>1000)
    {
        for (stli=0; stli<1000; stli++) stlset5.insert(stli);
        out2 << "The multiset contains 1000 elements.\n";
    }
    else out2 << "The multiset could not hold 1000 elements.\n";

    out2 << "insert testing" << std::endl;
    out2 << std::endl;

    ft::multiset<int> stllmultiset;
    ft::multiset<int>::iterator stllit;

    // set some inmyyitial values:
    for (int i=1; i<=501; i++) stllmultiset.insert(i*10);  // 10 20 30 40 50

    stllit=stllmultiset.insert(25);

    stllit=stllmultiset.insert (stllit,27);    // max efficiency inserting
    stllit=stllmultiset.insert (stllit,29);    // max efficiency inserting
    stllit=stllmultiset.insert (stllit,24);    // no max efficiency inserting (24<29)

    int stllints[]= {5,5,5,5,1,0,10,15,8,10,15};
    stllmultiset.insert (stllints,stllints+11);

    out2 << "mymultiset contains:";
    for (stllit=stllmultiset.begin(); stllit!=stllmultiset.end(); ++stllit)
        out2 << ' ' << *stllit;
    out2 << '\n';

    out2 << "erase testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset7;
    std::multiset<int>::iterator stlit7;

    // insert some values:
    for (int i=1; i<10; i++) stlset7.insert(i*10);  // 10 20 30 40 50 60 70 80 90

    stlit7 = stlset7.begin();
    ++stlit7;                                         // "stlit7" points now to 20

    stlset7.erase (stlit7);

    stlset7.erase (40);

    stlit7 = stlset7.find (60);
    stlset7.erase (stlit7, stlset7.end());

    out2 << "myset contains:";
    for (stlit7=stlset7.begin(); stlit7!=stlset7.end(); ++stlit7)
        out2 << ' ' << *stlit7;
    out2 << '\n';

    out2 << "swap testing" << std::endl;
    out2 << std::endl;

    int stlints8[]={12,75,10,32,20,25};
    std::multiset<int> stlfirst8 (stlints8,stlints8+3);     // 10,12,75
    std::multiset<int> stlsecond8 (stlints8+3,stlints8+6);  // 20,25,32

    stlfirst8.swap(stlsecond8);

    out2 << "first contains:";
    for (std::multiset<int>::iterator it=stlfirst8.begin(); it!=stlfirst8.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';

    out2 << "second contains:";
    for (std::multiset<int>::iterator it=stlsecond8.begin(); it!=stlsecond8.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';

    out2 << "clear testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset10;

    stlset10.insert (100);
    stlset10.insert (200);
    stlset10.insert (300);

    out2 << "myset contains:";
    for (std::multiset<int>::iterator it=stlset10.begin(); it!=stlset10.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';

    stlset10.clear();
    stlset10.insert (1101);
    stlset10.insert (2202);

    out2 << "myset contains:";
    for (std::multiset<int>::iterator it=stlset10.begin(); it!=stlset10.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';

    out2 << "key_comp testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset11;
    int stlhighest;

    std::multiset<int>::key_compare stlcomp11 = stlset11.key_comp();

    for (int i=0; i<=5; i++) stlset11.insert(i);

    out2 << "myset contains:";

    stlhighest=*stlset11.rbegin();
    std::multiset<int>::iterator stlit11=stlset11.begin();
    do {
        out2 << ' ' << *stlit11;
    } while ( stlcomp11(*(++stlit11),stlhighest) );

    out2 << '\n';

    out2 << "value_comp testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset12;

    std::multiset<int>::value_compare stlcomp12 = stlset12.value_comp();

    for (int i=0; i<=5; i++) stlset12.insert(i);

    out2 << "myset contains:";

    int stlhighest12=*stlset12.rbegin();
    std::multiset<int>::iterator stlit12=stlset12.begin();
    do {
        out2 << ' ' << *stlit12;
    } while ( stlcomp12(*(++stlit12),stlhighest12) );

    out2 << '\n';


    out2 << "find testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset13;
    std::multiset<int>::iterator stlit13;

    // multiset some initial values:
    for (int i=1; i<=5; i++) stlset13.insert(i*10);    // multiset: 10 20 30 40 50

    stlit13=stlset13.find(20);
    stlset13.erase (stlit13);
    stlset13.erase (stlset13.find(40));

    out2 << "myset contains:";
    for (stlit13=stlset13.begin(); stlit13!=stlset13.end(); ++stlit13)
        out2 << ' ' << *stlit13;
    out2 << '\n';

    out2 << "count testing" << std::endl;
    out2 << std::endl;

    ft::multiset<int> stlset14;

  // multiset some initial values:
    for (int i=1; i<5; ++i) stlset14.insert(i*3);    // multiset: 3 6 9 12

    for (int i=0; i<10; ++i)
    {
        out2 << i;
        if (stlset14.count(i)!=0)
        out2 << " is an element of myset.\n";
        else
        out2 << " is not an element of myset.\n";
    }

    out2 << "lower_bound testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset15;
    std::multiset<int>::iterator stlitlow,stlitup;

    for (int i=1; i<10; i++) stlset15.insert(i*10); // 10 20 30 40 50 60 70 80 90

    stlitlow=stlset15.lower_bound (30);                //       ^
    stlitup=stlset15.upper_bound (60);                 //                   ^

    stlset15.erase(stlitlow,stlitup);                     // 10 20 70 80 90

    out2 << "myset contains:";
    for (std::multiset<int>::iterator it=stlset15.begin(); it!=stlset15.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';

    out2 << "upper_bound testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset16;
    std::multiset<int>::iterator stlitlow16,stlitup16;

    for (int i=1; i<10; i++) stlset16.insert(i*10); // 10 20 30 40 50 60 70 80 90

    stlitlow16=stlset16.lower_bound (30);                //       ^
    stlitup16=stlset16.upper_bound (60);                 //                   ^

    stlset16.erase(stlitlow16,stlitup16);                     // 10 20 70 80 90

    out2 << "myset contains:";
    for (std::multiset<int>::iterator it=stlset16.begin(); it!=stlset16.end(); ++it)
        out2 << ' ' << *it;
    out2 << '\n';

    out2 << "equal_range testing" << std::endl;
    out2 << std::endl;

    std::multiset<int> stlset17;

    for (int i=1; i<=5; i++) stlset17.insert(i*10);   // stlset17: 10 20 30 40 50

    std::pair<std::multiset<int>::const_iterator,std::multiset<int>::const_iterator> stlret17;
    stlret17 = stlset17.equal_range(30);

    out2 << "the lower bound points to: " << *stlret17.first << '\n';
    out2 << "the upper bound points to: " << *stlret17.second << '\n';

    out2.close();
    return (0);
}