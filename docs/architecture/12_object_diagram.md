<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [12 Object Diagram](#12-object-diagram)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# 12 Object Diagram

The object diagram visualizes a distinct snapshot in time of the configuration instances required for execution.

```mermaid
classDiagram
    Object <|-- `sptr_dbini_config : std::shared_ptr<Inifile>`
    Object <|-- `sptr_sqlini_config : std::shared_ptr<Inifile>`
    Object <|-- `dbConnect : pqxx::connection`

    class `sptr_dbini_config : std::shared_ptr<Inifile>` {
        pathToIniFile = "/iac/photo_gallery/db/db_system.ini"
        dbConnectString = "dbname=photo_gallery user=postgres password=IchBinRoot host=192.168.178.19 port=1111"
        sectionTypes = ["system"]
    }

    class `sptr_sqlini_config : std::shared_ptr<Inifile>` {
        pathToIniFile = "/iac/photo_gallery/db/deploy/db_sql.ini"
        orderedSections[1] = "tab1"
        orderedSections[2] = "notab3"
        orderedSections[3] = "istab5"
    }

    class `dbConnect : pqxx::connection` {
        hostname = "192.168.178.19"
        port = "1111"
        backendpid = 12345
        status = is_open
    }

```
