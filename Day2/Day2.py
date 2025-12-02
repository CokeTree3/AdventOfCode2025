import re

def half_1(inp):
    ranges = inp.split(',')
    IdSum = 0

    for r in ranges:
        startString,endString = r.split('-')
        start = int(startString)
        end = int(endString)

        currentNum = start

        if(len(startString) % 2 != 0):
            if(len(endString) == len(startString)):
                continue
            
            currentNum = pow(10, len(startString))

        while(currentNum <= end):
            curNumString = str(currentNum)
            first = int(curNumString[:len(curNumString)//2])
            sec = int(curNumString[len(curNumString)//2:])

            if(len(str(sec)) != len(curNumString)//2):
                sec = pow(10, len(curNumString) // 2 - 1)
                currentNum = int(str(first) + str(sec)) 
                continue

            if(first == sec):
                IdSum += int(str(first) + str(sec)) 

            if(first > sec):
                sec += 1
            elif(first < sec):
                if(int(str(first) + str(first)) > start):
                    sec = first
                else:
                    first += 1
            else:
                first += 1
                sec += 1
            
            currentNum = int(str(first) + str(sec)) 
        
    return IdSum

def half_2(inp):
    ranges = inp.split(',')
    IdSum = 0

    for r in ranges:
        startString,endString = r.split('-')
        start = int(startString)
        end = int(endString)

        reg = r"(.+)\1+"
        currentNum = start

        while(currentNum <= end):
            m = re.fullmatch(reg, str(currentNum))
            if(m):
                IdSum += int(m[0])
            
            currentNum += 1

    return IdSum


inpFile = open("input.txt", "r")
inp = inpFile.read()

print("Answer to Part 1:", half_1(inp))
print()
print("Answer to Part 2:", half_2(inp))

