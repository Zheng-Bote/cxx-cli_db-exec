#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

namespace rz_parse_sqlfile
{
  // Function to trim leading and trailing whitespaces
  std::string trim(const std::string &str)
  {
    size_t start = 0;
    while (start < str.length() && std::isspace(str[start]))
      start++;

    size_t end = str.length();
    while (end > start && std::isspace(str[end - 1]))
      end--;

    return str.substr(start, end - start);
  }

  // Function to parse the SQL file and separate statements
  void parseSQLFile(const std::string &filePath)
  {
    std::ifstream file(filePath);

    if (!file.is_open())
    {
      std::cerr << "Failed to open file!" << std::endl;
      return;
    }

    std::string line;
    std::string sqlStatement;
    std::vector<std::string> statements;

    // Read the file line by line
    while (std::getline(file, line))
    {
      // Trim each line to remove leading/trailing spaces
      line = trim(line);

      // Skip empty lines or comments
      if (line.empty() || line[0] == '-' || line[0] == '#')
      {
        continue;
      }

      // Append the line to the current SQL statement
      sqlStatement += line + " ";

      // If we find a semicolon, it's the end of the current statement
      if (line.back() == ';')
      {
        statements.push_back(trim(sqlStatement));
        sqlStatement.clear(); // Reset for the next statement
      }
    }

    file.close();

    // Print all parsed SQL statements
    std::cout << "Parsed SQL Statements: " << std::endl;
    for (const auto &statement : statements)
    {
      std::cout << statement << std::endl
                << "------" << std::endl;
    }
  }

};