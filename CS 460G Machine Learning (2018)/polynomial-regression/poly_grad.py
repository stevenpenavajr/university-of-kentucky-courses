# Steven Penava
# Dr. Brent Harrison
# CS 460G Homework 3: Polynomial Regression with Gradient Descent
# 3 March 2018

# Imports
from numpy import *
import matplotlib.pyplot as plt
from tqdm import tqdm

# Gradient Descent
def runGradDesc(weights, dataPoints, alpha, numIterations):
    for i in range(numIterations):
        weights = updateWeights(weights, dataPoints, alpha)
    return weights

# Getting H(theta) function value
def getHofTheta(weights, x):
    final = 0.0
    for i in range(len(weights)):
        final += (weights[i] * x ** i)
    return final

# Get gradient at current iteration
def updateWeights(weights, dataPoints, alpha):
    m = len(dataPoints)
    gradients = []

    for i in range(len(weights)):
        gradients.append(0)
    for i in range(m):
        x = dataPoints[i][0]
        y = dataPoints[i][1]
        for k in range(len(weights)):
            gradients[k] += (1 / m) * (x ** k) * ( getHofTheta(weights, x) - y)
            if isnan(gradients[k]):
                break

    for i in range(len(weights)):
        weights[i] = weights[i] - (alpha * gradients[i])
    return weights

# Printing final weights (thetas)
def printWeights(weights):
    print("Weight values:")
    for i in range(len(weights)):
        print("θ" + str(i) + " = " + str(weights[i]))

# Graphing data & weights with matplotlib
def graphWeights(weights, data, fileName, alpha, order, numIterations, error):
    plt.ylabel("Y values")
    plt.xlabel("X values")
    plt.title("Graph of " + "'" + fileName + "'")
    if (fileName == "data/synthetic-3.csv"):
        plt.text(-.3, 1.3, "Alpha = " + str(alpha) + ",\nOrder = " + str(order) + ",\nIterations = " + str(numIterations) + ",\nError = " + str(round(error,3)))
    else:
        plt.text(0, 6, "Alpha = " + str(alpha) + ",\nOrder = " + str(order) + ",\nIterations = " + str(numIterations) + ",\nError = " + str(round(error,3)))
    plt.axis([min(data[:, 0]) - .5, max(data[:, 0]) + .5, min(data[:, 1]) - .5, max(data[:, 1]) + .5])
    plt.scatter(data[:, 0], data[:, 1], color = 'C1')
    x = linspace(-2.5, 2.5)
    y = 0
    for i in range(len(weights)):
        y += weights[i] * x ** i
    plt.plot(x, y)
    plt.show()

# Getting the mean squared error
def getMSQ(weights, data):
    msqe = 0.0
    for i in range(len(data)):
        final = 0.0
        x = data[i][0]
        y = data[i][1]
        for i in range(len(weights)):
            final += (weights[i] * x ** i)
        msqe += (final - y) ** 2
    return 1/(len(data)) * msqe

# Main function
def main():
    print("Welcome to the Polynomial Regression program.\n")
    fNum = input("Please enter 1, 2, or 3 for synthetic file selection: ").strip()
    try:
        data = genfromtxt("data/synthetic-"+fNum+".csv", delimiter=',')
        try:
            order = int(input("Enter an order (1, 2, 4, or 9): "))
            alpha = float(input("Enter an alpha value (float): "))
            numIterations = int(input("Enter an iteration count: "))
            weights = [0 for i in range(order + 1)]
            weights = runGradDesc(weights, data, alpha, numIterations)
            printWeights(weights)
            error = getMSQ(weights, data)
            print("Mean squared error: " + str(error))
            graphWeights(weights, data, "data/synthetic-"+fNum+".csv", alpha, order, numIterations, error)
        except ValueError:
            print("You must have not entered a number. Try again.")
            exit(0)
    except IOError:
        print("That file was not found. Try again.")
        exit(0)

# Running main
if __name__ == '__main__':
    main()