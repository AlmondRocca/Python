import string
import re
import matplotlib.pyplot as plt
import math
#I am aware that this code is really hard to read and kinda weirdly written but this
#is a practice program so I will not be fixing it.


def main():
    #This clears the file so i dont keep adding stuff
    temp = open('tokenized', 'w')
    temp.write('')

    textIn = open('middlemarch', 'r',)
    #This took me a long time to figure out but the middlemarch book is not actually in UTF-8. I dont know
    #what its in but it broke everything. It works on my laptop for some reason tho.
    #return codecs.charmap_decode(input,self.errors,decoding_table)[0]
    #UnicodeDecodeError: 'charmap' codec can't decode byte 0x9d in position 6993: character maps to <undefined>
    textOut = open('tokenized', 'a')
    cleanData(textIn, textOut)

    textIn.close()
    textOut.close()

    processToDict()



def cleanData(textIn, textOut):
    for line in textIn:
        toProcess = line
        toProcess = removePunc(toProcess)
        textOut.write(toProcess)



def removePunc(str):
    #These goofy characters were in the middlemarch text. real annoying to deal with
    punc = string.punctuation + '“' + '—'
    #maketrans makes a translation table. 1st two inputs replace something with something else
    #'a' -> 'b'. The last input replaces anything in that string.
    #translate just calls the table
    removed = str.translate(str.maketrans("", "", punc))
    #The re.sub's arent needed but you use them and I felt like learning them
    removed = re.sub('\n', ' ', removed)
    removed = re.sub('\t', ' ', removed)
    return removed



def processToDict():
    tokensToDict = open('tokenized', 'r')
    clearFile = open('finalcount', 'w')
    clearFile.write("")
    clearFile.close()
    processedFile = open('finalcount', 'a')
    wordDict = {}


    #This is the type of thing I was taught to do in java with scanners. Is there a better way?
    for line in tokensToDict:
        listOfWords = line.split()
        for word in listOfWords:
            if word in wordDict:
                wordDict[word] += 1
            else:
                wordDict[word] = 1

    #.items takes the key value pairs in a dictionary and turns them into a list of tuples.
    #Each tuple has a key string and a value string. It then uses sorted to sort the dict.
    #This would sort by key instead of value so I use the key= thing which is a part of sort
    #This determines what it will be sorted by. I then add an anonymous function that
    #takes in a tuple from the items thing and returns the tuple[1] which is the key
    #This is still really hard for me to do quickly but I get the concept.
    #Because I made it so complex I may as well reverse it so the most frequent word
    #is put at the beginning.
    sortedByVal =  dict(sorted(wordDict.items(), key=lambda v : v[1], reverse = True))

    #yucky list comprehension way. I think I need the key, value otherwise
    #it grabs the tuple to i. Is there any way to specify this?
    x = [math.log(i+1) for i, (key, value) in enumerate(sortedByVal.items())]
    y = [math.log(value) for key, value in sortedByVal.items()]
    graphZipf(x, y)

    #normal human way
    #for i, (key, value) in enumerate(sortedByVal.items()):
    #    x.append(i)
    #    y.append(value)

    for key, value in sortedByVal.items():
        processedFile.write('%s: %d\n' % (key, value))
    
    tokensToDict.close()
    processedFile.close()

def graphZipf(x,y):
    plt.plot(x, y) #takes lists!

    plt.show()

main()