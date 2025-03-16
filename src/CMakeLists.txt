cmake_minimum_required(VERSION 3.23)
# -DCMAKE_BUILD_TYPE=Release
# -DCMAKE_BUILD_TYPE=Debug
# cmake -B . -S ../src -DCMAKE_BUILD_TYPE=Debug
# cmake --build . --parallel 6
# cmake --build . --target doxygen

project(
  db_test
  VERSION 0.2.0
  DESCRIPTION "cli app to deploy db"
  HOMEPAGE_URL "https://github.com/Zheng-Bote/"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_CXX_COMPILER clang++)
endif()

set(PROG_EXEC_NAME "${PROJECT_NAME}")
set(PROG_NAME "DB deployments")
set(PROG_VERSION "${PROJECT_VERSION}")
set(PROG_HOMEPAGE "${PROJECT_HOMEPAGE_URL}")
set(PROG_DESCRIPTION "${PROJECT_DESCRIPTION}")
set(PROG_BUILD_TYPE "${CMAKE_BUILD_TYPE}")

configure_file("${CMAKE_SOURCE_DIR}/configure/rz_config.h.in"
               "${CMAKE_SOURCE_DIR}/includes/rz_config.h")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

set(SRC_LIST main.cpp 
  includes/rz_config.h
  includes/dotenv.h
  includes/inicpp.h
  includes/rz_db.h
  includes/rz_parse_sqlfile.h
  includes/rz_inifile.cpp includes/rz_inifile.h
  includes/rz_snippets.cpp includes/rz_snippets.h
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CXX_FLAGS_DEBUG} ${CXX_FLAGS_ALL}")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CXX_FLAGS_RELEASE} ${CXX_FLAGS_ALL}")
endif()

add_executable(${PROJECT_NAME} ${SRC_LIST})

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message("DEBUG mode")
    set(CMAKE_CXX_CLANG_TIDY clang-tidy;  -header-filter=.; -checks=cppcoreguidelines-*)
  # are we clean?
  #include(configure/ClangTidy)
  #addclangtidy(${PROJECT_NAME})
ENDIF()

target_link_libraries(${PROJECT_NAME} ${PQXX_LIB} ${PQ_LIB})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# --target doxygen
include("${CMAKE_SOURCE_DIR}/configure/Doxygen.cmake")
doxygen(. docs)

IF(CMAKE_BUILD_TYPE MATCHES Release)
  message("RELEASE mode")

  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "building SHA256sum on Linux ${CMAKE_SYSTEM_VERSION}")
    add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND sha256sum ARGS "${PROJECT_NAME}" >
              "${PROJECT_NAME}.sha256sum")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "building SHA256sum on MacOS ${CMAKE_SYSTEM_VERSION}")
    add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND shasum ARGS "-a 256 ${PROJECT_NAME}" >
              "${PROJECT_NAME}.sha256sum")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "building SHA256sum on Windows ${CMAKE_SYSTEM_VERSION}")
    # Powershell
    add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND Get-Filehash ARGS "$<TARGET_FILE_NAME:t${PROJECT_NAME}.exe>"
              > "${PROJECT_NAME}.sha256sum")
  endif()
ENDIF()

include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

# the end
message("Build with CMake version: ${CMAKE_VERSION} and c++${CMAKE_CXX_STANDARD}")
include(ProcessorCount)
ProcessorCount(N)
message("number of processors: " ${N})
message("cmake -S ../src -B . --parallel ${N}")
