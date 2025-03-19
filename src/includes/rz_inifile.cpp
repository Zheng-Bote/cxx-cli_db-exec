/**
 * @file rz_inifile.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief classlib for inicpp.h
 * @details simple class for reading and writing the inifile
 * @date 2023-04-15
 * @copyright Copyright (c) 2023 ZHENG Robert
 */

#include "rz_inifile.h"

/**
 * @brief Inifile::Inifile
 */
Inifile::Inifile()
{
}

/**
 * @brief Inifile::Inifile
 * @param pathToInifile
 */
Inifile::Inifile(std::string &pathToInifile)
{
    setIniFileName(pathToInifile);
    loadIni(pathToInifile);
}

/**
 * @brief Inifile::~Inifile
 */
Inifile::~Inifile()
{
}

/**
 * @brief Inifile::setIniFileName
 * @param pathToInifile
 */
void Inifile::setIniFileName(std::string &pathToInifile)
{
    pathToInifile = pathToInifile;
}

/**
 * @brief Inifile::getInifile
 * @return std::string
 */
std::string Inifile::getInifile()
{
    return pathToInifile;
}

/**
 * @brief Inifile::createIni
 */
void Inifile::createIni()
{
    myIni["Webserver"]["url"] = "http://localhost";
    myIni["Webserver"]["port"] = 8080;

    myIni["Webserver"]["ssl_certfile"] = "/path/to/cert.crt";
    myIni["Webserver"]["ssl_keyfile"] = "/path/to/keyfile.key";
    myIni["Webserver"]["ssl_pemfile"] = "none";

    myIni["Webserver"]["write_dir"] = "/tmp";
    myIni["Webserver"]["upload_dir"] = "/tmp/crow_web/uploads";

    /*
    myIni["System"]["PROG_NAME"] = PROG_NAME;
    myIni["System"]["PROG_VERSION"] = PROG_VERSION;
    myIni["System"]["PROG_HOMEPAGE"] = PROG_HOMEPAGE;
    myIni["System"]["PROG_DESCRIPTION"] = PROG_DESCRIPTION;
    myIni["System"]["PROG_BUILD_TYPE"] = PROG_BUILD_TYPE;
    */
}

/**
 * @brief Inifile::saveIniToFile
 * @param pathToInifile
 * @return std::tuple<bool, std::string>
 */
std::tuple<bool, std::string> Inifile::saveIniToFile(std::string &pathToInifile)
{
    try
    {
        myIni.save(pathToInifile);
    }
    catch (...)
    {
        std::cerr << "Write Ini failed; " << pathToInifile << std::endl;
        return std::make_tuple(false, "Write Ini failed: " + pathToInifile);
    }

    return std::make_tuple(true, "Write Ini successfull: " + pathToInifile);
}

/**
 * @brief Inifile::loadIni
 * @param pathToInifile
 * @return std::tuple<bool, std::string>
 */
std::tuple<bool, std::string> Inifile::loadIni(std::string &pathToInifile)
{
    std::string msg = __FUNCTION__;

    if (std::filesystem::exists(pathToInifile) == 0)
    {
        // std::cerr << "doesn't exist or is not readable: " << pathToInifile << std::endl;
        //  Inifile::pathToInifile = "";
        return std::make_tuple(false, msg + ": doesn't exist or is not readable: " + pathToInifile);
    }

    Inifile::pathToInifile = pathToInifile;
    myIni.load(pathToInifile);

    if (myIni.size() < 1)
    {
        // std::cerr << "wrong INI size " << myIni.size() << ", should be at least 1 section." << std::endl;

        return std::make_tuple(false,
                               msg + ": wrong INI size, should be at least 1 section: " + std::to_string(myIni.size()));
    }
    return std::make_tuple(true, msg + ": Inifile loaded: " + pathToInifile);
}

/**
 * @brief Inifile::listIniEntries()
 * @return void
 */
void Inifile::listIniEntries()
{
    std::println("Parsed ini contents");
    std::println("Has {} sections", myIni.size());
    for (const auto &sectionPair : myIni)
    {
        const std::string &sectionName = sectionPair.first;
        const ini::IniSection &section = sectionPair.second;

        std::string out = "\nSection '" + sectionName + "' has " + std::to_string(section.size()) + " fields";
        int len = (int)out.length();

        // std::cout << "Section '" << sectionName << "' has " << section.size() << " fields" << std::endl;
        std::println("{}", out);
        std::cout << std::setfill('*') << std::setw(len) << "\n";

        for (const auto &fieldPair : sectionPair.second)
        {
            const std::string &fieldName = fieldPair.first;
            const ini::IniField &field = fieldPair.second;

            std::println("{}={}", fieldName, field.as<std::string>());
        }
    }
}

/**
 * @brief Inifile::getIniEntries
 * @return std::map<std::string, std::string>
 */
std::unordered_map<std::string, std::string> Inifile::getIniEntries()
{
    std::unordered_map<std::string, std::string> iniMap;

    for (const auto &sectionPair : myIni)
    {
        const std::string &sectionName = sectionPair.first;
        const ini::IniSection &section = sectionPair.second;

        for (const auto &fieldPair : sectionPair.second)
        {
            const std::string &fieldName = fieldPair.first;
            const ini::IniField &field = fieldPair.second;

            iniMap[sectionName + ": " + fieldName] = field.as<std::string>();
        }
    }

    return iniMap;
}

void Inifile::listIniSectionEntries(std::string section)
{
    for (const auto &fieldPair : myIni[section])
    {
        const std::string &fieldName = fieldPair.first;
        const ini::IniField &field = fieldPair.second;

        std::println("attr: {} val: {}", fieldName, field.as<std::string>());
    }
}

std::tuple<bool, std::string> Inifile::getStringValue(std::string &section, std::string &key)
{

    try
    {
        std::string val = myIni[section][key].as<std::string>();
        if (val.empty())
        {
            return std::make_tuple(false, std::format("{}: getStringValue: section [{}] attribute {}: empty value", __FUNCTION__, section, key));
        }
        else
        {
            return std::make_tuple(true, val);
        }
    }
    catch (std::exception const &e)
    {
        std::make_tuple(false, std::format("{}: {}", __FUNCTION__, e.what()));
    }
    return std::make_tuple(false, "getStringValue: unknown error");
}

Inifile::dbType Inifile::getDBConnectStruct(std::string &section)
{
    dbType dbConnectStruct;
    std::string hostname{""};
    int port{0};

    dbConnectStruct.hostname = myIni[section]["hostname"].as<std::string>();
    dbConnectStruct.port = myIni[section]["port"].as<int>();
    dbConnectStruct.use_proxy = myIni[section]["use_proxy"].as<bool>();
    dbConnectStruct.db_proxy = myIni[section]["db_proxy"].as<std::string>();
    dbConnectStruct.db_proxy_port = myIni[section]["db_proxy_port"].as<int>();
    dbConnectStruct.dbname = myIni[section]["dbname"].as<std::string>();
    dbConnectStruct.password = myIni[section]["password"].as<std::string>();
    dbConnectStruct.username = myIni[section]["username"].as<std::string>();

    if (dbConnectStruct.use_proxy)
    {
        hostname = dbConnectStruct.db_proxy;
        port = dbConnectStruct.db_proxy_port;
    }
    else
    {
        hostname = dbConnectStruct.hostname;
        port = dbConnectStruct.port;
    }
    dbConnectString = "user=" + dbConnectStruct.username + " password=" + dbConnectStruct.password + " host=" + hostname + " port=" + std::to_string(port) + " dbname=" + dbConnectStruct.dbname + " target_session_attrs=read-write";

    return dbConnectStruct;
}

void Inifile::getUniqueSectionTypes()
{

    for (const auto &sectionPair : myIni)
    {

        sectionTypes.push_back(myIni[sectionPair.first]["type"].as<std::string>());
    }

    std::sort(sectionTypes.begin(), sectionTypes.end());

    auto last = std::unique(sectionTypes.begin(), sectionTypes.end());
    sectionTypes.erase(last, sectionTypes.end());
    /*
        for (auto &e : sectionTypes)
        {
            std::println("unique: {}", e);
        }
    */
}

void Inifile::setOrderedType(std::string &type)
{
    for (const auto &sectionPair : myIni)
    {
        if (myIni[sectionPair.first]["type"].as<std::string>().compare(type) == 0)
        {
            if (myIni[sectionPair.first]["active"].as<bool>())
            {
                orderedId.push_back(myIni[sectionPair.first]["id"].as<int>());
                orderedSections[myIni[sectionPair.first]["id"].as<int>()] = sectionPair.first;
            }
        }
    }

    std::sort(orderedId.begin(), orderedId.end());

    auto last = std::unique(orderedId.begin(), orderedId.end());
    orderedId.erase(last, orderedId.end());

    for (auto &item : orderedSections)
    {
        std::println("map -- id: {} section: {}", item.first, item.second);
    }
    for (auto &e : orderedId)
    {
        std::println("unique: {} - key: {}", e, orderedSections[e]);
    }
}

std::vector<std::string> Inifile::getOrderedType(std::string &type)
{
    std::vector<std::string> sortedSections;
    std::vector<int> orderedId;
    std::unordered_map<int, std::string> orderedSections;

    for (const auto &sectionPair : myIni)
    {
        if (myIni[sectionPair.first]["type"].as<std::string>().compare(type) == 0)
        {
            if (myIni[sectionPair.first]["active"].as<bool>())
            {
                orderedId.push_back(myIni[sectionPair.first]["id"].as<int>());
                orderedSections[myIni[sectionPair.first]["id"].as<int>()] = sectionPair.first;
            }
        }
    }

    std::sort(orderedId.begin(), orderedId.end());
    auto last = std::unique(orderedId.begin(), orderedId.end());
    orderedId.erase(last, orderedId.end());

    for (auto &e : orderedId)
    {
        sortedSections.push_back(orderedSections[e]);
    }

    return sortedSections;
}
