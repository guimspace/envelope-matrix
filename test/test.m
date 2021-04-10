addpath('../src');

A = eye(6);
[diagg, env, env_col, env_lin] = col_envelope(A)
[diagg, env, env_col, env_lin] = lin_envelope(A')


A = [
    11  12  0   14  0   0;
    0   22  23  0   0   0;
    0   0   33  0   0   0;
    0   0   0   44  0   46;
    0   0   0   0   55  0;
    0   0   0   0   0   66
];
[diagg, env, env_col, env_lin] = col_envelope(A)
[diagg, env, env_col, env_lin] = lin_envelope(A')


A = [
    11  12  0   0   0   0;
    0   22  23  0   0   0;
    0   0   33  0   0   0;
    0   0   0   44  0   46;
    0   0   0   0   55  0;
    0   0   0   0   0   66
];
[diagg, env, env_col, env_lin] = col_envelope(A)
[diagg, env, env_col, env_lin] = lin_envelope(A')



A = [
    11  12  0   0   0   0;
    0   22  23  0   0   0;
    0   0   33  34  0   0;
    0   0   0   44  45  0;
    0   0   0   0   55  56;
    0   0   0   0   0   66
];
[diagg, env, env_col, env_lin] = col_envelope(A)
[diagg, env, env_col, env_lin] = lin_envelope(A')


A = [
    11  12  13  14  15  16;
    0   22  0   0   0   0;
    0   0   33  0   0   0;
    0   0   0   44  0   0;
    0   0   0   0   55  0;
    0   0   0   0   0   66
];
[diagg, env, env_col, env_lin] = col_envelope(A)
[diagg, env, env_col, env_lin] = lin_envelope(A')
