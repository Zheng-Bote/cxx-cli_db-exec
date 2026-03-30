# 01 Overview Diagram

This document provides a high-level overview of the `cxx-cli_db-exec` architecture, detailing its context boundary and external interfaces.

## Bounded Context Diagram

The bounded context diagram shows the CLI application in relation to external actors, such as the user, configuration files, and the target databases.

```mermaid
mindmap
  root((cxx-cli_db-exec))
    Configuration
      DB System INI
      DB SQL INI
    Target Environment
      PostgreSQL Databases
      Database Proxies
    Input Data
      SQL Scripts
    Observability
      Console Output
      Rolling Log Files
```

## Interfaces Diagram

The interfaces diagram illustrates the primary inputs and outputs of the tool.

```mermaid
flowchart TD
    User([User]) -->|Executes CLI with args| App(cxx-cli_db-exec)
    
    subgraph Inputs
        SysIni[db_system.ini]
        SqlIni[db_sql.ini]
        SqlFiles[*.sql Source Files]
    end
    
    SysIni -->|Parsed via inicpp| App
    SqlIni -->|Parsed via inicpp| App
    SqlFiles -->|Read & Parsed| App
    
    subgraph Outputs
        DB[(PostgreSQL DB)]
        LogFile[File Logger]
        Console[Console Output]
    end
    
    App -->|Executes SQL| DB
    App -->|Appends logs| LogFile
    App -->|Standard Output| Console
```
