#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int);
void makeColumns(int);
void checkPrimes(int, int);
void errorCheck(int);


int main(int argc, char* argv[]){
    int primeAmount = atoi(argv[1]);
    int colAmount = atoi(argv[2]);
    if(primeAmount || colAmount <= 0){
        errorCheck(1);
    }
    //todo; add more error check cases.
    //can i send the array down like this?
    checkPrimes(primeAmount, colAmount);
    return 0;
}
//probably kinda working. 
//maybe return the int[] once its full to main
//send the int[] down to makeColumns
//num is the amount of primes we're looking for
//primeAmount is the current amount of primes found

void checkPrimes(int num, int colAmount){
    int primeAmount = 0;
    int currentNum = 3;
    int primes[num];
    //the isPrime function doesn't check for two. This is
    //just put in because you'll always need two.
    primes[0] = 2;
    while(primeAmount < (num - 1)){
        if(isPrime(currentNum)){
            primes[primeAmount + 1] = currentNum;
            primeAmount++;
        }
        currentNum++;
    }

    for(int i = 0; i < sizeof(primes); i++){
        if(i % colAmount == 0){
            makeColumns(primes[i]);
            cout << endl;
        } else {
            makeColumns(primes[i]);
        }
    }
    
}

//The largest num you have to check for primes is the sqrt of the
//number. At least thats what wikipedia says. 
bool isPrime(int num){
    for(int i = 3; i < sqrt(num); i + 2){
        if(num % i == 0){
            return false;
        }
        return true;
    }
    return true;
}

//make the colums man
void makeColumns(int prime){
     cout << prime << "\t";
}

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