/*
* FILE		    : DataStructuresAssign2.cpp
* PROJECT	    : SENG1070 Assign 2
* PROGRAMMER	: NICHOLAS REILLY, RODRIGO GOMES, BRYAN LEONOR
* FIRST VERSION	: 2025-02-16
* DESCRIPTION	: Task priority queue with a stack to help undo deletions
* REFERENCING   : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc.
*/

//Reference the libraries used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define the Task struct as per Madhan's specs
typedef struct Task {
    char name[100];
    int PriorityLevel;
    struct Task* next;
} Task;

//Function Prototypes
//Main functions

void AddTask(Task** TaskQueue, char* taskName, int priority); //Nick
void UndoLastTask(Task** CompletedTaskStack, Task** TaskQueue); //Nick
void MainMenu(void); //Nick
void FreeStackAndQueue(Task** TaskQueue, Task** CompletedTaskStack); //Nick

//Helper Functions for cleaner code
int GetValidIntegerInput(void); //Nick
int GetValidPriority(void); //Nick
void ClearBuffer(void); //Nick
void GetTaskDetails(char* taskName, int nameSize, int* priority); //Nick
void ValidateTaskName(char* taskName, int nameSize); //Nick
Task* CreateTask(const char* taskName, int priority); //Nick
void InsertTaskByPriority(Task** TaskQueue, Task* newTask); //Nick





int main(void) {
    MainMenu();
    return 0;
}


void MainMenu(void) {

    //Initlaize the TaskQueue and the CompletedTaskStack
    Task* TaskQueue = NULL;
    Task* CompletedTaskStack = NULL;

    //Used enumerators as per Madhans request for clearer understanding in switch on case correlation.
    enum MenuOptions { ADD_TASK = 1, COMPLETE_TASK = 2, UNDO_TASK = 3,VIEW_PENDING = 4,VIEW_COMPLETED = 5, EXIT_PROGRAM = 6 };

    //Defining local variables
    int choice;
    char taskName[100];
    int priority;

    do {

        //Bryan, remove this. And make it its own function. Then repalce this with the call. 
        //I needed it so I can see what I am doing lol
        printf("\nTask Scheduler Menu:\n");
        printf("1. Add Task\n");
        printf("2. Complete Task\n");
        printf("3. Undo Last Completed Task\n");
        printf("4. View Pending Tasks\n");
        printf("5. View Completed Tasks\n");
        printf("6. Exit the program\n");
        printf("Enter your choice: ");

        choice = GetValidIntegerInput();
        switch (choice) {
        case ADD_TASK:
            GetTaskDetails(taskName, sizeof(taskName), &priority);
            AddTask(&TaskQueue, taskName, priority);
            break;
        case COMPLETE_TASK:
            UndoLastTask(&CompletedTaskStack, &TaskQueue);
            break;
        case UNDO_TASK:
            UndoLastTask(&CompletedTaskStack, &TaskQueue);
        case VIEW_PENDING:
            
            break;
        case VIEW_COMPLETED:

            break;
        case EXIT_PROGRAM:
            FreeStackAndQueue(&TaskQueue, &CompletedTaskStack);
            printf("Exiting program. Memory freed.\n");
            break;

        default:
            printf("Invalid choice! Try again.\n");
            break;
        }
    } while (choice != EXIT_PROGRAM);
}

//
// FUNCTION   : GetValidIntegerInput     
// DESCRIPTION: Makes sure that the input read from keyboard is a single int only between 1-6 inclusive  
//                    
// PARAMETERS : none     
// RETURNS    : value, which is the number isolated and meets the range of 1-6 inclusive.     
//
int GetValidIntegerInput(void) {
    
    //Declare the local variables
    int value;
    char buffer[100];

    while (1) {

        //Read the input from the user, make sure it is within bounds. 
        if (fgets(buffer, sizeof(buffer), stdin)) {

            //Use sscanf_s to parse the integer out of the input
            if (sscanf_s(buffer, "%d", &value) == 1) {

                //After parsing, initalize the pointer be equal to the buffer to get data.
                char* extra_char = buffer;

                //Skip over the number if it is more, increament the extra counter
                while (*extra_char >= '0' && *extra_char <= '9') {
                    extra_char++;
                }

                //Check to see if after skipping the number, there are actual characters at the end.
                while (*extra_char != '\0') {
                    if (*extra_char != ' ' && *extra_char != '\n') {
                        break;
                    }
                    extra_char++;
                }

                //Check to confirm that the number entered ends with null\newline
                if (*extra_char == '\0' || *extra_char == '\n') {
                    return value; // Valid input
                }
            }
        }
        printf("Invalid input! Please enter a valid number:\n");
    }
}

//
// FUNCTION   : CreateTask     
// DESCRIPTION: Creates a task. Dynamically allocates memory and adds in already validated input paramters  
//                    
// PARAMETERS : pointer to the taskName variable, and the int for priority number     
// RETURNS    : newTask, a new Task node. 
//
Task* CreateTask(const char* taskName, int priority) {

    //Dynamically allocate the memory required for a task
    Task* newTask = (Task*)malloc(sizeof(Task));

    //If no more exists, throw an error
    if (!newTask) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    //Copy all of the contents and update the nodes attributes. Return it.
    strcpy_s(newTask->name, sizeof(newTask->name), taskName);
    newTask->PriorityLevel = priority;
    newTask->next = NULL;
    return newTask;
}

//
// FUNCTION   : InsertTaskByPriority
// DESCRIPTION: Determines where to put the new task made by user depending on priority
//                    
// PARAMETERS : Task** TaskQueue, and Task* newtask. Pointer to the queue to find the tasks, and the new task to insert.
// RETURNS    : none.
//
void InsertTaskByPriority(Task** TaskQueue, Task* newTask) {
    //Check to see if the queue is empty or if the highest priorty task is less than the newTasks priority
    if (*TaskQueue == NULL || (*TaskQueue)->PriorityLevel < newTask->PriorityLevel) {
        //Makes the newTasks next attribute point to the one it succeeded
        newTask->next = *TaskQueue;
        //Make the queues highest level task the new task. 
        *TaskQueue = newTask;
    }
    else {
        //Start from the first task
        Task* current = *TaskQueue;
        //Traverse while the next task is not NULL and the next tasks priority is greater than newTasks priority
        while (current->next != NULL && current->next->PriorityLevel >= newTask->PriorityLevel) {
            current = current->next;
        }

        //Update the attributes
        newTask->next = current->next;
        current->next = newTask;
    }
}

//
// FUNCTION   : 
// DESCRIPTION:
//                    
// PARAMETERS :
// RETURNS    :
//
// Function to get a valid priority (1-5)
int GetValidPriority(void) {
    int priority;
    while (1) {
        priority = GetValidIntegerInput();
        if (priority >= 1 && priority <= 5) {
            return priority;
        }
        printf("Invalid priority!\n");
        printf("Enter a number between 1 and 5:\n");
    }
}


//
// FUNCTION   : AddTask
// DESCRIPTION: Takes in parameters made by helper functions and creates the task, inserts in queue
//                    
// PARAMETERS : Task** TaskQueue, pointer to where the TaskQueue is, pointer to a TaskName, prioirty number.
// RETURNS    :
//
void AddTask(Task** TaskQueue, char* taskName, int priority) {
    
    //Create the newTask.
    Task* newTask = CreateTask(taskName, priority);

    //If it fails, no memory. Break from function.
    if (!newTask) {
        return;
    }

    //Call the InsertTaskByPrioirty to find insertion point and insert accordingly.
    InsertTaskByPriority(TaskQueue, newTask);
    printf("Task '%s' with priority %d added successfully.\n", taskName, priority);
}
//
// FUNCTION   : UndoLastTask
// DESCRIPTION: Undos the last completed task and return it to the queue
//                    
// PARAMETERS : Task** TaskQueue and CompletedTestStack, the locations of the stack and queue.
//
void UndoLastTask(Task** CompletedTaskStack, Task** TaskQueue) {

    //Check if empty. Throw error if so.
    if (*CompletedTaskStack == NULL) {
        printf("No completed tasks to undo!\n");
        return;
    }

    //Remove the last completed task from the stack
    Task* lastCompletedTask = *CompletedTaskStack;
    *CompletedTaskStack = (*CompletedTaskStack)->next;

    //Reinsert it into the task queue
    lastCompletedTask->next = *TaskQueue;
    *TaskQueue = lastCompletedTask;

    printf("Task '%s' has been undone and moved back to the pending task queue.\n", lastCompletedTask->name);
}


//
// FUNCTION   : FreeStackAndQueue
// DESCRIPTION: Frees the memory used for nodes from stack and queue.
//                    
// PARAMETERS : Task** TaskQueue and CompleteTaskStack, the locations for the queue and stack.
// RETURNS    : none.
//
// Function to free memory from both queue and stack
void FreeStackAndQueue(Task** TaskQueue, Task** CompletedTaskStack) {

    //Initialize the task buffer.
    Task* temp;

    //While the task queue has an entry, assign buffer info, update next atttribute free.
    while (*TaskQueue) {
        temp = *TaskQueue;
        *TaskQueue = (*TaskQueue)->next;
        free(temp);
    }

    //Same process for the stack
    while (*CompletedTaskStack) {
        temp = *CompletedTaskStack;
        *CompletedTaskStack = (*CompletedTaskStack)->next;
        free(temp);
    }
}

//
// FUNCTION   : GetTaskDetails
// DESCRIPTION: Helper function used to get the task entry name
//                    
// PARAMETERS : pointer to taskName buffer, nameSize int, pointer to the value at priority
// RETURNS    : none
//
void GetTaskDetails(char* taskName, int nameSize, int* priority) {
    printf("Enter task name: ");
    fgets(taskName, nameSize, stdin);
    taskName[strcspn(taskName, "\n")] = 0;

    //Call the helper function to validate task name
    ValidateTaskName(taskName, nameSize);

    printf("Enter priority (1-5): ");

    //Use existing validation function to validate priority is within range
    *priority = GetValidPriority();  
}

//
// FUNCTION   : ValidateTaskName
// DESCRIPTION: Confirms that the user actually entered in something that is correct based on size value
//                    
// PARAMETERS : pointer to the taskName buffer, size in int of nameSize
// RETURNS    : none
//
// Helper function to validate task name
void ValidateTaskName(char* taskName, int nameSize) {
    while (strlen(taskName) == 0) {
        printf("Invalid task name! Please enter a valid task name.\n");
        printf("Enter task name: ");
        fgets(taskName, nameSize, stdin);
        taskName[strcspn(taskName, "\n")] = 0;
    }
}

//
// FUNCTION   : ClearBuffer
// DESCRIPTION: Clears buffer, consumes trailing characters
//                    
// PARAMETERS : none
// RETURNS    : none
//
void ClearBuffer(void) {
    while (getchar() != '\n');  // This will discard characters until a newline is found
}

