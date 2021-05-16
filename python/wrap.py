# MIT License
#
# Copyright (c) 2021 Igor Costa Carvalho Campos Silva
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

def envMatrix(matrix):
    ENVcol = []
    envelope = []
    ENVlin = []
    Diagg = []

    p = 0
    i = 0
    j = 0

    while(j < n):
        Diagg.append(matrix[j][j])
        while(i < j and matrix[i][j] == 0):  #skips 0 before an whole number
            i = i + 1
        ENVcol.append(p)
        while(i != j): #print the numbers before the diagonal
            envelope.append(matrix[i][j])
            print(f'{matrix[i][j]}\t', end = "")
            ENVlin.append(i)
            p = p + 1
            i = i + 1
        j = j + 1
        i = 0

    return {
        'diagg': Diagg,
        'enve': envelope,
        'enveCol': ENVcol,
        'enveLin': ENVlin
    }
