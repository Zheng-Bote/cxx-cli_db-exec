<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [10 Interaction Overview Diagram](#10-interaction-overview-diagram)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# 10 Interaction Overview Diagram

The interaction overview diagram brings the focus to the control flow between various interactions or participants inside the application architecture.

```mermaid
flowchart TD
    subgraph Initialization
    A((Start App)) --> B[Read DB_INI]
    B --> C[Setup Logger]
    C --> D[Read SQL_INI]
    D --> E[Establish Database Connection]
    end

    subgraph "Execution Sequence Loop"
    F{Are there sections\nleft to process?}
    E --> F
    F -->|Yes| G[Process `sql_string`]
    G --> H[Process `sql_file`]
    H --> I[Process `sql_path`]
    I --> F
    end

    subgraph Termination
    F -->|No| J((Exit App))
    end
```
