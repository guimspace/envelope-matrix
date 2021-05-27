clear all

n = 100;
d = round(sqrt(n));

A = rand(n);
A = 0.5 * (A + A');
A = A * A';
A = A + n * eye(n);
A - triu(A, d) - tril(A, -d);

b = A * [n:-1:1]';
x = A \ b;

save A.mat A;
save b.mat b;
save x.mat x;
