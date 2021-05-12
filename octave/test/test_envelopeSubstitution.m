clear all
addpath('../src');

n = 6;

U = triu(randi(9, n));
L = eye(n) + tril(randi(9, n), -1);
b = (L * U) * [1:n]';


envelope = envelopeBuild(L');
y = envelopeForwardSubstitution(envelope, b);

envelope = envelopeBuild(U);
x = envelopeBackwardSubstitution(envelope, y)
