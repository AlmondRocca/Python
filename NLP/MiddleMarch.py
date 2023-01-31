import string
import re

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
    wordDict = {}
    #This is the type of thing I was taught to do in java with scanners. Is there a better way?
    for line in tokensToDict:
        listOfWords = line.split()
        for word in listOfWords:
            if word in wordDict:
                wordDict[word] += 1
            else:
                wordDict[word] = 1
    #How do i display this pretty
    print(wordDict)


main()