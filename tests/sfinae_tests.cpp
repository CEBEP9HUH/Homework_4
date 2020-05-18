#include <gtest/gtest.h>
#include <sstream>

#include "ip_printing.hpp"

TEST(SFINAE, string_test)
{
    std::stringstream ss;
    std::string result = "\n";
    ip_printing::print_as_ip(result, ss);
    result+='\n';
    ASSERT_STREQ(ss.str().c_str(), result.c_str());
}

template<size_t size, typename T>
std::enable_if_t<std::is_integral_v<T>, void> 
check(T in_arr[size], std::string out_arr[size])
{
    std::stringstream ss;
    for(size_t i = 0; i < size; ++i)
    {
        ip_printing::print_as_ip(in_arr[i], ss);
        ASSERT_STREQ(ss.str().c_str(), out_arr[i].c_str());
        ss.str("");
    }
}

TEST(SFINAE, integral_test)
{
    const size_t size = 3;
    int32_t int_in_arr[size] = {0, 1, 2130706433};
    std::string int_out_arr[size] = {"0.0.0.0\n", "0.0.0.1\n", "127.0.0.1\n"};
    check<size>(int_in_arr, int_out_arr);
    
    unsigned char uchar_in_arr[size] = {0, 1, 127};
    std::string uchar_out_arr[size] = {"0\n", "1\n", "127\n"};
    check<size>(uchar_in_arr, uchar_out_arr);
    
    int16_t short_in_arr[size] = {0, -1, 127};
    std::string short_out_arr[size] = {"0.0\n", "255.255\n", "0.127\n"};
    check<size>(short_in_arr, short_out_arr);
}

TEST(SFINAE, container_test)
{
    std::stringstream ss;

    std::vector in_vector = {1,2,3,4};
    std::string out_vector = "1.2.3.4\n";
    ip_printing::print_as_ip(in_vector, ss);
    ASSERT_STREQ(ss.str().c_str(), out_vector.c_str());
    ss.str("");

    std::list in_list = {"1","5567","3","22"};
    std::string out_list = "1.5567.3.22\n";
    ip_printing::print_as_ip(in_list, ss);
    ASSERT_STREQ(ss.str().c_str(), out_list.c_str());
    ss.str("");

    std::forward_list in_flist = {"h","e","l","l","o"};
    std::string out_flist = "h.e.l.l.o\n";
    ip_printing::print_as_ip(in_flist, ss);
    ASSERT_STREQ(ss.str().c_str(), out_flist.c_str());
    ss.str("");
}

TEST(SFINAE, tuple_test)
{
    std::stringstream ss;

    ip_printing::print_as_ip(std::make_tuple(1,2), ss);
    std::string out_tuple_1 = "1.2\n";
    ASSERT_STREQ(ss.str().c_str(), out_tuple_1.c_str());
    ss.str("");

    ip_printing::print_as_ip(std::make_tuple('t','u','p','l','e'), ss);
    std::string out_tuple_2 = "t.u.p.l.e\n";
    ASSERT_STREQ(ss.str().c_str(), out_tuple_2.c_str());
    ss.str("");
}