#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct date {
	int day;
	int month;
	int year;
}Date;

typedef struct apartment {
	short int code;
	char* address;
	short int numOfRooms;
	int price;
	Date entryDate;
	Date dataBaseEntryDate;
}Apartment;

//This function adds an apartment to the apartment pool.
void addAnApart(short int code, char* str, Apartment** arr, int* logSize, int* phySize);
//This function receives a code of purchased apartment and deletes it from the pool of apartments.
void buyAnApart(Apartment** arr, int code, int* logSize, int* phySize);
//This function prints the codes of the apartments that have entered the database in the last <numOfDays> days.
void getAnApartEnter(Apartment* arr, int numOfDays, int logSize);
//This function deletes the apartments that have entered the database in the last <numOfDays> days.
void deleteAnApartEnter(Apartment** arr, int numOfDays, int* logSize, int* phySize);
//Shell function to "maximumPrice", "minimumNumRooms", "maximumNumRooms", "freeUpToDate"
void getAnApart(Apartment* arr, int size, char* str);
//This function deletes the apartments that cost more than <maxPrice> from the array. 
void maximumPrice(Apartment** copyArr, int* size, int maxPrice);
//This function deletes the apartments that have less than <minRooms> from the array. 
void minimumNumRooms(Apartment** copyArr, int* size, int minRooms);
//This function deletes the apartments that have more than <maxRooms> from the array. 
void maximumNumRooms(Apartment** copyArr, int* size, int maxRooms);
//This function deletes the apartments that are not vacated until the given date from the array.
void freeUpToDate(Apartment** copyArr, int* size, char* date);
//This function copies the given array and returns the copy array.
Apartment* copyArr(Apartment* arr, int size);
//This function deletes an apartment from the given array and frees the apartment's address.
void deleteFromArray(Apartment* arr, int index, int logSize);
//This function receives a pointer to the current day and updates it to the day that was <numOfDays> days ago.
void fromThisDayRec(Date* currDay, int numOfDays);
//This function prints the given apartment.
void printApt(Apartment toPrint);
//This function prints the given apartments array.
void printArray(Apartment* arr, int size);
//This function frees all the allocations in the given apartments array.
void freeAptArray(Apartment* arr, int size);
//This function updates the date to the current date.
void timeToDate(Date* curr);
//This function converts a string that represents a month to an integer.
int monthToNum(char* str);
//This function returs the number of days in the given month.
int numOfDaysInMonth(int month);
//This function converts a string that represents a number to an integer.
int stringToInt(char* str);
//This function checks whether the given character is a digit.
int isDigit(char ch);
//This function turns the given character into a digit.
int charToDig(char ch);
//This function swaps between two given organs.
void swap(Apartment* a, Apartment* b);
//Merge sort according to the apartment's price.
void mergeSortStudentArray(Apartment* arr, int size, char order);
void mergeStudentArray_s(Apartment* arr1, int size1, Apartment* arr2, int size2, Apartment* res);
void mergeStudentArray_sr(Apartment* arr1, int size1, Apartment* arr2, int size2, Apartment* res);
//This function writes the apartments from the repositories into the given binary file.
void writeAptsToFile(char* aptsFileName, Apartment* aptArr, int size);
//This function adds an apartment from the given binary file to the apartment pool.
void addAnApartFromFile(short int code, char* address, short int numOfRooms, int price, Date entryDate, Date dataBaseEntryDate, Apartment** arr, int* logSize, int* phySize);
//This function reades the apartments from the given binary file into the repositories.
void readAptsFromFile(char* aptsFileName, Apartment** aptArr, int* logSize, int* phySize, short int* countApt);
//Binary search.
int bin_search(Apartment* array, int size, int val);