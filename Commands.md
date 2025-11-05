# **Linux Command Guide**

---

## **1️⃣ File and Directory Commands**

| Command    | Example                 | Description                                      |
| ---------- | ----------------------- | ------------------------------------------------ |
| `ls`       | `ls [directory]`        | List files in `directory`                        |
| `pwd`      | `pwd`                   | Show current working directory                   |
| `cd`       | `cd /path/to/directory` | Change directory (absolute or relative)          |
| `cd ~`     | `cd`                    | Return to home directory                         |
| `mkdir`    | `mkdir folder`          | Create a directory                               |
| `rmdir`    | `rmdir folder`          | Delete an empty directory                        |
| `rm`       | `rm file.txt`           | Delete a file                                    |
| `rm -r`    | `rm -r folder`          | Delete folder recursively                        |
| `rm *.txt` | `rm *.txt`              | Delete all `.txt` files in the current directory |

**Notes:**

* `ls` with `-l` will list files with name, size, and date.
* `cd` will fail if the path doesn’t exist or is a file.
* `mkdir` will fail if directory already exists.
* `rm folder` without `-r` will fail if folder is not empty.

---

## **2️⃣ Copying and Moving Files**

| Command | Example                      | Description             |
| ------- | ---------------------------- | ----------------------- |
| `cp`    | `cp file.txt /path/to/dest/` | Copy file to directory  |
| `cp`    | `cp file.txt newfile.txt`    | Copy and rename file    |
| `cp -r` | `cp -r folder Backup`        | Copy folder recursively |
| `mv`    | `mv file.txt /path/to/dest/` | Move file or directory  |
| `mv`    | `mv file.txt newname.txt`    | Rename file             |
| `mv`    | `mv files Backup`            | Move directory          |

**Notes:**

* `mv` removes the source after moving.
* Copying directories with `cp` requires `-r`; moving with `mv` does not require `-r`.
* If the target path/name does not exist, `mv` will rename the source to the target name.
* If the target exists and is a directory, `mv` will move the source inside the target directory.

---

## **3️⃣ Viewing File Content**

| Command               | Example               | Description                  |
| --------------------- | --------------------- | ---------------------------- |
| `cat`                 | `cat file.txt`        | Print full content of file   |
| `head`                | `head file.txt`       | Print first 10 lines of file |
| `head -n 5 file.txt`  | `head -n 5 file.txt`  | Print first 5 lines          |
| `head -c 10 file.txt` | `head -c 10 file.txt` | Print first 10 bytes         |
| `tail`                | `tail file.txt`       | Print last 10 lines of file  |
| `tail -n 5 file.txt`  | `tail -n 5 file.txt`  | Print last 5 lines           |
| `tail -c 10 file.txt` | `tail -c 10 file.txt` | Print last 10 bytes          |

**Notes:**

* `head`, `tail` or `cat` on directories will give an error.
* Binary files (`.exe`) will print gibberish when using `head`/`tail`/`cat`.

---

## **4️⃣ Creating and Updating Files**

| Command | Example                            | Description                           |
| ------- | ---------------------------------- | ------------------------------------- |
| `touch` | `touch file.txt`                   | Create empty file or update timestamp |
| `echo`  | `echo [text] [redirection] [file]` | Prints text to terminal or file       |

---

## **5️⃣ Miscellaneous Commands**

| Command   | Example                              | Description                                 |
| --------- | ------------------------------------ | ------------------------------------------- |
| `date`    | `date`                               | Show current date                           |
| `time`    | `time`                               | Show current time                           |
| `clear`   | `clear`                              | Clear terminal screen                       |
| `reset`   | `reset`                              | Reset file structure                        |
| `history` | `history`                            | Show previously run commands                |
| `exit`    | `exit`                               | Terminates the session and ends the program |
| `help`    | `help`                               | Show this manual but on terminal            |
| `grep`    | `grep [options] [pattern] [file]`    | Search for pattern in file                  |
| `find`    | `find [path] [options] [expression]` | Search for files matching a pattern         |

### **Common `grep` Options**

* `-i` → Case-insensitive search
* `-n` → Show line numbers of hits, followed by line itself
* `-w` → Match the whole word only
* `-c` → Count the number of matching lines

### **Common `find` Options**

* `-name [filename]` → Match files by filename (case-sensitive)
* `-iname [filename]` → Match files by filename (case-insensitive)
* `-type f` → Find all files in `[path]`
* `-type d` → Find all directories in `[path]`
* `-size <number>[C|K|M]` → Find files by size:

  * `C` → bytes
  * `K` → kilobytes
  * `M` → megabytes

---

## **6️⃣ Redirect Operators**

| Command | Example Usage                         | Description                                                 |
| ------- | ------------------------------------- | ----------------------------------------------------------- |
| `cat`   | `cat < file.txt`                      | Works the same way as `cat file.txt`                        |
|         | `cat file1.txt > file2.txt`           | Overwrite `file2.txt` with `file1.txt` content              |
|         | `cat file1.txt >> file2.txt`          | Append `file1.txt` content to `file2.txt`                   |
| `echo`  | `echo < "text"`                       | Works the same way as `echo "text"`                         |
|         | `echo "text" > file.txt`              | Overwrite "`text`" with `file.txt` content                  |
|         | `echo "text" >> file.txt`             | Append "`text`" to `file.txt`                               |
| `ls`    | `ls < folder`                         | Works the same way as `ls folder`                           |
|         | `ls > file.txt`                       | Save listing to `file.txt`                                  |
|         | `ls -l >> file.txt`                   | Append long-format listing to `file.txt`                    |
| `grep`  | `grep "error" < file.txt`             | Works the same way as `grep "error" file.txt`               |
|         | `grep "error" file1.txt > file2.txt`  | Overwrite matching lines of `file1.txt` in `file2.txt`      |
|         | `grep "error" file1.txt >> file2.txt` | Append matching lines of `file1.txt` to `file2.txt`         |
| `find`  | `find . -name "*.py" < file.txt`      | Works the same way as `file . -name "*.py"`                 |
|         | `find . -size +1M > file.txt`         | Save filenames of all files greater than 1 MB in `file.txt` |
|         | `find . -type f >> file.txt`          | Append all filenames to `file.txt`                          |

**Notes:**

* Redirect operators can be used with `echo`, `cat`, `find`, `ls`, `grep` commands.
* The input redirection operator (`<`) can be used, but wouldn’t have any effect.

---

## **7️⃣ Logical Operators**

| Operator | Description                                |
| -------- | ------------------------------------------ |
| `&&`     | Run command only if the first one succeeds |
| `\|\|`   | Run command only if the first one fails    |

**Example:**

```bash
grep "World" hello.txt && echo "Match found" || echo "No match"
```

**Note:**

* `&&` has **higher precedence** than `||`.
* Grouped command `A || (B && C) || (D && E)` is interpreted as `A || (B && C) || (D && E)`
 1. Run `A`
  - If `A` succeeds → stop, entire chain considered successful.
  - If `A` fails → evaluate `(B && C)`.
 2. Evaluate `B && C`
  - Run `B`. If `B` fails → skip `C` and treat `(B && C)` as failed.
  - If `B` succeeds → run `C`.
   - If `C` succeeds → stop, chain considered successful.
   - If `C` fails → `(B && C)` fails → move to `(D && E)`.
 3. Evaluate `D && E`
  - Same logic as above: `D` runs first, if it succeeds → run `E`.
  - Chain ends with success if `E` succeeds, otherwise failure.
