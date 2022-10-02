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
void toBlock(string PTFile);
char encrypt(char ch, int key);
char decrypt(char ch, int key);
int keyRead(string keyFile);
bool remove(char ch);
void ctControl(string ctFile, int key);
void dcControl(string ctFile, string dcFile, int key);

const string BKfile = "BKfile";

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
        toBlock(argv[3]);
        int key = keyRead(argv[2]);
        ctControl(argv[4], key);
        }
    else if(mode == 2)
        {
        int key = keyRead(argv[2]);
        dcControl(argv[3], argv[4], key);
        }
    return 0;
}

//This function sends the characters to be encrypted by encrypt and
//opens the BKfile and ctFile in order to do so.
//Inputs: ctFile name, shift amount, technically BKfile too
//Output: encrypted text in CTfile
void ctControl(string ctFile, int key){
        fstream fin; 
        fileOpen(fin, BKfile, 'r');
        fstream fout;
        fileOpen(fout, ctFile, 'w');

        char current;
        while(fin.peek() != EOF){
            if(fin.peek() != '\n'){
                current = fin.get();
                current = encrypt(current, key);
                fout << current;
            }
            else{
                fout << endl;
                fin.get();
            }
        }
        fin.close();
        fout.close();
}

//This function sends encrypted characters to be decrypted by decrypt
//It opens ctFile, dcFile in order to do so.
//Inputs: ctFile name, dcFile name, shift amount
//Outputs: decrypted text in dcFile
void dcControl(string ctFile, string dcFile, int key){
        fstream fin; 
        fileOpen(fin, ctFile, 'r');
        fstream fout;
        fileOpen(fout, dcFile, 'w');

        char current;
        while(fin.peek() != EOF){
            if(fin.peek() != '\n'){
                current = fin.get();
                current = decrypt(current, key);
                fout << current;
            }
            else{
                fout << endl;
                fin.get();
            }
        }
        fin.close();
        fout.close();
}

//keyGen outputs a key between 1 and 25 to the keyFile file.
//Input: keyFile 
//Output: Rand to keyFile file
void keyGen(string keyFile){
    srand(time(NULL));
    int shift = (rand() % 25) + 1;
    fstream fout;
    fileOpen(fout, keyFile, 'w');
    fout << shift;
    fout.close();
}

//This returns the previously written key from keyFile. I wrote
//this to declutter main.
//Input: keyFile 
//Output: returns int to function that calls it
int keyRead(string keyFile){
    fstream fin;
    fileOpen(fin, keyFile, 'r');
    string temp;
    getline(fin, temp);
    int key = stoi(temp);
    fin.close();
    return key;
}

//This function encrypts a character through the ceaser cipher.
//Input: char, shift amout
//Output: Returns encrypted char to calling function
char encrypt(char ch, int key){
    if(isalpha(ch)){
        int pos = ch - 'A';
        pos = ((pos + key) % 26);
        ch = pos + 'A';
        return ch;
    }
    else{
        return ch;
    }
}

//This function decrypts a character through the ceaser cipher.
//Input: encrypted char, shift amount
//Output: Returns decrypted char to calling function
char decrypt(char ch, int key){
    if(isalpha(ch)){
        int pos = ch - 'A';
        pos = ((pos - key + 26) % 26);
        ch = pos + 'A';
        return ch;
    } 
    else{
        return ch;
    }
}

//This function turns a plaintext file to a blocktext one in 50 char
//chunks. It removes spaces, punctuation, and uppercases all letters
//Input: PlainTextfile
//Output: Puts the blocktext into BKfile. BKfile is a constant
void toBlock(string PTfile){
    fstream fin;
    fileOpen(fin, PTfile, 'r');
    fstream fout;
    fileOpen(fout, BKfile, 'w');
    string charBlock;
    char current;

    while(fin.peek() != EOF){
        current = fin.get();
        if(isalpha(current) && (!remove(current))){
            charBlock += toupper(current);
        }
        else if(isdigit(current)){
            charBlock += current;
        }
        if(charBlock.length() == 50){
            fout << charBlock << endl;
            charBlock = "";
        }
    }
    fout << charBlock << endl;
    fout.close();
    fin.close();
}

bool remove(char ch){
    if(ispunct(ch) || (ch == '\n')){
        return true;        
    }
    else{
        return false;
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
