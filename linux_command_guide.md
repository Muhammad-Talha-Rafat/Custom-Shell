# **Linux Command Guide**

---

## **1️⃣ File and Directory Commands**

| Command | Example | Description |
|---------|---------|-------------|
| `ls` | `ls` | List files in current directory (names only) |
| `ls -l` | `ls -l` | List files with details (permissions, owner, size, date) |
| `pwd` | `pwd` | Show current working directory |
| `cd` | `cd /path/to/directory` | Change directory (absolute or relative) |
| `cd ~` | `cd` | Return to home directory |
| `mkdir` | `mkdir folder` | Create a directory |
| `rmdir` | `rmdir folder` | Delete an empty directory |
| `rm` | `rm file.txt` | Delete a file |
| `rm -r` | `rm -r folder` | Delete folder recursively |

**Notes:**
- `cd` will fail if the path doesn’t exist or is a file.
- `mkdir` will fail if directory already exists (unless using `mkdir -p`).
- `rm folder` without `-r` will fail if folder is not empty.

---

## **2️⃣ Copying and Moving Files**

| Command | Example | Description |
|---------|---------|-------------|
| `cp` | `cp file.txt /path/to/dest/` | Copy file to directory |
| `cp` | `cp file.txt newfile.txt` | Copy and rename file |
| `cp -r` | `cp -r folder Backup` | Copy folder recursively |
| `mv` | `mv file.txt /path/to/dest/` | Move file or directory |
| `mv` | `mv file.txt newname.txt` | Rename file or directory |

**Notes:**
- `mv` **removes the source** after moving.
- Copying/moving directories without `-r` will fail.

---

## **3️⃣ Viewing File Content**

| Command | Example | Description |
|---------|---------|-------------|
| `cat` | `cat file.txt` | Print full content of file |
| `head` | `head file.txt` | Print first 10 lines of file |
| `head -n 5 file.txt` | `head -n 5 file.txt` | Print first 5 lines |
| `head -c 10 file.txt` | `head -c 10 file.txt` | Print first 10 bytes |
| `tail` | `tail file.txt` | Print last 10 lines of file |
| `tail -n 5 file.txt` | `tail -n 5 file.txt` | Print last 5 lines |
| `tail -c 10 file.txt` | `tail -c 10 file.txt` | Print last 10 bytes |

**Notes:**
- `head` or `tail` on directories will give an error.
- Binary files (`.exe`) will print gibberish when using `head`/`tail`.

---

## **4️⃣ Creating and Updating Files**

| Command | Example | Description |
|---------|---------|-------------|
| `touch` | `touch file.txt` | Create empty file or update timestamp |
| `echo` | `echo "Hello" > file.txt` | Write text to file (overwrites) |
| `echo` | `echo "Hello" >> file.txt` | Append text to file |

---

## **5️⃣ Miscellaneous Commands**

| Command | Example | Description |
|---------|---------|-------------|
| `date` | `date` | Show current date and time |
| `clear` | `clear` | Clear terminal screen |
| `history` | `history` | Show previously run commands |
| `man` | `man ls` | Show manual/help for command |
| `grep` | `grep "pattern" file.txt` | Search for pattern in file |
| `find` | `find . -name "*.txt"` | Search for files matching pattern |
| `chmod` | `chmod 755 file.sh` | Change file permissions |
| `chown` | `chown user:group file.txt` | Change file owner and group |
| `df` | `df -h` | Show disk usage of filesystems |
| `du` | `du -sh folder` | Show size of folder/files |
| `ps` | `ps aux` | List running processes |
| `top` | `top` | Monitor processes in real time |
| `kill` | `kill PID` | Terminate process by PID |
| `ssh` | `ssh user@host` | Connect to remote host via SSH |
| `scp` | `scp file.txt user@host:/path/` | Copy file to remote host |

---

## **6️⃣ Logical Operators**

| Operator | Description |
|----------|-------------|
| `&&` | AND: run second command only if first succeeds |
| `||` | OR: run second command only if first fails |
| `!` | NOT: invert the exit status of a command (output remains the same) |

**Example:**
```bash
mkdir test && cd test || echo "Failed to create or enter folder"
```

**Note:**
- `&&` has **higher precedence** than `||`.
- Bash evaluates `A && B || C && D || E` as `((A && B) || (C && D)) || E`.

---

✅ **This guide covers:**
- File and directory management
- Viewing and editing files
- Common utilities and processes
- Logical operators for command chaining

