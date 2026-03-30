<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [11 Communication Diagram](#11-communication-diagram)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# 11 Communication Diagram

This diagram displays how independent modules pass messages and coordinate in order to achieve the SQL execution lifecycle. In Mermaid JS, a `flowchart` is used to represent the communication patterns.

```mermaid
flowchart LR
    Main["main()"]
    Options["rz_options"]
    INI["Inifile Configs"]
    Parse["rz_parse_sqlfile"]
    FS["Filesystem"]
    DB["rz_db"]
    Pos["PostgreSQL Server"]
    Logger["plog Log Engine"]

    Main -- "1: parse args" --> Options
    Main -- "2: load system config" --> INI
    Main -- "3: init logger" --> Logger
    Main -- "4: load sql config" --> INI
    Main -- "5: set up connection" --> DB
    DB -- "6: open remote connection" --> Pos
    Main -- "7: call SQL string/folder" --> FS
    Main -- "8: parse raw SQL" --> Parse
    Main -- "9: push SQL to exec" --> DB
    DB -- "10: exec & commit" --> Pos
    Main -- "11: flush output" --> Logger
```
