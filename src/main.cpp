/**
 * @file main.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief main program
 * @details executes sql in an ordered way
 * @version 0.3.0
 * @date 2025-03-17
 *
 * @copyright Copyright (c) 2025 ZHENG Robert
 *
 */
#include <iostream>
#include <print>
#include <memory>
#include <pqxx/pqxx>

#include "includes/rz_inifile.h"
#include "includes/rz_snippets.h"
#include "includes/rz_db.h"
#include "includes/rz_parse_sqlfile.h"
#include "includes/rz_fs.h"
#include "includes/rz_strings.h"

auto sptr_dbini_config = std::make_shared<Inifile>();
auto sptr_sqlini_config = std::make_shared<Inifile>();
auto sptr_snippets = std::make_shared<Snippets>();

int main(int argc, char *argv[])
{

  // deployment =>
  std::string dbSystemIni, dbSqlIni, env, type, msg = "";
  if (argc < 5)
  {
    std::cerr << "\n\033[0;31m" << "FATAL: wrong parameters" << "\n\x1B[39m" << std::endl;
    std::cout << sptr_snippets->helpSyntax() << std::endl;
    exit(EXIT_FAILURE);
  }
  else
  {
    dbSystemIni = argv[1];
    dbSqlIni = argv[2];
    env = argv[3];
    type = argv[4];
  }

  std::println("args: {} ini: {} env: {} type: {}", argc, dbSystemIni, dbSqlIni, env, type);
  // <= deployment

  std::tuple<bool, std::string> ret;

  sptr_dbini_config->setIniFileName(dbSystemIni);
  sptr_snippets->checkFunctionReturn(sptr_dbini_config->loadIni(dbSystemIni), Snippets::Status::FATAL);

  sptr_sqlini_config->setIniFileName(dbSqlIni);
  sptr_snippets->checkFunctionReturn(sptr_sqlini_config->loadIni(dbSqlIni), Snippets::Status::FATAL);
  sptr_snippets->checkFunctionReturn(rz_db::setDbConnect(sptr_dbini_config, env), Snippets::Status::FATAL);

  // Tests
  // Snippets::AboutType about;
  // std::println("Prog Info: {}", about.getProgInfo());

  std::vector<std::string> sortedSections = sptr_sqlini_config->getOrderedType(type);
  for (const auto &section : sortedSections)
  {
    std::string sectionName = section;

    // sql_string
    std::string sectionAttribute = "sql_string";
    ret = sptr_sqlini_config->getStringValue(sectionName, sectionAttribute);
    sptr_snippets->checkFunctionReturn(ret, Snippets::Status::WARNING);
    if (std::get<0>(ret))
    {
      std::string sql = std::get<1>(ret);
      sptr_snippets->checkFunctionReturn(rz_db::execSQL(sql), Snippets::Status::FATAL);
    }

    // sql_file
    sectionAttribute = "sql_file";
    ret = sptr_sqlini_config->getStringValue(sectionName, sectionAttribute);
    sptr_snippets->checkFunctionReturn(ret, Snippets::Status::WARNING);
    if (std::get<0>(ret))
    {
      std::string sqlfile = std::get<1>(ret);
      std::tuple<bool, std::vector<std::string>> retV = rz_parse_sqlfile::parseSQLFile(sqlfile);
      std::vector<std::string> dirItem = std::get<1>(retV);
      sptr_snippets->checkFunctionReturn(std::make_tuple(std::get<0>(retV), dirItem[0]), Snippets::Status::FATAL);
      if (std::get<0>(retV))
      {
        std::vector<std::string> sqls = std::get<1>(retV);
        for (auto sql : sqls)
        {
          sptr_snippets->checkFunctionReturn(rz_db::execSQL(sql), Snippets::Status::FATAL);
        }
      }
    }

    // sql_path
    sectionAttribute = "sql_path";
    ret = sptr_sqlini_config->getStringValue(sectionName, sectionAttribute);
    sptr_snippets->checkFunctionReturn(ret, Snippets::Status::WARNING);
    if (std::get<0>(ret))
    {
      Filesystem fs;
      std::string sqlpath = std::get<1>(ret);
      std::tuple<bool, std::vector<std::string>> retV = fs.listDirectoryItems(sqlpath, ".sql");
      std::vector<std::string> dirItem = std::get<1>(retV);
      sptr_snippets->checkFunctionReturn(std::make_tuple(std::get<0>(retV), dirItem[0]), Snippets::Status::FATAL);
      if (std::get<0>(retV))
      {
        std::vector<std::string> dirItems = std::get<1>(retV);
        std::vector<int> numbers;
        std::unordered_map<int, std::string> dirItemsList;

        for (const auto &item : dirItems)
        {
          std::string fileName = std::filesystem::path(item).filename();
          std::vector<std::string> _numbers = rz_strings::split(fileName, '_');
          for (const auto &number : _numbers)
          {
            if (rz_strings::is_number(number))
            {
              numbers.push_back(std::stoi(number));
              dirItemsList[std::stoi(number)] = item;
            }
          }
        }

        std::sort(numbers.begin(), numbers.end());
        for (const auto &number : numbers)
        {
          std::string sqlfile = dirItemsList[number];

          std::tuple<bool, std::vector<std::string>> retV = rz_parse_sqlfile::parseSQLFile(sqlfile);
          std::vector<std::string> sqlItem = std::get<1>(retV);
          sptr_snippets->checkFunctionReturn(std::make_tuple(std::get<0>(retV), sqlItem[0]), Snippets::Status::WARNING);
          if (!std::get<0>(retV))
          {
            continue;
          }
          std::vector<std::string> dirItem = std::get<1>(retV);
          sptr_snippets->checkFunctionReturn(std::make_tuple(std::get<0>(retV), dirItem[0]), Snippets::Status::FATAL);
          if (std::get<0>(retV))
          {
            std::vector<std::string> sqls = std::get<1>(retV);
            for (auto sql : sqls)
            {
              sptr_snippets->checkFunctionReturn(rz_db::execSQL(sql), Snippets::Status::FATAL);
            }
          }
        }
      }
    }
  }

  /* ##### the END ##### */
  rz_db::closeDb(sptr_snippets);
  exit(EXIT_SUCCESS);
}