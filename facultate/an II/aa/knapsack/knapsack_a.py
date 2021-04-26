def readData(filename):
    with open(filename) as f:
        capacity = int(f.readline())
        weights = [int(x) for x in f.readline().split()]
        return capacity, weights


def knapsack_a(weights, capacity, circular=0):
    matix = [[0 for i in range(capacity + 1)] for j in range(2)]
    for i in range(len(weights)):
        for j in range(capacity + 1):
            if j == 0:
                matix[circular][j] = 0
            elif i == 0 and weights[i] <= j:
                matix[circular][j] = weights[i]
            elif weights[i] > j:
                matix[circular][j] = matix[1 - circular][j]
            else:
                matix[circular][j] = max(
                    matix[1 - circular][j],
                    weights[i] + matix[1 - circular][j - weights[i]],
                )
        circular = 1 - circular
    return matix[circular][capacity]


if __name__ == "__main__":
    capacity, weights = readData("knapsack_a_data.in")
    print("Solution: ", knapsack_a(weights, capacity))
