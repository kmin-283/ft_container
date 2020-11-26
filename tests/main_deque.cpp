/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_deque.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:15:54 by kmin              #+#    #+#             */
/*   Updated: 2020/11/26 21:37:09 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Deque/deque.hpp"
#include <deque>
#include <iostream>

int main()
{
    std::deque<int> stldq;
    ft::deque<int> dq;
    int *p;
    unsigned int i;

    for (auto it = stldq.begin(); it != stldq.end();++it)
        std::cout << *it << " ";
    std::cout <<std::endl;
    std::cout << "allocator test" << std::endl;

    p = dq.getAllocator().allocate(5);
    for (i=0; i<5; i++) dq.getAllocator().construct(&p[i],i);
    std::cout << "The allocated array contains:";
    for (i=0; i<5; i++) std::cout << ' ' << p[i];
    std::cout << '\n';

    // destroy and deallocate:
    for (i=0; i<5; i++) dq.getAllocator().destroy(&p[i]);
    dq.getAllocator().deallocate(p,5);

    std::cout << "max_size test" << std::endl;

    std::cout << dq.max_size() << std::endl;


    return (0);
}