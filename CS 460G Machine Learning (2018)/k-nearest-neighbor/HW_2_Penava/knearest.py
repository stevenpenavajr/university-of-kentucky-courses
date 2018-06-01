'''
- Steven Penava
- Homework 2
- CS 460G
- 02/19/2018
'''

# Imports
from math import sqrt

# Imports training data file and returns data in dictionary of dictionaries
def importBase():
    baseFile = open("u1-base.base")
    firstLine = baseFile.readline()
    firstLineArr = firstLine.split('\t')[0:3]

    tempKey = int(firstLineArr[0])
    tempDict = {}
    outerDict = {}
    tempDict[int(firstLineArr[1])] = int(firstLineArr[2]) # handle file position

    for fileLine in baseFile:
        line = fileLine.split('\t')[0:3]
        if (int(line[0]) == tempKey):
            tempDict[int(line[1])] = int(line[2])
        else:
            outerDict[tempKey] = tempDict
            tempDict = {}
            tempKey = int(line[0])
            tempDict[int(line[1])] = int(line[2])
    outerDict[tempKey] = tempDict
    baseFile.seek(0, 0)
    return outerDict

# Returns a normalized similarity value between 0 and 1
def calculateSimilarity(user1, user2):
    sumSquares = 0.0
    result = 0

    u1MoviesSet = set(user1.keys())
    u2MoviesSet = set(user2.keys())

    moviesIn1Not2 = u1MoviesSet - u2MoviesSet
    moviesIn2Not1 = u2MoviesSet - u1MoviesSet

    for movie in moviesIn1Not2:
        user2[movie] = 0
    for movie in moviesIn2Not1:
        user1[movie] = 0

    for movie in user1.keys():
        diff = user1[movie] - user2[movie]
        sumSquares += diff * diff

    result = sqrt(sumSquares)
    normalizedResult = 1 / (1 + result)

    return normalizedResult

# Returns list of tuples
def getSimilarities(relUsers, userToPredict, trainingData):
    similarities = []
    for indivUser in trainingData:
        if indivUser in list(relUsers):
            if (userToPredict != indivUser):
                sim = calculateSimilarity(trainingData[userToPredict], trainingData[indivUser])
                similarities.append((sim, indivUser))
    return similarities

# Returns prediction given a user, movie, and k-value
def predict(movieToPredict, userToPredict, trainingData, K, moviesToUsers):
    try:
        topK = sorted(getSimilarities(moviesToUsers[movieToPredict], userToPredict, trainingData), reverse=True)[:K]
        total = 0.0
        for i in range(len(topK)):
            total += topK[i][0] * trainingData[topK[i][1]][movieToPredict]

        average = 0
        simSums = 0.0
        if len(topK) != 0:
            for i in range(len(topK)):
                simSums += topK[i][0]
            average = total / simSums

        return average
    except:
        return 0.0

# Returns dictionary of movies to users to narrow down the similarity list before run
def getRelUsers(baseFile):
    lines = []
    for line in baseFile:
        line = line.split('\t')
        lines.append(line)

    movies = [int(row[1]) for row in lines]
    moviesSet = set(movies)
    moviesToUsers = {}
    for movie in moviesSet:
        users = []
        for line in lines:
            if line[1] == str(movie):
                users.append(int(line[0]))
        users = set(users)
        moviesToUsers[movie] = users

    return moviesToUsers

def main():
    trainingData = importBase()
    baseFile = open("u1-base.base")

    print("Welcome to the KNN user/movie program.\n")
    print("Pre-computing some data (~30 seconds)...")
    moviesToUsers = getRelUsers(baseFile)

    print("You have a few options of things to do...")
    print("1) Make a singular prediction based on your input with a k-value of 3")
    print("2) Calculate mean squared error for test set with a k-value of 3 (20-30 minutes)")
    print("3) Cross-validate with 5 different k-values (3,4,7,8,10) using leave-one-out (~5-6 hours)")
    print("4) Print cross validation and test set error results\n")

    selection = input("Enter your selection: ")

    if selection == '1':
        u = ''
        m = ''
        while u != 'q' or m != 'q':
            try:
                u = int(input("Enter a user number ('q' to quit): "))
                m = int(input("Enter a movie number ('q' to quit): "))
                prediction = predict(m, u, trainingData, 3, moviesToUsers)
                print("Prediction result (if it is 0, movie didn't exist in training set):", str(prediction))
            except:
                u = 'q'
                m = 'q'

    if selection == '2':
        print("Running mean squared error on test set...")
        testFile = open("u1-test.test")
        lineCount = 0
        msqError = 0.0
        for line in testFile:
            datum = line.split('\t')[0:3]
            lineCount += 1
            msqError += ((int(datum[2]) - predict(int(datum[1]), int(datum[0]), trainingData, 3, moviesToUsers)) ** 2)

        multiplier = 1.0 / lineCount
        msqError = multiplier * msqError
        baseFile.seek(0, 0)
        print("Mean squared error for test set: " + str(msqError))

    if selection == '3':
        trainingData = importBase()
        baseFile = open("u1-base.base")
        baseFile.seek(0, 0)

        kVals = [3, 4, 7, 8, 10]
        for i in range(len(kVals)):
            lineCount = 0
            msqError = 0.0
            for line in baseFile:
                datum = line.split('\t')[0:3]
                lineCount += 1
                msqError += ((int(datum[2]) - predict(int(datum[1]), int(datum[0]), trainingData, kVals[i], moviesToUsers)) ** 2)
            baseFile.seek(0, 0)
            multiplier = 1.0/lineCount
            msqError = multiplier * msqError
            print("Error for k value " + str(kVals[i]) + ": " + str(msqError))

    if selection == '4':
        print("Test set mean squared error: 1.464")
        print()
        print("Leave-one-out mean squared error (K = 3): 1.305")
        print("Leave-one-out mean squared error (K = 4): 1.224")
        print("Leave-one-out mean squared error (K = 7): 1.118")
        print("Leave-one-out mean squared error (K = 8): 1.104")
        print("Leave-one-out mean squared error (K = 10): 1.081")
        print()
        print("Average mean squared error: 1.166")


if __name__ == "__main__":
    main()
