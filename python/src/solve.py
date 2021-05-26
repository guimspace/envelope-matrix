#   MIT License
#
#   Copyright (c) 2021 Guilherme Tadashi Maeoka
#   https://github.com/guimspace/envelope-matrix
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.

import math

def choleskyDecomposition(triU):
    n = len(triU['diagg'])

    if triU['diagg'][0] <= 0:
        print("Factorization impossible")
        return

    triU['diagg'][0] = math.sqrt(triU['diagg'][0])

    for j in range(1, n):
        if triU['enveLin'][j] != 0:
            continue

        p = triU['enveCol'][j]
        if (p < triU['enveCol'][j + 1]):
            triU['enve'][p] = triU['enve'][p] / triU['diagg'][0]

    n_1 = n - 1
    for i in range(1, n_1):
        summ = triU['diagg'][i] - sumLkiUkj(triU, i, triU, i)
        if summ <= 0:
            print("Factorization impossible")
            return

        triU['diagg'][i] = math.sqrt(summ)

        for j in range(i + 1, n):
            l = triU['enveLin'][j]
            p = triU['enveCol'][j] + i - l
            if l <= i and p < triU['enveCol'][j + 1]:
                summ = sumLkiUkj(triU, j, triU, i)
                triU['enve'][p] = (triU['enve'][p] - summ) / triU['diagg'][i]

    summ = triU['diagg'][n_1] - sumLkiUkj(triU, n_1, triU, n_1)
    if summ <= 0:
        print("Factorization impossible")
    else:
        triU['diagg'][n_1] = math.sqrt(summ)

def luDecomposition(triL, triU):
    if triU['diagg'][0] == 0:
        print("Factorization impossible")
        return

    n = len(triL['diagg'])

    triL['diagg'][0] = 1

    u_ii = triU['diagg'][0]
    for j in range(1, n):
        triL['diagg'][j] = 1

        p = triL['enveCol'][j]
        if p == triL['enveCol'][j + 1] or triL['enveLin'][j] != 0:
            continue

        triL['enve'][p] = triL['enve'][p] / u_ii

    for i in range(1, n - 1):
        summ = sumLkiUkj(triL, i, triU, i)
        u_ii = triU['diagg'][i] - summ

        if u_ii == 0:
            print("Factorization impossible")
            return

        triU['diagg'][i] = u_ii

        for j in range(i + 1, n):
            l = triU['enveLin'][j]
            p = triU['enveCol'][j] + i - l
            if l <= i and p < triU['enveCol'][j + 1]:
                summ = sumLkiUkj(triL, i, triU, j)
                triU['enve'][p] = triU['enve'][p] - summ

            l = triL['enveLin'][j]
            p = triL['enveCol'][j] + i - l
            if l <= i and p < triL['enveCol'][j + 1]:
                summ = sumLkiUkj(triU, i, triL, j)
                triL['enve'][p] = (triL['enve'][p] - summ) / u_ii

    summ = sumLkiUkj(triL, n - 1, triU, n - 1)
    triU['diagg'][n - 1] = triU['diagg'][n - 1] - summ

    if triU['diagg'][n - 1] == 0:
        print("A = LU but A is singular")

def sumLkiUkj(triL, indI, triU, indJ):
    pL = triL['enveCol'][indI]
    pU = triU['enveCol'][indJ]

    if triL['enveLin'][indI] >= triU['enveLin'][indJ]:
        pU = pU + triL['enveLin'][indI] - triU['enveLin'][indJ]
    else:
        pL = pL + triU['enveLin'][indJ] - triL['enveLin'][indI]

    d = triL['enveCol'][indI + 1] - pL
    if d > triU['enveCol'][indJ + 1] - pU:
        d = triU['enveCol'][indJ + 1] - pU

    v1 = triL['enve'][pL:(pL + d)]
    v2 = triU['enve'][pU:(pU + d)]

    summ = sum([a * b for a, b in zip(v1, v2)])

    return summ

def solveForwardSubstitution(triL, b):
    diagg = triL['diagg']
    enve = triL['enve']
    enveCol = triL['enveCol']
    enveLin = triL['enveLin']

    v = b[:]

    n = len(diagg)
    x = [0] * n

    j = 0
    while j < n:
        p = enveCol[j]
        up = enveCol[j + 1]
        l = enveLin[j]
        while p < up:
            v[j] = v[j] - enve[p] * x[l]
            p = p + 1
            l = l + 1

        x[j] = v[j] / diagg[j]

        j = j + 1

    return x

def solveBackwardSubstitution(triU, b):
    diagg = triU['diagg']
    enve = triU['enve']
    enveCol = triU['enveCol']
    enveLin = triU['enveLin']

    v = b[:]

    n = len(diagg)
    x = [0] * n

    j = n - 1
    while j > -1:
        x[j] = v[j] / diagg[j]

        p = enveCol[j]
        up = enveCol[j + 1]
        l = enveLin[j]
        while p < up:
            v[l] = v[l] - enve[p] * x[j]
            p = p + 1
            l = l + 1

        j = j - 1

    return x
