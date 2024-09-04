#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TASK_DESC_LENGTH 256
#define FILE_NAME "tasks.txt"

typedef struct
{
    int id;
    char description[TASK_DESC_LENGTH];
    int completed;
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;

// Function to load tasks from the file
void load_tasks()
{
    FILE *file = fopen(FILE_NAME, "r");

    // If the file doesn't exist or can't be opened, return early
    if (file == NULL)
        return;

    // Reads task data from the file and stores it in the tasks array
    while (fscanf(file, "%d %[^\n] %d", &tasks[task_count].id, tasks[task_count].description,
                  &tasks[task_count].completed) != EOF)
    {
        task_count++;
    }

    fclose(file);
}

// Function to show the available commands
void show_help()
{
    printf("To-Do App Commands:\n");
    printf("    add <task description>  - Add a new task\n");
    printf("    list                    - List all tasks\n");
    printf("    complete <task ID>      - Mark a task as completed\n");
    printf("    delete <task ID>        - Remove a task from the list\n");
    printf("    help                    - List the commands\n");
}

// Function to save the current tasks to the file
void save_task()
{
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("Failed to save task.\n");
        return;
    }

    // Writes each task's data to the file
    for (int i = 0; i < task_count; i++)
    {
        fprintf(file, "%d %s %d\n", tasks[i].id, tasks[i].description, tasks[i].completed);
    }

    fclose(file);
}

// Function to add a new task
void add_task(const char *description)
{
    if (task_count >= MAX_TASKS)
    {
        printf("Task list is full.\n");
        return;
    }

    // Assign a new ID to the task
    tasks[task_count].id = task_count + 1;

    // Copy the description while ensuring no overflow
    strncpy(tasks[task_count].description, description, TASK_DESC_LENGTH - 1);
    tasks[task_count].description[TASK_DESC_LENGTH - 1] = '\0'; // Null-terminate the string

    // Set the task as not completed
    tasks[task_count].completed = 0;

    // Increment the task count
    task_count++;

    // Save the updated tasks to the file
    save_task();
    printf("Task added.\n");
}

// Function to list all tasks
void list_task()
{
    for (int i = 0; i < task_count; i++)
    {
        printf("%d. [%s] %s\n", tasks[i].id, tasks[i].completed ? "X" : " ", tasks[i].description);
    }
}

// Function to mark a task as completed
void complete_task(int task_id)
{
    for (int i = 0; i < task_count; i++)
    {
        if (tasks[i].id == task_id)
        {
            tasks[i].completed = 1;
            save_task();
            printf("Task %d marked as completed.\n", task_id);
            return;
        }
    }
    printf("Task ID %d not found.\n", task_id);
}

// Function to delete a task by ID
void delete_task(int task_id)
{
    int found = 0;

    // Iterate through the tasks to find the one with the given ID
    for (int i = 0; i < task_count; i++)
    {
        if (tasks[i].id == task_id)
        {
            found = 1;
        }

        // Shift remaining tasks up to fill the gap
        if (found && i < task_count - 1)
        {
            tasks[i] = tasks[i + 1];
        }
    }

    // If the task was found and removed, decrement the task count
    if (found)
    {
        task_count--;
        save_task();
        printf("Task %d removed.\n", task_id);
    }
    else
    {
        printf("Task ID %d not found.\n", task_id);
    }
}

// Main function to handle user input and execute commands
int main(int argc, char *argv[])
{
    load_tasks();

    // Show help if no arguments are provided
    if (argc < 2)
    {
        show_help();
        return 1;
    }

    // Handle the "add" command
    if (strcmp(argv[1], "add") == 0 && argc > 2)
    {
        char description[TASK_DESC_LENGTH];

        // Join all the arguments after the command into one string for the description
        // snprintf is used to format a string and store the result in a buffer.
        // int snprintf(char *str, size_t size, const char *format, arguments);
        snprintf(description, TASK_DESC_LENGTH, "%s", argv[2]);
        for (int i = 3; i < argc; i++)
        {
            // strncat is a function used to concatenate (append) one string to another.
            // char *strncat(char *dest, const char *src, size_t n);
            // n: The maximum number of characters to append from src
            strncat(description, " ", TASK_DESC_LENGTH - strlen(description) - 1);
            strncat(description, argv[i], TASK_DESC_LENGTH - strlen(description) - 1);
        }

        // Pass the full description to add_task
        add_task(description);
    }
    // Handle the "list" command
    else if (strcmp(argv[1], "list") == 0)
    {
        list_task();
    }
    // Handle the "complete" command
    else if (strcmp(argv[1], "complete") == 0 && argc > 2)
    {
        complete_task(atoi(argv[2]));
    }
    // Handle the "delete" command
    else if (strcmp(argv[1], "delete") == 0 && argc > 2)
    {
        delete_task(atoi(argv[2]));
    }
    // Handle the "help" command
    else if (strcmp(argv[1], "help") == 0)
    {
        show_help();
    }

    /*
    TODO:
    * Enable Editing: Implement a feature to edit an existing task's description.
    * Time Stamping: Automatically record the creation time of each task.
    * Deadlines: Enable users to set due dates for tasks, helping with prioritization and time management.
    * Visual Indicator (e.g., color-coding) to highlight tasks with deadlines that are approaching or overdue.
    */

    else
    {
        printf("Invalid Command. Type 'help' to list the commands.\n");
    }

    return 0;
}
