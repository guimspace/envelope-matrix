import sys
import wrap


matrix = [
    [11, 12, 0, 14, 0, 0],
    [0, 22, 23, 0, 0, 0],
    [0, 0, 33, 0, 0, 0],
    [0, 0, 0, 44, 0, 46],
    [0, 0, 0, 0, 55, 0],
    [0, 0, 0, 0, 0, 66]
]
envelope = []
n = len(matrix)

print("A triangular superior")

i = 0
j = 0
while(i < n):
    if j < i:
        print(f'{""}\t', end = "")  #format matrix
        j = j + 1
    elif j < n:
        print(f'{matrix[i][j]}\t', end = "")
        j = j + 1
    else:
        print("")
        i = i + 1
        j = 0


print("Envelope da matriz")

envelope = []

i = 0
j = 0
while(j < n):
    while(i < j and matrix[i][j] == 0):  #skips 0 before an whole number
        i = i + 1
    while(i != j): #print the numbers before the diagonal
        envelope.append(matrix[i][j])
        print(f'{matrix[i][j]}\t', end = "")
        i = i + 1
    j = j + 1
    i = 0

envelope.append(0)
print("0")



print("")


print("Matrix diagonal")
i = 0

while(i < n):
    print(f'{matrix[i][i]}\t', end = "")
    i = i + 1


print("")

print("Envcol")
