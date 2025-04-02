<div id="top" align="center">
<h1>cxx-cli_db-exec</h1>

<p>command line tool to execute sql in an ordered manner</p>

[Report Issue](https://github.com/Zheng-Bote/cxx-cli_db-exec/issues) [Request Feature](https://github.com/Zheng-Bote/cxx-cli_db-exec/pulls)

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/Zheng-Bote/cxx-cli_db-exec?logo=GitHub)](https://github.com/Zheng-Bote/cxx-cli_db-exec/releases)

</div>

<hr>

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Description](#description)
  - [Features](#features)
- [Status](#status)
- [Documentation](#documentation)
  - [Usage](#usage)
    - [Example](#example)
      - [example DB system ini](#example-db-system-ini)
      - [example DB sql ini](#example-db-sql-ini)
- [Installation](#installation)
  - [Dependencies](#dependencies)
    - [Conan](#conan)
    - [CMake](#cmake)
    - [Doxygen](#doxygen)
      - [Doxygen Awesome](#doxygen-awesome)
    - [cxxopts](#cxxopts)
    - [inifile-cpp](#inifile-cpp)
    - [plog](#plog)
    - [PQXX_LIB](#pqxx_lib)
  - [folder structure](#folder-structure)
- [Authors and License](#authors-and-license)
  - [License](#license)
  - [Authors](#authors)
    - [Code Contributors](#code-contributors)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

<hr>

# Description

![CXX](https://img.shields.io/badge/C++-23-blue?logo=cplusplus)
![GHA](https://img.shields.io/badge/Github-Action-black?logo=githubactions)

command line tool to execute sql in an ordered way.

## Features

- \[ ] advanced-super-extra-special feature xyz

  <br>

- \[x] OSS and license
- \[x] works as designed
- \[ ] no bugs

<br>

- \[x] some more or less usefull Github Actions for GH-repo, GH-pages, GH-wiki, CI/CD-Pipelines
- \[x] Packagemanager (CPack)
- \[x] Installation routine (IFW;DEB;ZIP;TBZ2;RPM)
- \[ ] portable application
- \[x] logrotation included (100KiB)

<br>

- \[ ] runs on DOS/Windows
- \[ ] runs on MacOS
- \[x] runs on Linux
- \[ ] runs on iOS
- \[ ] runs on Android
- \[ ] runs on HarmonyOS

<p align="right">(<a href="#top">back to top</a>)</p>

# Status

![GitHub Created At](https://img.shields.io/github/created-at/Zheng-Bote/cxx-cli_db-exec)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/Zheng-Bote/cxx-cli_db-exec?logo=GitHub)](https://github.com/Zheng-Bote/cxx-cli_db-exec/releases)
![GitHub Release Date](https://img.shields.io/github/release-date/Zheng-Bote/cxx-cli_db-exec)
![Status](https://img.shields.io/badge/Status-stable-green)
![Status](https://img.shields.io/badge/Status-works_as_designed-green)

![GitHub Issues](https://img.shields.io/github/issues/Zheng-Bote/cxx-cli_db-exec)
![GitHub Pull Requests](https://img.shields.io/github/issues-pr/Zheng-Bote/cxx-cli_db-exec)

<p align="right">(<a href="#top">back to top</a>)</p>

# Documentation

- DB connections for different environments are managed in an (db system) Inifile (e.g.: dev, test, int, prod)
- SQL are defined in an (db sql) Inifile, divided into sections
  - each section has an `active`-attribute so the section can be de-activated
  - each section has a `type`-definition (e.g.: schema, fdw, db-links, triggers)
  - each section has an `id` so sections with same `type`-definition will be sorted ascending for execution
  - each section has an attribute `sql_string` which will be executed in this section first
  - each section has an attribute `sql_file` which will executed in this section as second (the sql-file will be parsed and each sql-statement within this file will be executed)
  - each section has an attribute `sql_path` which will executed in this section as third (all sql-files in the defined folder, starting with `<number>_<filename>.sql` will be sorted ascending, parsed and each sql-statement within this file will be executed). SQL-files in this folder without prefix `<number>_` will be ignored.

> \[!WARNING]
> please keep in mind about case sensitivity

> \[!CAUTION]
> it's highly recommended to encrypt your DB system Inifile.\
> Encrypt before upload to Git repository\
> Decrypt before using and encrypt after using\
> _see also:_ [qt-cli_file_encryption-decryption](https://github.com/Zheng-Bote/qt-cli_file_encryption-decryption)

<p align="right">(<a href="#top">back to top</a>)</p>

## Usage

```bash
DB deployments
command line tool to execute sql in an ordered manner
Usage:
  db_deploy [OPTION...]

  -c, --connect arg  <path/to/db_system.ini> with DB connect data
  -d, --debug        optional: run logging in debug mode
  -e, --env arg      environment to use, e.g.: dev, int, prod
  -s, --sql arg      <path/to/sql.ini> with sql instructions
  -t, --type arg     which type in sql.ini to work on, e.g.: schema, db-links
  -v                 print program version and exit
      --version      print program information and exit
  -h, --help         Print help and exit
```

### Example

run the tool and deploy schema definitions in dev environment

```cli
./db_deploy -c /iac/photo_gallery/db/db_system.ini -s /iac/photo_gallery/db/deploy/db_sql.ini --env dev --type schema
```

#### example DB system ini

> \[!CAUTION]
> it's highly recommended to encrypt your DB system Inifile.\
> Encrypt before upload to Git repository\
> Decrypt before using and encrypt after using\
> _see also:_ [qt-cli_file_encryption-decryption](https://github.com/Zheng-Bote/qt-cli_file_encryption-decryption)

```ini
[dev]
id=0
type=system
dbname=photo_gallery
hostname=192.168.178.19
password=IchBinRoot
port=1111
username=postgres
use_proxy=false
db_proxy=
db_proxy_port=
logfile_path=/tmp

[test]
id=1
type=system
dbname=t_photo_gallery
hostname=192.168.178.19
password=photo_gallery
port=1112
username=photo_gallery
use_proxy=false
db_proxy=
db_proxy_port=
logfile_path=/tmp/

[int]
id=2
type=system
dbname=i_photo_gallery
hostname=
password=Top$ecret?
port=
username=master
use_proxy=true
db_proxy=dbproxy-li52y.eu-central-1.aws.cloud
db_proxy_port=5555
logfile_path=/var/log/

[prod]
id=3
type=system
dbname=p_photo_gallery
hostname=
password=2hot4U!
port=
username=master
use_proxy=true
db_proxy=dbproxy-mh81h.eu-central-1.aws.cloud
db_proxy_port=8888
logfile_path=/var/log/
```

<p align="right">(<a href="#top">back to top</a>)</p>

#### example DB sql ini

> \[!WARNING]
> please keep in mind about case sensitivity

```ini
[tab1]
id=1
type=schema
name=base
active=true
sql_string=CREATE TABLE IF NOT EXISTS test_users (id INT PRIMARY KEY, name VARCHAR(100));
sql_file=./sql/schemas/base/base_starter.sql
sql_path=./sql/schemas/base

[othertab2]
id=1
type=trigger
name=triggers
active=true
sql_string=
sql_file=./sql/schemas/trigger/trigger_starter.sql
sql_path=

[notab3]
id=2
type=schema
name=base_extended
active=true
sql_string=
sql_file=
sql_path=./sql/schemas/

[betab4]
id=5
type=fdw
name=foreign_data_wrapper
active=false
sql_string=CREATE USER MAPPING FOR master SERVER geoapi  OPTIONS (user 'apiuser', password 'admin1234');
sql_file=#./sql/schemas/fdw/geoapi.sql
sql_path=

[istab5]
id=3
type=data
name=test_data
active=true
sql_string=INSERT INTO photo_location(id,continent, country, country_code, province, city, district) VALUES (10,'EU', 'Germoney', 'de', 'Bavaria', 'Munich', 'gma');
sql_file=
sql_path=./sql/data/photo_gallery

[mytab6]
id=3
type=schema
name=mytable3
active=false
sql_string=
sql_file=./test/create_table.sql
sql_path=

[othername]
id=39
type=schema
name=mytable3
active=false
sql_string=
sql_file=
sql_path=#./test

[dotab8]
id=23
type=schema
name=mytable3
active=false
sql_string=
sql_file=
sql_path=./schemas
```

<p align="right">(<a href="#top">back to top</a>)</p>

# Installation

Several installation packages are available, depending on your Linux system (deb, rpm, zip, AppImage).

> \[!NOTE]
> see (latest) Release for packages

## Dependencies

> \[!NOTE]
> All licenses are therefore Open Source.

### Conan

Conan, software package manager for C and C++ developers

[![Conan](https://img.shields.io/badge/Conan-v2+-6699CB?logo=conan)](https://github.com/conan-io/conan)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

### CMake

CMake: A Powerful Software Build System

[![CMake](https://img.shields.io/badge/CMake-v3.23+-064F8C?logo=cmake)](https://github.com/conan-io/conan)
[![BSD-3 License](https://img.shields.io/badge/License-BSD_3-green.svg)](https://choosealicense.com/licenses/bsd-3-clause/)

### Doxygen

Code Documentation. Automated.

[![Doxygen](https://img.shields.io/badge/Doxygen-v1.12+-2C4AA8?logo=doxygen)](https://github.com/doxygen/doxygen)
[![GPL-2 License](https://img.shields.io/badge/License-GPL_2-green.svg)](https://choosealicense.com/licenses/gpl-2.0/)

#### Doxygen Awesome

Doxygen Awesome is a custom CSS theme for Doxygen HTML documentation.

This theme is an attempt to update the visuals of Doxygen without changing its overall layout too much.

[![Doxygen Awesome](https://img.shields.io/badge/Doxygen_Awesome-v2.3.3-2C4AA8?logo=doxygen)](https://github.com/jothepro/doxygen-awesome-css)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

### cxxopts

a lightweight C++ option parser library, supporting the standard GNU style syntax for options.

[![jarro2783](https://img.shields.io/badge/Github-jarro2783-black?logo=github)](https://github.com/jarro2783/cxxopts)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

> \[!NOTE]
> managed via the package manager [![Conan Center](https://img.shields.io/conan/v/cxxopts)](https://conan.io/center/recipes/cxxopts)

### inifile-cpp

inifile-cpp is a simple and easy to use single header-only ini file en- and decoder for C++.

[![Fabian Meyer](https://img.shields.io/badge/Github-Fabian_Meyer-black?logo=github)](https://github.com/Rookfighter/inifile-cpp)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

> \[!NOTE]
> included in `src/includes`

### plog

Plog - portable, simple and extensible C++ logging library

[![Sergey Podobry](https://img.shields.io/badge/Github-Sergey_Podobry-black?logo=github)](https://github.com/SergiusTheBest/plog)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

> \[!NOTE]
> managed via the package manager [![Conan Center](https://img.shields.io/conan/v/plog)](https://conan.io/center/recipes/plog)

### PQXX_LIB

__tbd__

## folder structure

<!-- readme-tree start -->
```
.
├── .github
│   ├── actions
│   │   └── doctoc
│   │       ├── README.md
│   │       ├── action.yml
│   │       └── dist
│   │           ├── index.js
│   │           ├── index.js.map
│   │           ├── licenses.txt
│   │           └── sourcemap-register.js
│   └── workflows
│       ├── ghp-call_Readme.yml
│       ├── ghp-create_doctoc.yml
│       ├── ghp-markdown_index.yml
│       ├── repo-actions_docu.yml
│       ├── repo-call_Readme.yml
│       ├── repo-create_doctoc.yml_
│       ├── repo-create_doctoc_md.yml
│       └── repo-create_tree_readme.yml
├── .gitignore
├── LICENSE
├── README.md
├── do_compile.sh
├── docs
│   ├── .gitkeep
│   └── img
│       └── console_logs.png
├── src
│   ├── CMakeLists.txt
│   ├── conanfile.txt
│   ├── configure
│   │   ├── ClangTidy.cmake
│   │   ├── Doxygen.cmake
│   │   ├── extra_headers
│   │   └── rz_config.h.in
│   ├── includes
│   │   ├── dotenv.h
│   │   ├── inicpp.h
│   │   ├── rz_config.h
│   │   ├── rz_db.h
│   │   ├── rz_fs.cpp
│   │   ├── rz_fs.h
│   │   ├── rz_inifile.cpp
│   │   ├── rz_inifile.h
│   │   ├── rz_logpath.h
│   │   ├── rz_options.h
│   │   ├── rz_parse_sqlfile.h
│   │   ├── rz_snippets.cpp
│   │   ├── rz_snippets.h
│   │   └── rz_strings.h
│   └── main.cpp
└── tree.bak

11 directories, 42 files
```
<!-- readme-tree end -->

<p align="right">(<a href="#top">back to top</a>)</p>

# Authors and License

## License

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

Copyright (c) 2025 ZHENG Robert

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

        https://choosealicense.com/licenses/mit/

## Authors

- [![Zheng Robert](https://img.shields.io/badge/Github-Zheng_Robert-black?logo=github)](https://www.github.com/Zheng-Bote)

### Code Contributors

![Contributors](https://img.shields.io/github/contributors/Zheng-Bote/cxx-cli_db-exec?color=dark-green)

[![Zheng Robert](https://img.shields.io/badge/Github-Zheng_Robert-black?logo=github)](https://www.github.com/Zheng-Bote)

<hr>

:vulcan_salute:

<p align="right">(<a href="#top">back to top</a>)</p>
