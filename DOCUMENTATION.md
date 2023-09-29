# Documentation

This guide gives a brief overview of all the supported commands in the `REPL`. It must be noted that all the commands as well names `ARE` case-sensitive in nature. All the reserved keywords would be in `UPPERCASE`.

## Non Nestable Commands

These commands are non-nestable in nature, that is they must be executed on the fresh line of the REPL and cannot be merged or used with conjunction with any other commands.

- `HI`: Asks Icarus to introduce itself. A short sanity check!
- `EXIT`: Exits out of the REPL.
- `LOAD <path_to_csv_file>`: Reads the provided CSV file and stores it as a table, which can be referred to by it's name in the subsequent REPL commands. The CSV files are expected to have headers, and use `,` as their delimeter. The name of the CSV file is used as the relation name by default.
- `SHOW TABLES`: Gives a brief description of the database, with all the loaded tables, and their field and row counts.
- `SHOW <table_name>`: Shows the records from the table that has been input by the user.

## Nestable Commands

These are the basic operators of Relation Algebra which can be nested to create complex queries. Some notes that must be kept in mind while using the same:

- All the operations are CASE-SENSITIVE, for the names and commands both.
- The REPL has an inbuilt memory, so all the data that can be populated before the execution of the said command will be remembered.
- Table names can also have lowercase alphabets as uppercase strings are reserved for keywords.
- The commands are whitespace agnostic.

Here is a detailed documentation related to the syntax of the same:

---

### Select

#### Syntax

`Select(table, filterQuery)`

#### Use

- Displays all the rows from `table` which pass the filter specified by `filterQuery`.
- The `table` field can be either a name of the table in the database, or another relational operator which returns a table.
- `filterQuery Specifications`:
  - Can contain field names like `fieldName` or dereferenced parent names like `TableName.FieldName`
  - Can consist of comparision operators like `=`, `!=`, `>`, `<`, `>=` and `<=`
  - Can have logical operators `&&` and `||`
  - Can contain string data enclosed in `""` or `''` and numeric data without enclosing in quotes.
  - Can contain nested conditionals with help of `()`.

#### Sample

`SELECT(students, RollNo >= 14123006 && Department = 'CSE')`

---

### Project

#### Syntax

`PROJECT(table, fieldName1, fieldName2, ...)`

#### Use

- Displays all the specificied fields from `table`.
- The `table` field can be either a name of the table in the database, or another relational operator which returns a table.

#### Sample

`PROJECT(courses, CourseID)`

---

### Rename

#### Syntax

`REANME(oldTableName, newTableName)`

#### Use

- Renames an already existing table identified by `oldTableName` to `newTableName` for convinience.
- `oldTableName` also accepts an already existing table in the memory.

#### Sample

`RENAME(students, stud)`
