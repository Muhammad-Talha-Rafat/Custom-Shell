# ⚙️ CustomShell
[![cpp](https://img.shields.io/badge/Language-C++-darkpink?style=for-the-badge)](https://code.visualstudio.com/docs/languages/cpp)
[![windows](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge)](https://www.microsoft.com/en-us/windows?r=1)

> 🧠 A Linux-style terminal emulator built in C++ for Windows

---

### 🎯 Overview
**CustomShell** simulates a Linux-like shell experience on Windows. It allows users to execute familiar terminal commands, use logical operators, and perform file operations — all within a sandboxed environment (`Playground`) using pure C++.

---

### 📂 File Structure
```
CustomShell/
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
│   ├── [command]_CMD.h  ← one for each command (ls, cd, grep, etc.)
│
└── Playground/
    └── sample files & directories
```

---

### ⚡ Features
- 🧩 **Command support:** `ls`, `cd`, `mkdir`, `rmdir`, `rm`, `touch`, `echo`, `cp`, `mv`, `cat`, `head`, `tail`, `grep`, `find`
- ⚙️ **Misc commands:** `pwd`, `help`, `reset`, `clear`, `data`, `history`, `time`, `exit`
- 🔗 **Logical operators:** `&&`, `||` with proper precedence handling
- 📤 **Redirections:** redirect command output to files
- 🕒 **Command history:** logs all commands with timestamps in `history.log`
- 🔒 **Sandboxed environment:** restricts access outside `Playground`
- ♻️ **Reset simulation:** restores `Playground` to its original state

---

### 🚀 Getting Started
#### Prerequisites
- Windows OS  
- g++ compiler (MinGW or equivalent)

#### Run the Shell
```bash
play
```
or double-click `play.bat`  
This compiles and launches the shell using:
```bash
g++ *.cpp resources/*.cpp -o main
clear && main
```

---

### 🧠 Architecture Overview
- **main.cpp** – Parses user commands, handles logical chaining, and dispatches execution.  
- **shell.h / shell.cpp** – Define regex patterns, command validation, and Playground initialization.  
- **command.h / command.cpp** – Contain base `COMMAND` class (`validate()`, `execute()`, `dispatch()`, `get_location(path)`).  
- **user.h** – Stores user’s home and current directory.  
- **[command]_CMD.h** – Each command inherits from `COMMAND` and implements its logic using C++ STL and `filesystem`.

---

### 💻 Example Session
```bash
Playground $ ls -l
2025-11-05 16:22:27   371 B   bash.txt
2025-11-05 16:22:27   500 B   essay.txt
2025-11-05 16:22:28   148 B   summary.log
Playground $ cd documents
Playground\documents $ mkdir projects
Playground\documents $ echo "Hello World" > hello.txt
Hello World
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

### 🧾 Notes
- Errors are caught in `main.cpp` and displayed on the terminal.  
- Full command reference available in [`Commands.md`](./Commands.md).  
- The `help` command shows available commands within the shell.  
- Runs entirely on Windows — no dependencies beyond standard **g++**.

---

**CustomShell** — A lightweight, educational, and extensible C++ terminal simulator for Windows.
