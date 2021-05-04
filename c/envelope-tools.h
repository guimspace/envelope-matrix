#include <stdio.h>
#include <stdlib.h>

typedef
        struct strEnvelope {
                int n;
                int s;
                float *diagg;
                float *enve;
                int *enveCol;
                int *enveLin;
        } strEnvelope, *env;

void print_envelope(env envelope);
env init_envelope(int n);
void end_envelope(env envelope);
