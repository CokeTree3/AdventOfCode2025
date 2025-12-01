
def half_1(inp):
    dialPos = 50
    countAtZero = 0

    for line in inp:
        line = line.strip()
        dir = line[0]
        count = int(line[1:])

        if(dir == "R"):
            while count > 0:
                dialPos += 1
                if(dialPos == 100):
                    dialPos = 0
                count -= 1
        elif(dir == "L"):
            while count > 0:
                dialPos -= 1
                if(dialPos == -1):
                    dialPos = 99
                count -= 1
        if(dialPos == 0):
            countAtZero += 1

    return countAtZero

def half_2(inp):
    dialPos = 50
    countAtZero = 0

    for line in inp:
        line = line.strip()
        dir = line[0]
        count = int(line[1:])

        if(dir == "R"):
            while count > 0:
                dialPos += 1
                if(dialPos == 100):
                    dialPos = 0

                if(dialPos == 0):
                    countAtZero += 1
                count -= 1
        elif(dir == "L"):
            while count > 0:
                dialPos -= 1
                if(dialPos == -1):
                    dialPos = 99

                if(dialPos == 0):
                    countAtZero += 1
                count -= 1

    return countAtZero


inpFile = open("input.txt", "r")
inp = inpFile.readlines()

print("Answer to Part 1:", half_1(inp))
print()
print("Answer to Part 2:", half_2(inp))

