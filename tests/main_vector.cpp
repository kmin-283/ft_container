/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 10:06:39 by kmin              #+#    #+#             */
/*   Updated: 2020/10/31 16:44:44 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "../Vector/vector.hpp"

int main()
{
    ft::vector<int> v;
    ft::vector<int> v2(10, 0);
    ft::vector<int>::iterator it;
    // for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;
    std::cout << "=======================" << std::endl;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    it = v.begin();
    ++it;
    ++it;
    v.insert(it, 4, 150);
    

    int myarray[] = {501, 502, 503};
    v.insert(v.begin(), myarray, myarray + 3);
    // v.insert(it, v2.begin(), v2.end());

    for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    // while (1);
    return (0);
}