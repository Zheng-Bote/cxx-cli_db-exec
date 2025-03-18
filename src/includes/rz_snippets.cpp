/**
 * @file rz_snippets.hpp
 * @author ZHENG Bote (robert.hase-zheng.net)
 * @brief CXX23 classlib with snippets
 * @details ragpicker for unsorted methods
 * @version 1.1.0
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023 ZHENG Robert
 *
 */

#include "rz_snippets.h"

#include <format>
#include <print>
#include <format>
#include <iostream>

#include "rz_config.h"

template <typename CharT>
using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

template <typename CharT>
using tstringstream = std::basic_stringstream<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

/**
 * @brief Snippets::Snippets
 */
Snippets::Snippets() {}

/**
 * @brief Snippets::~Snippets
 */
Snippets::~Snippets()
{
}

/**
 * @brief helpSyntax
 * @details call: rz_snippets db_ini sql_ini env type
 *
 * @return std::string
 */
std::string Snippets::helpSyntax()
{
    AboutType aboutStruct;
    return std::format("call: {} db_ini sql_ini env type", aboutStruct.PROGEXECNAME);
}

/**
 * @brief Snippets::checkFunctionReturn
 * @param ret (tuple <bool, string>; from called function)
 * @param statusInstruction (OK, ERROR, FATAL, how to handle the ret value)
 * @return bool
 * @description false & ERROR: PLOG_ERROR & return bool, fasle & FATAL: PLOG_FATAL & exit(1)
 */
bool Snippets::checkFunctionReturn(const std::tuple<bool, std::string> &ret,
                                   Status statusInstruction)
{
    bool oknok{false};
    Status status = statusInstruction;
    std::string msg{"blank"};
    std::tie(oknok, msg) = ret;

    if (!oknok)
    {
        // std::cerr << std::format("checkFunction NOK: {}", msg);
        // \e[0m	Reset // \x1B[39m
        switch (status)
        {
        case Status::OK:
            PLOG(plog::info) << msg;
            // std::cout << "\033[0;32m" << "OK: " << msg << "\e[0m" << std::endl;
            oknok = true;
            break;
        case Status::WARNING:
            PLOG(plog::warning) << msg;
            // std::cerr << "\033[0;33m" << "WARNING: " << msg << "\e[0m" << std::endl;
            oknok = false;
            break;
        case Status::ERROR:
            PLOG(plog::error) << msg;
            // std::cerr << "\033[0;31m" << "ERROR: " << msg << "\e[0m" << std::endl;
            oknok = false;
            break;
        case Status::FATAL:
            PLOG(plog::fatal) << msg;
            // std::cerr << "\033[0;31m" << "FATAL: " << msg << "\e[0m" << std::endl;
            exit(EXIT_FAILURE);
            break;
        }
    }
    else
    {
        PLOG(plog::debug) << msg;
        // std::cout << "\033[0;32m" << "OK: " << msg << "\e[0m" << std::endl;
        oknok = true;
    }
    return oknok;
}
