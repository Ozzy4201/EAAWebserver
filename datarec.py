import random   
import os

num = random.randint(1, 2147483647)
fileNames = []

def GenNumb():
    file = f"serverData/data{num}.txt"
    return file


def DataRec():
    file_name = GenNumb()
    x = True
    name = f"data{num}.txt"
    variables = (name, file_name)

    f = open("dataFiles.txt", "a")
    f.write("%s\n" % name)



    while x is True:
        if os.path.exists(file_name):
            print("Attempted to create file, but file already existed.")
            file_name = GenNumb()  
        else:
            open(GenNumb(), "x")
            x = False
            return variables
name = DataRec()
