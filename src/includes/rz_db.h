/**
 * @file rz_db.h
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief read db system attributes from inifile and connect to db
 * @version 0.1.0
 * @date 2025-03-17
 * @copyright Copyright (c) 2025 ZHENG Robert *
 */
#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <pqxx/pqxx>
#include <format>

#include "rz_inifile.h"
#include "rz_snippets.h"

// OK https://libpqxx.readthedocs.io/stable/prepared.html#autotoc_md24

pqxx::connection *dbConnect;

namespace rz_db
{

  /**
   * @brief Set the Db Connect object
   *
   * @param sptr_dbini_config
   * @param env (e.g. "test", "int", "prod")
   * @return std::tuple<bool, std::string> (e.g. "false", "DB connect failed...")
   */
  std::tuple<bool, std::string> setDbConnect(std::shared_ptr<Inifile> &sptr_dbini_config, std::string &env)
  {
    Inifile::dbType dbConnectData = sptr_dbini_config->getDBConnectStruct(env);
    try
    {
      dbConnect = new pqxx::connection(sptr_dbini_config->dbConnectString);
    }
    catch (std::exception const &e)
    {
      return std::make_tuple(false, std::format("{}: {}", __FUNCTION__, e.what()));
      // std::cerr << "\n\033[0;31m" << e.what() << "\n\x1B[39m" << std::endl;
      // exit(EXIT_FAILURE);
    }
    return std::make_tuple(true, std::format("{}: DB connect successfull", __FUNCTION__));
  }

  /**
   * @brief Execute SQL statement
   * @details no check/no protect for SQL Injection!
   * @param sql
   * @return std::tuple<bool, std::string> (e.g. "false", "Sql failed...")
   */
  std::tuple<bool, std::string> execSQL(std::string &sql)
  {
    try
    {
      pqxx::work db{*dbConnect};
      db.exec(sql);
      db.commit();
    }
    catch (const pqxx::sql_error &e)
    {
      return std::make_tuple(false, std::format("{}: {}: {}", __FUNCTION__, e.sqlstate(), e.what()));
    }
    return std::make_tuple(true, std::format("{}: {}", __FUNCTION__, sql));
  }

};