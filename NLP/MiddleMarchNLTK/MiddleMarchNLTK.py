import matplotlib.pyplot as plt
import math
import nltk
from nltk.tokenize import word_tokenize


def main():
    #This seems better than the with open thing but I might
    #use with open for something else
    file = open("/home/csuser/Desktop/NLP/MiddleMarchNLTK/middlemarch.txt", "r")
    text = file.read()
    file.close()

    #This is a list
    tokens = word_tokenize(text)

    #With open 'wraps' the thing youre doing. Apparently this
    #auto closes the file when you exit the scope but I'm not
    #sure if im gonna use this.
    with open("tokenized.txt", "w") as file:
        file.write("\n".join(tokens))
    
    processToDict()

def processToDict():
    with open("tokenized.txt", "r") as tokenized:
        wordDict = {}
        for line in tokenized:
            listOfWords = line.split()
            for word in listOfWords:
                if word in wordDict:
                    wordDict[word] += 1
                else:
                    wordDict[word] = 1
    
    sortedByVal =  dict(sorted(wordDict.items(), key=lambda v : v[1], reverse = True))

    #I grab key and value in the first one because I'm unsure how to just get I
    #without python setting it as the tuple
    x = [math.log(i+1) for i, (un, used) in enumerate(sortedByVal.items())]
    y = [math.log(value) for unused, value in sortedByVal.items()]
    graphZipf(x, y)

def graphZipf(x, y):
    plt.plot(x, y)
    plt.show()

main()