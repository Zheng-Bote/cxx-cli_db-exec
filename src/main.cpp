/**
 * @file main.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief main program
 * @details executes sql in an ordered way
 * @version 1.0.0
 * @date 2025-03-17
 *
 * @copyright Copyright (c) 2025 ZHENG Robert
 *
 */

// TODOS: clean-up

#include <iostream>
#include <print>
#include <memory>
#include <unordered_map>
#include <stdlib.h>

#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>

#include "includes/rz_inifile.h"
#include "includes/rz_snippets.h"
#include "includes/rz_db.h"
#include "includes/rz_parse_sqlfile.h"
#include "includes/rz_fs.h"
#include "includes/rz_strings.h"
#include "includes/rz_options.h"
#include "includes/rz_logpath.h"

auto sptr_dbini_config = std::make_shared<Inifile>();
auto sptr_sqlini_config = std::make_shared<Inifile>();
auto sptr_snippets = std::make_shared<Snippets>();
Snippets::AboutType about;

void exit_handler();

int main(int argc, char *argv[])
{
  std::atexit(exit_handler);
  std::at_quick_exit(exit_handler);

  std::string msg, logfilePath, logfileName, logfile = "";
  std::unordered_map<std::string, std::string> args = rz_options::check_options(argc, argv);
  Filesystem fs;
  std::tuple<bool, std::string> ret;

  sptr_dbini_config->setIniFileName(args["dbSystemIni"]);
  sptr_snippets->checkFunctionReturn(sptr_dbini_config->loadIni(args["dbSystemIni"]), Snippets::Status::FATAL);

  /* ##### Logfile ##### */
  // TODOS: passwords or other sensitive data in logfile
  msg = "logfile_path";
  logfileName = about.PROGEXECNAME + ".log";
  ret = sptr_dbini_config->getStringValue(args["env"], msg);
  sptr_snippets->checkFunctionReturn(ret, Snippets::Status::WARNING);
  if (std::get<0>(ret))
  {
    logfilePath = std::get<1>(ret);
    ret = rz_logpath::checkLogPath(logfilePath, logfileName);
    logfile = std::get<1>(ret);
  }
  else
  {
    logfilePath = std::filesystem::temp_directory_path();
    ret = rz_logpath::checkLogPath(logfilePath, logfileName);
    logfile = std::get<1>(ret);
  }
  /* ##### Logfile ##### */

  static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(logfile.c_str(), 10000, 3);
  if (args["debug"].compare("yes") == 0)
  {
    plog::init(plog::debug, &fileAppender);
  }
  else
  {
    plog::init(plog::info, &fileAppender);
  }
  plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::get()->addAppender(&consoleAppender); // Also add logging to the console.
  PLOG(plog::info) << __FUNCTION__ << ": Logfile: " << logfile;
  // fileAppender.setFileName("SetFileNameBBB.log");
  /* ##### Logfile ##### */

  sptr_sqlini_config->setIniFileName(args["dbSqlIni"]);
  sptr_snippets->checkFunctionReturn(sptr_sqlini_config->loadIni(args["dbSqlIni"]), Snippets::Status::FATAL);
  sptr_snippets->checkFunctionReturn(rz_db::setDbConnect(sptr_dbini_config, args["env"]), Snippets::Status::FATAL);

  // Tests
  // Snippets::AboutType about;
  // std::println("Prog Info: {}", about.getProgInfo());

  std::vector<std::string> sortedSections = sptr_sqlini_config->getOrderedType(args["type"]);
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
  // rz_db::closeDb(sptr_snippets);
  exit(EXIT_SUCCESS);
}

void exit_handler()
{
  // sptr_snippets->exitMsg();
}