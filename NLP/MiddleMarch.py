import string

def main():
    textIn = open('middlemarch', 'r')
    temp = open('tokenized' 'w')
    temp.write("")
    temp.close()
    textOut = open('tokenized', 'a')
    cleanData(textIn, textOut)



def cleanData(textIn, textOut):
    for line in textIn:
        toProcess = line
        str(toProcess)
        toProcess = removePunc(toProcess)
        textOut.write(toProcess)



def removePunc(str):
    punc = string.punctuation + '“' + '—'
    removed = str.translate(str.maketrans("", "", punc))
    return removed



def 
main()