class Envelope:

    def initEnvelope(self):
        return {
            'diagg': [],
            'enve': [],
            'enveCol': [],
            'enveLin': []
        }
        
    def luDecomposition(self, triL, triU):
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
                p = triU['enveCol'][j]
                l = triU['enveLin'][j]
                p = p + i - l
                if l <= i and p < triU['enveCol'][j + 1]:
                    summ = sumLkiUkj(triL, i, triU, j)
                    triU['enve'][p] = triU['enve'][p] - summ

                p = triL['enveCol'][j]
                l = triL['enveLin'][j]
                p = p + i - l
                if l <= i and p < triL['enveCol'][j + 1]:
                    summ = sumLkiUkj(triU, i, triL, j)
                    triL['enve'][p] = (triL['enve'][p] - summ) / u_ii

        summ = sumLkiUkj(triL, n - 1, triU, n - 1)
        triU['diagg'][n - 1] = triU['diagg'][n - 1] - summ

        if triU['diagg'][n - 1] == 0:
            print("A = LU but A is singular")

    def sumLkiUkj(self, triL, indI, triU, indJ):
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

    def generateEnvelope(self, matrix, isLine):
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
            while(i != j): #print the numbers before the diagonal
                if isLine:
                    envelope.append(matrix[j][i])
                else:
                    envelope.append(matrix[i][j])
                p = p + 1
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

    def getElement(self, envelope, i, j):
        if i == j:
            return envelope['diagg'][i]
        elif envelope['enveCol'][j] == envelope['enveCol'][j + 1]:
            return 0

        p = envelope['enveCol'][j]
        l = envelope['enveLin'][p]

        if l > i:
            return 0

        p = p + i - l

        return envelope['enve'][p]
