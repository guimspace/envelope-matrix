float *solve_backward_substitution(env envelope, float vecB[]);
float *solve_forward_substitution(env envelope, float vecB[]);
void lu_decomposition(env triL, env triU);
float sum_lki_ukj(env triL, int indI, env triU, int indJ);
void cholesky_decomposition(env triU);
