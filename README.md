# Data Clinic - Healthcare System [Academic Project]

This is a simple academic project developed in C++ for managing patient records in a healthcare system. It is a terminal-based application focused on data structures and pointer manipulation, built as part of a university assignment.

## Features

- Patient record management
  - Create, update, remove, and list patient records
  - Each patient has an ID, name, and diagnosis
- Data stored in memory (no database)
- Utilizes data structures such as doubly linked lists

## Project Structure

```
src/
├── controller/
│   └── module-folder/
├── model/
│   └── module-folder/
├── view/
│   └── module-folder/
├── main.cpp
build/
Makefile
```

## Compilation and Execution

To **compile** the project, run the following command from the root of the project:

```bash
make
```

To **clean** the build and compile from scratch, use:

```bash
make clean && make
```

To **run** the application, execute the following command:

```bash
./build/app
```

## Dependencies

- **g++**: GNU Compiler Collection (g++) for compiling C++ code.
- **Make**: Build automation tool for managing the project compilation process.

## Academic Context

This project is part of an academic assignment focused on data structures and pointer manipulation. The main goal is to practice and apply these concepts in the development of a terminal-based application.

## License

This project was made for academic purposes only. Feel free to modify or extend it.