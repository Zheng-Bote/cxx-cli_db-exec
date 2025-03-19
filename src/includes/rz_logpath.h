#pragma once

#include <memory>
#include <string>
#include <tuple>
#include <filesystem>
#include <fstream>

namespace rz_logpath
{
  bool isWriteable(const std::string &pathToLogfile)
  {
    bool ret{false};

    std::ofstream file(pathToLogfile, std::ios::out | std::ios::app);

    if (file.is_open())
    {
      file.close();
      ret = true;
    }
    else
    {
      ret = false;
    }

    return ret;
  }

  bool createNestedDir(const std::string &path)
  {
    std::filesystem::path nested = path;
    bool ret{false};

    try
    {
      if (std::filesystem::create_directories(nested))
      {
        ret = true;
      }
      else
      {
        ret = false;
      }
    }
    catch (...)
    {
      ret = false;
    }

    return ret;
  }

  bool isDirectory(const std::string &path)
  {
    bool ret{false};

    if (std::filesystem::is_directory(path))
    {
      ret = true;
    }
    else
    {
      ret = createNestedDir(path);
    }

    return ret;
  }

  std::tuple<bool, std::string> checkLogPath(std::string &path, std::string &logfile)
  {
    const std::source_location location = std::source_location::current();

    if (!path.ends_with("/"))
    {
      path += "/";
    }

    if (isDirectory(path))
    {
      if (isWriteable(path + logfile))
      {
        // std::cout << __FUNCTION__ << " Line: " << __LINE__ << ": isWriteable" << std::endl;
      }
      else
      {
        // not writeable
        path = std::filesystem::temp_directory_path();
        if (!path.ends_with("/"))
        {
          path += "/";
        }
      }
    }

    return std::make_tuple(true, path + logfile);
  }
};