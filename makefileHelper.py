#!/usr/bin/env python3

raise Exception("Dont use this code")

import os

start = 'CC = gcc\nCFLAGS = -Wall -pedantic -O -std=c99\nLDLIBS = -lm\n# add $(LDLIBS) for math\n'

def evaluateFolder(folder: str):# -> (list, str):
    files = filter(lambda x: x.endswith('.c'), os.listdir(folder))

    allObjectFiles = []
    text = ''

    for fName in files:
        f = open(f'{folder}/{fName}', 'r')
        includes = map(lambda x: x.split('"')[1], filter(lambda x: x.startswith('#include "'), f.read().split('\n')))

        dependencies = ' '.join(map(lambda x: os.path.relpath(f'{folder}/{x}'), includes))
        tmp = fName.rsplit('.', 1)[0] + '.o'
        objectName = os.path.relpath(f'{folder}/{tmp}')

        allObjectFiles.append(objectName)

        fNamePath = os.path.relpath(f'{folder}/{fName}')

        text += f'{objectName}: {fNamePath} {dependencies}\n'

        text += '\t' + f'$(CC) $(CFLAGS) $(LDLIBS) -c {fNamePath} -o {objectName}\n'
        text += '\n'
        
        f.close()
    
    return allObjectFiles, text

if __name__ == '__main__':
    f = open('Makefile', 'w')
    f.write(start)
    f.write('\n')

    example = 'all: spirals/tiffReader.o\n\t$(CC) -o main spirals/tiffReader.o'

    allObjectFiles, text = evaluateFolder('dataTypes')
    tmpObjectFiles, tmpText = evaluateFolder('.')

    allObjectFiles += tmpObjectFiles
    text += tmpText

    f.write('all: ' + ' '.join(allObjectFiles) + '\n')
    f.write('\t$(CC) -o main ' + ' '.join(allObjectFiles) + '\n')
    f.write('\n')

    #f.write('main.o: main.c\n\t$(CC) $(CFLAGS) $(LDLIBS) -c main.c main.o\n\n')

    f.write(text)

    f.write('clean:\n\trm *.o dataTypes/*.o main\n\n')

    f.close()

