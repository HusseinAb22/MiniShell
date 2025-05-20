# Minishell

A simple Unix‐like command‐line shell implemented in C++17.  
Supports built-in commands, external command execution, background jobs, history, and environment-variable expansion.

---

## Features

- **Interactive prompt**  
  Displays `<shell>` and waits for user input.

- **Built-in commands**
    - `cd <dir>` Change working directory (defaults to `$HOME`).
    - `myjobs` List running background jobs.
    - `myhistory` Show previously entered commands (saved in `history.txt`).
    - `help` Display help message.
    - `exit` Quit the shell.
    - `sleep <sec>` Pause execution for <sec> seconds (external)
    - `who`  Show who is logged in (external)

- **External commands**  
  Searches `$PATH` or accepts absolute/relative paths.  
  Forks and `execv()`s the command.

- **Background execution**  
  Append `&` to any command to run it in the background (e.g. `sleep 5 &`).  
  Background jobs are tracked and cleaned up automatically.

- **Environment-variable expansion**  
  Supports `$VAR` and `${VAR}` syntax (e.g. `echo $HOME`).

- **Command history**  
  All entered commands are appended to `history.txt`, and you can review them with `myhistory`.

---

## Requirements

- **C++17** or later
- **CMake** ≥ 3.10
- A POSIX-compliant environment (Linux, macOS, WSL)

---

## Usage
- **Start the shell**

- ./minishell

- **Try built-ins**

- `<shell>` help
- `<shell>` cd /tmp
- `<shell>` myhistory
- `<shell>` myjobs
- `<shell>` exit

- **Run external commands**

- `<shell>` ls -l /usr/bin
- `<shell>` echo $HOME
- `<shell>` sleep 5 &

- **View and clean up background jobs**

- `<shell>` myjobs

- **Inspect history**

-`<shell>` myhistory

    # shows all past commands from history.txt

---

## Notes & TODO
History is stored in history.txt in the current working directory.

Future enhancements might include:

Tab-completion

I/O redirection (>, <, |)

Command aliases

Signal handling improvements

---
## Building

```bash
git clone https://github.com/HusseinAb22/MiniShell.git
cd minishell
mkdir build && cd build
cmake ..
make
```

---

## License
    MIT License © 2025



