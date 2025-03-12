#include <iostream>
#include <print>
#include <memory>

#include "includes/rz_inifile.h"
#include "includes/rz_snippets.h"

#include <pqxx/pqxx>

auto sptr_ini_config = std::make_shared<Inifile>();
auto sptr_snippets = std::make_shared<Snippets>();

int main(int argc, char *argv[])
{
  std::string dbSystemIni, env, type, msg = "";
  if (argc < 4)
  {
    std::cerr << "\n\033[0;31m" << "FATAL: wrong parameters" << "\n\x1B[39m" << std::endl;
    std::cout << sptr_snippets->helpSyntax() << std::endl;
    exit(EXIT_FAILURE);
  }
  else
  {
    dbSystemIni = argv[1];
    env = argv[2];
    type = argv[3];
  }

  std::println("args: {} ini: {} env: {} type: {}", argc, dbSystemIni, env, type);

  Snippets::AboutType about;
  std::println("Prog Info: {}", about.getProgInfo());

  sptr_ini_config->setIniFileName(dbSystemIni);
  sptr_snippets->checkFunctionReturn(sptr_ini_config->loadIni(dbSystemIni), Snippets::Status::FATAL);

  sptr_ini_config->setOrderedType(type);

  /* OK https://libpqxx.readthedocs.io/stable/prepared.html#autotoc_md24
    Inifile::dbType dbConnectData = sptr_ini_config->getDBConnectString(env);

    pqxx::connection *dbConnect;
    try
    {
      // pqxx::connection dbConnect("user=" + dbConnectData.username + " password=" + dbConnectData.password + " host=" + dbConnectData.hostname + " port=" + std::to_string(dbConnectData.port) + " dbname=" + dbConnectData.dbname + " target_session_attrs=read-write");
      dbConnect = new pqxx::connection("user=" + dbConnectData.username + " password=" + dbConnectData.password + " host=" + dbConnectData.hostname + " port=" + std::to_string(dbConnectData.port) + " dbname=" + dbConnectData.dbname + " target_session_attrs=read-write");

      pqxx::work db{*dbConnect};

      pqxx::result rows{db.exec("SELECT file_name_orig FROM photo_main;")};
      for (auto row : rows)
      {
        std::cout << row["file_name_orig"].c_str() << std::endl;
      }
    }
    catch (std::exception const &e)
    {
      std::cerr << "\n\033[0;31m" << e.what() << "\n\x1B[39m" << std::endl;
      exit(EXIT_FAILURE);
    }

    dbConnect->close();
    delete dbConnect;
    */

  exit(EXIT_SUCCESS);
}