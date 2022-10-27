/*
Name: Kevin Rocca
Class: CPSC 122, Project 1
9/8/22
This program finds the first n prime numbers and displays it over c
columns. It only checks odd numbers and up until the square root of
the number it is testing for efficiency. 
https://en.wikipedia.org/wiki/Prime_number
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

bool isPrime(int);
void display(int, int);
void errorCheck(int);


int main(int argc, char* argv[]){
    int primesToFind = atoi(argv[1]);
    int colAmount = atoi(argv[2]);

    if((primesToFind || colAmount) <= 0){
        errorCheck(1);
    }
    if(primesToFind < colAmount){
        errorCheck(2);
    }

    display(primesToFind, colAmount);
    
    return 0;
}

void display(int primesToFind, int colAmount){
    int primesFound = 1;
    int currentTest = 3;
    //My program skips two since it is a special case, all other nums are odd
    //allowing isPrime to only check odd nums
    cout << "2" << "\t";
    while(primesFound < primesToFind){
        if(isPrime(currentTest)){
            if(primesFound % colAmount == 0){
                cout << endl;
            }
            cout << currentTest << "\t";
            currentTest += 2;
            primesFound++;
        } else {
            currentTest += 2;
        }
    }
    
}
/*
The function above asks isPrime if a number is prime. If it is
it prints out the prime along with a tab for formatting. Once it
reaches the desired number of columns it creates a new row. It skips
even numbers because they arent prime.
Inputs: How many primes to find and how many columns to display on
Outputs: The prime numbers in nice neat columns
*/

bool isPrime(int num){
   for(int i = 2; i <= sqrt(num); i++){
       if(num % i == 0){
           return false;
       } 
   }
   return true;
}
/*
The above function checks to see whether a number is prime or not
for the display function. It only goes to the square root of the 
number it is checking as wikipedia says thats the highest the number 
can be divided by? not sure how it works really but it does.
Input: A number to check
Output: True if the number is prime, false otherwise.
*/

void errorCheck(int num){
    switch (num)
    {
    case(1):
        exit(EXIT_FAILURE);
        break;
    
    case(2):
        exit(EXIT_FAILURE);
        break;
    }

}
/*
Light errorcheck in case the inputs are bad
*/
