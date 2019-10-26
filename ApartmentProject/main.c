#include "command.h"

/*********************************************************************************************
aptProject
Ofek Nehser & Lidor Hadar
06/06/18
**********************************************************************************************/

void main(int argc,char ** argv)
{
	int logSize = 0, phySize = 1, countCommand = 0, flag = 1;
	short int  countApt = 0;
	Apartment* aptArr;
	char* short_term_history[N] = { 0 };
	List commandLst;
	commandLst = makeEmptyList();

	//read commands and apartments from files
	readCommandsFromFile(argv[1], short_term_history, &commandLst);
	readAptsFromFile(argv[2], &aptArr, &logSize, &phySize, &countApt);

	printf("Please enter one of the following commands:\nadd - an - apt, get - an - apt, buy - an - apt or delete - an - apt\nFor reconstruction commands, please enter :\n!!, !num, history, short_history or !num^str1^str2\nTo exit, enter exit.\n");

	while (flag)
	{
		navigate(getCommand(), &aptArr, &logSize, &phySize, &countApt, &flag, short_term_history, &commandLst, &countCommand, argv[1], argv[2]);
	}

	freeAptArray(aptArr, logSize);
	freeComList(commandLst);
	freeComArr(short_term_history);
}