<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [03 Sequence Diagram](#03-sequence-diagram)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# 03 Sequence Diagram

This sequence diagram illustrates the lifecycle of the application execution, triggered from standard user invocation.

```mermaid
sequenceDiagram
    actor User
    participant main as main()
    participant options as rz_options
    participant db_ini as Inifile (DB)
    participant sql_ini as Inifile (SQL)
    participant rz_db
    participant db as PostgreSQL DB
    participant plog as plog Logger
    
    User->>main: ./db_deploy [args]
    main->>options: check_options(argc, argv)
    options-->>main: args (unordered_map)
    
    main->>db_ini: loadIni(dbSystemIni)
    db_ini-->>main: success
    
    main->>db_ini: getStringValue(env, "logfile_path")
    db_ini-->>main: logfilePath
    main->>plog: init(logfile)
    
    main->>sql_ini: loadIni(dbSqlIni)
    sql_ini-->>main: success
    
    main->>rz_db: setDbConnect(db_ini, env)
    rz_db->>db: pqxx::connection(connectString)
    db-->>rz_db: connected
    rz_db-->>main: success
    
    main->>sql_ini: getOrderedType(args["type"])
    sql_ini-->>main: sortedSections list
    
    loop for each section Name in sortedSections
        main->>sql_ini: getStringValue("sql_string")
        opt if valid sql_string
            main->>rz_db: execSQL(sql)
            rz_db->>db: db.exec(sql), db.commit()
            db-->>rz_db: success
            rz_db-->>main: success
        end
        
        main->>sql_ini: getStringValue("sql_file")
        opt if valid sql_file
            main->>main: rz_parse_sqlfile::parseSQLFile(file)
            loop for each sql statement
                main->>rz_db: execSQL(sql)
                rz_db->>db: exec
                db-->>rz_db: success
                rz_db-->>main: success
            end
        end
        
        main->>sql_ini: getStringValue("sql_path")
        opt if valid sql_path
            main->>main: Filesystem::listDirectoryItems()
            main->>main: sort files by number prefix
            loop for each sql file
                main->>main: parseSQLFile(file)
                loop for each sql statement
                    main->>rz_db: execSQL(sql)
                    rz_db->>db: exec
                    db-->>rz_db: success
                    rz_db-->>main: success
                end
            end
        end
    end
    
    main->>User: exit(EXIT_SUCCESS)
```
