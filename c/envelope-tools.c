/**
 * MIT License
 *
 * Copyright (c) 2021 Guilherme Tadashi Maeoka
 * https://github.com/guimspace/envelope-matrix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "envelope-tools.h"

float get_element(env envelope, int indL, int indC)
{
        float *diagg = envelope->diagg;
        float *enve = envelope->enve;
        int *enveCol = envelope->enveCol;
        int *enveLin = envelope->enveLin;

        if (indL == indC)
                return diagg[indL];
        else if (enveCol[indC] == enveCol[indC + 1])
                return 0;

        int p = enveCol[indC];
        int i = enveLin[p];

        if (i > indL)
                return 0;

        p += indL - i;

        return enve[p];
}

void print_envelope(env envelope)
{
        int i;

        for (i = 0; i < envelope->n; i++)
                printf("%.2f\t", envelope->diagg[i]);
        printf("\n");

        for (i = 0; i <= envelope->s; i++)
                printf("%.2f\t", envelope->enve[i]);
        printf("\n");

        for (i = 0; i <= envelope->n; i++)
                printf("%d\t", envelope->enveCol[i]);
        printf("\n");

        for (i = 0; i <= envelope->s; i++)
                printf("%d\t", envelope->enveLin[i]);
        printf("\n");
}

void end_envelope(env envelope)
{
        free(envelope->diagg);
        free(envelope->enve);
        free(envelope->enveCol);
        free(envelope->enveLin);

        free(envelope);
}

env init_envelope(int n)
{
        int i;
        int s = n * (n - 1) / 2;

        env envelope = malloc( sizeof(strEnvelope) );

        envelope->n = n;
        envelope->s = s;
        envelope->diagg = (float *)calloc(n, sizeof(float));
        envelope->enve = (float *)calloc(1 + s, sizeof(float));
        envelope->enveCol = (int *)calloc(1 + n, sizeof(int));
        envelope->enveLin = (int *)calloc(1 + s, sizeof(int));

        return envelope;
}
