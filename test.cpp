#include <iostream>
#include <map>

int main ()
{
  std::map<char,int> mymap;
  

  mymap['x']=1001;
  mymap['y']=4004;
  mymap['z']=3003;

  std::cout << "mymap contains:\n";

  std::pair<char,int> highest = *mymap.rbegin();          // last element

  std::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

  char highest2 = mymap.rbegin()->first;     // key value of last element
  std::map<char,int>::key_compare mycomp = mymap.key_comp();
  it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mycomp((*it++).first, highest2) );

  return 0;
}