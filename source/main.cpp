#include <iostream>
#include "ip_printing.hpp"


/**
 * @mainpage Print_ip
 * This app is for converting different data types into ip address (OTUS homework #4).
 **/
/**
 * @brief entrance point of programm
 **/
int main()
{
    ip_printing::print_as_ip(char(-1));
    ip_printing::print_as_ip(short(0));
    ip_printing::print_as_ip(int(2130706433));
    ip_printing::print_as_ip(long(8875824491850138409));
    ip_printing::print_as_ip(std::string("It's a string"));
    std::vector<char> char_v{'v','e','c','t','o','r'};
    ip_printing::print_as_ip(char_v);
    std::list<char> char_l{'l','i','s','t'};
    ip_printing::print_as_ip(char_l);
    ip_printing::print_as_ip(std::make_tuple('t','u','p','l','e'));
    return 0;
}