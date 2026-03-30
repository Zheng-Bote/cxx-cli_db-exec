<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [05 Deployment Diagram](#05-deployment-diagram)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# 05 Deployment Diagram

The deployment diagram illustrates the CLI tool on its host system and how it interfaces with external infrastructure.

```mermaid
flowchart TB
    subgraph Host["Host Machine (Linux)"]
        CLI["db_deploy (Binary)"]
        subgraph Files["Local Filesystem"]
            SysIni[("db_system.ini")]
            SqlIni[("db_sql.ini")]
            SqlDocs[("*.sql Files")]
            Logs["Log Files (.log)"]
        end
        CLI -- Reads --> SysIni
        CLI -- Reads --> SqlIni
        CLI -- Reads --> SqlDocs
        CLI -- Writes --> Logs
    end

    subgraph Internal_Network["Internal Network"]
        PROXY["Database Proxy"]
        DB_TEST[("Test PostgreSQL DB")]
    end

    subgraph Cloud["Cloud Infrastructure"]
        DB_PROD[("Prod PostgreSQL DB")]
    end

    CLI -- "TCP/IP (pqxx direct)" --> DB_TEST
    CLI -- "TCP/IP (pqxx via proxy)" --> PROXY
    PROXY -- Forward --> DB_PROD

```
