def main():
    cont = ""
    while cont.lower() != "n": 
        tmp = input("Input a temperature to convert ")
        unit = input("Would you like to convert to C or F? (type C or F) ")
        convert(float(tmp), unit)
        cont = input("Would you like to continue? y/n ")
        print()



def convert(tmp, unit):
    #Make sure inputs are ok
    try: 
        int(tmp)
    except:
        print("Temperature was not a number, please try again")
        return
    
    #Convert F to C or C to F. I use str() because you cant print a float and str
    if unit.upper() == 'C':
        print(str(((tmp - 32) * 5/9)) + " degrees C")
        return
    elif unit.upper() == 'F':
        print(str(((tmp * 9/5) + 32)) + " degrees F")
        return
    print("Unit was not C or F, please try again")


main()