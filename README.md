# Apartment Project

# Introduction:
As part of an advanced C language programming course we were given a task to write a program that manages a pool of apartments for sale.

# Our Project:
The program receives and executes commands from the user. The "exit" command will end the program.
The input from the user can be assumed to be correct.

Possible commands are:

• get-an-apt –MaximumPrice 1500000

All apartments with a maximum cost of 1500000 will be printed

• get-an-apt –MinimumNumRooms 3

All apartments with at least 3 rooms will be printed

• get-an-apt –MaximumNumRooms 5

All apartments with a maximum of 5 rooms will be printed

• get-an-apt –Date 01052017

All apartments vacated by May 1, 2017 will be printed


The user can combine several requirements, for example:

• get-an-apt –MinimumNumRooms 3 –MaximumNumRooms 5 –MaximumPrice 1750000

For each of the above commands, the user can add the option –s and get the information sorted from the lowest price to the highest price, or the option –sr and get the information sorted from the highest price to the lowest.

for example,
• get-an-apt –MaximumNumRooms 5 -sr

All 5-room apartments can be printed on a private screen, sorted from the most expensive to the cheapest.

• add-an-apt "Hasavyonim 23 Ramat Ono" 2000000 4 01 01 20

Adding an apartment to the reservoir on Savyonim Street 23 Ramat Ono, which costs 2 million, the number of rooms in it 4 and the date of entry is 1.1.20.
The add-in will be in memory only, while at the end of the program all apartments data added following the add-an-apt command will be saved to the file.

• buy-an-apt <number>
  
This command will signify the purchase of the apartment whose code is the number and of course result in its removal from the repository.

• get-an-apt –Enter <x>
  
The codes of the apartments that entered the repository will be printed in the last <x> days

• delete-an-apt –Enter <x>
  
Exited from the pool of apartments that entered it in the last <x> days

The commands will store in two repositories as described below:
      Repository A: A queue to be used by a 7-pointer array containing the 7 most recent commands.
      Repository B: A linked list of the older commands.

The program displays a prompt to the user at each stage and receives a command from it. The command can be a get-an-apt, add-an-apt, buy-an-apt, delete-an-apt or request to restore a repository from the repository (recovery options are described below).
The program executes the command and then stores the (normal or restored) command in repository A. If repository A is full, the oldest command must be passed from repository A to repository B and update repository A to contain the last 7 commands (including the command that has just been inserted).

Recovery options from the repository are listed below:
1. Bow !! Will trigger the last command inserted into repository A.
2. Press <num>! Will trigger a command with the specified number num.
3. Pressing short_history will print the 7 most recent commands (repository A)
4. Tapping history will print both repositories.
Option 3 and 4 next to each command will print a digit (from 1 onwards. The command with the maximum number is the last hardened command).
5. Enter! <num> ^ str1 ^ str2 will execute the command with the number num containing str1 sub string and the same sub string will be replaced with str2.

For example, if command # 4 was
• get-an-apt –MinimumNumRooms 3

So the following command:
•! 4 ^ 3 ^ 2

Will actually be the command:
• get-an-apt –MinimumNumRooms 2


The commands will be saved between program runs, so commands issued during a previous program run can also be restored. The commands will be saved in a text file from the last (newest) to the oldest.




