#   MIT License
#
#   Copyright (c) 2021 Igor Costa Carvalho Campos Silva
#   https://github.com/guimspace/envelope-matrix
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in all
#   copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.

def unwrapSymmetricEnvelope(envelope, matrix):
    n = len(envelope['diagg'])

    p = 0
    for i in range(n):
        matrix[i][i] = envelope['diagg'][i]

        d = envelope['enveLin'][i] - p
        top = envelope['enveCol'][i + 1]
        while p < top:
            matrix[i][d + p] = envelope['enve'][p]
            matrix[d + p][i] = envelope['enve'][p]
            p = p + 1

def unwrapEnvelope(envelope, matrix, isLine = False):
    n = len(envelope['diagg'])

    p = 0
    for i in range(n):
        matrix[i][i] = envelope['diagg'][i]

        d = envelope['enveLin'][i] - p
        top = envelope['enveCol'][i + 1]
        while p < top:
            if isLine:
                matrix[i][d + p] = envelope['enve'][p]
            else:
                matrix[d + p][i] = envelope['enve'][p]
            p = p + 1

def generateEnvelope(matrix, isLine = False):
    ENVcol = []
    envelope = []
    ENVlin = []
    Diagg = []

    n = len(matrix)

    p = 0
    i = 0
    j = 0

    while(j < n):
        Diagg.append(matrix[j][j])
        if isLine:
            while(i < j and matrix[j][i] == 0):  #skips 0 before an whole number
                i = i + 1
        else:
            while(i < j and matrix[i][j] == 0):  #skips 0 before an whole number
                i = i + 1
        ENVcol.append(p)
        ENVlin.append(i)
        p = p + (j - i)
        while(i != j): #print the numbers before the diagonal
            if isLine:
                envelope.append(matrix[j][i])
            else:
                envelope.append(matrix[i][j])
            i = i + 1
        j = j + 1
        i = 0

    envelope.append(0)
    ENVcol.append(p)

    return {
        'diagg': Diagg,
        'enve': envelope,
        'enveCol': ENVcol,
        'enveLin': ENVlin
    }
