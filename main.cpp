/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmin <kmin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:05:25 by kmin              #+#    #+#             */
/*   Updated: 2020/10/12 18:09:29 by kmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <list>
// #include "List/List.hpp"
#include <iostream>
struct A
{
    int b;
};

struct B : public A
{
    B(A b)
        : A(b)
    {}
};

struct C : public B
{
    C();
    C(A b)
        : B(b)
    {}
};


int main()
{
    struct A a;
    struct C c(a);
    c.b = 1;
    std::cout << c.b << std::endl;
    return (0);
}