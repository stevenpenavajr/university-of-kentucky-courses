# Steven Penava
# Dr. Brent Harrison
# Homework 4
# 03/20/18

# IMPORTS
import numpy as np

# CONSTANT VALUE(S)
ALPHA = 0.005
EPSILON = 0.00001

# Load file
def getInputFromFile(fName):
    return np.loadtxt(fName, delimiter=',')

# Return sigmoid activation function
def sigmoid(inActivatedNodes):
    return 1.0 / (1.0 + (np.exp(-inActivatedNodes)))

# Get delta values for hidden nodes
def getHiddenDeltas(size, hiddenActivated, weightsHO, outPutDelta):
    deltas = []
    for i in range(size):
        deltas.append(hiddenActivated[i] * (1 - hiddenActivated[i]) * weightsHO[i] * outPutDelta)
    return deltas

# Update weights from hidden to output and input to hidden
def updateWeights(weightsHO, hiddenActivated, weightsIH, hDeltas, individualRow, outputDelta, size):
    for k in range(size):
        weightsHO[k] = weightsHO[k] + ALPHA * hiddenActivated[k] * outputDelta

    for j in range(len(individualRow)):
        for z in range(size):
            weightsIH[j][z] = weightsIH[j][z] + ALPHA * individualRow[j] * hDeltas[z]

# Run against test set to get number of correct guesses
def reportNumCorrect(testData, weightsHO, weightsIH):
    numCorrect = 0

    for m in range(len(testData)):
        hiddenNotActivatedT = np.dot(testData[m][1:], weightsIH)
        hiddenActivatedT = sigmoid(-hiddenNotActivatedT)

        outputNotActivatedT = np.dot(hiddenActivatedT, weightsHO)
        outputActivatedT = sigmoid(-outputNotActivatedT)

        guess = 0
        if (outputActivatedT >= 0.5):
            guess = 1
        if testData[m][0] == guess:
            numCorrect += 1

    return numCorrect

# Run
def main():

    print("Loading files...")
    data = getInputFromFile("data/mnist_train_0_1.csv")
    testData = getInputFromFile("data/mnist_test_0_1.csv")
    print("Files loaded successfully.")

    weightsIH = np.random.uniform(-1, 1, (785,4)) # input to hidden layer weights
    weightsHO = np.random.uniform(-1, 1, (4, 1)) # hidden to output layer weights

    epochNum = 0

    # Inserting a 1.0 for the bias (0th index is the expected answer given in the data, so insert at pos. 1)
    data = np.insert(data, 1, 1.0, axis=1)
    testData = np.insert(testData, 1, 1.0, axis=1)

    while True:
        epochNum += 1

        print("Running Epoch #" + str(epochNum) + "...")

        for i in range(len(data)): # ~12,000
            hiddenNotActivated = np.dot(data[i][1:], weightsIH)
            hiddenActivated = sigmoid(hiddenNotActivated)
            hiddenActivated[0] = 1.0

            outputNotActivated = np.dot(hiddenActivated, weightsHO)
            outputActivated = sigmoid(outputNotActivated)

            outPutError = data[i][0] - outputActivated[0]

            outPutDelta = outPutError * outputActivated[0] * (1 - outputActivated[0])

            hDeltas = getHiddenDeltas(4, hiddenActivated, weightsHO, outPutDelta)

            individualRow = data[i][1:]

            updateWeights(weightsHO, hiddenActivated, weightsIH, hDeltas, individualRow, outPutDelta, 4)

        numCorrect = reportNumCorrect(testData, weightsHO, weightsIH) # run through test data

        percentage = float(numCorrect/len(testData)) * 100

        print("Epoch #" + str(epochNum) + ": " + str(percentage) + "% accurate.")
        print("============")

        if percentage >= 99:
            print("Accurate to satisfaction with", percentage)
            break

if __name__ == '__main__':
    main()

