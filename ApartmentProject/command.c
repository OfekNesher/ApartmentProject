#include "command.h"

char* getCommand()
{
	char ch;
	int logSize = 0, phySize = 1;
	char* str = (char*)malloc(sizeof(char));

	scanf("%c", &ch);
	while (ch != '\n')
	{
		//realloc
		if (logSize == phySize)
		{
			str = (char*)realloc(str, sizeof(char)*phySize * 2);
			phySize = phySize * 2;
		}

		str[logSize] = ch;
		logSize++;
		scanf("%c", &ch);
	}

	str[logSize] = '\0';

	//realloc
	if (logSize < phySize)
	{
		str = (char*)realloc(str, sizeof(char)*logSize + 1);
	}

	return str;
}

void navigate(char* command, Apartment** aptArr, int* logSize, int* phySize, short int* countApt, int* flag, char** commandArr, List* commandLst, int* countCommand, char* commandsFileName, char* aptsFileName)
{
	//save the original command
	char* orgCommand = (char*)malloc(sizeof(char)*strlen(command) + 1);
	strcpy(orgCommand, command);
	char* out, *in, *newCommand;
	char* tempStr ,*tempStr2; 

	tempStr2 = (char*)malloc(sizeof(char)*strlen(command) + 1);
	strcpy(tempStr2, command);

	char* token = strtok(command, " ");
	int code, numOfDays, logSizeOfComArr;
	int i, num, sizeLst, indexOfStrToDoAgain, flagSpecial = 1;

	if (strcmp(token, "add-an-apt") == 0)
	{
		storeCommand(orgCommand, commandArr, commandLst);

		(*countApt)++;
		addAnApart(*countApt, command + (strlen(token) + 1), aptArr, logSize, phySize);
		(*countCommand)++;
	}

	else if (strcmp(token, "buy-an-apt") == 0)
	{
		storeCommand(orgCommand, commandArr, commandLst);

		token = strtok(NULL, " ");
		code = stringToInt(token);
		buyAnApart(aptArr, code, logSize, phySize);
		(*countCommand)++;
	}

	else if (strcmp(token, "delete-an-apt") == 0)
	{
		storeCommand(orgCommand, commandArr, commandLst);

		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		numOfDays = stringToInt(token);
		deleteAnApartEnter(aptArr, numOfDays, logSize, phySize);
		(*countCommand)++;
	}

	else if (strcmp(token, "get-an-apt") == 0)
	{
		storeCommand(orgCommand, commandArr, commandLst);

		token = strtok(NULL, " ");
		if (strcmp(token, "-Enter") == 0)
		{
			token = strtok(NULL, " ");
			numOfDays = stringToInt(token);
			getAnApartEnter((*aptArr), numOfDays, *logSize);
		}
		else
		{
			getAnApart((*aptArr), *logSize, orgCommand + strlen("get-an-apt "));
		}
		(*countCommand)++;
	}

	//special commands
	else if ((strcmp(token, "!!") == 0))
	{
		tempStr = (char*)malloc(sizeof(char)*strlen(commandArr[0]) + 1);
		strcpy(tempStr, commandArr[0]);
		//tempStr is re-used as our command an therefore will be free at the main
		navigate(tempStr, aptArr, logSize, phySize, countApt, flag, commandArr, commandLst, countCommand, commandsFileName, aptsFileName);
	}

	else if (token[0] == '!' && token[1] != '!')
	{
		for (i = 0; token[i] != '\0' && flagSpecial; i++)
		{
			if (token[i] == '^')
				flagSpecial = 0;
		}
		
		//activate the command number "num"
		if (flagSpecial)
		{
			num = stringToInt(token + 1); //get the command number
			sizeLst = sizeOfList(commandLst); //get the list size

			if (sizeLst >= num) //if the given command is in the list 
			{
				tempStr = (char*)malloc(sizeof(char)*strlen(findStrInLst(commandLst, num, sizeLst)) + 1);
				strcpy(tempStr, findStrInLst(commandLst, num, sizeLst));
				//tempStr is re-used as our command an therefore will be free at the main
				navigate(tempStr, aptArr, logSize, phySize, countApt, flag, commandArr, commandLst, countCommand, commandsFileName, aptsFileName);
			}

			else
			{
				logSizeOfComArr = getLogSizeOfArr(commandArr); //get the size of the arr
				indexOfStrToDoAgain = sizeLst + logSizeOfComArr; //index for finding the given command
				for (i = 0; i < logSizeOfComArr; i++)
				{
						if (indexOfStrToDoAgain == num)//if we found the command to do again
						{
							tempStr = (char*)malloc(sizeof(char)*strlen(commandArr[i]) + 1);
							strcpy(tempStr, commandArr[i]);
							//do it again
							//tempStr is re-used as our command an therefore will be free at the main
							navigate(tempStr, aptArr, logSize, phySize, countApt, flag, commandArr, commandLst, countCommand, commandsFileName, aptsFileName);
						}
						indexOfStrToDoAgain--;
				}
			}
		}
		
		else 
		{
			num = stringToInt(token+1);
			sizeLst = sizeOfList(commandLst);

			if (sizeLst >= num) //if the given command is in the list
			{
				token = strtok(tempStr2, "^");
				tempStr = (char*)malloc(sizeof(char)*strlen(findStrInLst(commandLst, num, sizeLst)) + 1);
				strcpy(tempStr, findStrInLst(commandLst, num, sizeLst));
				token = strtok(NULL, "^");
				out = token;
				token = strtok(NULL, "\n");
				in = token;
				newCommand = dull_replace(tempStr, out, in); //do the switch between the sub strings
				free(tempStr);
				//newCommand is re-used as our command an therefore will be free at the main
				navigate(newCommand, aptArr, logSize, phySize, countApt, flag, commandArr, commandLst, countCommand, commandsFileName, aptsFileName);
			}
			
			else //the command is in the arr
			{

				logSizeOfComArr = getLogSizeOfArr(commandArr); //get the size of the arr
				indexOfStrToDoAgain = sizeLst + logSizeOfComArr;
				for (i = 0; i < logSizeOfComArr; i++)
				{
					if (indexOfStrToDoAgain == num) //if we found the given command
					{
						tempStr = (char*)malloc(sizeof(char)*strlen(commandArr[i]) + 1);
						strcpy(tempStr, commandArr[i]);
						token = strtok(tempStr2, "^");
						token = strtok(NULL, "^");
						out = token;
						token = strtok(NULL, "\n");
						in = token;
						newCommand = dull_replace(tempStr, out, in); //switch between the two substrings
						free(tempStr);
						//newCommand is re-used as our command an therefore will be free at the main
						navigate(newCommand, aptArr, logSize, phySize, countApt, flag, commandArr, commandLst, countCommand, commandsFileName, aptsFileName);
					}
					indexOfStrToDoAgain--;
				}
			}
		}
	}

	else if ((strcmp(token, "short_history") == 0))
	{
		printCommandArr(commandArr, commandLst);
	}

	else if ((strcmp(token, "history") == 0))
	{
		printComList(commandLst);
		printCommandArr(commandArr, commandLst);
	}

	//exit
	else if (strcmp(token, "exit") == 0)
	{
		printf("Good Bye!\n");

		//write commands to text file
		writeCommandsToFile(commandsFileName, commandArr, commandLst);
		writeAptsToFile(aptsFileName, *aptArr, *logSize);
		*flag = 0;
	}

	//free allocations
	free(tempStr2);
}

List makeEmptyList()
{
	List result;

	result.head = result.tail = NULL;
	return result;
}

ListNode* createNode(char* data, ListNode* next)
{
	ListNode *result;

	result = (ListNode*)malloc(sizeof(ListNode));

	result->command = data;
	result->next = next;

	return result;
}

void insertNodeToTail(List* lst, ListNode* newTail)
{
	newTail->next = NULL;

	if (isEmptyList(*lst))
		lst->head = lst->tail = newTail;
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

int isEmptyList(List lst)
{
	return (lst.head == NULL);
}

void freeComList(List lst)
{
	ListNode *p, *q;

	if (isEmptyList(lst))
		return;

	p = lst.head;

	while (p->next != NULL)
	{
		q = p;
		p = p->next;
		free(q->command);
		free(q);
	}

	free(p->command);
	free(p);
}

int sizeOfList(List* lst)
{
	int size = 0;
	ListNode* curr = lst->head;

	while (curr != NULL)
	{
		size++;
		curr = curr->next;
	}

	return size;
}

void storeCommand(char* command, char** arr, List* lst)
{
	int i;

	//arr[0] is the newest command

	if (arr[N - 1] == NULL)
	{
		for (i = N - 1; i > 0; i--)
		{
			arr[i] = arr[i - 1];
		}
		arr[0] = command;
	}

	else
	{
		insertNodeToTail(lst, createNode(arr[N - 1], NULL));
		for (i = N - 1; i > 0; i--)
		{
			arr[i] = arr[i - 1];
		}
		arr[0] = command;
	}

}

void printCommandArr(char** arr, List* lst)
{
	int i, saveIndex = 0;
	int listSize = sizeOfList(lst);

	if (listSize > 0)
	{
		for (i = N - 1; i >= 0; i--)
		{
			printf("%d: %s\n", listSize + N - i, arr[i]);
		}
	}

	else
	{
		if (arr[0] != NULL)
		{
			for (i = 0; i < N && saveIndex == 0; i++)
			{
				if (arr[i] == NULL)
					saveIndex = i;
				if (i == N - 1)
					saveIndex = i + 1;
			}

			for (i = saveIndex - 1; i >= 0; i--)
			{
				printf("%d: %s\n", saveIndex - i, arr[i]);
			}
		}
	}
}

void printComList(List* lst)
{
	int count = 1;
	ListNode* curr = lst->head;

	while (curr != NULL)
	{
		printf("%d: %s\n", count, curr->command);
		count++;
		curr = curr->next;
	}
}

char* findStrInLst(List* lst, int numOfCommand, int sizeOfList)
{
	ListNode* curr = lst->head;
	int count = 1;

	while (count <= sizeOfList)
	{
		if (count == numOfCommand)
			return curr->command;
		
		count++;
		curr = curr->next;
	}
	return NULL;
}

char * dull_replace(char *in, char *pattern, char *by)
{
	size_t outsize = strlen(in) + 1;
	// TODO maybe avoid reallocing by counting the non-overlapping occurences of pattern
	char *res = malloc(outsize);
	// use this to iterate over the output
	size_t resoffset = 0;

	char *needle;
	while (needle = strstr(in, pattern)) {
		// copy everything up to the pattern
		memcpy(res + resoffset, in, needle - in);
		resoffset += needle - in;

		// skip the pattern in the input-string
		in = needle + strlen(pattern);

		// adjust space for replacement
		outsize = outsize - strlen(pattern) + strlen(by);
		res = realloc(res, outsize);

		// copy the pattern
		memcpy(res + resoffset, by, strlen(by));
		resoffset += strlen(by);
	}

	// copy the remaining input
	strcpy(res + resoffset, in);

	return res;
}

void freeComArr(char** arr)
{
	int i;

	for (i = 0; i < N; i++)
		free(arr[i]);
}

void writeCommandsToFile(char* commandsFileName, char** commandArr, List* commandLst)
{
	int i, logSizeOfArr;
	FILE* file;
	file = fopen(commandsFileName, "w");

	if (commandArr[N-1] != NULL)
	{
		for (i = 0; i < N; i++)
		{
			fprintf(file, "%s\n", commandArr[i]);
		}
		
		//write from list
		writeCommandsToFileFromList(file, commandLst->head);
	}
	
	else
	{
		logSizeOfArr = getLogSizeOfArr(commandArr);
		for (i = 0; i < logSizeOfArr; i++)
		{
			fprintf(file, "%s\n", commandArr[i]);
		}
	}

	fclose(file);
}

int getLogSizeOfArr(char** commandArr)
{
	int i , count = 0;
	for (i = 0; i < N; i++)
	{
		if (commandArr[i] != NULL)
			count++;
	}
	return count;
}

void writeCommandsToFileFromList(FILE* f, ListNode* curr)
{
	if (curr == NULL)
		return;

	else
	{
		writeCommandsToFileFromList(f, curr->next);
		fprintf(f, "%s\n", curr->command);
	}
}

void readCommandsFromFile(char* commandsFileName, char** commandArr, List* commandLst)
{
	int count = 0;
	long int fileSize;
	FILE* file;
	file = fopen(commandsFileName, "r");

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
			if (count < N)
			{
				commandArr[count] = getCommandFromFile(file);
				count++;
			}
			
			else
			{
				insertNodeToHead(commandLst, createNode(getCommandFromFile(file), commandLst->head));
			}	
		}
	}
	
	fclose(file);
}

char* getCommandFromFile(FILE* f)
{
	char ch;
	int logSize = 0, phySize = 1;
	char* str = (char*)malloc(sizeof(char));

	fscanf(f, "%c", &ch);
	while (ch != '\n')
	{
		//realloc
		if (logSize == phySize)
		{
			phySize = phySize * 2;
			str = (char*)realloc(str, sizeof(char)*phySize);

		}

		str[logSize] = ch;
		logSize++;
		fscanf(f, "%c", &ch);
	}
	if (logSize <= phySize)
	{
		str = reallocation(str, logSize);
	}
	str[logSize] = '\0';

	//realloc

	return str;
}

char* reallocation(char* str, int logicSize)
{
	char* newStr = (char*)calloc(logicSize + 1, sizeof(char));

	for (int i = 0; i < logicSize; i++)
	{
		newStr[i] = str[i];
	}
	free(str);
	return newStr;

}

void insertNodeToHead(List* lst, ListNode* newHead)
{
	newHead->next = lst->head;
	if (lst->tail == NULL)
		lst->tail = newHead;
	lst->head = newHead;
}
