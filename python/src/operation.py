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

import solve

def multiplyTriangles(triL, triU):
    n = len(triL['diagg'])

    product = []
    for i in range(n):
        product.append([0] * n)

    for i in range(n):
        j = triL['enveLin'][i]

        while j < i:
            summ = solve.sumLkiUkj(triL, i, triU, j)

            if triL['enveLin'][i] <= j:
                pL = triL['enveCol'][i] + j - triL['enveLin'][i]
                summ = summ + triL['enve'][pL] * triU['diagg'][j]

            product[i][j] = summ
            j = j + 1

        if triU['enveLin'][j] <= i:
            product[i][j] = solve.sumLkiUkj(triL, i, triU, i) + triL['diagg'][i] * triU['diagg'][i]

        j = j + 1

        while j < n:
            if triU['enveLin'][j] > i:
                j = j + 1;
                continue

            summ = solve.sumLkiUkj(triL, i, triU, j)

            if triU['enveLin'][j] <= i:
                pU = triU['enveCol'][j] + i - triU['enveLin'][j]
                summ = summ + triL['diagg'][i] * triU['enve'][pU]

            product[i][j] = summ
            j = j + 1

    i = i + 1
    return product
