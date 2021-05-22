class Matrices:

    def solveForwardSubstitution(self, triL, b):
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

    def solveBackwardSubstitution(self, triU, b):
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

    def unwrapEnvelope(self, envelope, matrix, isLine):
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