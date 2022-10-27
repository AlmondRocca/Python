/*
Name: Kevin Rocca
Class: CPSC 122, Project 5
10/9/22
This program is a string bubble sort algorithm.
It takes an unsorted input file and sorts it to an output
file as designated in the command line. Theres really
not too much to say about this one.
*/
#include <cstring>
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

void bubbleSort(string arr[], int numLines);
void sink(string arr[], int bottom);
void shift(string arr[], int cur);
void readToArray(string arr[], string fileName);
void writeToFile(string arr[], string fileName);

const int MAX_FILE_SIZE = 100;
/*
Main serves to call the input and output files. Since it
is so simple, making a control function would be
redundant. The array is set at size 100 because
we dont know linked lists yet and cant make a dynamic
array to suit the input file.
*/
int main(int argc, char* argv[]){
    string toSort[MAX_FILE_SIZE]; 
    readToArray(toSort, argv[1]);
    writeToFile(toSort, argv[2]);
    return 0;
}

/*
This function reads a file designated in main and
stores each line into the array created in main.
It then calls the bubbleSort() method to begin sorting
Inputs: 
    Array created in main
    Filename to read from (also from main)
*/
void readToArray(string arr[], string fileName){
    int numLines = 0;
    string temp;
    ifstream fin;
    fin.open(fileName);
    while(fin.peek() != EOF){
        getline(fin, temp);
        arr[numLines] = temp;
        numLines++;
    }
    fin.close();
    bubbleSort(arr, numLines);
}

/*
This function takes the sorted array from main and 
writes the sorted output to a file designated in main.
Inputs: 
    Array created in main 
    Output filename from main
*/
void writeToFile(string arr[], string fileName){
    ofstream fout;
    fout.open(fileName);
    for(int i = 0; i < 100; i++){
        fout << arr[i] << endl;
    }
}

/*
This function is a control method for the bubbleSort
algorithm. It checks to see how many passes it needs
to do and calls sink() if it should do a pass.
Inputs:
    The array created in main
    The number of lines from the reading file.
*/
void bubbleSort(string arr[], int numLines){
    int pass = 0;
    int bottom = numLines;
    while(pass < numLines - 1){ 
        sink(arr, bottom);
        bottom--;
        pass++;
    }
}

/*
This function checks to see if the string it is looking at
is further down the alphabet than the string it is comparing to. 
If it is it calls shift() to swap the strings
Inputs:
    Array created in main
    Int that shows how many elements have been sorted.
*/
void sink(string arr[], int bottom){
    int cur = 0;
    while(cur < bottom - 1){
        if(arr[cur].compare(arr[cur+1]) > 0){
            shift(arr, cur);
        }
        cur++;
    }  
}

/*
This function 'sinks' the string by swapping the
current string with the string below it in the array.
For example it sinks Z past the letter Y.
Inputs:
    Array created in, you guessed it, main
    The index of the string that needs to be sunk
*/
void shift(string arr[], int cur){
    string temp = arr[cur];
    arr[cur] = arr[cur+1];
    arr[cur+1] = temp;
}
