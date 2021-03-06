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

#include "utils.h"

float get_element(env envelope, int indL, int indC)
{
        if (indL == indC)
                return envelope->diagg[indL];
        else if (envelope->enveCol[indC] == envelope->enveCol[indC + 1])
                return 0;

        int p = envelope->enveCol[indC];
        int i = envelope->enveLin[indC];

        if (i > indL)
                return 0;

        p += indL - i;

        return envelope->enve[p];
}

void print_envelope(env envelope)
{
        int n = envelope->n;
        int i;

        for (i = 0; i < n; i++)
                printf("%.2f\t", envelope->diagg[i]);
        printf("\n");

        for (i = 0; i <= envelope->enveCol[n]; i++)
                printf("%.2f\t", envelope->enve[i]);
        printf("\n");

        for (i = 0; i <= n; i++)
                printf("%d\t", envelope->enveCol[i]);
        printf("\n");

        for (i = 0; i < n; i++)
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

env init_eye_envelope(int n, float c)
{
        env envelope = malloc( sizeof(strEnvelope) );

        envelope->n = n;
        envelope->diagg = (float *)calloc(n, sizeof(float));
        envelope->enve = (float *)calloc(1, sizeof(float));
        envelope->enveCol = (int *)calloc(1 + n, sizeof(int));
        envelope->enveLin = (int *)calloc(n, sizeof(int));

        for (int i = 0; i < n; i++) {
                envelope->diagg[i] = c;
                envelope->enveLin[i] = i;
        }

        return envelope;
}

env init_envelope(int n)
{
        int s = n * (n - 1) / 2;
        env envelope = malloc( sizeof(strEnvelope) );

        envelope->n = n;
        envelope->diagg = (float *)calloc(n, sizeof(float));
        envelope->enve = (float *)calloc(1 + s, sizeof(float));
        envelope->enveCol = (int *)calloc(1 + n, sizeof(int));
        envelope->enveLin = (int *)calloc(n, sizeof(int));

        return envelope;
}
