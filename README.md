# 🐚 Minishell 

<div align=center>

*A simple bash re-creation*
![Minishell Demo](https://i.imgur.com/YvASFOO.gif)
[![42 School](https://img.shields.io/badge/School-000000?style=flat-square&logo=42&logoColor=white)](https://42.fr/)
[![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))

</div>

# 📑 About
**Minishell** is a 42 project about re-creating a simpler version of bash.  
The project guidelines ask that the shell be able to run **commands**, handle **unix signals**, **redirecting** and **piping**, as well as a few **built in commands**.  
Despite the simple sounding premise, this is a project that requires a great amount of research, planning and understanding of what you're recreating. Making this project *infamous* as one of the first biggest roadblocks for 42 students in the core program.

# 🛠️ Features
* ⚙️**Command execution** - using absolute and relative paths, as well as the PATH environement variable, the shell can execute other processes
* 📡**Signal handling** - signals should not crash the shell, and be passed onto child processes
* **Piping & redirection** - redirecting the input and outputs of processes to and from files using redirects (< >), or piping outputs to inputs of other processes
* 🔧**Built in commands** - echo, cd, export, unset and exit are commands built into the shell, as they let you modify its state, which child processes cannot, and should not do.
* ❎**Environement Variables** - The shell keeps track of the given environement variables and passes them on to child processes.

# 🎓 Skills Developed

* 👥 **Collaboration** - This is the first group project in 42, which allowed us to learn how to work together and divide the workloads effectively between team members.

* 🔧 **Git & Version Control** - Collaboration brought on the need to understand git better beyond just pushing and pulling, including branching, merging, conflict resolution, and coordinating code changes across multiple developers.

* ⚙️ **Process Management** - Gained deep understanding of Unix processes, including fork(), exec(), wait(), and managing parent-child process relationships for command execution.

* 🔌 **File Descriptors & I/O Redirection** - Learned to manipulate file descriptors for implementing input/output redirection (`>`, `>>`, `<`), pipes (`|`), and managing stdin, stdout, and stderr streams.

* 🧠 **Memory Management** - Developed skills in dynamic memory allocation, preventing memory leaks, and proper resource cleanup in a complex C program.

* 📝 **Parsing & Lexical Analysis** - Implemented tokenization and parsing of command-line input, handling quotes, special characters, and command syntax validation.

* 🌐 **Environment Variables** - Understanding and manipulation of environment variables, implementing variable expansion (`$VAR`) and managing the shell's environment.

* 🏗️ **System Programming** - Deepened knowledge of system calls, signal handling, and low-level Unix/Linux programming concepts.

* 🔍 **Built-in Commands** - Implemented shell built-ins (`cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`) and understood the difference between built-ins and external commands.

* 🐛 **Debugging & Testing** - Enhanced debugging skills for complex programs with multiple processes, and learned to create comprehensive test suites for shell functionality.

* 📐 **Software Architecture** - Structured a complex program into modular components (lexer, parser, executor) and learned about separation of concerns in software design.

* 🔄 **Inter-Process Communication** - Implemented pipes for communication between processes and coordinated multiple concurrent processes.

* 📚 **Shell Scripting Understanding** - Gained practical insight into how shells work internally, improving overall command-line proficiency and bash scripting skills.

# 🚀 Getting Started
### Dependencies
- **GCC** compiler
- **Make** 

### Installation
*Clone The repo and make the project*
``` bash
git clone https://github.com/eth1711/minishell
cd ./minishell
make
```
### Usage
Then run the shell and use it like you would a normal shell!
``` bash
./minishell
```

## 📄 License

This project is part of the 42 School curriculum and follows the school's academic guidelines.

## 🤝 Contributing

As this is an academic project, direct contributions are not accepted. However, feel free to:
- Report bugs or issues
- Suggest improvements
- Use this as reference for your own learning
