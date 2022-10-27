/*
Name: Kevin Rocca
Class: CPSC 122, Project 7
10/22/22
This program is a binary search.
This program dynamically creates an array with length
specified by the command line and  fills it
with random numbers up to the limit specified
in the command line. It then sorts the array
using bubblesort. After this it does a binary
search to find a target and prints out the
location of the target or says the target
was not found. Target is specified in the
command line. 
*/
#include <cstring>
#include <fstream>
#include <time.h>
#include <iostream>
using namespace std;

void bubbleSort(int* arr, int numLines);
void sink(int* arr, int bottom);
void shift(int* arr, int cur);
int binarySearch(int* arr, int size, int target);
void fillArray(int* arr, int size, int limit);
void targetFound(int target, int check);
void printToFile(int* arr, int size, string fileOut);

/*
Main declares a few variables for readability and
calls functions to get the program going.
Usage:
    ./a.out size limit target fileName
Ex:
    ./a.out 100 100 50 printOut
*/
int main(int argc, char* argv[]){
    //naming variables for readability
    int size = atoi(argv[1]);
    int limit = atoi(argv[2]);
    int target = atoi(argv[3]);
    string fileOut = argv[4];

    int* arr = new int[size];
    fillArray(arr, size, limit);
    bubbleSort(arr, size);
    targetFound(target, binarySearch(arr, size, target));
    printToFile(arr, size, fileOut);

    return 0;
}

/*
This function prints out the sorted array to a file.
Inputs:
    Sorted array
    Size of the array
    Name of the file to print to
*/
void printToFile(int* arr, int size, string fileOut){
    ofstream fout;
    fout.open(fileOut);
    for(int i = 0; i < size; i++){
        fout << arr[i] << endl;
    }
}

/*
This function says whether the target number was found and at what position.
I wrote this to declutter main, it does no real calculations
Inputs:
    Target value
    Check returned from binarySearch. Check shows whether or not the target
    was found
*/
void targetFound(int target, int check){
    if(check != -1){
        cout << target << " found at position " << check << " in the array" << endl;
    }
    else{
        cout << target << " not found" << endl;
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
void bubbleSort(int* arr, int size){
    int pass = 0;
    int bottom = size;
    while(pass < size - 1){ 
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
void sink(int* arr, int bottom){
    int cur = 0;
    while(cur < bottom - 1){
        if(arr[cur] > arr[cur+1]){
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
void shift(int* arr, int cur){
    int temp = arr[cur];
    arr[cur] = arr[cur+1];
    arr[cur+1] = temp;
}

/*
This function fills the array with random numbers
that are less than limit. I'm pretty sure it doesn't
include the limit. I could make it include the limit
by adding 1 to the rand % limit thing but I don't
know if i'm supposed to do that.
Inputs:
    Array from main
    Size of the array
    Limit (largest number to put in the array)
*/
void fillArray(int* arr, int size, int limit){
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        arr[i] = (rand() % limit);
    }
}

/*
This function does a binary search until it finds the
target number. It then returns the position of the 
target number in the array. Otherwise it returns -1.
Inputs:
    Sorted array
    Size of the array
    Target number in the array
Outputs:
    Returns position of target in the array
*/
int binarySearch(int* arr, int size, int target){
    int top = 0;
    int bottom = size;
    int mid;
    while(top <= bottom){
        mid = (top + bottom)/2;
        if(arr[mid] == target){
            return mid;
        }
        if(target < arr[mid]){
            bottom = mid - 1;
        }
        else{
            top = mid + 1;
        }
    }
    return -1;
}