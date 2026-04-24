# Simple Shell

## 📌 Description

**Simple Shell** is a minimal Unix command-line interpreter developed as part of the Holberton School program.

It mimics basic behavior of standard shells by reading user input, parsing commands, and executing them using the system environment.

---

## ⚙️ Features

* Execute commands from the system PATH
* Built-in commands:

  * `exit` — exit the shell
  * `env` — print environment variables

---

## 🛠️ Compilation

Compile using `gcc`:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell
```

---

## 🚀 Usage


```bash
./simple_shell
simple_shell$ ls
simple_shell$ env
simple_shell$ exit
```


## 📂 Project Structure

* `main.c` – Entry point of the shell
* `simple_shell.h` – Header file containing function prototypes and shared definitions
* `simple_shell.c` – Command execution
* `parent_child.c` – Built-in commands
* `man_1_simple_shell` – Manual page

*(Adjust this section to match your actual files)*

---

## ⚠️ Limitations

This shell is a simplified implementation and does not support:

* Pipes (`|`)
* Redirection (`>`, `<`)
* Command chaining (`&&`, `||`)
* Wildcards (`*`)
* Advanced shell scripting

---

## 🧪 Examples

```bash
$ ./simple_shell
simple_shell$ ls
simple_shell$ env
```

---

## 🐞 Bugs

If you find any bugs, please report them via the project repository or email: 13071@holbertonstudents.com

---

## 👥 Authors

* Venghour Heng
* Lachlan Luchetti
* Anthony Joy

---

## 📚 References

* `man sh`
* `man execve`
* `man fork`
* `https://en.wikipedia.org/wiki/Unix_shell`
* `https://en.wikipedia.org/wiki/Thompson_shell`
* `https://en.wikipedia.org/wiki/Ken_Thompson`
