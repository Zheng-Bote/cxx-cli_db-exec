/**
 * @file rz_parse_sqlfile.h
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief parse sql-file into vector of sql statements
 * @version 0.1.0
 * @date 2025-03-17
 *
 * @copyright Copyright (c) 2025 ZHENG Robert
 *
 */
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <tuple>
#include <algorithm>
#include <format>

namespace rz_parse_sqlfile
{
  /**
   * @brief trim leading/trailing spaces
   *
   * @param str
   * @return std::string
   */
  std::string trim(const std::string &str)
  {
    auto start = str.find_first_not_of(" \t\n\r\f\v");
    auto end = str.find_last_not_of(" \t\n\r\f\v");

    if (start == std::string::npos || end == std::string::npos)
      return ""; // String is all whitespace

    return str.substr(start, end - start + 1);
  }

  /**
   * @brief parseSQLFile into vector of sql statements
   * @details parse sql-file into vector of sql statements
   * @param filePath
   * @return std::tuple<bool, std::vector<std::string>>
   */
  std::tuple<bool, std::vector<std::string>> parseSQLFile(const std::string &filePath)
  {
    std::ifstream file(filePath);
    std::string line;
    std::string sqlStatement;
    std::vector<std::string> statements;
    statements.reserve(100);

    if (!file.is_open())
    {
      statements.push_back("rz_parse_sqlfile: Failed to open file!");
      return std::make_tuple(false, statements);
    }

    while (std::getline(file, line))
    {
      // Trim each line to remove leading/trailing spaces
      line = trim(line);

      if (line.empty() || line[0] == '-' || line[0] == '#')
      {
        continue;
      }

      sqlStatement += line + " ";

      if (line.back() == ';')
      {
        statements.emplace_back(trim(sqlStatement));
        sqlStatement.clear(); // Reset for the next statement
      }
    }

    file.close();

    if (statements.empty())
    {
      statements.push_back(std::format("rz_parse_sqlfile: No SQL statements found in file: {}", filePath));
      return std::make_tuple(false, statements);
    }
    return std::make_tuple(true, statements);
  }
};