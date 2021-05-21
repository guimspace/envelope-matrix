import sys
import pprint

sys.path.append("../src")

import utils
import wrap
import solve
import operation

def evaluateMatrices(matrix, approx):
    n = len(matrix)
    n2 = n * n

    p = 0
    r = 0

    mP = 0
    mR = 0

    i = 0
    j = 0
    while i < n:
        t = abs(matrix[i][j] - approx[i][j])
        if r < t:
            r = t

        t = abs(matrix[i][j])
        if p < t:
            p = t

        j = j + 1
        if j % n == 0:
            if mP < p:
                mP = p
            if mR < r:
                mR = r

            r = 0
            p = 0

            j = 0
            i = i + 1

    print(mR / mP)

def evaluateSolution(x_, x):
    x = [abs(a - b) for a, b in zip(x_, x)]
    x_ = [abs(e) for e in x_]

    x = max(x)
    x_ = max(x_)

    print(x / x_)

def loadMatrix(file_A, file_b, file_x):
    with open(file_A) as file_object:
        lines = file_object.readlines()

    matrix = []
    for line in lines:
        if line == "":
            break
        line = line.split()
        line = [float(x) for x in line]
        matrix.append(line)

    with open(file_b) as file_object:
        lines = file_object.readlines()

    b = []
    for num in lines:
        if num == "":
            break
        num = float(num)
        b.append(num)

    with open(file_x) as file_object:
        lines = file_object.readlines()

    x_ = []
    for num in lines:
        if num == "":
            break
        num = float(num)
        x_.append(num)

    return matrix, b, x_


def main():
    if len(sys.argv) > 3:
        matrix, b, x_ = loadMatrix(sys.argv[1], sys.argv[2], sys.argv[3])
    else:
        matrix = [
            [11, 12, 0, 14, 0, 0],
            [-12, 22, 23, 0, 0, 0],
            [0, -23, 33, 0, 0, 0],
            [-14, 0, 0, 44, 0, 46],
            [0, 0, 0, 0, 55, 0],
            [0, 0, 0, -46, 0, 66]
        ]
        b = [91, 101, 53, 438, 275, 212]
        x_ = [1, 2, 3, 4, 5, 6]

    n = len(matrix)

    regen = []
    for i in range(n):
        regen.append([0] * n)

    triL = wrap.generateEnvelope(matrix, True)
    triU = wrap.generateEnvelope(matrix)

    wrap.unwrapEnvelope(triL, regen, True)
    wrap.unwrapEnvelope(triU, regen)

    evaluateMatrices(matrix, regen)

    solve.luDecomposition(triL, triU)

    product = operation.multiplyTriangles(triL, triU)

    evaluateMatrices(matrix, product)

    y = solve.solveForwardSubstitution(triL, b)
    x = solve.solveBackwardSubstitution(triU, y)

    evaluateSolution(x_, x)

if __name__ == "__main__":
    main()
