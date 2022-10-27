/*
Name: Kevin Rocca
Class: CPSC 122, Project 3
9/22/22
This program is the ceaser cipher.
This program takes multiple different inputs and a mode char. If the
mode is '0' it takes a keyFile string and randomly generates a
key between 1 and 25 and writes it to the keyFile file. If the 
mode is 1 it takes the keyFile, plaintext file, and a encryption
file. It turns the plaintext to a blocktext (all caps no punctuation). 
It then reads the keyfile to encrypt each character and stores it
in the encryption file. In mode 3 it takes the keyfile, encrypted file
and an output file. It reads the encrypted file and keyfile and passes
each char to a decrypt function and sends the decrypted blocktext
to the output file. This is a lossy conversion as punctuation doesnt
come back.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <cstdio>
#include <cstring>
using namespace std;

void fileOpen(fstream&, string, char);
void keyGen(string keyFile);
char encrypt(char ch, int shift, int alpha);
char decrypt(char ch, int shift, int alphaInverse);
void fileControl (string keyFile, string fileIn, string fileOut, int mode);

const int MI [26] = {1, 0, 9, 0, 21, 0, 15, 0, 3, 0, 19, 0, 0, 0, 7, 0, 23, 0, 11, 0, 5, 0, 17, 0, 25, 0};

/*
Main checks what mode the program is in and calls the functions
according to the mode it is in. It either generates a key, encrypts,
or decrypts.
Inputs:
    Mode 0: '0', keyFile
    Mode 1: '1', keyFile PTfile CTfile
    Mode 2: '2', keyfile CTfile DCfile
Outputs:
    Mode 0: Random key to keyFile
    Mode 1: Encrypted text to CTfile and blocktext to BKfile
    Mode 2: Decrypted text to DCfile
*/
int main(int argc, char* argv[]){
    int mode = atoi(argv[1]);
    if(mode == 0)
        {
        keyGen(argv[2]);
        }   
    else if(mode == 1)
        {
        fileControl(argv[2], argv[3], argv[4], 1);
        }
    else if(mode == 2)
        {
        fileControl(argv[2], argv[3], argv[4], 2);
        }
    return 0;
}

/*
This function sends uppercase letters to encrypt and outputs it to a file along 
with any numbers in the plaintext file in mode 1. In mode two it takes 
encrypted characters from a encrypted file and sends them to be decrypted
once again outputting the result to a file along with any numbers.
Input: names of key file, input file and output file. mode value of 1 or 2
Output: writes to the output file
*/
void fileControl (string keyFile, string fileIn, string fileOut, int mode){
    fstream fin; 
    fileOpen(fin, fileIn, 'r');
    fstream fout;
    fileOpen(fout, fileOut, 'w');
    fstream key;
    fileOpen(key, keyFile, 'r');

    //Get the keys
    string temp;
    getline(key, temp);
    int shift = stoi(temp);
    getline(key, temp);
    int alpha = stoi(temp);
    key.close();

    char current;
    //Encrypt
    if(mode == 1){
        while(fin.peek() != EOF){
            if((fin.peek() != '\n') && (isalpha(fin.peek()))){
                current = toupper(fin.get());
                current = encrypt(current, shift, alpha);
                fout << current;
            }
            else if(isdigit(fin.peek())){
                current = fin.get();
                fout << current;
            }
            else if(ispunct(fin.peek())){
                fin.get();
            }
            else if(fin.peek() == '\n'){
                fout << endl;
                fin.get();
            } 
            else{
                fin.get();
            }
        }
        fin.close();
        fout.close();
    }
    //Decrypt
    if(mode == 2){
        int alphaInverse = MI[alpha - 1];
        while(fin.peek() != EOF){
            if(isalpha(fin.peek())){
                current = fin.get();
                current = decrypt(current, shift, alphaInverse);
                fout << current;
            }
            else if(isdigit(fin.peek())){
                current = fin.get();
                fout << current;
            }
            else if(fin.peek() == '\n'){
                fout << endl;
                fin.get();
            }
        }
    }
}

//keyGen outputs a key between 1 and 25 to the keyFile file and a
//random multiplier from the alpha array
//Input: keyFile 
//Output: shift and alpha to keyFile 
void keyGen(string keyFile){
    int alpha [12] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
    srand(time(NULL));
    int shift = (rand() % 25) + 1;
    int multiplier = alpha[(rand() % 12)];
    fstream fout;
    fileOpen(fout, keyFile, 'w');
    fout << shift << "\n" << multiplier;
    fout.close();
}

//This function encrypts a character through the affine cipher.
//Input: char, shift amount, alpha
//Output: Returns encrypted char to calling function
char encrypt(char ch, int shift, int alpha){
    if(isalpha(ch)){
        int pos = ch - 'A';
        pos = (((alpha * pos) + shift) % 26);
        ch = pos + 'A';
        return ch;
    }
    else{
        return ch;
    }
}

//This function decrypts a character through the affine cipher.
//Input: encrypted char, shift amount, multiplicative inverse of alpha
//Output: Returns decrypted char to calling function
char decrypt(char ch, int shift, int alphaInverse){
    if(isalpha(ch)){
        int pos = ch - 'A';
        pos = (alphaInverse * (26 + pos - shift) % 26);
        ch = pos + 'A';
        return ch;
    } 
    else{
        return ch;
    }
}

/*
Description: function opens a file 
Input: file stream object reference, name of the file, mode of open
Output: void function, but at exit, file stream object is tied to 
the input file name because 'file' is a reference variable 
*/ 
void fileOpen(fstream& file, string name, char mode)
//void fileOpen(fstream& file, char name[], char mode)
{
 string fileType;

 if (mode == 'r')
  fileType = "input";
 if (mode == 'w')
  fileType = "output";

 if (mode == 'r')
  file.open(name, ios::in);  //available thorugh fstream
 else
  if (mode == 'w')
   file.open(name, ios::out);  //available through fstream;

 if (file.fail()) //error condition 
 {
  cout << "Error opening " << fileType << " file" << endl; 
  exit(EXIT_FAILURE);
 }
}
