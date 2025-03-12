#include "rz_snippets.h"

#include <format>
#include <print>
#include <format>
#include <iostream>

#include "rz_config.h"

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
    return std::format("call: {} ini dev type", aboutStruct.PROGEXECNAME);
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
        switch (status)
        {
        case Status::OK:
            break;
        case Status::ERROR:
            std::cerr << "\n\033[0;31m" << "ERROR: " << msg << "\n\x1B[39m" << std::endl;
            oknok = false;
            break;
        case Status::FATAL:
            std::cerr << "\n\033[0;31m" << "FATAL: " << msg << "\n\x1B[39m" << std::endl;
            exit(EXIT_FAILURE);
            break;
        }
    }
    return oknok;
}
