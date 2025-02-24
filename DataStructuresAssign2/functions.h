/*
* FILE		    : functions.h
* PROJECT	    : SENG1070 Assign 2
* PROGRAMMER	: NICHOLAS REILLY, RODRIGO GOMES, BRYAN LEONOR
* FIRST VERSION	: 2025-02-16
* DESCRIPTION	: Task priority queue with a stack to help undo deletions
* REFERENCING   : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc.
*/


#pragma once

//Referecing the custom library made in the project.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//Define the Task struct as per Madhan's specs
typedef struct Task {
    char name[100];
    int PriorityLevel;
    struct Task* next;
} Task;

//Used enumerators as per Madhans request for clearer understanding in switch on case correlation.
typedef enum {
    ADD_TASK = 1,
    COMPLETE_TASK,
    UNDO_TASK,
    VIEW_PENDING,
    VIEW_COMPLETED,
    EXIT_PROGRAM
} MenuOptions;

//Function Prototypes
void AddTask(Task** TaskQueue, char* taskName, int priority); //Nick
void UndoLastTask(Task** CompletedTaskStack, Task** TaskQueue); //Nick
void MainMenu(void); //Nick
void FreeStackAndQueue(Task** TaskQueue, Task** CompletedTaskStack); //Nick
void ViewPendingTasks(Task* TaskQueue);// Rodrigo
void ViewCompletedTasks(Task* CompletedTaskStack); // Rodrigo 
void ProcessTask(Task** TaskQueue, Task** CompletedTaskStack); // Bryan

//Helper Functions for cleaner code
int GetValidIntegerInput(void); //Nick
int GetValidPriority(void); //Nick
void ClearBuffer(void); //Nick
void GetTaskDetails(char* taskName, int nameSize, int* priority); //Nick
void ValidateTaskName(char* taskName, int nameSize); //Nick
Task* CreateTask(const char* taskName, int priority); //Nick
void InsertTaskByPriority(Task** TaskQueue, Task* newTask); //Nick
bool IsQueueEmpty(Task* TaskQueue); //Nick
bool IsStackEmpty(Task* CompletedTaskStack);
