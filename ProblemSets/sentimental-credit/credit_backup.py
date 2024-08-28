import math
import ast


def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            pass


def main():
    inputNumber = get_int("Number: ")

    inputNumberlen = len(str(inputNumber))
    firstOne = int(str(inputNumber)[0:1])
    firstTwo = int(str(inputNumber)[0:2])

    if checksum(inputNumber, inputNumberlen):
        if inputNumberlen == 15 and firstTwo in [34, 37]:
            print("AMEX")
        elif inputNumberlen == 16 and (firstTwo in [51, 52, 53, 54, 55]):
            print("MASTERCARD")
        elif (inputNumberlen == 13 or inputNumberlen == 16) and firstOne == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def checksum(inputNumber, inputNumberlen):

    stringSingle = ""
    stringDouble = ""

    if inputNumberlen % 2 == 0:
        for i in range(math.ceil(inputNumberlen/2)):
            stringDouble += str(2*int(str(inputNumber)[i*2]))
            stringSingle += str(int((str(inputNumber)[i*2+1])))
    else:
        for i in range(math.floor(inputNumberlen/2)):
            stringDouble += str(2*int(str(inputNumber)[i*2+1]))
        for i in range(math.ceil(inputNumberlen/2)):
            stringSingle += str(int((str(inputNumber)[i*2])))

    # convert the strings elementwise to array of ints and sum
    total = sum([int(x) for x in stringSingle]) + sum([int(x) for x in stringDouble])

    if total % 10 == 0:
        return True


main()
