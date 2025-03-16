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

#pragma once

#include <print>
#include <string>
#include <tuple>

#include "rz_config.h"

class Snippets
{
public:
    Snippets();
    ~Snippets();

    struct AboutType
    {
        const std::string PROGEXECNAME = PROG_EXEC_NAME;
        const std::string PROGNAME = PROG_NAME;
        const std::string PROGVERSION = PROG_VERSION;
        const std::string PROGHOMEPAGE = PROG_HOMEPAGE;
        const std::string PROGDESCRIPTION = PROG_DESCRIPTION;
        const std::string PROGBUILDTYPE = PROG_BUILD_TYPE;

        std::string getProgInfo() const noexcept { return std::format("{} v{}-{}\n{}\n{}", PROGNAME, PROGVERSION, PROGBUILDTYPE, PROGDESCRIPTION, PROGHOMEPAGE); }
    };
    std::string helpSyntax();

    enum class Status
    {
        OK,
        WARNING,
        ERROR,
        FATAL
    };
    bool checkFunctionReturn(std::tuple<bool, std::string> const &ret,
                             Status statusInstruction = Snippets::Status::ERROR);

    template <typename CharT>
    using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

    template <typename CharT>
    using tstringstream = std::basic_stringstream<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

    template <typename CharT>
    tstring<CharT> trim(tstring<CharT> &text);

private:
};
