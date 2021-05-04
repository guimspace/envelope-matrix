#include "envelope-tools.h"

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
