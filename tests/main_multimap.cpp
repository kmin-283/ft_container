/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_multimap.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:20:05 by kmin              #+#    #+#             */
/*   Updated: 2020/11/24 20:34:12 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MultiMap/multimap.hpp"
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <stdlib.h>

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};

int main()
{
    std::ofstream out1("./result/my", std::ios_base::out);
    std::ofstream out2("./result/stl", std::ios_base::out);

    out1 << "mymultimap testing" << std::endl;
    out1 << std::endl;

    ft::multimap<char,int> myyfirst;

    myyfirst.insert(std::pair<char,int>('a',10));
    myyfirst.insert(std::pair<char,int>('b',15));
    myyfirst.insert(std::pair<char,int>('b',20));
    myyfirst.insert(std::pair<char,int>('c',25));

    std::multimap<char,int> myysecond (myyfirst.begin(),myyfirst.end());

    std::multimap<char,int> myyythird (myysecond);

    std::multimap<char,int,classcomp> myyfourth;                 // class as Compare

    bool(*myyfn_pt)(char,char) = fncomp;
    ft::multimap<char,int,bool(*)(char,char)> myyfifth (myyfn_pt); // function pointer as comp

    out1 << "constructing maps" << std::endl;
    out1 << std::endl;
    ft::multimap<char, int> myfirst;

    myfirst.insert(std::pair<char, int> ('a', 10));
    myfirst.insert(std::pair<char, int> ('b', 20));
    myfirst.insert(std::pair<char, int>('c', 80));
    myfirst.insert(std::pair<char, int>('b', 1500));

    for (ft::multimap<char, int>::iterator it = myfirst.begin(); it != myfirst.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::multimap<char, int>::reverse_iterator it = myfirst.rbegin(); it != myfirst.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    ft::multimap<char, int> mysecond(myfirst.begin(), myfirst.end());
    for (ft::multimap<char, int>::iterator it = mysecond.begin(); it != mysecond.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::multimap<char, int>::reverse_iterator it = mysecond.rbegin(); it != mysecond.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    ft::multimap<char, int> mythird(mysecond);
    for (ft::multimap<char, int>::iterator it = mythird.begin(); it != mythird.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::multimap<char, int>::reverse_iterator it = mythird.rbegin(); it != mythird.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    ft::multimap<char, int, classcomp> myfourth; // class as Compare
    for (ft::multimap<char, int>::iterator it = myfourth.begin(); it != myfourth.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::multimap<char, int>::reverse_iterator it = myfourth.rbegin(); it != myfourth.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    bool (*myfn_pt)(char, char) = fncomp;
    ft::multimap<char, int, bool (*)(char, char)> myfifth(myfn_pt);
    for (ft::multimap<char, int>::iterator it = myfifth.begin(); it != myfifth.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::multimap<char, int>::reverse_iterator it = myfifth.rbegin(); it != myfifth.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    out1 << std::endl;
    out1 << "size check" << std::endl;
    out1 << std::endl;
    ft::multimap<char, int> myfirst2;
    ft::multimap<char, int> mysecond2;

    myfirst2.insert(std::pair<char, int>('x', -8));
    myfirst2.insert(std::pair<char, int>('y', 16));
    myfirst2.insert(std::pair<char, int>('z', 32));

    mysecond2 = myfirst2;            // mysecond2 now contains 3 ints
    myfirst2 = ft::multimap<char, int>(); // and first is now empty

    out1 << "Size of first: " << myfirst2.size() << '\n';
    out1 << "Size of second: " << mysecond2.size() << '\n';

    out1 << std::endl;
    out1 << "max size check" << std::endl;
    out1 << std::endl;

    out1 << myfirst2.max_size() << std::endl;

    out1 << std::endl;
    out1 << "empty check" << std::endl;
    out1 << std::endl;
    ft::multimap<char, int> mymap;

    mymap.insert(std::pair<char, int> ('a', 10));
    mymap.insert(std::pair<char, int>('b', 15));
    mymap.insert(std::pair<char, int>('b', 30));

    while (!mymap.empty())
    {
        out1 << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
        mymap.erase(mymap.begin());
    }

    out1 << std::endl;
    out1 << "insert check" << std::endl;
    out1 << std::endl;

    ft::multimap<char,int> mymultimap;
    ft::multimap<char,int>::iterator multimapit;

    // first insert function version (single parameter):
    mymultimap.insert ( std::pair<char,int>('a',100) );
    mymultimap.insert ( std::pair<char,int>('z',150) );
    multimapit=mymultimap.insert ( std::pair<char,int>('b',75) );

    // second insert function version (wmultimapith hint posmultimapition):
    mymultimap.insert (multimapit, std::pair<char,int>('c',300));  // max efficiency inserting
    mymultimap.insert (multimapit, std::pair<char,int>('z',400));  // no max efficiency inserting

    // third insert function version (range insertion):
    ft::multimap<char,int> anothermultimap;
    anothermultimap.insert(mymultimap.begin(),mymultimap.find('c'));

    // showing contents:
    out1 << "mymultimap contains:\n";
    for (multimapit=mymultimap.begin(); multimapit!=mymultimap.end(); ++multimapit)
        out1 << (*multimapit).first << " => " << (*multimapit).second << '\n';

    out1 << "anothermultimap contains:\n";
    for (multimapit=anothermultimap.begin(); multimapit!=anothermultimap.end(); ++multimapit)
        out1 << (*multimapit).first << " => " << (*multimapit).second << '\n';

    out1 << std::endl;
    out1 << "swap & clear check" << std::endl;
    out1 << std::endl;

    ft::multimap<char, int> myfoo, mybar;

    myfoo.insert(std::pair<char, int>('x', 100));
    myfoo.insert(std::pair<char, int>('y', 200));

    mybar.insert(std::pair<char, int> ('a', 10));
    mybar.insert(std::pair<char, int>('b', 22));
    mybar.insert(std::pair<char, int>('c', 33));

    myfoo.swap(mybar);
    mybar.clear();

    out1 << "foo contains:\n";
    for (ft::multimap<char, int>::iterator it = myfoo.begin(); it != myfoo.end(); ++it)
        out1 << it->first << " => " << it->second << '\n';

    out1 << "bar contains:\n";
    for (ft::multimap<char, int>::iterator it = mybar.begin(); it != mybar.end(); ++it)
        out1 << it->first << " => " << it->second << '\n';

    out1 << std::endl;
    out1 << "key_comp check" << std::endl;
    out1 << std::endl;

    ft::multimap<char, int> mymap3;

    ft::multimap<char, int>::key_compare mycomp = mymap3.key_comp();

    mymap3.insert(std::pair<char, int> ('a', 10));
    mymap3.insert(std::pair<char, int>('b', 200));
    mymap3.insert(std::pair<char, int>('c', 300));

    out1 << "multimap contains:\n";

    char myhighest = mymap3.rbegin()->first; // key value of last element

    ft::multimap<char, int>::iterator myit4 = mymap3.begin();
    do
    {
        out1 << myit4->first << " => " << myit4->second << '\n';
    } while (mycomp((*myit4++).first, myhighest));

    out1 << '\n';

    std::pair<char, int> myhighest2 = *mymap3.rbegin(); // last element

    ft::multimap<char, int>::iterator myit5 = mymap3.begin();
    do
    {
        out1 << myit5->first << " => " << myit5->second << '\n';
    } while (mymap3.value_comp()(*myit5++, myhighest2));

    out1 << '\n';

    out1 << std::endl;
    out1 << "find check" << std::endl;
    out1 << std::endl;

    ft::multimap<char, int> mymap6;
    ft::multimap<char, int>::iterator myit6;

    mymap6.insert(std::pair<char, int> ('a', 10));
    mymap6.insert(std::pair<char, int>('b', 200));
    mymap6.insert(std::pair<char, int>('c', 150));
    mymap6.insert(std::pair<char, int>('d', 200));

    myit6 = mymap6.find('b');
    if (myit6 != mymap6.end())
        mymap6.erase(myit6);

    // print content:
    out1 << "elements in multimap:" << '\n';
    out1 << "a => " << mymap6.find('a')->second << '\n';
    out1 << "c => " << mymap6.find('c')->second << '\n';
    out1 << "d => " << mymap6.find('d')->second << '\n';

    out1 << std::endl;
    out1 << "count check" << std::endl;
    out1 << std::endl;

    std::multimap<char, int> mymap7;
    char myc;

    mymap7.insert(std::pair<char, int> ('a', 10));
    mymap7.insert(std::pair<char, int>('e', 202));
    mymap7.insert(std::pair<char, int>('f', 303));

    for (myc = 'a'; myc < 'h'; myc++)
    {
        out1 << myc;
        if (mymap7.count(myc) > 0)
            out1 << " is an element of multimap.\n";
        else
            out1 << " is not an element of multimap.\n";
    }

    out1 << std::endl;
    out1 << "lower_bound & upper_bound check" << std::endl;
    out1 << std::endl;

    ft::multimap<char, int> mymap8;
    ft::multimap<char, int>::iterator myitlow, myitup;

    mymap8.insert(std::pair<char, int> ('a', 10));
    mymap8.insert(std::pair<char, int>('b', 40));
    mymap8.insert(std::pair<char, int>('c', 60));
    mymap8.insert(std::pair<char, int>('d', 80));
    mymap8.insert(std::pair<char ,int>('e', 100));

    myitlow = mymap8.lower_bound('b'); // myitlow points to b
    myitup = mymap8.upper_bound('d');  // myitup points to e (not d!)

    mymap8.erase(myitlow, myitup); // erases [myitlow,myitup)

    // print content:
    for (ft::multimap<char, int>::iterator it = mymap8.begin(); it != mymap8.end(); ++it)
        out1 << it->first << " => " << it->second << '\n';

    out1 << std::endl;
    out1 << "equal_range check" << std::endl;
    out1 << std::endl;

    ft::multimap<char, int> mymap9;

    mymap9.insert(std::pair<char, int> ('a', 10));
    mymap9.insert(std::pair<char, int>('b', 15));
    mymap9.insert(std::pair<char, int>('b', 30));

    std::pair<ft::multimap<char, int>::iterator, ft::multimap<char, int>::iterator> ret9;
    ret9 = mymap9.equal_range('b');

    out1 << "lower bound points to: ";
    out1 << ret9.first->first << " => " << ret9.first->second << '\n';

    out1 << "upper bound points to: ";
    out1 << ret9.second->first << " => " << ret9.second->second << '\n';

    out1.close();

    ///////////////////////////////////////////////////////////////////////////////////

    out2 << "STLmultimap testing" << std::endl;
    out2 << std::endl;

    std::multimap<char,int> stllfirst;

    stllfirst.insert(std::pair<char,int>('a',10));
    stllfirst.insert(std::pair<char,int>('b',15));
    stllfirst.insert(std::pair<char,int>('b',20));
    stllfirst.insert(std::pair<char,int>('c',25));

    std::multimap<char,int> stllsecond (stllfirst.begin(),stllfirst.end());

    std::multimap<char,int> stllthird (stllsecond);

    std::multimap<char,int,classcomp> stllfourth;                 // class as Compare

    bool(*stllfn_pt)(char,char) = fncomp;
    std::multimap<char,int,bool(*)(char,char)> stllfifth (stllfn_pt);

    out2 << "constructing maps" << std::endl;
    out2 << std::endl;
    std::multimap<char, int> first;

    first.insert(std::pair<char, int> ('a', 10));
    first.insert(std::pair<char, int> ('b', 20));
    first.insert(std::pair<char, int>('c', 80));
    first.insert(std::pair<char, int>('b', 1500));
    for (std::multimap<char, int>::iterator it = first.begin(); it != first.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::multimap<char, int>::reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    std::multimap<char, int> second(first.begin(), first.end());
    for (std::multimap<char, int>::iterator it = second.begin(); it != second.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::multimap<char, int>::reverse_iterator it = second.rbegin(); it != second.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    std::multimap<char, int> third(second);
    for (std::multimap<char, int>::iterator it = third.begin(); it != third.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::multimap<char, int>::reverse_iterator it = third.rbegin(); it != third.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    std::multimap<char, int, classcomp> fourth; // class as Compare
    for (std::multimap<char, int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::multimap<char, int>::reverse_iterator it = fourth.rbegin(); it != fourth.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    bool (*fn_pt)(char, char) = fncomp;
    std::multimap<char, int, bool (*)(char, char)> fifth(fn_pt);
    for (std::multimap<char, int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::multimap<char, int>::reverse_iterator it = fifth.rbegin(); it != fifth.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    out2 << std::endl;
    out2 << "size check" << std::endl;
    out2 << std::endl;
    std::multimap<char, int> first2;
    std::multimap<char, int> second2;

    first2.insert(std::pair<char, int>('x', -8));
    first2.insert(std::pair<char, int>('y', 16));
    first2.insert(std::pair<char, int>('z', 32));

    second2 = first2;               // second2 now contains 3 ints
    first2 = std::multimap<char, int>(); // and first is now empty

    out2 << "Size of first: " << first2.size() << '\n';
    out2 << "Size of second: " << second2.size() << '\n';

    out2 << std::endl;
    out2 << "max size check" << std::endl;
    out2 << std::endl;

    out2 << first2.max_size() << std::endl;

    out2 << std::endl;
    out2 << "empty check" << std::endl;
    out2 << std::endl;
    std::multimap<char, int> stlmap;

    stlmap.insert(std::pair<char, int> ('a', 10));
    stlmap.insert(std::pair<char, int>('b', 15));
    stlmap.insert(std::pair<char, int>('b', 30));

    while (!stlmap.empty())
    {
        out2 << stlmap.begin()->first << " => " << stlmap.begin()->second << '\n';
        stlmap.erase(stlmap.begin());
    }

    out2 << std::endl;
    out2 << "insert check" << std::endl;
    out2 << std::endl;

    ft::multimap<char,int> stllmultimap;
    ft::multimap<char,int>::iterator stllmultimapit;

    // first insert function version (single parameter):
    stllmultimap.insert ( std::pair<char,int>('a',100) );
    stllmultimap.insert ( std::pair<char,int>('z',150) );
    stllmultimapit=stllmultimap.insert ( std::pair<char,int>('b',75) );

    // second insert function version (wmultimapith hint posmultimapition):
    stllmultimap.insert (stllmultimapit, std::pair<char,int>('c',300));  // max efficiency inserting
    stllmultimap.insert (stllmultimapit, std::pair<char,int>('z',400));  // no max efficiency inserting

    // third insert function version (range insertion):
    ft::multimap<char,int> stllanothermultimap;
    stllanothermultimap.insert(stllmultimap.begin(),stllmultimap.find('c'));

    // showing contents:
    out2 << "mymultimap contains:\n";
    for (stllmultimapit=stllmultimap.begin(); stllmultimapit!=stllmultimap.end(); ++stllmultimapit)
        out2 << (*stllmultimapit).first << " => " << (*stllmultimapit).second << '\n';

    out2 << "anothermultimap contains:\n";
    for (stllmultimapit=stllanothermultimap.begin(); stllmultimapit!=stllanothermultimap.end(); ++stllmultimapit)
        out2 << (*stllmultimapit).first << " => " << (*stllmultimapit).second << '\n';

    out2 << std::endl;
    out2 << "swap & clear check" << std::endl;
    out2 << std::endl;

    std::multimap<char, int> stlfoo, stlbar;

    stlfoo.insert(std::pair<char, int>('x', 100));
    stlfoo.insert(std::pair<char, int>('y', 200));

    stlbar.insert(std::pair<char, int> ('a', 10));
    stlbar.insert(std::pair<char, int>('b', 22));
    stlbar.insert(std::pair<char, int>('c', 33));

    stlfoo.swap(stlbar);
    stlbar.clear();

    out2 << "foo contains:\n";
    for (std::multimap<char, int>::iterator it = stlfoo.begin(); it != stlfoo.end(); ++it)
        out2 << it->first << " => " << it->second << '\n';

    out2 << "bar contains:\n";
    for (std::multimap<char, int>::iterator it = stlbar.begin(); it != stlbar.end(); ++it)
        out2 << it->first << " => " << it->second << '\n';

    out2 << std::endl;
    out2 << "key_comp check" << std::endl;
    out2 << std::endl;

    std::multimap<char, int> stlmap3;

    std::multimap<char, int>::key_compare stlcomp = stlmap3.key_comp();

    stlmap3.insert(std::pair<char, int> ('a', 10));
    stlmap3.insert(std::pair<char, int>('b', 200));
    stlmap3.insert(std::pair<char, int>('c', 300));

    out2 << "multimap contains:\n";

    char stlhighest = stlmap3.rbegin()->first; // key value of last element

    std::multimap<char, int>::iterator stlit4 = stlmap3.begin();
    do
    {
        out2 << stlit4->first << " => " << stlit4->second << '\n';
    } while (stlcomp((*stlit4++).first, stlhighest));

    out2 << '\n';

    std::pair<char, int> stlhighest2 = *stlmap3.rbegin(); // last element

    std::multimap<char, int>::iterator stlit5 = stlmap3.begin();
    do
    {
        out2 << stlit5->first << " => " << stlit5->second << '\n';
    } while (stlmap3.value_comp()(*stlit5++, stlhighest2));

    out2 << '\n';

    out2 << std::endl;
    out2 << "find check" << std::endl;
    out2 << std::endl;

    std::multimap<char, int> stlmap6;
    std::multimap<char, int>::iterator stlit6;

    stlmap6.insert(std::pair<char, int> ('a', 10));
    stlmap6.insert(std::pair<char, int>('b', 200));
    stlmap6.insert(std::pair<char, int>('c', 150));
    stlmap6.insert(std::pair<char, int>('d', 200));

    stlit6 = stlmap6.find('b');
    if (stlit6 != stlmap6.end())
        stlmap6.erase(stlit6);

    // print content:
    out2 << "elements in multimap:" << '\n';
    out2 << "a => " << stlmap6.find('a')->second << '\n';
    out2 << "c => " << stlmap6.find('c')->second << '\n';
    out2 << "d => " << stlmap6.find('d')->second << '\n';

    out2 << std::endl;
    out2 << "count check" << std::endl;
    out2 << std::endl;

    std::multimap<char, int> stlmap7;
    char stlc;

    stlmap7.insert(std::pair<char, int> ('a', 10));
    stlmap7.insert(std::pair<char, int>('e', 202));
    stlmap7.insert(std::pair<char, int>('f', 303));

    for (stlc = 'a'; stlc < 'h'; stlc++)
    {
        out2 << stlc;
        if (stlmap7.count(stlc) > 0)
            out2 << " is an element of multimap.\n";
        else
            out2 << " is not an element of multimap.\n";
    }

    out2 << std::endl;
    out2 << "lower_bound & upper_bound check" << std::endl;
    out2 << std::endl;

    std::multimap<char, int> stlmap8;
    std::multimap<char, int>::iterator stlitlow, stlitup;

    stlmap8.insert(std::pair<char, int> ('a', 10));
    stlmap8.insert(std::pair<char, int>('b', 40));
    stlmap8.insert(std::pair<char, int>('c', 60));
    stlmap8.insert(std::pair<char, int>('d', 80));
    stlmap8.insert(std::pair<char ,int>('e', 100));

    stlitlow = stlmap8.lower_bound('b'); // stlitlow points to b
    stlitup = stlmap8.upper_bound('d');  // stlitup points to e (not d!)

    stlmap8.erase(stlitlow, stlitup); // erases [stlitlow,stlitup)

    // print content:
    for (std::multimap<char, int>::iterator it = stlmap8.begin(); it != stlmap8.end(); ++it)
        out2 << it->first << " => " << it->second << '\n';

    out2 << std::endl;
    out2 << "equal_range check" << std::endl;
    out2 << std::endl;

    std::multimap<char, int> stlmap9;

    stlmap9.insert(std::pair<char, int> ('a', 10));
    stlmap9.insert(std::pair<char, int>('b', 15));
    stlmap9.insert(std::pair<char, int>('b', 30));

    std::pair<std::multimap<char, int>::iterator, std::multimap<char, int>::iterator> stlret9;
    stlret9 = stlmap9.equal_range('b');

    out2 << "lower bound points to: ";
    out2 << stlret9.first->first << " => " << stlret9.first->second << '\n';

    out2 << "upper bound points to: ";
    out2 << stlret9.second->first << " => " << stlret9.second->second << '\n';

    out2.close();
    return (0);
}
