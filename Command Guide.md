# Command Guide

---

## **`ls`** Command and Options

| # | Command | Description |
|---|------------------|--------------|
| 1 | `ls` | List files in current directory with name only |
| 2 | `ls -l` | List files in current directory with name and size |

---

## **`rm`** Command and Options

| # | Command Example       | Description                               | Works? |
|---| --------------------- | ----------------------------------------- | ------ |
| 1 | `rm file.txt`         | Deletes file.txt                          |   ✅   |
| 2 | `rm -r folder`        | Deletes `folder` recursively              |   ✅   |
| 3 | `rm folder`           | Gives error: `No such file or directory`  |   ❌   |
| 4 | `rm *.txt`            | Deletes all `.txt` files                  |   ✅   |

---

## **`cd`** Command Behavior

| # | Command Example                          | Description                                      | Will it Work? | Notes                                                  |
|---| ---------------------------------------- | ------------------------------------------------ | ------------- | ------------------------------------------------------ |
| 1 | `cd ~`                                   | Returns to home directory                        | ✅            | Shortcut to home directory                             |
| 2 | `cd`                                     | Returns to home directory                        | ✅            | Same as `cd ~`                                         |
| 3 | `cd /path/to/directory`                  | Moves to directory via absolute path             | ✅            | Must exist and be accessible                           |
| 4 | `cd ./path/to/directory`                 | Moves using relative path from current dir       | ✅            | Same as `cd /path/to/directory` if absolute equivalent |
| 5 | `cd ../path/to/directory`                | Moves one level up, then into path               | ✅            | Must exist relative to parent directory                |
| 6 | `cd /path/to/directory`                  | A directory doesn't exist somewhere in the path  | ❌            | `cd: No such file or directory`                        |
| 7 | `cd file.txt`                            | Tries to open a file as directory                | ❌            | `cd: file.txt: Not a directory`                        |
| 8 | `cd folder`                              | Moves into `folder` in current dir               | ✅            | Error if folder doesn’t exist                          |
| 9 | `cd ./folder`                            | Moves into `folder` in current dir               | ✅            | Same as `cd folder`                                    |
| 10 | `cd ..`                                  | Moves one directory up                           | ✅            | Does nothing if already at home root in sandbox        |
| 11 | `cd ../..`                               | Moves two directories up                         | ✅            | Works only if both parents exist                       |
| 12 | `cd ....`                                | Trying to move two directories up                | ❌            | `cd: ....: No such file or directory`                  |

---

## **`mkdir`** & **`rmdir`** Command Behavior

| # | Command Example             | Description                                                        | Will it work? |
|---| --------------------------- | ------------------------------------------------------------------ | ------------- |
| 1 | `mkdir directory`           | Creates `directory` in the current directory                        | ✅           |
| 2 | `mkdir directory`           | `directory` already exists in the current directory                 | ❌           |
| 3 | `mkdir /path/directory`     | Creates `directory` inside `path`                                   | ✅           |
| 4 | `rmdir directory`           | Deletes `directory`, only if its empty                              | ✅           |
| 5 | `rmdir directory`           | `directory` is not empty                                            | ❌           |
| 6 | `rmdir /path/directory`     | Moves along the `path` and deletes `directory`, only if its empty   | ✅           |

---

## **`cp`** & **`mv`** Command Behavior

| # | Command Example | Description | Works? | Notes |
|---|------------------|--------------|--------|-------|
| 1 | `cp notes.txt Files` | Copies file into an existing directory | ✅ | `Files` must be an existing folder |
| 2 | `cp notes.txt Files` | Copies file but directory doesn’t exist | ❌ | Error: *No such file or directory* |
| 3 | `cp notes.txt list.txt` | Copies and rename a file | ✅ | Creates `list.txt` |
| 4 | `cp notes.txt Files/list.txt` | Copies file into a directory with a new name | ✅ | Directory must exist |
| 5 | `cp -r Files Backup` | Copies an entire directory recursively | ✅ | Copies folder and all contents |
| 6 | `cp Files Backup` | Copies directory without `-r` | ❌ | Error: *omitting directory* |
| 7 | `cp file.txt destination` | `file.txt` doesn’t exist in current directory | ❌ | Error: *cannot stat 'file.txt'* |
| 8 | `cp ../file.txt ./` | Copies a file from parent directory into current directory | ✅ | `../file.txt` must exist |
| 9 | `cp file.txt ../` | Copies a file from current directory into parent directory | ✅ | Creates `../file.txt` |

### **Note**
Every command starting with `mv` works just the **same way** as `cp`,  
except that **`mv` removes the source file or directory after moving**.

---

## **`head`** & **`tail`** & **`cat`** Commands and Options

| # | Command                  | Description                                                     | Will it Work? |
|---|--------------------------|-----------------------------------------------------------------|---------------|
| 1 | `head file.txt`          | Prints first 5 lines of `file.txt`                              | ✅            |
| 2 | `head program.exe`       | Will print gibberish like `MZ��@�...PE..L..text...data..@#$`  | ✅            |
| 3 | `head Folder`            | Gives error: `'Folder' is a directory`                          | ❌            |
| 4 | `head -n 10 file.txt`    | Prints first 5 lines of `file.txt`                              | ✅            |
| 5 | `head -c 10 program.exe` | Will first 5 characters of `program.exe` like `MZ��@�...P`    | ✅            |

### **Note**
Every command starting with `tail` works just the **same way** as `head`,  
except that **`tail` will print from bottom up**.

Every command starting with `tail` works just the **same way** as `head`,  
except that **`cat` will print everything, and doesn't have any option**.

---

## Miscellaneous Commands

| # | Command | Description |
|---|------------------|--------------|
| 1 | `pwd` | Shows the current working directory path |
| 2 | `date` | Shows current date and time |
| 3 | `clear` | Clears the terminal screen |
| 4 | `history` | Shows command history |
| 5 | `echo <text>` | Prints `text` to the terminal |
| 6 | `touch <file.txt>` | Creates a `file.txt` in current dir/Updates timestamp of `file.txt` |

---

## Logical Operators

| # | Operator | Description |
|---|------------------|--------------|
| 1 | `&&` | Performs an AND operation between two commands |
| 2 | `\|\|` | Performs an OR operation between two commands |
| 2 | `!` | Inverts the `exit status` but output will remain the same |

### **Note**
The precedence of `&&` is higher than `||`, so a `||` operation will only
be evaluated after performing all `&&` operations in its group.
