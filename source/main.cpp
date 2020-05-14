#include <iostream>
#include "ip_printing.hpp"

int main()
{
    ip_printing::print_as_ip(char(-1));
    ip_printing::print_as_ip(short(0));
    ip_printing::print_as_ip(int(2130706433));
    ip_printing::print_as_ip(long(8875824491850138409));
    
    ip_printing::print_as_ip(std::make_tuple(1,2,3,4));
    return 0;
}