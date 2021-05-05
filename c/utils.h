#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;

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
float get_element(env envelope, int indL, int indC);
float sum_lki_ukj(env triL, int indI, env triU, int indJ);
