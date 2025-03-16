#include <iostream>
#include <print>
#include <memory>
#include <pqxx/pqxx>

#include "includes/rz_inifile.h"
#include "includes/rz_snippets.h"
#include "includes/rz_db.h"
#include "includes/rz_parse_sqlfile.h"

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

  sptr_dbini_config->setIniFileName(dbSystemIni);
  sptr_snippets->checkFunctionReturn(sptr_dbini_config->loadIni(dbSystemIni), Snippets::Status::FATAL);

  sptr_sqlini_config->setIniFileName(dbSqlIni);
  sptr_snippets->checkFunctionReturn(sptr_sqlini_config->loadIni(dbSqlIni), Snippets::Status::FATAL);
  sptr_snippets->checkFunctionReturn(rz_db::setDbConnect(sptr_dbini_config, env), Snippets::Status::OK);

  // Tests
  // Snippets::AboutType about;
  // std::println("Prog Info: {}", about.getProgInfo());
  rz_db::getPhotos(sptr_snippets);
  sptr_sqlini_config->setOrderedType(type);

  rz_parse_sqlfile::parseSQLFile("test/example.sql");

  rz_db::closeDb(sptr_snippets);
  exit(EXIT_SUCCESS);
}