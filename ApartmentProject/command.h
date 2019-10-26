#include "apartment.h"
#define N 7

typedef struct listNode {
	char* command;
	struct listNode* next;
}ListNode;

typedef struct list {
	ListNode* head;
	ListNode* tail;
}List;

//This function gets a command from the user and returns it as a string.
char* getCommand();
//Navigation function between all possible commands.
void navigate(char* command, Apartment** aptArr, int* logSize, int* phySize, short int* countApt, int* flag, char** commandArr, List* commandLst, int* countCommand, char* commandsFileName, char* aptsFileName);
//This function returns empty list.
List makeEmptyList();
//This function creates a new list node.
ListNode* createNode(char* data, ListNode* next);
//This function inserts node to the tail of the list.
void insertNodeToTail(List* lst, ListNode* newTail);
//This function checks whether the list is empty.
int isEmptyList(List lst);
//This function frees all the allocations in the given commands list.
void freeComList(List lst);
//This function returns the size of the given list.
int sizeOfList(List* lst);
//This function stores the given command in one of the two repositories.
void storeCommand(char* command, char** arr, List* lst);
//This function prints the given array of commands.
void printCommandArr(char** arr, List* lst);
//This function prints the given list of commands.
void printComList(List* lst);
//This function returs command number <numOfCommand> in the list.
char* findStrInLst(List* lst, int numOfCommand, int sizeOfList);
//This function switches between two sub-strings and returns the new string .
char * dull_replace(char *in, char *pattern, char *by);
//This function frees all the allocations in the given commands array.
void freeComArr(char** arr);
//This function writes the commands from the repositories into the given text file.
void writeCommandsToFile(char* commandsFileName, char** commandArr, List* commandLst);
//This function returns the logical size of the given array.
int getLogSizeOfArr(char** commandArr);
//This function writes the commands from the commands list into the given text file.
void writeCommandsToFileFromList(FILE* f, ListNode* curr);
//This function reades the commands from the given text file into the repositories.
void readCommandsFromFile(char* commandsFileName, char** commandArr, List* commandLst);
//This function gets a command from the text file and returns it as a string.
char* getCommandFromFile(FILE* f);
//realloc.
char* reallocation(char* str, int logicSize);
//This function inserts node to the head of the list.
void insertNodeToHead(List* lst, ListNode* newHead);