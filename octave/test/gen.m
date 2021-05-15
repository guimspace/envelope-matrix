clear all

n = 100;
A = rand(n);

[L, U, P] = lu(A);
clear L U

A = P * A;
b = A * [1:n]';

save A.mat A;
save b.mat b;

run('test_run.m')
