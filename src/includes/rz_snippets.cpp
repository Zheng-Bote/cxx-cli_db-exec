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
            std::cout << "\033[0;32m" << "OK: " << msg << "\e[0m" << std::endl;
            oknok = true;
            break;
        case Status::WARNING:
            std::cerr << "\033[0;33m" << "WARNING: " << msg << "\e[0m" << std::endl;
            oknok = false;
            break;
        case Status::ERROR:
            std::cerr << "\033[0;31m" << "ERROR: " << msg << "\e[0m" << std::endl;
            oknok = false;
            break;
        case Status::FATAL:
            std::cerr << "\033[0;31m" << "FATAL: " << msg << "\e[0m" << std::endl;
            exit(EXIT_FAILURE);
            break;
        }
    }
    else
    {
        std::cout << "\033[0;32m" << "OK: " << msg << "\e[0m" << std::endl;
        oknok = true;
    }
    return oknok;
}

template <typename CharT>
inline tstring<CharT> Snippets::trim(tstring<CharT> &text)
{
    return tstring<CharT>();
}