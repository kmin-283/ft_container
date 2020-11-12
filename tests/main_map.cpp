/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:20:05 by kmin              #+#    #+#             */
/*   Updated: 2020/11/12 19:00:56 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Map/map.hpp"
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

    out1 << "mymap testing" << std::endl;
    out1 << std::endl;

    out1 << "constructing maps" << std::endl;
    out1 << std::endl;
    ft::map<char, int> myfirst;

    myfirst['a'] = 10;
    myfirst['b'] = 30;
    myfirst['c'] = 50;
    myfirst['d'] = 70;

    for (ft::map<char, int>::iterator it = myfirst.begin(); it != myfirst.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::map<char, int>::reverse_iterator it = myfirst.rbegin(); it != myfirst.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    ft::map<char, int> mysecond(myfirst.begin(), myfirst.end());
    for (ft::map<char, int>::iterator it = mysecond.begin(); it != mysecond.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::map<char, int>::reverse_iterator it = mysecond.rbegin(); it != mysecond.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    ft::map<char, int> mythird(mysecond);
    for (ft::map<char, int>::iterator it = mythird.begin(); it != mythird.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::map<char, int>::reverse_iterator it = mythird.rbegin(); it != mythird.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    ft::map<char, int, classcomp> myfourth; // class as Compare
    for (ft::map<char, int>::iterator it = myfourth.begin(); it != myfourth.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::map<char, int>::reverse_iterator it = myfourth.rbegin(); it != myfourth.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    bool (*myfn_pt)(char, char) = fncomp;
    ft::map<char, int, bool (*)(char, char)> myfifth(myfn_pt);
    for (ft::map<char, int>::iterator it = myfifth.begin(); it != myfifth.end(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    for (ft::map<char, int>::reverse_iterator it = myfifth.rbegin(); it != myfifth.rend(); ++it)
        out1 << it->first << " " << it->second;
    out1 << std::endl;

    out1 << std::endl;
    out1 << "size check" << std::endl;
    out1 << std::endl;
    ft::map<char, int> myfirst2;
    ft::map<char, int> mysecond2;

    myfirst2['x'] = 8;
    myfirst2['y'] = 16;
    myfirst2['z'] = 32;

    mysecond2 = myfirst2;            // mysecond2 now contains 3 ints
    myfirst2 = ft::map<char, int>(); // and first is now empty

    out1 << "Size of first: " << myfirst2.size() << '\n';
    out1 << "Size of second: " << mysecond2.size() << '\n';

    out1 << std::endl;
    out1 << "max size check" << std::endl;
    out1 << std::endl;

    out1 << myfirst2.max_size() << std::endl;

    out1 << std::endl;
    out1 << "empty check" << std::endl;
    out1 << std::endl;
    ft::map<char, int> mymap;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;

    while (!mymap.empty())
    {
        out1 << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
        mymap.erase(mymap.begin());
    }

    out1 << std::endl;
    out1 << "insert check" << std::endl;
    out1 << std::endl;

    ft::map<char, int> mymap2;

    // first insert function version (single parameter):
    mymap2.insert(std::pair<char, int>('a', 100));
    mymap2.insert(std::pair<char, int>('z', 200));

    std::pair<ft::map<char, int>::iterator, bool> ret;

    ret = mymap2.insert(std::pair<char, int>('z', 500));
    if (ret.second == false)
    {
        out1 << "element 'z' already existed";
        out1 << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    ft::map<char, int>::iterator it = mymap2.begin();
    mymap2.insert(it, std::pair<char, int>('b', 300)); // max efficiency inserting
    mymap2.insert(it, std::pair<char, int>('c', 400)); // no max efficiency inserting

    // third insert function version (range insertion):
    ft::map<char, int> anothermap;
    anothermap.insert(mymap2.begin(), mymap2.find('c'));

    // showing contents:
    out1 << "map2 contains:\n";
    for (it = mymap2.begin(); it != mymap2.end(); ++it)
        out1 << it->first << " => " << it->second << '\n';

    out1 << "anothermap contains:\n";
    for (it = anothermap.begin(); it != anothermap.end(); ++it)
        out1 << it->first << " => " << it->second << '\n';

    out1 << std::endl;
    out1 << "swap & clear check" << std::endl;
    out1 << std::endl;

    ft::map<char, int> myfoo, mybar;

    myfoo['x'] = 100;
    myfoo['y'] = 200;

    mybar['a'] = 11;
    mybar['b'] = 22;
    mybar['c'] = 33;

    myfoo.swap(mybar);
    mybar.clear();

    out1 << "foo contains:\n";
    for (ft::map<char, int>::iterator it = myfoo.begin(); it != myfoo.end(); ++it)
        out1 << it->first << " => " << it->second << '\n';

    out1 << "bar contains:\n";
    for (ft::map<char, int>::iterator it = mybar.begin(); it != mybar.end(); ++it)
        out1 << it->first << " => " << it->second << '\n';

    out1 << std::endl;
    out1 << "key_comp check" << std::endl;
    out1 << std::endl;

    ft::map<char, int> mymap3;

    ft::map<char, int>::key_compare mycomp = mymap3.key_comp();

    mymap3['a'] = 100;
    mymap3['b'] = 200;
    mymap3['c'] = 300;

    out1 << "map contains:\n";

    char myhighest = mymap3.rbegin()->first; // key value of last element

    ft::map<char, int>::iterator myit4 = mymap3.begin();
    do
    {
        out1 << myit4->first << " => " << myit4->second << '\n';
    } while (mycomp((*myit4++).first, myhighest));

    out1 << '\n';

    std::pair<char, int> myhighest2 = *mymap3.rbegin(); // last element

    ft::map<char, int>::iterator myit5 = mymap3.begin();
    do
    {
        out1 << myit5->first << " => " << myit5->second << '\n';
    } while (mymap3.value_comp()(*myit5++, myhighest2));

    out1 << '\n';

    out1 << std::endl;
    out1 << "find check" << std::endl;
    out1 << std::endl;

    ft::map<char, int> mymap6;
    ft::map<char, int>::iterator myit6;

    mymap6['a'] = 50;
    mymap6['b'] = 100;
    mymap6['c'] = 150;
    mymap6['d'] = 200;

    myit6 = mymap6.find('b');
    if (myit6 != mymap6.end())
        mymap6.erase(myit6);

    // print content:
    out1 << "elements in map:" << '\n';
    out1 << "a => " << mymap6.find('a')->second << '\n';
    out1 << "c => " << mymap6.find('c')->second << '\n';
    out1 << "d => " << mymap6.find('d')->second << '\n';

    out1 << std::endl;
    out1 << "count check" << std::endl;
    out1 << std::endl;

    std::map<char, int> mymap7;
    char myc;

    mymap7['a'] = 101;
    mymap7['c'] = 202;
    mymap7['f'] = 303;

    for (myc = 'a'; myc < 'h'; myc++)
    {
        out1 << myc;
        if (mymap7.count(myc) > 0)
            out1 << " is an element of map.\n";
        else
            out1 << " is not an element of map.\n";
    }

    out1 << std::endl;
    out1 << "lower_bound & upper_bound check" << std::endl;
    out1 << std::endl;

    ft::map<char, int> mymap8;
    ft::map<char, int>::iterator myitlow, myitup;

    mymap8['a'] = 20;
    mymap8['b'] = 40;
    mymap8['c'] = 60;
    mymap8['d'] = 80;
    mymap8['e'] = 100;

    myitlow = mymap8.lower_bound('b'); // myitlow points to b
    myitup = mymap8.upper_bound('d');  // myitup points to e (not d!)

    mymap8.erase(myitlow, myitup); // erases [myitlow,myitup)

    // print content:
    for (ft::map<char, int>::iterator it = mymap8.begin(); it != mymap8.end(); ++it)
        out1 << it->first << " => " << it->second << '\n';

    out1 << std::endl;
    out1 << "equal_range check" << std::endl;
    out1 << std::endl;

    ft::map<char, int> mymap9;

    mymap9['a'] = 10;
    mymap9['b'] = 20;
    mymap9['c'] = 30;

    std::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret9;
    ret9 = mymap9.equal_range('b');

    out1 << "lower bound points to: ";
    out1 << ret9.first->first << " => " << ret9.first->second << '\n';

    out1 << "upper bound points to: ";
    out1 << ret9.second->first << " => " << ret9.second->second << '\n';

    out1.close();

    ///////////////////////////////////////////////////////////////////////////////////

    out2 << "STLmap testing" << std::endl;
    out2 << std::endl;
    out2 << "constructing maps" << std::endl;
    out2 << std::endl;
    std::map<char, int> first;

    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;
    for (std::map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::map<char, int>::reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    std::map<char, int> second(first.begin(), first.end());
    for (std::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::map<char, int>::reverse_iterator it = second.rbegin(); it != second.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    std::map<char, int> third(second);
    for (std::map<char, int>::iterator it = third.begin(); it != third.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::map<char, int>::reverse_iterator it = third.rbegin(); it != third.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    std::map<char, int, classcomp> fourth; // class as Compare
    for (std::map<char, int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::map<char, int>::reverse_iterator it = fourth.rbegin(); it != fourth.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    bool (*fn_pt)(char, char) = fncomp;
    std::map<char, int, bool (*)(char, char)> fifth(fn_pt);
    for (std::map<char, int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    for (std::map<char, int>::reverse_iterator it = fifth.rbegin(); it != fifth.rend(); ++it)
        out2 << it->first << " " << it->second;
    out2 << std::endl;

    out2 << std::endl;
    out2 << "size check" << std::endl;
    out2 << std::endl;
    std::map<char, int> first2;
    std::map<char, int> second2;

    first2['x'] = 8;
    first2['y'] = 16;
    first2['z'] = 32;

    second2 = first2;               // second2 now contains 3 ints
    first2 = std::map<char, int>(); // and first is now empty

    out2 << "Size of first: " << first2.size() << '\n';
    out2 << "Size of second: " << second2.size() << '\n';

    out2 << std::endl;
    out2 << "max size check" << std::endl;
    out2 << std::endl;

    out2 << first2.max_size() << std::endl;

    out2 << std::endl;
    out2 << "empty check" << std::endl;
    out2 << std::endl;
    std::map<char, int> stlmap;

    stlmap['a'] = 10;
    stlmap['b'] = 20;
    stlmap['c'] = 30;

    while (!stlmap.empty())
    {
        out2 << stlmap.begin()->first << " => " << stlmap.begin()->second << '\n';
        stlmap.erase(stlmap.begin());
    }

    out2 << std::endl;
    out2 << "insert check" << std::endl;
    out2 << std::endl;

    std::map<char, int> stlmap2;

    // first insert function version (single parameter):
    stlmap2.insert(std::pair<char, int>('a', 100));
    stlmap2.insert(std::pair<char, int>('z', 200));

    std::pair<std::map<char, int>::iterator, bool> ret2;

    ret2 = stlmap2.insert(std::pair<char, int>('z', 500));
    if (ret.second == false)
    {
        out2 << "element 'z' already existed";
        out2 << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    std::map<char, int>::iterator it2 = stlmap2.begin();
    stlmap2.insert(it2, std::pair<char, int>('b', 300)); // max efficiency inserting
    stlmap2.insert(it2, std::pair<char, int>('c', 400)); // no max efficiency inserting

    // third insert function version (range insertion):
    std::map<char, int> anothermap2;
    anothermap2.insert(stlmap2.begin(), stlmap2.find('c'));

    // showing contents:
    out2 << "map2 contains:\n";
    for (it2 = stlmap2.begin(); it2 != stlmap2.end(); ++it2)
        out2 << it2->first << " => " << it2->second << '\n';

    out2 << "anothermap contains:\n";
    for (it2 = anothermap2.begin(); it2 != anothermap2.end(); ++it2)
        out2 << it2->first << " => " << it2->second << '\n';

    out2 << std::endl;
    out2 << "swap & clear check" << std::endl;
    out2 << std::endl;

    std::map<char, int> stlfoo, stlbar;

    stlfoo['x'] = 100;
    stlfoo['y'] = 200;

    stlbar['a'] = 11;
    stlbar['b'] = 22;
    stlbar['c'] = 33;

    stlfoo.swap(stlbar);
    stlbar.clear();

    out2 << "foo contains:\n";
    for (std::map<char, int>::iterator it = stlfoo.begin(); it != stlfoo.end(); ++it)
        out2 << it->first << " => " << it->second << '\n';

    out2 << "bar contains:\n";
    for (std::map<char, int>::iterator it = stlbar.begin(); it != stlbar.end(); ++it)
        out2 << it->first << " => " << it->second << '\n';

    out2 << std::endl;
    out2 << "key_comp check" << std::endl;
    out2 << std::endl;

    std::map<char, int> stlmap3;

    std::map<char, int>::key_compare stlcomp = stlmap3.key_comp();

    stlmap3['a'] = 100;
    stlmap3['b'] = 200;
    stlmap3['c'] = 300;

    out2 << "map contains:\n";

    char stlhighest = stlmap3.rbegin()->first; // key value of last element

    std::map<char, int>::iterator stlit4 = stlmap3.begin();
    do
    {
        out2 << stlit4->first << " => " << stlit4->second << '\n';
    } while (stlcomp((*stlit4++).first, stlhighest));

    out2 << '\n';

    std::pair<char, int> stlhighest2 = *stlmap3.rbegin(); // last element

    std::map<char, int>::iterator stlit5 = stlmap3.begin();
    do
    {
        out2 << stlit5->first << " => " << stlit5->second << '\n';
    } while (stlmap3.value_comp()(*stlit5++, stlhighest2));

    out2 << '\n';

    out2 << std::endl;
    out2 << "find check" << std::endl;
    out2 << std::endl;

    std::map<char, int> stlmap6;
    std::map<char, int>::iterator stlit6;

    stlmap6['a'] = 50;
    stlmap6['b'] = 100;
    stlmap6['c'] = 150;
    stlmap6['d'] = 200;

    stlit6 = stlmap6.find('b');
    if (stlit6 != stlmap6.end())
        stlmap6.erase(stlit6);

    // print content:
    out2 << "elements in map:" << '\n';
    out2 << "a => " << stlmap6.find('a')->second << '\n';
    out2 << "c => " << stlmap6.find('c')->second << '\n';
    out2 << "d => " << stlmap6.find('d')->second << '\n';

    out2 << std::endl;
    out2 << "count check" << std::endl;
    out2 << std::endl;

    std::map<char, int> stlmap7;
    char stlc;

    stlmap7['a'] = 101;
    stlmap7['c'] = 202;
    stlmap7['f'] = 303;

    for (stlc = 'a'; stlc < 'h'; stlc++)
    {
        out2 << stlc;
        if (stlmap7.count(stlc) > 0)
            out2 << " is an element of map.\n";
        else
            out2 << " is not an element of map.\n";
    }

    out2 << std::endl;
    out2 << "lower_bound & upper_bound check" << std::endl;
    out2 << std::endl;

    std::map<char, int> stlmap8;
    std::map<char, int>::iterator stlitlow, stlitup;

    stlmap8['a'] = 20;
    stlmap8['b'] = 40;
    stlmap8['c'] = 60;
    stlmap8['d'] = 80;
    stlmap8['e'] = 100;

    stlitlow = stlmap8.lower_bound('b'); // stlitlow points to b
    stlitup = stlmap8.upper_bound('d');  // stlitup points to e (not d!)

    stlmap8.erase(stlitlow, stlitup); // erases [stlitlow,stlitup)

    // print content:
    for (std::map<char, int>::iterator it = stlmap8.begin(); it != stlmap8.end(); ++it)
        out2 << it->first << " => " << it->second << '\n';

    out2 << std::endl;
    out2 << "equal_range check" << std::endl;
    out2 << std::endl;

    std::map<char, int> stlmap9;

    stlmap9['a'] = 10;
    stlmap9['b'] = 20;
    stlmap9['c'] = 30;

    std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> stlret9;
    stlret9 = stlmap9.equal_range('b');

    out2 << "lower bound points to: ";
    out2 << stlret9.first->first << " => " << stlret9.first->second << '\n';

    out2 << "upper bound points to: ";
    out2 << stlret9.second->first << " => " << stlret9.second->second << '\n';

    out2.close();
    return (0);
}
