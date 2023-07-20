# Minishell-42KL


## 1. Abstract

<p align="center">
  <img
       width="800"
       src="https://github.com/Wongoose/minishell-42KL/assets/99158692/687ddf0f-da28-4490-923e-96bb8234b3fe"
  >
</p>

The project "Minishell" presents a replica of a bash environment, implementing numerous features to provide a functional and user-friendly shell experience.
The Minishell project encompasses various functionalities, including prompt display, history management, executable search and launch, and handling of special
characters and quoting rules. The project further incorporates redirections, pipes for command chaining, and environment variable expansion. Additionally,
it handles essential keyboard interrupts, such as ctrl-C, ctrl-D, and ctrl-, mirroring their behavior in the bash shell. Lastly, Minishell introduces support
for logical operators (&& and ||) with parenthesis for command priorities and enables the usage of wildcards (\*) in the current working directory.
This project effectively replicates a bash-like environment, providing users with a powerful and feature-rich shell for their command-line interactions.

## 2. Setup

#### 1. Do ensure that readline is installed:
1.1 On Linux
```
    sudo apt install libreadline-dev
```
1.2 On Mac
```
    brew install readline
```
1.3 On Windows
```
    // For Cygwin, run the Cygwin installer and select the libreadline-devel package during the installation process.
    // For MinGW, use the package manager mingw-get
           mingw-get install msys-readline
```

#### 2. Git clone and run make in project root directory

```
    make
```

#### 3. Run the executable in project root directory

```
    ./minishell
```
