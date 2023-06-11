# Todo App

## A simple todo application to manage your tasks.

### Features
- Add new tasks
- Mark tasks as completed
- Edit task titles
- Add notes to tasks
- View task details

### Build the project from source

#### Clone the repository 
```
git clone https://github.com/ebrahim100/command_line_todo_list.git
```
#### Change into the project directory:
```
cd command_line_todo_list
```
#### Create ./build directory and change into the directory
```
mkdir build
cd build
```
#### Configure it with cmake command
```
cmake ../
```

#### Build the app with make command
```
make
```

#### Run app with command line options
```
./todo --help

A simple CLI based todo app 
Usage: ./todo [OPTIONS] [SUBCOMMAND]

Options:
  -h,--help                   Print this help message and exit

Subcommands:
  add                         Add new task
  edit                        Set title of a task
  note                        Add a note to a task
  status                      Set status of a task
  notes                       Get notes of a task
  list                        List tasks
```

## License
This project is licensed under the MIT License.
