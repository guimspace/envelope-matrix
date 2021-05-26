clear all

n = 100;
A = rand(n);
A = 0.5 * (A + A');
A = A * A';
A = A + n * eye(n);

b = A * [n:-1:1]';
x = A \ b;

save A.mat A;
save b.mat b;
save x.mat x;
