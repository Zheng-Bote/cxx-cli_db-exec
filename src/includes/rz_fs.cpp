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