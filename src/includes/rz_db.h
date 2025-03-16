#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <pqxx/pqxx>

#include "rz_inifile.h"
#include "rz_snippets.h"

// OK https://libpqxx.readthedocs.io/stable/prepared.html#autotoc_md24

pqxx::connection *dbConnect;

namespace rz_db
{

  std::tuple<bool, std::string> setDbConnect(std::shared_ptr<Inifile> &sptr_dbini_config, std::string &env)
  {
    Inifile::dbType dbConnectData = sptr_dbini_config->getDBConnectStruct(env);
    try
    {
      dbConnect = new pqxx::connection(sptr_dbini_config->dbConnectString);
    }
    catch (std::exception const &e)
    {
      return std::make_tuple(false, e.what());
      // std::cerr << "\n\033[0;31m" << e.what() << "\n\x1B[39m" << std::endl;
      // exit(EXIT_FAILURE);
    }
    return std::make_tuple(true, "DB connect successfull");
  }

  void getPhotos(std::shared_ptr<Snippets> &sptr_snippets)
  {
    try
    {
      pqxx::work db{*dbConnect};

      pqxx::result rows{db.exec("SELECT file_name_orig FROM photo_main;")};
      for (auto row : rows)
      {
        std::cout << row["file_name_orig"].c_str() << std::endl;
      }
    }
    catch (std::exception const &e)
    {
      sptr_snippets->checkFunctionReturn(std::make_tuple(false, e.what()), Snippets::Status::WARNING);
    }
  }

  void closeDb(std::shared_ptr<Snippets> &sptr_snippets)
  {
    dbConnect->close();
    if (dbConnect != nullptr)
    {
      delete dbConnect;
    }
    sptr_snippets->checkFunctionReturn(std::make_tuple(true, "DB disconnected"), Snippets::Status::OK);
  }
};