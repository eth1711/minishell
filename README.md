# 🐚 Minishell 

<div align=center>

*A simple bash re-creation*  
![Minishell Demo](https://i.imgur.com/YvASFOO.gif)

[![42 School](https://img.shields.io/badge/School-000000?style=flat-square&logo=42&logoColor=white)](https://42.fr/)
[![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![made-with-bash](https://img.shields.io/badge/-Bash-1f425f.svg?style=flat-square&logo=image%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyZpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw%2FeHBhY2tldCBiZWdpbj0i77u%2FIiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8%2BIDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuNi1jMTExIDc5LjE1ODMyNSwgMjAxNS8wOS8xMC0wMToxMDoyMCAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENDIDIwMTUgKFdpbmRvd3MpIiB4bXBNTTpJbnN0YW5jZUlEPSJ4bXAuaWlkOkE3MDg2QTAyQUZCMzExRTVBMkQxRDMzMkJDMUQ4RDk3IiB4bXBNTTpEb2N1bWVudElEPSJ4bXAuZGlkOkE3MDg2QTAzQUZCMzExRTVBMkQxRDMzMkJDMUQ4RDk3Ij4gPHhtcE1NOkRlcml2ZWRGcm9tIHN0UmVmOmluc3RhbmNlSUQ9InhtcC5paWQ6QTcwODZBMDBBRkIzMTFFNUEyRDFEMzMyQkMxRDhEOTciIHN0UmVmOmRvY3VtZW50SUQ9InhtcC5kaWQ6QTcwODZBMDFBRkIzMTFFNUEyRDFEMzMyQkMxRDhEOTciLz4gPC9yZGY6RGVzY3JpcHRpb24%2BIDwvcmRmOlJERj4gPC94OnhtcG1ldGE%2BIDw%2FeHBhY2tldCBlbmQ9InIiPz6lm45hAAADkklEQVR42qyVa0yTVxzGn7d9Wy03MS2ii8s%2BeokYNQSVhCzOjXZOFNF4jx%2BMRmPUMEUEqVG36jo2thizLSQSMd4N8ZoQ8RKjJtooaCpK6ZoCtRXKpRempbTv5ey83bhkAUphz8fznvP8znn%2B%2F3NeEEJgNBoRRSmz0ub%2FfuxEacBg%2FDmYtiCjgo5NG2mBXq%2BH5I1ogMRk9Zbd%2BQU2e1ML6VPLOyf5tvBQ8yT1lG10imxsABm7SLs898GTpyYynEzP60hO3trHDKvMigUwdeaceacqzp7nOI4n0SSIIjl36ao4Z356OV07fSQAk6xJ3XGg%2BLCr1d1OYlVHp4eUHPnerU79ZA%2F1kuv1JQMAg%2BE4O2P23EumF3VkvHprsZKMzKwbRUXFEyTvSIEmTVbrysp%2BWr8wfQHGK6WChVa3bKUmdWou%2BjpArdGkzZ41c1zG%2Fu5uGH4swzd561F%2BuhIT4%2BLnSuPsv9%2BJKIpjNr9dXYOyk7%2FBZrcjIT4eCnoKgedJP4BEqhG77E3NKP31FO7cfQA5K0dSYuLgz2TwCWJSOBzG6crzKK%2BohNfni%2Bx6OMUMMNe%2Fgf7ocbw0v0acKg6J8Ql0q%2BT%2FAXR5PNi5dz9c71upuQqCKFAD%2BYhrZLEAmpodaHO3Qy6TI3NhBpbrshGtOWKOSMYwYGQM8nJzoFJNxP2HjyIQho4PewK6hBktoDcUwtIln4PjOWzflQ%2Be5yl0yCCYgYikTclGlxadio%2BBQCSiW1UXoVGrKYwH4RgMrjU1HAB4vR6LzWYfFUCKxfS8Ftk5qxHoCUQAUkRJaSEokkV6Y%2F%2BJUOC4hn6A39NVXVBYeNP8piH6HeA4fPbpdBQV5KOx0QaL1YppX3Jgk0TwH2Vg6S3u%2BdB91%2B%2FpuNYPYFl5uP5V7ZqvsrX7jxqMXR6ff3gCQSTzFI0a1TX3wIs8ul%2Bq4HuWAAiM39vhOuR1O1fQ2gT%2F26Z8Z5vrl2OHi9OXZn995nLV9aFfS6UC9JeJPfuK0NBohWpCHMSAAsFe74WWP%2BvT25wtP9Bpob6uGqqyDnOtaeumjRu%2ByFu36VntK%2FPA5umTJeUtPWZSU9BCgud661odVp3DZtkc7AnYR33RRC708PrVi1larW7XwZIjLnd7R6SgSqWSNjU1B3F72pz5TZbXmX5vV81Yb7Lg7XT%2FUXriu8XLVqw6c6XqWnBKiiYU%2BMt3wWF7u7i91XlSEITwSAZ%2FCzAAHsJVbwXYFFEAAAAASUVORK5CYII%3D)](https://en.wikipedia.org/wiki/Bash_(Unix_shell))

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
