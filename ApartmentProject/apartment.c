#include "apartment.h"

void addAnApart(short int code, char* str, Apartment** arr, int* logSize, int* phySize)
{
	int lSize = *logSize;
	int pSize = *phySize;
	int counter = 0;

	//realloc
	if (lSize == pSize)
	{
		(*arr) = (Apartment*)realloc((*arr), sizeof(Apartment)*(pSize + 1));
		pSize++;
	}
	else if (pSize == 1)
		(*arr) = (Apartment*)malloc(sizeof(Apartment)*pSize);

	(*arr)[lSize].code = code;
	timeToDate(&(*arr)[lSize].dataBaseEntryDate);

	char* token = strtok(str, "\"");
	(*arr)[lSize].address = (char*)malloc(sizeof(char)*strlen(token) + 1);
	strcpy((*arr)[lSize].address, token);

	token = strtok(NULL, " ");

	while (token != NULL)
	{
		if (counter == 0)
			(*arr)[lSize].price = stringToInt(token);
		else if (counter == 1)
			(*arr)[lSize].numOfRooms = stringToInt(token);
		else if (counter == 2)
			(*arr)[lSize].entryDate.day = stringToInt(token);
		else if (counter == 3)
			(*arr)[lSize].entryDate.month = stringToInt(token);
		else if (counter == 4)
			(*arr)[lSize].entryDate.year = stringToInt(token) + 2000;

		counter++;
		token = strtok(NULL, " ");
	}
	lSize++;

	*logSize = lSize;
	*phySize = pSize;
}

void buyAnApart(Apartment** arr, int code, int* logSize, int* phySize)
{
	int size;
	int	theIndex;
	size = *logSize;

	//binary search
	theIndex = bin_search(*arr, size, code);
	deleteFromArray((*arr), theIndex, size);

	(*logSize)--;
	(*phySize)--;

	//realloc
	(*arr) = (Apartment*)realloc((*arr), sizeof(Apartment)*(*logSize));
}

void getAnApartEnter(Apartment* arr, int numOfDays, int logSize)
{
	int i;
	Date startDate;
	//update the date to the current date
	timeToDate(&startDate);
	//send the current date to the help rec function
	fromThisDayRec(&startDate, numOfDays);

	for (i = 0; i < logSize; i++)
	{
		if (arr[i].dataBaseEntryDate.year > startDate.year)
			printf("Code: %d\n", arr[i].code);

		else if (arr[i].dataBaseEntryDate.year == startDate.year)
		{
			if (arr[i].dataBaseEntryDate.month > startDate.month)
				printf("Code: %d\n", arr[i].code);

			else if (arr[i].dataBaseEntryDate.month == startDate.month)
			{
				if (arr[i].dataBaseEntryDate.day > startDate.day)
					printf("Code: %d\n", arr[i].code);
			}
		}
	}
}

void deleteAnApartEnter(Apartment** arr, int numOfDays, int* logSize, int* phySize)
{
	int i, size, count = 0;
	Date startDate;
	size = *logSize;
	//update the date to the current date
	timeToDate(&startDate);
	//send the current date to the help rec function
	fromThisDayRec(&startDate, numOfDays);

	for (i = 0; i < size - count; i++) // check!!!
	{
		if ((*arr)[i].dataBaseEntryDate.year > startDate.year)
		{
			deleteFromArray((*arr), i, size - count);
			count++;
			i--;
		}

		else if ((*arr)[i].dataBaseEntryDate.year == startDate.year)
		{
			if ((*arr)[i].dataBaseEntryDate.month > startDate.month)
			{
				deleteFromArray((*arr), i, size - count);
				count++;
				i--;
			}

			else if ((*arr)[i].dataBaseEntryDate.month == startDate.month)
			{
				if ((*arr)[i].dataBaseEntryDate.day > startDate.day)
				{
					deleteFromArray((*arr), i, size - count);
					count++;
					i--;
				}
			}
		}
	}

	size = size - count;
	//realloc
	(*arr) = (Apartment*)realloc((*arr), sizeof(Apartment)*size);
	*logSize = size;
	*phySize = size;
}

void getAnApart(Apartment* arr, int size, char* str)
{
	//save the original command
	char* orgCommand = (char*)malloc(sizeof(char)*strlen(str) + 1);
	strcpy(orgCommand, str);

	int arrCopySize = size;
	Apartment* arrCopy = copyArr(arr, arrCopySize);
	char* token = strtok(orgCommand, " ");

	while (token != NULL)
	{
		if (strcmp(token, "-MinimumNumRooms") == 0)
		{
			token = strtok(NULL, " \0");
			minimumNumRooms(&arrCopy, &size, stringToInt(token));
		}
		else if (strcmp(token, "-MaximumNumRooms") == 0)
		{
			token = strtok(NULL, " ");
			maximumNumRooms(&arrCopy, &size, stringToInt(token));
		}
		else if (strcmp(token, "-Date") == 0)
		{
			token = strtok(NULL, " ");
			freeUpToDate(&arrCopy, &size, token);
		}
		else if (strcmp(token, "-MaximumPrice") == 0)
		{
			token = strtok(NULL, " ");
			maximumPrice(&arrCopy, &size, stringToInt(token));
		}
		else if (strcmp(token, "-s") == 0)
		{
			mergeSortStudentArray(arrCopy, size, 's');
		}
		else if (strcmp(token, "-sr") == 0)
		{
			mergeSortStudentArray(arrCopy, size, 'r');
		}

		token = strtok(NULL, " ");
	}

	//print
	printArray(arrCopy, size);

	//free the copy array and the string
	free(arrCopy);
	free(orgCommand);
}

void maximumPrice(Apartment** copyArr, int* size, int maxPrice)
{
	int i, count = 0;
	int tempSize = *size;

	for (i = 0; i < tempSize - count; i++)
	{
		if ((*copyArr)[i].price > maxPrice)
		{
			deleteFromArray((*copyArr), i, tempSize - count);
			count++;
			i--;
		}
	}

	tempSize = tempSize - count;
	//realloc
	if (count > 0)
	{
		(*copyArr) = (Apartment*)realloc((*copyArr), sizeof(Apartment)*tempSize);
	}
	*size = tempSize;
}

void minimumNumRooms(Apartment** copyArr, int* size, int minRooms)
{
	int i, count = 0;
	int tempSize = *size;

	for (i = 0; i < tempSize - count; i++)
	{
		if ((*copyArr)[i].numOfRooms < minRooms)
		{
			deleteFromArray((*copyArr), i, tempSize - count);
			count++;
			i--;
		}
	}

	tempSize = tempSize - count;
	//realloc
	if (count > 0)
	{
		(*copyArr) = (Apartment*)realloc((*copyArr), sizeof(Apartment)*tempSize);
	}
	*size = tempSize;
}

void maximumNumRooms(Apartment** copyArr, int* size, int maxRooms)
{
	int i, count = 0;
	int tempSize = *size;

	for (i = 0; i < tempSize - count; i++)
	{

		if ((*copyArr)[i].numOfRooms > maxRooms)
		{
			deleteFromArray((*copyArr), i, tempSize - count);
			count++;
			i--;
		}
	}

	tempSize = tempSize - count;
	//realloc
	if (count > 0)
	{
		(*copyArr) = (Apartment*)realloc((*copyArr), sizeof(Apartment)*tempSize);
	}
	*size = tempSize;
}

void freeUpToDate(Apartment** copyArr, int* size, char* date)
{
	int i, count = 0;
	int tempSize = *size;

	Date d;
	d.day = charToDig(date[0]) * 10 + charToDig(date[1]);
	d.month = charToDig(date[2]) * 10 + charToDig(date[3]);
	d.year = stringToInt(date + 6);

	for (i = 0; i < tempSize - count; i++)
	{
		if ((*copyArr)[i].entryDate.year - 2000 > d.year)
		{
			deleteFromArray((*copyArr), i, tempSize - count);
			count++;
			i--;
		}
		else if ((*copyArr)[i].entryDate.year - 2000 == d.year)
		{
			if ((*copyArr)[i].entryDate.month > d.month)
			{
				deleteFromArray((*copyArr), i, tempSize - count);
				count++;
				i--;
			}
			else if ((*copyArr)[i].entryDate.month == d.month)
			{
				if ((*copyArr)[i].entryDate.day > d.day)
				{
					deleteFromArray((*copyArr), i, tempSize - count);
					count++;
					i--;
				}
			}
		}
	}

	tempSize = tempSize - count;
	//realloc
	if (count > 0)
	{
		(*copyArr) = (Apartment*)realloc((*copyArr), sizeof(Apartment)*tempSize);
	}
	*size = tempSize;
}

Apartment* copyArr(Apartment* arr, int size)
{
	int i;
	Apartment* arrCopy;
	arrCopy = (Apartment*)malloc(sizeof(Apartment)*size);

	for (i = 0; i < size; i++)
	{
		arrCopy[i].address = (char*)malloc(sizeof(char)* strlen(arr[i].address) + 1);
		strcpy(arrCopy[i].address, arr[i].address);
		arrCopy[i].code = arr[i].code;
		arrCopy[i].dataBaseEntryDate.day = arr[i].dataBaseEntryDate.day;
		arrCopy[i].dataBaseEntryDate.month = arr[i].dataBaseEntryDate.month;
		arrCopy[i].dataBaseEntryDate.year = arr[i].dataBaseEntryDate.year;
		arrCopy[i].entryDate.day = arr[i].entryDate.day;
		arrCopy[i].entryDate.month = arr[i].entryDate.month;
		arrCopy[i].entryDate.year = arr[i].entryDate.year;
		arrCopy[i].numOfRooms = arr[i].numOfRooms;
		arrCopy[i].price = arr[i].price;
	}

	return arrCopy;
}

void deleteFromArray(Apartment* arr, int index, int logSize)
{
	int i;

	free(arr[index].address);
	for (i = index; i < logSize - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
}

void fromThisDayRec(Date* currDay, int numOfDays)
{
	int temp, diff;

	if (numOfDays <= 0)
		return;

	else
	{
		diff = currDay->day - numOfDays;
		if (diff > 0)
		{
			currDay->day = diff;
			return;
		}
		else
		{
			//in case we need to go back to the previous year
			if (currDay->month == 1)
			{
				temp = numOfDaysInMonth(currDay->month - 1);
				currDay->day = temp;
				(currDay->year)--;
				currDay->month = 12;
				fromThisDayRec(currDay, diff*(-1));
			}
			else
			{
				temp = numOfDaysInMonth(currDay->month - 1);
				currDay->day = temp;
				(currDay->month)--;
				fromThisDayRec(currDay, diff*(-1));
			}
		}
	}
}

void printApt(Apartment toPrint)
{
	printf("Apt details:\n");
	printf("Code: %d\n", toPrint.code);
	printf("Address: %s\n", toPrint.address);
	printf("Number of rooms: %d\n", toPrint.numOfRooms);
	printf("Price: %d\n", toPrint.price);
	printf("Entry date: %d.%d.%d\n", toPrint.entryDate.day, toPrint.entryDate.month, toPrint.entryDate.year);
	printf("Database entry date: %d.%d.%d\n", toPrint.dataBaseEntryDate.day, toPrint.dataBaseEntryDate.month, toPrint.dataBaseEntryDate.year);
}

void printArray(Apartment* arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
		printApt(arr[i]);
}

void freeAptArray(Apartment* arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		free(arr[i].address);
	}
	free(arr);
}

void timeToDate(Date* curr)
{
	int counter = 0;
	time_t curtime;
	time(&curtime);
	char str[26];
	strcpy(str, ctime(&curtime));

	char* token = strtok(str, " ");
	while (token != NULL)
	{
		if (counter == 1)
			curr->month = monthToNum(token);
		else if (counter == 2)
			curr->day = stringToInt(token);
		else if (counter == 4)
			curr->year = stringToInt(token);

		counter++;
		token = strtok(NULL, " ");
	}
}

int monthToNum(char* str)
{
	if (strcmp(str, "Jan") == 0)
		return 1;
	else if (strcmp(str, "Feb") == 0)
		return 2;
	else if (strcmp(str, "Mar") == 0)
		return 3;
	else if (strcmp(str, "Apr") == 0)
		return 4;
	else if (strcmp(str, "May") == 0)
		return 5;
	else if (strcmp(str, "Jun") == 0)
		return 6;
	else if (strcmp(str, "Jul") == 0)
		return 7;
	else if (strcmp(str, "Aug") == 0)
		return 8;
	else if (strcmp(str, "Sep") == 0)
		return 9;
	else if (strcmp(str, "Oct") == 0)
		return 10;
	else if (strcmp(str, "Nov") == 0)
		return 11;
	else
		return 12;
}

int numOfDaysInMonth(int month)
{
	if (month == 2)
		return 28;
	if (month == 6 || month == 9 || month == 11 || month == 4)
		return 30;
	else
		return 31;
}

int stringToInt(char* str)
{
	int i = 0;
	int num = 0;

	while (isDigit(str[i]))
	{
		num = num * 10 + charToDig(str[i]);
		i++;
	}

	return num;
}

int isDigit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

int charToDig(char ch)
{
	return (ch - '0');
}

void swap(Apartment* a, Apartment* b)
{
	Apartment tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void mergeSortStudentArray(Apartment* arr, int size, char order)
{
	Apartment* temp;
	int i;

	if (size <= 1)
	{
		return;
	}
	else
	{
		if (order == 's')
		{
			mergeSortStudentArray(arr, size / 2, order);
			mergeSortStudentArray(arr + (size / 2), size - (size / 2), order);
			temp = (Apartment*)malloc(sizeof(Apartment)*size);
			mergeStudentArray_s(arr, size / 2, arr + (size / 2), size - (size / 2), temp);

			for (i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}

			free(temp);
		}
		else
		{
			mergeSortStudentArray(arr, size / 2, order);
			mergeSortStudentArray(arr + (size / 2), size - (size / 2), order);
			temp = (Apartment*)malloc(sizeof(Apartment)*size);
			mergeStudentArray_sr(arr, size / 2, arr + (size / 2), size - (size / 2), temp);

			for (i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}

			free(temp);
		}

	}
}

void mergeStudentArray_s(Apartment* arr1, int size1, Apartment* arr2, int size2, Apartment* res)
{
	int i1 = 0, i2 = 0, write = 0;

	while (i1 < size1 && i2 < size2)
	{
		if (arr1[i1].price > arr2[i2].price)
		{
			res[write] = arr2[i2];
			i2++;
			write++;
		}
		else
		{
			res[write] = arr1[i1];
			i1++;
			write++;
		}
	}

	while (i1 < size1)
	{
		res[write] = arr1[i1];
		i1++;
		write++;
	}

	while (i2 < size2)
	{
		res[write] = arr2[i2];
		i2++;
		write++;
	}
}

void mergeStudentArray_sr(Apartment* arr1, int size1, Apartment* arr2, int size2, Apartment* res)
{
	int i1 = 0, i2 = 0, write = 0;

	while (i1 < size1 && i2 < size2)
	{
		if (arr1[i1].price > arr2[i2].price)
		{
			res[write] = arr1[i1];
			i1++;
			write++;
		}
		else
		{
			res[write] = arr2[i2];
			i2++;
			write++;
		}
	}

	while (i1 < size1)
	{
		res[write] = arr1[i1];
		i1++;
		write++;
	}

	while (i2 < size2)
	{
		res[write] = arr2[i2];
		i2++;
		write++;
	}
}

void addAnApartFromFile(short int code, char* address, short int numOfRooms, int price, Date entryDate, Date dataBaseEntryDate, Apartment** arr, int* logSize, int* phySize)
{
	int lSize = *logSize;
	int pSize = *phySize;
	int counter = 0;

	//realloc
	if (lSize == pSize)
	{
		(*arr) = (Apartment*)realloc((*arr), sizeof(Apartment)*(pSize + 1));
		pSize++;
	}
	else if (pSize == 1)
		(*arr) = (Apartment*)malloc(sizeof(Apartment)*pSize);

	(*arr)[lSize].code = code;

	(*arr)[lSize].address = (char*)malloc(sizeof(char)*strlen(address) + 1);
	strcpy((*arr)[lSize].address, address);

	(*arr)[lSize].numOfRooms = numOfRooms;
	(*arr)[lSize].price = price;
	(*arr)[lSize].entryDate = entryDate;
	(*arr)[lSize].dataBaseEntryDate = dataBaseEntryDate;

	lSize++;

	*logSize = lSize;
	*phySize = pSize;
}

void writeAptsToFile(char* aptsFileName, Apartment* aptArr, int size)
{
	int i;
	short int addressLen;
	FILE* file;
	unsigned char aptBits[3], tempByte;
	unsigned short int data_base, temp2Byte;

	file = fopen(aptsFileName, "wb");

	for (i = 0; i < size; i++)
	{
		//code, address and price
		fwrite(&aptArr[i].code, sizeof(short int), 1, file);
		addressLen = (short int)strlen(aptArr[i].address);
		fwrite(&addressLen, sizeof(short int), 1, file);
		fwrite(aptArr[i].address, sizeof(char), addressLen, file);
		fwrite(&aptArr[i].price, sizeof(int), 1, file);

		//num of rooms and entry date
		aptBits[0] = aptArr[i].numOfRooms << 4;
		tempByte = aptArr[i].entryDate.day;
		aptBits[0] = aptBits[0] | (tempByte >> 1);
		aptBits[1] = tempByte << 7;
		tempByte = aptArr[i].entryDate.month;
		aptBits[1] = aptBits[1] | (tempByte << 3);
		tempByte = aptArr[i].entryDate.year - 2000;
		aptBits[1] = aptBits[1] | (tempByte >> 4);
		aptBits[2] = tempByte << 4;

		fwrite(&aptBits[0], sizeof(char), 1, file);
		fwrite(&aptBits[1], sizeof(char), 1, file);
		fwrite(&aptBits[2], sizeof(char), 1, file);

		//dataBase entry date
		temp2Byte = aptArr[i].dataBaseEntryDate.day;
		data_base = temp2Byte << 11;
		temp2Byte = aptArr[i].dataBaseEntryDate.month;
		data_base = data_base | (temp2Byte << 7);
		temp2Byte = aptArr[i].dataBaseEntryDate.year - 2000;
		data_base = data_base | temp2Byte;

		fwrite(&data_base, sizeof(short int), 1, file);
	}

	fclose(file);
}

void readAptsFromFile(char* aptsFileName, Apartment** aptArr, int* logSize, int* phySize, short int* countApt)
{
	long int fileSize;
	FILE* file;
	file = fopen(aptsFileName, "rb"); 
	short int code, numOfRooms, addressLen, dBase, dMaskDay = 0xF800, dMaskMonth = 0x0780, dMaskYear = 0x007F;
	char* address;
	int price;
	Date entryDate, dataBaseEntryDate;
	unsigned char aptBits[3], tempByte, maskDay = 0x0F, maskMonth = 0x78, maskYear = 0x07;

	//the first time the program works
	if (file == NULL)
		return;

	else
	{
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		rewind(file);

		while (ftell(file) < fileSize)
		{
			fread(&code, sizeof(short int), 1, file);
			fread(&addressLen, sizeof(short int), 1, file);
			address = (char*)malloc(sizeof(char)*addressLen + 1);
			fread(address, sizeof(char), addressLen, file);
			address[addressLen] = '\0';
			fread(&price, sizeof(int), 1, file);
			
			//compressed
			fread(aptBits, sizeof(char), 3, file);
			fread(&dBase, sizeof(short int), 1, file);

			//num of rooms and entry date 
			numOfRooms = aptBits[0] >> 4;
			entryDate.day = maskDay & aptBits[0];
			entryDate.day = entryDate.day << 1;
			tempByte = aptBits[1] >> 7;
			entryDate.day = entryDate.day | tempByte;
			entryDate.month = maskMonth & aptBits[1];
			entryDate.month = entryDate.month >> 3;
			entryDate.year = maskYear & aptBits[1];
			entryDate.year = entryDate.year << 4;
			aptBits[2] = aptBits[2] >> 4;
			entryDate.year = (entryDate.year | aptBits[2]) + 2000;

			//dataBase entry date
			dataBaseEntryDate.day = dBase & dMaskDay;
			dataBaseEntryDate.day = dataBaseEntryDate.day >> 11;
			dataBaseEntryDate.month = dBase & dMaskMonth;
			dataBaseEntryDate.month = dataBaseEntryDate.month >> 7;
			dataBaseEntryDate.year = dBase & dMaskYear;
			dataBaseEntryDate.year = dataBaseEntryDate.year + 2000;

			//add an apart
			addAnApartFromFile(code, address, numOfRooms, price, entryDate, dataBaseEntryDate, aptArr, logSize, phySize);
		}
	}

	//update the aprtment's code
	if ((*logSize) > 0)
	{
		*countApt = (*aptArr)[(*logSize) - 1].code;
	}

	fclose(file);
}

int bin_search(Apartment* array, int size, int val)
{
	int first, last, middle;

	first = 0;
	last = size - 1;
	middle = (first + last) / 2;

	while (first <= last) {
		if (array[middle].code < val)
			first = middle + 1;
		else if (array[middle].code == val)
			return middle;
		else
			last = middle - 1;

		middle = (first + last) / 2;
	}

	return -1;
}