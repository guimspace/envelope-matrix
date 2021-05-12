clear all
addpath('../src');
addpath('../src/envelopeLuDecomposition');

PA = [
    1, 1, -1, 2;
    1, 2, 0, 2;
    -1, -1, 2, 0;
    0, 0, -1, 1
];
b = PA * [1:4]';


enveTriL = envelopeBuild(tril(PA)');
enveTriU = envelopeBuild(triu(PA));

[L, U] = envelopeLuDecomposition(enveTriL, enveTriU);


y = envelopeForwardSubstitution(L, b);
x = envelopeBackwardSubstitution(U, y)



n = 6;

U = triu(randi(9, n));
L = eye(n) + tril(randi(9, n), -1);
A = L * U;
b = A * [1:n]';

enveTriL = envelopeBuild(tril(A)');
enveTriU = envelopeBuild(triu(A));

[L, U] = envelopeLuDecomposition(enveTriL, enveTriU);


y = envelopeForwardSubstitution(L, b);
x = envelopeBackwardSubstitution(U, y)



n = 6;

A = rand(6);
[L, U, P] = lu(A);
A = P * A;
b = A * [1:n]';

enveTriL = envelopeBuild(tril(A)');
enveTriU = envelopeBuild(triu(A));

[L, U] = envelopeLuDecomposition(enveTriL, enveTriU);


y = envelopeForwardSubstitution(L, b);
x = envelopeBackwardSubstitution(U, y)



n = 6;

A = [
    11  12  0   14  0   0;
    0   22  23  0   0   0;
    0   0   33  0   0   0;
    0   0   0   44  0   46;
    0   0   0   0   55  0;
    0   0   0   0   0   66
];
[L, U, P] = lu(A);
A = P * A;
b = A * [1:n]';

enveTriL = envelopeBuild(tril(A)');
enveTriU = envelopeBuild(triu(A));

[L, U] = envelopeLuDecomposition(enveTriL, enveTriU);


y = envelopeForwardSubstitution(L, b);
x = envelopeBackwardSubstitution(U, y)
