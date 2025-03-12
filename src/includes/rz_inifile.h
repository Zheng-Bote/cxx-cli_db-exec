/**
 * @file rz_inifile.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief classlib for inicpp.h
 * @details simple class for reading and writing the inifile
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <format>
#include <print>
#include <filesystem>
#include <iostream>
#include <algorithm>

#include "inicpp.h"

class Inifile
{
public:
    Inifile();
    Inifile(std::string &pathToInifile);
    ~Inifile();

    void createIni();
    std::tuple<bool, std::string> saveIniToFile(std::string &pathToInifile);
    std::tuple<bool, std::string> loadIni(std::string &pathToInifile);
    void setIniFileName(std::string &pathToInifile);
    std::string getInifile();

    void listIniEntries();
    std::unordered_map<std::string, std::string> getIniEntries();
    void listIniSectionEntries(std::string section);

    struct dbType
    {
        std::string hostname{""};
        int port{0};
        bool use_proxy{false};
        std::string db_proxy{""};
        int db_proxy_port{0};
        std::string dbname{""};
        std::string password{""};
        std::string username{""};
    };
    struct dbType getDBConnectString(std::string &section);

    void getUniqueSectionTypes();
    void setOrderedType(std::string &type);

private:
    ini::IniFile myIni;
    std::string pathToInifile;

    std::vector<std::string> sectionTypes;
    std::vector<int> orderedId;
    std::unordered_map<int, std::string> orderedSections;
};
