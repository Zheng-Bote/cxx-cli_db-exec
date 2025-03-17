/**
 * @file rz_strings.h
 * @author ZHENGH Bote (robert.hase-zheng.net)
 * @brief header only; some string functions (re-build from rz_string_lib.h)
 * @version 0.3.0
 * @date 2025-03-17 (2024-10-13)
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#include <string>
#include <algorithm>
#include <regex>

namespace rz_strings
{
  template <typename CharT>
  using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

  template <typename CharT>
  using tstringstream = std::basic_stringstream<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

  /* ##### */

  /**
   * @brief split
   * @details split a string based on given delimiter into a vector of strings
   * @tparam CharT
   * @param text
   * @param delimiter
   * @return std::vector<tstring<CharT>>
   */
  template <typename CharT>
  inline std::vector<tstring<CharT>> split(tstring<CharT> text, CharT const delimiter)
  {
    auto sstr = tstringstream<CharT>{text};
    auto tokens = std::vector<tstring<CharT>>{};
    auto token = tstring<CharT>{};
    while (std::getline(sstr, token, delimiter))
    {
      if (!token.empty())
        tokens.push_back(token);
    }

    return tokens;
  }

  /**
   * @brief trim
   * @details trim leading/trailing spaces
   * @tparam CharT
   * @param text
   * @return tstring<CharT>
   */
  template <typename CharT>
  inline tstring<CharT> trim(tstring<CharT> const &text)
  {
    auto first{text.find_first_not_of(' ')};
    auto last{text.find_last_not_of(' ')};
    return text.substr(first, (last - first + 1));
  }

  bool is_number(const std::string &stringToCheck)
  {
    static const std::regex number_regex(R"(^\d*$)");
    return std::regex_match(stringToCheck, number_regex);
  }
};