/**
 * @file rz_fs.h
 * @author ZHENG Bote (robert.hase-zheng.net)
 * @brief CXX20+ filesystem library (re-build from rz_filesystem.h)
 * @version 3.0.0
 * @date 2024-03-17 (2023-03-24)
 *
 * @copyright Copyright (c)2023 ZHENG Robert
 */

#pragma once

#include <filesystem>
#include <vector>
#include <iostream>
#include <format>

class Filesystem
{
public:
  Filesystem();

  std::tuple<bool, std::string> isDirectory(const std::filesystem::path &path);
  std::tuple<bool, std::string> createDirectories(const std::filesystem::path &path) noexcept;
  std::tuple<bool, std::vector<std::string>> listDirectoryItems(const std::filesystem::path &pathToDir, const std::string &filter = ".*");
};