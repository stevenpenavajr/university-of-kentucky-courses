'''
Steven Penava
CS 460G: Homework #5
Naive Bayes Text Classification
04/09/2018
'''

# IMPORTS
import numpy as np
import pprint as pp
import re
import math
from collections import Counter

PSEUDOCOUNT_INCREMENT = .001

# Class log probability for each class (all 1/4)
CLASS_P = math.log(0.25, 10)

# MAIN
def main():

    # Raw training data
    hamletFile   = open("Data/Training Files/hamlet_train.txt", "r")
    hamletLines  = hamletFile.readlines()

    julietFile   = open("Data/Training Files/juliet_train.txt", "r")
    julietLines  = julietFile.readlines()

    macbethFile  = open("Data/Training Files/macbeth_train.txt", "r")
    macbethLines = macbethFile.readlines()

    romeoFile    = open("Data/Training Files/romeo_train.txt", "r")
    romeoLines   = romeoFile.readlines()

    # Raw test data
    hamletTestFile   = open("Data/Testing Files/hamlet_test.txt", "r")
    hamletTestLines  = hamletTestFile.readlines()

    julietTestFile   = open("Data/Testing Files/juliet_test.txt", "r")
    julietTestLines  = julietTestFile.readlines()

    macbethTestFile  = open("Data/Testing Files/macbeth_test.txt", "r")
    macbethTestLines = macbethTestFile.readlines()

    romeoTestFile    = open("Data/Testing Files/romeo_test.txt", "r")
    romeoTestLines   = romeoTestFile.readlines()

    # Bags of words (still have duplicates here)
    hamletBOW   = getBagOfWords(hamletLines) # still has duplicates here
    julietBOW   = getBagOfWords(julietLines)
    macbethBOW  = getBagOfWords(macbethLines)
    romeoBOW    = getBagOfWords(romeoLines)

    # Counters for bags of words (no duplicates --> (word, count))
    hamletC  = Counter(hamletBOW)
    julietC  = Counter(julietBOW)
    macbethC = Counter(macbethBOW)
    romeoC   = Counter(romeoBOW)

    # Unigram testing
    hamletTestLinesU = repairTestLines(hamletTestLines)
    julietTestLinesU = repairTestLines(julietTestLines)
    macbethTestLinesU = repairTestLines(macbethTestLines)
    romeoTestLinesU = repairTestLines(romeoTestLines)

    # Report unigram accuracies
    print("=====================")
    print("Report for unigram method accuracy:")
    testLines = [hamletTestLinesU, julietTestLinesU, macbethTestLinesU, romeoTestLinesU]
    charTokenCounts = [hamletC, julietC, macbethC, romeoC]
    charWordCounts = [len(hamletBOW), len(julietBOW), len(macbethBOW), len(romeoBOW)]
    reportAccuracies(testLines, charTokenCounts, charWordCounts)
    print("=====================")

    # Report bigram accuracies
    print("Report for bigram method accuracy:")
    hamletBigramBOW = getBigramBagOfWords(hamletLines)
    julietBigramBOW = getBigramBagOfWords(julietLines)
    macbethBigramBOW = getBigramBagOfWords(macbethLines)
    romeoBigramBOW = getBigramBagOfWords(romeoLines)

    hamletBC  = Counter(hamletBigramBOW)
    julietBC  = Counter(julietBigramBOW)
    macbethBC = Counter(macbethBigramBOW)
    romeoBC   = Counter(romeoBigramBOW)

    # Bigram testing
    hamletTestLinesB = repairBigramTestLines(hamletTestLines)
    julietTestLinesB = repairBigramTestLines(julietTestLines)
    macbethTestLinesB = repairBigramTestLines(macbethTestLines)
    romeoTestLinesB = repairBigramTestLines(romeoTestLines)

    testLinesB = [hamletTestLinesB, julietTestLinesB, macbethTestLinesB, romeoTestLinesB]
    charTokenCountsB = [hamletBC, julietBC, macbethBC, romeoBC]
    charWordCountsB = [len(hamletBigramBOW), len(julietBigramBOW), len(macbethBigramBOW), len(romeoBigramBOW)]
    reportAccuracies(testLinesB, charTokenCountsB, charWordCountsB)
    print("=====================")

def repairBigramTestLines(testLines):
    new = []
    for line in testLines:
        line = line.split(' ')[:-1]
        bigram = ""
        c = 0
        lineArr = []
        for word in line:
            if (c == 1):
                bigram += word
                lineArr.append(bigram)
                bigram = ""
                c = 0
            bigram += word + " "
            c += 1
        new.append(lineArr)
    return new

def getBigramBagOfWords(lines):
    bag = []
    for line in lines:
        line = line.split(' ')[:-1]
        bigram = ""
        c = 0
        for word in line:
            if (c == 1):
                bigram += word
                bag.append(bigram)
                bigram = ""
                c = 0
            bigram += word + " "
            c += 1
    return bag

# REPORT ACCURACIES USING UNIGRAM METHOD
def reportAccuracies(testLines, tokenCounts, wordCounts):
    # hamlet, juliet, macbeth, romeo
    names = ["Hamlet accuracy:  ", "Juliet accuracy:  ", "Macbeth accuracy: ", "Romeo accuracy:   "]
    totalCorrect = 0
    totalLineCount = len(testLines[0]) + len(testLines[1]) + len(testLines[2]) + len(testLines[3])
    for i in range(4):
        numCorrect = 0
        for sentence in testLines[i]:
            hF = CLASS_P + getLogSummationProb(sentence, tokenCounts[0], wordCounts[0])
            jF = CLASS_P + getLogSummationProb(sentence, tokenCounts[1], wordCounts[1])
            mF = CLASS_P + getLogSummationProb(sentence, tokenCounts[2], wordCounts[2])
            rF = CLASS_P + getLogSummationProb(sentence, tokenCounts[3], wordCounts[3])
            result = [hF, jF, mF, rF]
            maxIndex = result.index(max(result))
            if maxIndex == i:
                numCorrect += 1
                totalCorrect += 1
        percentageCorrect = round(numCorrect/len(testLines[i]) * 100, 3)
        print(names[i] + str(percentageCorrect) + "%")
    print()
    print("Total accuracy:   " + str(round((totalCorrect/totalLineCount) * 100, 3)) + "%")

# GET PROBABILITIES USING LOGARITHMS
def getLogSummationProb(sentence, charWords, n):
    sum = 0.0
    for word in sentence:
        sum += math.log((charWords[word] + PSEUDOCOUNT_INCREMENT)/(n + (PSEUDOCOUNT_INCREMENT * len(sentence))), 10)
    return sum

# TAKE <eol> OUT OF TEST LINES AND REMOVE SYMBOLS
def repairTestLines(lines):
    new = []
    for line in lines:
        line = line.split(' ')[:-1]
        line = removeSymbolsFrom(line)
        new.append(line)
    return new

# GET BAG OF WORDS (WITH DUPLICATES)
def getBagOfWords(lines):
    bag = []
    for line in lines:
        line = line.split(' ')[:-1]
        for word in line:
            bag.append(word)
    bag = removeSymbolsFrom(bag)
    return bag

# GETS RID OF "!", ".", "," and "'d", etc.. KEEPS "'tis", etc. as "tis"
# REMOVED SYMBOLS FOR SIMPLIFICATION
def removeSymbolsFrom(bagOfWords):
    newBag = []
    for word in bagOfWords:
        if (word.isalpha() == False): # keep words like 'tis or 'there
            word = word[1:]
            if len(word) > 1:
                newBag.append(word)
        else:
            newBag.append(word)
    return newBag

# RUN DRIVER
if __name__ == '__main__':
    main()