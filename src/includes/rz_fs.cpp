/**
 * @file rz_fs.h
 * @author ZHENG Bote (robert.hase-zheng.net)
 * @brief CXX20+ filesystem library (re-build from rz_filesystem.h)
 * @version 3.0.0
 * @date 2024-03-17 (2023-03-24)
 *
 * @copyright Copyright (c)2023 ZHENG Robert
 */

#include "rz_fs.h"

Filesystem::Filesystem() {}

/**
 * @brief isDirectory
 *
 * @param path
 * @return std::tuple<bool, std::string>
 */
std::tuple<bool, std::string> Filesystem::isDirectory(const std::filesystem::path &path)
{
  if (std::filesystem::is_directory(path))
  {
    ;
    return std::make_tuple(true, std::format("{}: is directory: {}", __FUNCTION__, path.c_str()));
  }
  return std::make_tuple(false, std::format("{}: is not a directory: {}", __FUNCTION__, path.c_str()));
}

std::tuple<bool, std::string> Filesystem::createDirectories(const std::filesystem::path &path) noexcept
{
  std::filesystem::path nested = path;
  std::string msg;
  bool ret{false};

  try
  {
    if (std::filesystem::create_directories(nested))
    {
      msg = std::format("{}: createDirectories: {}", __FUNCTION__, path.c_str());
      ret = true;
    }
    else
    {
      // std::cerr << "createDirectories: Failed to create nested directories: " << path.c_str() << std::endl;
      msg = std::format("{}: createDirectories: Failed to create nested directories: {}", __FUNCTION__, path.c_str());
      ret = false;
    }
  }
  catch (const std::exception &ex)
  {
    // std::cerr << "createDirectories: Exception Failed to create nested directories: " << path.c_str() << std::endl;
    msg = std::format("{}: createDirectories: Exception Failed to create nested directories: {} - {}", __FUNCTION__, path.c_str(), ex.what());
    ret = false;
  }

  return std::make_tuple(ret, msg);
}

/**
 * @brief listDirectoryItems
 *
 * @param pathToDir
 * @param filter (e.g. ".sql")
 * @return std::tuple<bool, std::vector<std::string>> (e.g. "true", "vector of pathToFile")
 */
std::tuple<bool, std::vector<std::string>> Filesystem::listDirectoryItems(const std::filesystem::path &pathToDir, const std::string &filter)
{

  std::filesystem::path dir = pathToDir;
  std::vector<std::string> dirItems;
  try
  {
    for (const auto &entry : std::filesystem::directory_iterator(pathToDir))
    {
      if (entry.is_regular_file() && entry.path().extension() == filter && std::filesystem::file_size(std::filesystem::path(entry)) > 1)
      {
        dirItems.push_back(std::filesystem::path(entry));
      }
    }
  }
  catch (const std::exception &ex)
  {
    // std::cerr << "\033[0;31m" << "ERROR: " << ex.what() << "\e[0m" << std::endl;
    dirItems.clear();
    dirItems.push_back(std::format("listDirectoryItems: {}", ex.what()));
    return std::make_tuple(false, dirItems);
  }
  return std::make_tuple(true, dirItems);
}