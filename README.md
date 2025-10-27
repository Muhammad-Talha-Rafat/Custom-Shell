# 🧠 Custom Shell - Operating Systems Project 1

### Course: Operating Systems (CS 23)
### Language: C++
### Team Members: [Your Names Here]

---

## 📘 Overview
This project implements a **Custom Shell** in **C++**, developed as part of the **Operating Systems Project 1**.  
The shell provides a command-line interface that accepts user input, parses commands, and executes both built-in and external programs using system calls such as `fork()`, `execvp()`, and `waitpid()`.

The main goal is to understand **process creation**, **I/O redirection**, **piping**, and **basic command interpretation** — core concepts of modern operating systems.

---

## ⚙️ Features Implemented
- Interactive shell prompt  
- Execution of built-in and external commands  
- Support for multiple arguments  
- Error handling for invalid commands  
- Relative and absolute path support  
- I/O redirection (`>`, `<`)  
- Piping between commands (`|`)  
- Command history (in-memory)  
- Graceful exit using `exit` command  
- Clean and minimal UI prompt  

---

## 💡 Built-in Commands
| Command | Description | Example |
|----------|--------------|----------|
| `cd` | Change directory | `cd E:/Repositories` |
| `pwd` | Print current working directory | `pwd` |
| `mkdir` | Create a new directory | `mkdir test` |
| `rmdir` | Remove an empty directory | `rmdir test` |
| `ls` | List files in current directory | `ls -l` |
| `touch` | Create a new file | `touch notes.txt` |
| `clear` | Clear the screen | `clear` |
| `echo` | Display a line of text | `echo Hello World` |
| `exit` | Close the shell | `exit` |

---

## 🚀 Custom / Fun Commands
| Command | Description |
|----------|--------------|
| `mood` | Displays a random message or quote |
| `sysinfo` | Shows system information (CPU, memory, uptime) |
| `calc` | Performs basic arithmetic operations |
| `whereami` | Prints the current user and working directory |
| `fortune` | Displays a random fortune message |
| `color` | Changes shell prompt color |

---

## 🏗️ System Calls & Concepts Used
- **`fork()`** – to create a new process  
- **`execvp()`** – to execute external programs  
- **`waitpid()`** – to wait for child processes  
- **`dup2()`** – for I/O redirection  
- **`pipe()`** – for command chaining  
- **`chdir()`** – for directory navigation  
- **Signals (`SIGINT`, `SIGTSTP`)** – to handle Ctrl+C and Ctrl+Z gracefully  

---

## 🧩 How to Run
### **1. Clone the repository**
```bash
git clone https://github.com/your-username/custom-shell.git
cd custom-shell
```

### **2. Compile**
```bash
g++ shell.cpp -o shell
```

### **3. Run**
```bash
./shell
```

---

---

## 🔮 Possible Future Enhancements
- Tab completion for commands and filenames  
- Persistent command history (`~/.darkshell_history`)  
- Multi-job background execution (`&`)  
- Theming and animated startup banner  
- Alias system for custom shortcuts  

---

## ✨ Authors
- [Your Name 1]  
- [Your Name 2]  
- [Your Name 3]  

---

## 📄 License
This project is developed for educational purposes as part of the **Operating Systems (CS 23)** coursework.  
Feel free to modify or extend it for learning or academic use.
