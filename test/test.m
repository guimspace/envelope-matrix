addpath("../src");

A = eye(6);
[diag env env_col env_lin] = envelope_matrix(A)


A = [
    11  12  0   14  0   0;
    0   22  23  0   0   0;
    0   0   33  0   0   0;
    0   0   0   44  0   46;
    0   0   0   0   55  0;
    0   0   0   0   0   66
];
[diag env env_col env_lin] = envelope_matrix(A)


A = [
    11  12  0   0   0   0;
    0   22  23  0   0   0;
    0   0   33  0   0   0;
    0   0   0   44  0   46;
    0   0   0   0   55  0;
    0   0   0   0   0   66
];
[diag env env_col env_lin] = envelope_matrix(A)
