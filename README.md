# Icarus

Icarus is a `REPL` that implements all the standard Relational Algebra Operations in CPP. Relational algebra is a procedural query language, which operates on relations (tables which are modelled using CSV files in this project) using some specified operators, such as `select`, `project`, `cartesian product`, `join`, `division`, `rename` etc. to answer user-defined queries. We use in memory storage to process all the queries, and also allow users to save the results. 

The following relational algebra operations have been implemented:


## Supported REPL Commands

### Non Nestable Commands
These commands are non-nestable in nature, that is they must be executed on the fresh line of the REPL and cannot be merged or used with conjunction with any other commands. 
- `HI`: Asks Icarus to introduce itself. A short sanity check!
- `EXIT`: Exits out of the RELP.
- `LOAD <path_to_csv_file>`: Reads the provided CSV file and stores it as a table, which can be referred to by it's name in the subsequent RELP commands. The CSV files are expected to have headers, and use `,` as their delimeter. The name of the CSV file is used as the relation name by default.
- `SHOW TABLES`: Gives a brief description of the database, with all the loaded tables, and their field and row counts.
- `SHOW <table_name>`: Shows the records from the table that has been input by the user.

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

- Built using the `OOPS` paradigm, which all of the data of a particular class being private by default and then only being exposed by the means of getters, setters and utlity functions.
- `Tables`
  - Utilities to view the table and it's content in the command line itself.
  - When creating new tables, ensures that the names of the tables are distinct.
  - Allows to customize the appearance of the tables being printed in the terminal.

## Try it Out!
Some sample relations have already been populated in the [`data`](./data/) directory, which are then used by the [`main.cpp`](./main.cpp) to solve some queries! Do give it a look!