## ✅ **`cp`** command

| # | Command Example | Description | Works? | Notes |
|---|------------------|--------------|--------|-------|
| 1 | `cp notes.txt Files` | Copy file into an existing directory | ✅ | `Files` must be an existing folder |
| 2 | `cp notes.txt newfile.txt` | Copy and rename a file | ✅ | Creates `newfile.txt` |
| 3 | `cp notes.txt Files/new_notes.txt` | Copy file into a directory with a new name | ✅ | Directory must exist |
| 4 | `cp notes.txt Files` | Copy file but directory doesn’t exist | ❌ | Error: *No such file or directory* |
| 5 | `cp -r Files Backup` | Copy an entire directory recursively | ✅ | Copies folder and all contents |
| 6 | `cp Files Backup` | Copy directory without `-r` | ❌ | Error: *omitting directory* |
| 7 | `cp file.txt destination` | Source file doesn’t exist in current directory | ❌ | Error: *cannot stat 'file.txt'* |
| 8 | `cp ../file.txt ./` | Copy a file from parent directory into current directory | ✅ | `../file.txt` must exist |
| 9 | `cp file.txt ../` | Copy a file from current directory into parent directory | ✅ | Creates `../file.txt` |
