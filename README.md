# 🧠 CustomShell

**CustomShell** is a C++-based terminal simulator designed to mimic Linux-like shell behavior on Windows.  
It allows users to interact with a virtual environment (`Playground` directory) through a rich set of commands, logical operations, and redirections — all inside a simulated terminal experience.

---

## ⚙️ Overview

CustomShell offers an interactive shell interface that accepts and executes commands similar to Unix/Linux terminals.  
It provides users a sandboxed environment to explore file operations, command logic, and error handling — all within Windows.

The shell supports:
- File and directory management
- Input/output redirections
- Logical command chaining (`&&`, `||`)
- Command history and timestamp logging
- Access restriction to the local sandbox (`Playground`)

---

## 🧩 File Structure

```
CustomShell/
│
├── main.cpp
├── play.bat
├── Commands.md
├── help.txt
├── history.log
│
├── resources/
│   ├── shell.h / shell.cpp
│   ├── user.h
│   ├── command.h / command.cpp
│   ├── ls_CMD.h
│   ├── cd_CMD.h
│   ├── mkdir_CMD.h
│   ├── rmdir_CMD.h
│   ├── rm_CMD.h
│   ├── touch_CMD.h
│   ├── echo_CMD.h
│   ├── cp_CMD.h
│   ├── mv_CMD.h
│   ├── cat_CMD.h
│   ├── head_CMD.h
│   ├── tail_CMD.h
│   ├── grep_CMD.h
│   ├── find_CMD.h
│   └── misc_CMD.h
│
└── Playground/
    └── (sample files and directories)
```

---

## 🚀 Getting Started

### Prerequisites
- **Windows OS**
- **g++** (from MinGW or equivalent)

### Running the Shell
1. Open a terminal in the project root.
2. Run the following command:
   
   ```bash
   play
   ```
   or simply double-click `play.bat`.

The batch file compiles all C++ sources and launches the shell:
```bash
g++ *.cpp resources/*.cpp -o main
clear && main
```

---

## 🧠 Core Architecture

- **`main.cpp`**  
  Handles command parsing, logical chaining (`&&`, `||`), and dispatching to command classes.

- **`resources/shell.h` & `shell.cpp`**  
  Define regex patterns for validating commands, paths, and content initialization for `Playground`.

- **`resources/command.h` & `command.cpp`**  
  Contain the base `COMMAND` class with virtual `validate()` and `execute()` methods, plus helper functions like:
  - `get_location()` – Validates and resolves user paths (restricts access outside `Playground`).
  - `dispatch()` – Routes command input to its respective child class.

- **Command Classes (`*_CMD.h`)**  
  Each class (e.g., `ls_CMD`, `grep_CMD`) inherits from `COMMAND` and implements its own validation and execution logic using C++ `filesystem`, STL containers (`unordered_map`, `unordered_set`, `vector`), and exception handling.

- **`user.h`**  
  Defines the user object that holds a fixed home directory (`Playground`) and the user’s current working path.

---

## ⚡ Features

✅ Command support for:
- File operations: `ls`, `cd`, `mkdir`, `rmdir`, `rm`, `touch`, `cp`, `mv`, `cat`, `head`, `tail`, `grep`, `find`
- Misc utilities: `pwd`, `help`, `reset`, `clear`, `data`, `history`, `time`, `exit`

✅ Logical operations:
- Supports `&&` and `||` chaining with proper precedence handling.

✅ Redirection:
- Output of commands can be redirected to files using standard redirection syntax.

✅ History Logging:
- Every command (valid or invalid) is recorded in `history.log` with a timestamp.

✅ Environment Reset:
- The `reset` command restores the `Playground` directory to its original state.

✅ Sandboxed Interaction:
- All operations are confined within the `Playground` directory for safety.

---

## 💻 Example Usage

```bash
Playground $ ls -l
2025-11-05 16:22:27   371 B   bash.txt
2025-11-05 16:22:27   500 B   essay.txt
2025-11-05 16:22:28   148 B   summary.log
Playground $ cd documents
Playground\documents $ mkdir projects
Playground\documents $ echo "Hello World" > hello.txt
Playground\documents $ cat hello.txt
Hello World
Playground\documents $ grep "World" hello.txt && echo "Match found" || echo "No match"
Hello World
Match found
Playground\documents $ reset
Playground\documents $ cd ~
Playground $
```

---

## 📘 Developer Notes

- All errors are caught in `main.cpp` and displayed gracefully on the terminal.  
- A full command reference is available in [`Commands.md`](./Commands.md).  
- The `help` command displays available commands directly within the shell.  
- The simulation runs entirely on Windows using native C++ compilation (no external dependencies).  

---

**CustomShell** – A lightweight, educational, and extensible C++ terminal simulator for Windows.
