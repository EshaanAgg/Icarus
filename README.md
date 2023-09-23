# Icarus

Icarus is a `REPL` that implements all the standard Relational Algebra Operations in CPP.

## Supported commands (in RELP)

- `HI`: Asks Icarus to introduce itself. A short sanity check!
- `EXIT`: Exits out of the RELP.
- `LOAD <path_to_csv_file>`: Reads the provided CSV file and stores it as a table, which can be referred to by it's name in the subsequent RELP commands,

## Running the CLI

The project uses `make` to bundle the dependencies and make a working executable.

To make an excutable of the [`main.cpp`](./main.cpp) file, you can use the `make compile` command in the terminal. To directly compile and run the program, you can use `make run` command, which first uses the `compile` command to make the executable and then tries to run it in the shell.
