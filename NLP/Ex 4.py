import math

def isPrime(num):
    for i in range(2, int(math.sqrt(num))+1):
        if num % i == 0:
            return False
    return True



def display(lowEnd, highEnd):
    primesFound = 0
    for x in range(lowEnd, highEnd):
        if isPrime(x):
            print(x, end='\t')
            primesFound += 1
            if (primesFound % 10 == 0):
                print('\n')



def main():
    print("This program will print all the prime numbers in a specified range")
    lowEnd = input("input low end of the range: ")
    highEnd = input("input high end of the range: ")
    lowEnd = int(lowEnd)
    highEnd = int(highEnd)

    try:
        if (lowEnd <= 0) or (highEnd <= 0) or (highEnd <= lowEnd):
            print("selected numbers do not work. Be sure neither are negative and high end is larger than low end.")
    except:
        print("you did not enter a number, please run again")

    display(lowEnd, highEnd)
main()