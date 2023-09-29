# Icarus

Icarus is a `REPL` that implements all the standard Relational Algebra Operations in CPP. Relational algebra is a procedural query language, which operates on relations (tables which are modelled using CSV files in this project) using some specified operators, such as `select`, `project`, `cartesian product`, `join`, `division`, `rename` etc. to answer user-defined queries. We use in memory storage to process all the queries, and also allow users to save the results.

The following relational algebra operations have been implemented:

- [Selection](./DOCUMENTATION.md/#select)
- [Projection](./DOCUMENTATION.md/#project)
- [Rename](./DOCUMENTATION.md/#rename)

These constitue a complete set of relational algebra operations, meaning that all other operations can be realized with the help of the composition of the same. A detailed documentation of the commands you can use in the REPL can be found in the [Documentation](./DOCUMENTATION.md).

## Available Methods for Scripting

These functions are exported on the `Icarus` class, that can be used by the programmer to customize the behaviour of Icarus and interact with the engine programmatically.

- `startREPL`: This is the main method which starts the interactive session with the user.
- `setFieldWidth`: Takes an `int` as argument with is used to set the width of columns outputted in the `SHOW TABLES` command. Defaults to `40`
- `loadCSV`: Used to load a CSV to the database before starting the REPL. Takes in a `const &string` as the argument, denoting the path to the file. Equivalent to calling the `LOAD` command in the REPL. Returns `""` if the parsing resulted in some error, or with the table name that was formed. May require command line iteration.
- `execute`: Takes in a string as input. Executes the same as a raw command that may have been entered in the REPL. Used as a way to programatically work with the Icarus engine from your programs.

## Running the CLI

The project uses `make` to bundle the dependencies and make a working executable.

To make an excutable of the [`main.cpp`](./main.cpp) file, you can use the `make compile` command in the terminal. To directly compile and run the program, you can use `make run` command, which first uses the `compile` command to make the executable and then tries to run it in the shell.

## Features

- Built using the `OOPS` paradigm, which all of the data of a particular class being private by default and then only being exposed by the means of getters, setters and utility functions.
- Use of pointers and referneces to ensure that no unecessary data is copied, ensuring better performance.
- `Tables`
  - Utilities to view the table and it's content in the command line itself.
  - When creating new tables, ensures that the names of the tables and well all the headers in the same are distinct. Even the regularity of the structure of the table is ensured.
  - Allows to customize the appearance of the tables being printed in the terminal.
  - Allows implicit conversion of fields to numeric types in queries so that all the aggregate operations can be performed.
- `Error Handling`
  - All the features of the `REPL` are equipped with error handling to enforce syntax and meaningful updates
  - If any error occurs, a user-friendly stack trace is shown to the user telling him where the error occured and how should he change the syntax
  - Prevent's the crashing of program in any case.

## Try it Out!

Some sample relations have already been populated in the [`data`](./data/) directory, which are then used by the [`main.cpp`](./main.cpp) to solve some queries! Do give it a look!
