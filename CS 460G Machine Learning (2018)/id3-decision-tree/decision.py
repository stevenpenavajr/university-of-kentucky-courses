# Steven Penava
# Dr. Brent Harrison
# CS 460G
# 02/07/18

# ------- IMPORTS
import csv
#from pprint import pprint ---- use this for better printing of tree
import math
from collections import abc

# ------- PREPARING DATA (READERS)
s1 = open('synthetic-1.csv', newline='')
s1r = csv.reader(s1)

s2 = open('synthetic-2.csv', newline='')
s2r = csv.reader(s2)

s3 = open('synthetic-3.csv', newline='')
s3r = csv.reader(s3)

s4 = open('synthetic-4.csv', newline='')
s4r = csv.reader(s4)

vG = open('Video_Games_Sales.csv', newline='')
vGr = csv.reader(vG)

# Getting a column in float form (should've used the python trick...)
def getColumn(dataList, cNum):
    column = []
    for i in range(len(dataList)):
        column.append(float(dataList[i][cNum]))
    return column

# Checks if a string is a number (for use in categorizing data)
def isNumber(stringNum):
    try:
        float(stringNum)
        return True
    except ValueError:
        return False

# Initially convert to Rainy, Sunny, Overcast, etc...
def discretizeContinuous(dataSet, numBins, labels, cNum):
    maxNum = max(getColumn(dataSet, cNum))
    minNum = min(getColumn(dataSet, cNum))
    numRange = maxNum - minNum

    splitSize = float(numRange / numBins)

    ranges = []
    ranges.append(minNum)
    for i in range(numBins - 1):
        ranges.append(minNum + splitSize * (i + 1))
    ranges.append(maxNum)

    for i in range(len(ranges) - 1):
        for item in dataSet:
            if (isNumber(item[cNum])):
                firstItem = float(item[cNum])
                if firstItem >= ranges[i] and firstItem < ranges[i+1]:
                    item[cNum] = labels[i]
                if firstItem == maxNum and i == numBins - 1:
                    item[cNum] = labels[i]

    labelsAndRanges = {}
    for i in range(numBins):
        # labels[i] falls between ranges[i] and ranges[i+1]
        labelsAndRanges[labels[i]] = [ranges[i],ranges[i+1]]



# Get entropy of a set of data (can be applied to whole data set or
def getEntropy(dataSet):

    # Handling more than just "0s" and "1s"
    lastColumnIndex = len(dataSet[0]) - 1
    lastColumn = [row[lastColumnIndex] for row in dataSet]
    totalElements = len(lastColumn)
    counts = []
    uniquesOnly = list(set(lastColumn))

    # Getting a counts array corresponding to unique elements (counts corresponds to uniquesOnly)
    for i in range(len(uniquesOnly)):
        tempCount = 0
        for k in range(len(dataSet)):
            if dataSet[k][lastColumnIndex] == uniquesOnly[i]:
                tempCount += 1
        counts.append(tempCount)

    # Calculating actual entropy value
    ent = 0.0
    for m in range(len(counts)):
        if counts[m] != 0:
            ent += -1 * ((counts[m]/totalElements) * math.log((counts[m]/totalElements), 2))

    return ent

# Return list of info gains corresponding to attributes/columns?
def getInfoGains(dataSet, attributes, classEntropy, avoid):

    gains = []
    for i in range(len(attributes) - 1): # Loop through all attributes except the last (last is class label)
        count = {}
        containers = {}
        for j in range(len(dataSet)):
            if dataSet[j][i] not in count.keys(): # dataSet[j][i] is "rainy", "overcast", etc...
                count[dataSet[j][i]] = 0 # count(rainy) = 0
                containers[dataSet[j][i]] = [] # containers(rainy) = [] if rainy, overcast, etc not in keys list in dictionary, make it a key and give its value []
            count[dataSet[j][i]] += 1 # adding one to count of rainy
            containers[dataSet[j][i]].append(dataSet[j]) # containers(rainy) = [ [1,2,3], [4,5,6] ]

        entropy = 0.0

        for k in count.keys():
            prob = count[k] / len(dataSet) ###
            entropy += prob * getEntropy(containers[k]) # containers[rainy] = [[1,2,3][4,5,6]]

        gain = classEntropy - entropy
        gains.append(gain)

    for i in range(len(gains)): # originally was - 1
        if i in avoid:
            gains[i] = -1000

    return gains

# ID3 function
def id3(dataSet, attributes, depth, avoid, tree):
    if (depth == 3):
        if(len(dataSet) > 0):
            if getEntropy(dataSet) == 0:
                answer = dataSet[0][len(dataSet[0])-1] # the last column value (all the same with entropy 0.0)
                tree[attributes[-1]] = answer
                # answer is LEAF here
            else:
                # must guess here
                lastColumnIndex = len(dataSet[0]) - 1
                lastColumn = [row[lastColumnIndex] for row in dataSet]
                totalElements = len(lastColumn)
                counts = []
                uniquesOnly = list(set(lastColumn))
                for i in range(len(uniquesOnly)):
                     tempCount = 0
                     for k in range(len(dataSet)):
                         if dataSet[k][lastColumnIndex] == uniquesOnly[i]:
                             tempCount += 1
                     counts.append(tempCount)
                majorityIndex = counts.index(max(counts))
                answer = uniquesOnly[majorityIndex]
                tree[attributes[-1]] = answer
                # answer is LEAF here

        # reached depth 3 here
    else:

        classLabelEntropy = getEntropy(dataSet)
        infoGains = getInfoGains(dataSet, attributes, classLabelEntropy, avoid)
        maxGainIndex = infoGains.index(max(infoGains))

        if max(infoGains) <= 0:
            lastColumnIndex = len(dataSet[0]) - 1
            lastColumn = [row[lastColumnIndex] for row in dataSet]
            totalElements = len(lastColumn)
            counts = []
            uniquesOnly = list(set(lastColumn))
            for i in range(len(uniquesOnly)):
                tempCount = 0
                for k in range(len(dataSet)):
                    if dataSet[k][lastColumnIndex] == uniquesOnly[i]:
                        tempCount += 1
                counts.append(tempCount)
            majorityIndex = counts.index(max(counts))
            answer = uniquesOnly[majorityIndex]
            tree[attributes[-1]] = answer
            # answer is LEAF here

            return

        tree[attributes[maxGainIndex]] = {}

        count = {}
        containers = {}

        for j in range(len(dataSet)):
            if dataSet[j][maxGainIndex] not in count.keys():
                count[dataSet[j][maxGainIndex]] = 0
                containers[dataSet[j][maxGainIndex]] = []
            count[dataSet[j][maxGainIndex]] += 1
            containers[dataSet[j][maxGainIndex]].append(dataSet[j])
        if maxGainIndex not in avoid:
            avoid.append(maxGainIndex)
        i = 0
        depth += 1
        for k in containers.keys():
            i += 1
            tree[attributes[maxGainIndex]][k] = {}
            id3(containers[k], attributes, depth, avoid, tree[attributes[maxGainIndex]][k])


def printPrediction(tree, attrVals):
    if 'playOrNot' in tree.keys():
        return tree['playOrNot']
    subKeys = tree[list(tree.keys())[0]]
    for i in attrVals:
        if i in subKeys:
            return printPrediction(subKeys[i], attrVals)

def printPrediction2(tree, attrVals):
    if 'Critic_Score' in tree.keys():
        return tree['Critic_Score']
    subKeys = tree[list(tree.keys())[0]]
    for i in attrVals:
        if i in subKeys:
            return printPrediction2(subKeys[i], attrVals)

def calculateError(dataSet, tree):
    correct = 0
    for i in range(len(dataSet)):
        temp = []
        result = dataSet[i][-1]
        for k in range(len(dataSet[i]) - 1):
            temp.append(dataSet[i][k])
        pred = printPrediction(tree, temp)
        if pred == result:
            correct += 1

    error = (float(len(dataSet)) - correct) / float(len(dataSet))

    return error

def calculateError2(dataSet, tree):
    correct = 0
    for i in range(len(dataSet)):
        temp = []
        result = dataSet[i][-1]
        for k in range(len(dataSet[i]) - 1):
            temp.append(dataSet[i][k])
        pred = printPrediction2(tree, temp)
        if pred == result:
            correct += 1

    error = (float(len(dataSet)) - correct) / float(len(dataSet))

    return error

def main():
    print("Welcome to the CS 460 HW1 Program.\n")
    print("Data is discretized into TWO bins.")
    syntheticFileName = input("Enter the filename of the data set to classify: ")
    syntheticFile = open(syntheticFileName, newline='')
    syntheticReader = csv.reader(syntheticFile)
    trainingSet = list(syntheticReader)

    # Possible labels for synthesized data
    labelsA = ['rainy', 'sunny', 'clear', 'overcast', 'snowy']
    labelsB = ['50s', '60s', '70s', '80s', '90s']

    # Attributes for synthetic data set
    syntheticAttributes = ['weather', 'temp', 'playOrNot']

    # Attributes for video game data
    vgAttributes = ['Platform' ,'Year_of_Release','Genre','Publisher','NA_Sales','EU_Sales','JP_Sales','Other_Sales','Global_Sales','Developer','Rating','Critic_Score']

    # Number of bins to create (1 to 5, no more unless labelsA and labelsB are appended...) - can change if you like
    initialBinCount = 2

    # Array to store attributes we've already visited
    avoid = []

    # Actual tree that is stored as nested dictionaries
    decisionTree = {}

    # If operating on a synthetic data set, discretize...
    if "synthetic" in syntheticFileName:
        # Assigning categories to each column in the set
        discretizeContinuous(trainingSet, initialBinCount, labelsA, 0)
        discretizeContinuous(trainingSet, initialBinCount, labelsB, 1)
        id3(trainingSet, syntheticAttributes, 1, avoid, decisionTree)  # synthetic data
        searchValuesList = []
        searchValue = ''


        while searchValue != "stop":
            searchValue = (input("Enter a value for prediction ('stop' to stop): "))
            if (searchValue != "stop"):
                searchValuesList.append(searchValue)
        print()
        print("Making prediction...")
        print("If the day has the qualities of ", end='')
        for i in range(len(searchValuesList)):
            if i == len(searchValuesList) - 1:
                print(searchValuesList[i],"...")
            else:
                print(searchValuesList[i] + ", ", end='')
        print("Then my guess is",printPrediction(decisionTree, searchValuesList))
        print()
        print("Training set error:", calculateError(trainingSet, decisionTree))
    else:
        id3(trainingSet[1:], vgAttributes, 1, avoid, decisionTree) # video game data

        searchValuesList = []
        searchValue = ''

        while searchValue != "stop":
            searchValue = (input("Enter a value for prediction ('stop' to stop): "))
            if (searchValue != "stop"):
                searchValuesList.append(searchValue)
        print()
        print("Making prediction...")
        print("If the video game has the qualities of ", end='')
        for i in range(len(searchValuesList)):
            if i == len(searchValuesList) - 1:
                print(searchValuesList[i],"...")
            else:
                print(searchValuesList[i] + ", ", end='')
        print("Then my guess is", printPrediction2(decisionTree, searchValuesList))
        print()
        print("Training set error:", calculateError2(trainingSet[1:], decisionTree))

    print("--")
    printTreeOrNot = input("Enter 'yes' to print tree (pretty print is recommended). Otherwise, hit enter to quit: ")
    if printTreeOrNot == "yes":
        pprint(decisionTree)
        print("--")
    else:
        print("Goodbye.")




main()