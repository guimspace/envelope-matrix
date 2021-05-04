#include <stdio.h>
#include <stdlib.h>

#include "envelope-tools.h"
#include "envelope-wrap.h"

int main(int argc, char **argv)
{
        float *matrix = (float[37]){6, 11, 12, 0, 14, 0, 0, 0, 22, 23, 0, 0, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 44, 0, 46, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 66};
        matrix += 1;

        env envelope = init_envelope((matrix - 1)[0]);

        build_envelope(envelope, matrix);

        print_envelope(envelope);

        float *matrix2 = unwrap_envelope(envelope);

        int l = (int)matrix2[0];
        int n = l * l;
        for (int i = 1; i <= n; ) {
                printf("%.2f\t", matrix2[i]);
                if (i++ % l == 0)
                        printf("\n");
        }

        end_envelope(envelope);

	return 0;
}
