<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [13 Package Diagram](#13-package-diagram)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# 13 Package Diagram

This diagram displays the namespaces and package layout conceptually modeled around the `cxx-cli_db-exec` repository structure.

```mermaid
classDiagram
    class `src` {
        <<package/folder>>
        main.cpp
    }

    class `includes` {
        <<package/folder>>
        inicpp.h
        cxxopts.hpp
    }

    class `rz_modules` {
        <<namespace collection>>
        rz_db
        rz_fs
        rz_options
        rz_logpath
        rz_parse_sqlfile
        rz_strings
    }

    class `Third-Party` {
        <<dependencies>>
        plog
        pqxx
    }

    `src` ..> `includes` : imports
    `includes` ..> `rz_modules` : outlines
    `rz_modules` ..> `Third-Party` : wrapper/interfaces
```
