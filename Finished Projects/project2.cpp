/*
Name: Kevin Rocca
Class: CPSC 122, Project 1
9/8/22
This program takes a character array of numbers in character form
and turns them into integers using myAtoi. Once this is done,
both numbers are multiplied and the result is written to a file.
The filename is specified in the commandline.
*/

#include <iostream>
#include <fstream>
using namespace std;

int myStrnlen(char*);
int myAtoi(char*);

//This function below sends the char arrays to myAtoi, multplies
//the resulting int, and prints the result to a file.
int main(int argc, char* argv[]){
    int firstNum = myAtoi(argv[1]);
    int secondNum = myAtoi(argv[2]);
    int product = firstNum * secondNum;

    ofstream outFile;
    outFile.open(argv[3], ios::app);
    outFile << product;
    outFile.close();
    return 0;
}

/*
This function takes uses myStrnlen to find out how many number
chars are in the array. It then goes through the array and 
subtracts the character '0' which is at position 48 in the
ascii table. Doing this gives a ascii value that is equal
to the numbers actual quantity. For example, '8' - '0' is
56 - 48 in ascii which becomes 8. This number is then multiplied
by 10 to shift the result to the left one digit and allow for 
bigger nubmers. Ex, 9 * 10 = 90, 90 + 5 = 95, 95 * 10 = 950...
*/
int myAtoi(char str[]){
    int length = myStrnlen(str);
    int toReturn = 0;
        for(int i = 0; i < length; i++){
            toReturn = ((toReturn * 10) + (str[i] - '0'));  
        }
    return toReturn;
}

//This function looks for how many chars the array contains
//exluding the null terminator
int myStrnlen(char str[]){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}


