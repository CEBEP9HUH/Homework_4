#pragma once
#include <ostream>
#include <vector>
#include <list>
#include <forward_list>
#include <type_traits>
#include <tuple>

namespace ip_printing
{
    template<typename T>                struct is_ip_container                              : std::false_type {};
    template<typename... Args>          struct is_ip_container<std::vector<Args...> >       : std::true_type  {};
    template<typename... Args>          struct is_ip_container<std::list<Args...> >         : std::true_type  {};
    template<typename... Args>          struct is_ip_container<std::forward_list<Args...> > : std::true_type  {};


    template<typename T>
    typename std::enable_if_t<std::is_same_v<T, std::__cxx11::string>, void > 
    print_as_ip(const T& val, std::ostream& out = std::cout)
    {
        out << val << "\n";
    }

    template<class T>
    typename std::enable_if_t<std::is_integral_v<T>, void> 
    print_as_ip(const T val, std::ostream& out = std::cout)
    {
        const int bits_in_byte = 8;
        int size = sizeof(val) * bits_in_byte;
        for(int i = 0, offset = size; offset > 0; ++i)
        {
            offset = size - bits_in_byte * (i + 1);
            out << ((val >> offset) & 0xFF);
            if(offset > 0)
            {
                out << ".";
            }
        }
        out << "\n";
    }

    template<template <class,
                        class> class C,
            class A,
            class B>
    typename std::enable_if_t<is_ip_container<C<A,B> >::value, void> 
    print_as_ip(const C<A,B>& val, std::ostream& out = std::cout)
    {
        for(auto it = val.cbegin(); it != val.cend(); ++it)
        {
            if(it != val.cbegin())
            {
                out << ".";
            }
            out << *it;
        }
        out << "\n";
    }


    template<size_t I = 0, typename... Args>
    typename std::enable_if_t<I == sizeof...(Args) - 1 && std::is_same_v<typename std::tuple_element_t<I, std::tuple<Args...> >, typename std::tuple_element_t<0, std::tuple<Args...> > >, void> 
    print_as_ip(const std::tuple<Args...>& val, std::ostream& out = std::cout)
    {
        if(I > 0)
            out << ".";
        out << std::get<I>(val) << "\n";
    }

    template<size_t I = 0, typename... Args>
    typename std::enable_if_t<I < sizeof...(Args) - 1 && std::is_same_v<typename std::tuple_element_t<I, std::tuple<Args...> >, typename std::tuple_element_t<0, std::tuple<Args...> > >, void> 
    print_as_ip(const std::tuple<Args...>& val, std::ostream& out = std::cout)
    {
        if(I > 0)
            out << ".";
        out << std::get<I>(val);
        print_as_ip<I + 1, Args...>(val, out);
    }
}