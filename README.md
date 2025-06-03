# UNIX SHELL IN C LANGUAGE

## Created by:

[Wasee Sun](https://github.com/waseesun) & [Sahil Iftekhar](https://github.com/sahil-iftekhar)


## 🔧 Basic Features of the UNIX Shell

This shell project implements several core features found in typical Unix-like terminal environments. Below is an overview of its primary functionalities:

### 1. 🧠 Command Execution
- Implemented in: `execute_cmd.c`, `execute_cmd.h`
- Parses and executes user-entered commands using system calls such as `fork()` and `exec()`.
- Supports running external programs in a child process.

### 2. 📜 Command History
- Implemented in: `history.c`, `history.h`
- Maintains a history of previously executed commands.
- Allows users to recall and re-execute past commands to improve productivity.

### 3. 🎛️ Input Handling
- Implemented in: `input.c`, `input.h`
- Reads user input and handles parsing, including tokenization and validation.
- Prepares commands for further processing (e.g., sequencing, redirection).

### 4. 🚨 Signal Handling
- Implemented in: `c_signal.c`, `c_signal.h`
- Handles Unix signals such as `SIGINT` and `SIGTSTP`.
- Ensures clean interruption or suspension of running processes.

### 5. 🔗 Command Sequencing and Separation
- Implemented in: `sequence_cmd.c`, `seperate_cmd.c`, `multiple_cmd.c`
- Supports executing multiple commands in a sequence using operators:
  - `;` (sequential execution)
  - `&&` (execute next only if previous succeeded)
  - `||` (execute next only if previous failed)

### 6. 📦 Pipelining
- Implemented in: `pipeline_cmd.c`, `pipeline_cmd.h`
- Enables command pipelining using the pipe `|` operator.
- Redirects the output of one command to be used as the input of the next (e.g., `ls | grep txt`).

### 7. 📁 Input/Output Redirection
- Implemented in: `redirect.c`, `redirect.h`
- Supports input and output redirection using `<`, `>`, and `>>`.
- Facilitates reading from files or writing command output to files.

---

These features collectively make this shell a robust, lightweight implementation suitable for exploring the inner workings of Unix-like command-line interpreters.
