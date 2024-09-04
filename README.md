# TerminalToDo App

A simple command-line To-Do list application written in C, allowing you to manage tasks directly from the terminal.

## Features

- **Add Task**: Add a new task to your list.
- **List Tasks**: Display all tasks with their completion status.
- **Complete Task**: Mark a specific task as completed.
- **Delete Task**: Remove a specific task from your list.
- **Help**: Lists all the commands.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc`)
- A terminal or command prompt

### Installation

1. **Clone the Repository**:
    ```sh
    git clone https://github.com/Sathvik79/TerminalToDo.git
    cd TerminalToDo
    ```

2. **Compile the Program**:
    ```sh
    gcc app.c -o app 
    ```

3. **Run the Application**:
    ```sh
    ./app <command> [arguments]
    ```

## Usage

### Commands

- **Add a Task**:
    ```sh
    ./app add "Your task description"
    ```

- **List All Tasks**:
    ```sh
    ./app list
    ```

- **Mark a Task as Completed**:
    ```sh
    ./app complete <task_id>
    ```

- **Delete a Task**:
    ```sh
    ./app delete <task_id>
    ```

- **Show Help**:
    ```sh
    ./app help
    ```

### Example Workflow

1. Add tasks:
    ```sh
    ./app add "Clone TerminalToDo"
    ./app add "Commit fantastic features"
    ```

2. List tasks:
    ```sh
    ./app list
    ```

3. Mark a task as completed:
    ```sh
    ./app complete 1
    ```

4. Delete a task:
    ```sh
    ./app delete 2
    ```

## Project Structure

- **`app.c`**: The main source code file containing all the functionality of the To-Do app.
- **`tasks.txt`**: The file where tasks are saved. This file is automatically created in the same directory when you run the program.

## Contributing

Feel free to fork this project, submit issues, or contribute by making pull requests. Any contributions, big or small, are welcome!
