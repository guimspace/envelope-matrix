clear all

n = 10;
A = rand(n);

[L, U, P] = lu(A);
clear L U

A = P * A;
b = A * [1:n]';
x = A \ b;

save A.mat A;
save b.mat b;
save x.mat x;
