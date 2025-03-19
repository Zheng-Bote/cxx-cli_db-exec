#pragma once

#include <memory>
#include <print>
#include <iostream>
#include <cxxopts.hpp>
#include <unordered_map>

#include "rz_config.h"

namespace rz_options
{

  std::unordered_map<std::string, std::string> check_options(const int argc,
                                                             char *argv[])
  {
    std::unordered_map<std::string, std::string> args;

    cxxopts::Options options(PROG_EXEC_NAME, PROG_DESCRIPTION);

    // c connect = db_system.ini
    // e env = env
    // s sql = db_sql.ini
    // t type = type
    options.set_width(120).add_options()("c,connect",
                                         "<path/to/db_system.ini> with DB connect data", cxxopts::value<std::string>())("d,debug", "optional: run logging in debug mode")("e,env", "environment to use, e.g.: dev, int, prod", cxxopts::value<std::string>())("s,sql", "<path/to/sql.ini> with sql instructions", cxxopts::value<std::string>())("t,type", "which type in sql.ini to work on, e.g.: schema, db-links", cxxopts::value<std::string>())("v", "print program version and exit")("version", "print program information and exit")("h, help", "Print help and exit");

    auto result = options.parse(argc, argv);

    if (argc <= 1 || result.count("help"))
    {
      std::cout << "\n"
                << PROG_NAME << "\n"
                << options.help() << std::endl;
      exit(EXIT_SUCCESS);
    }

    if (result.count("v"))
    {
      std::print("{}", PROG_VERSION);
      exit(EXIT_SUCCESS);
    }
    if (result.count("version"))
    {
      std::println("\n\t{} v{}\n\t{}\n\t{} mode: {}\n\t{}\n\t{}\n", PROG_NAME, PROG_VERSION, PROG_DESCRIPTION, PROG_EXEC_NAME, PROG_BUILD_TYPE, PROG_COPYRIGHT, PROG_HOMEPAGE);
      exit(EXIT_SUCCESS);
    }

    if (result.count("connect"))
    {
      args["dbSystemIni"] = result["connect"].as<std::string>();
    }
    else
    {
      std::cerr << "\n\033[0;31m" << "FATAL: " << "missing: <path/to/db_system.ini> with DB connect data."
                << "\e[0m" << std::endl;
      std::cout << "\n"
                << PROG_NAME << "\n"
                << options.help() << std::endl;
      exit(EXIT_FAILURE);
    }

    if (result.count("debug"))
    {
      args["debug"] = "yes";
    }
    else
    {
      args["debug"] = "no";
    }

    if (result.count("env"))
    {
      args["env"] = result["env"].as<std::string>();
    }
    else
    {
      std::cerr << "\n\033[0;31m" << "FATAL: " << "missing: environment to use."
                << "\e[0m" << std::endl;
      std::cout << "\n"
                << PROG_NAME << "\n"
                << options.help() << std::endl;
      exit(EXIT_FAILURE);
    }

    if (result.count("sql"))
    {
      args["dbSqlIni"] = result["sql"].as<std::string>();
    }
    else
    {
      std::cerr << "\n\033[0;31m" << "FATAL: " << "missing: <path/to/sql.ini> with sql instructions."
                << "\e[0m" << std::endl;
      std::cout << "\n"
                << PROG_NAME << "\n"
                << options.help() << std::endl;
      exit(EXIT_FAILURE);
    }

    if (result.count("type"))
    {
      args["type"] = result["type"].as<std::string>();
    }
    else
    {
      std::cerr << "\n\033[0;31m" << "FATAL: " << "missing: which type in sql.ini to work on."
                << "\e[0m" << std::endl;
      std::cout << "\n"
                << PROG_NAME << "\n"
                << options.help() << std::endl;
      exit(EXIT_FAILURE);
    }

    return args;
  }
};
