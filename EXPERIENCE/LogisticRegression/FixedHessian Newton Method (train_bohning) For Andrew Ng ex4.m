% Bohning's method

clear all; close all; clc

x = load('ex4x.dat'); 
y = load('ex4y.dat');
x(1:5,:)
y(1:5)

% tiny d = 10;
% medium
d = 2;
% big  d = 500;
n = size(x)(1);

% function r = dirichlet_sample(a,n)
% DIRICHLET_SAMPLE(a) returns a probability vector sampled from a 
% Dirichlet distribution with parameter vector A.
% DIRICHLET_SAMPLE(a,n) returns N samples, collected into a matrix, each 
% vector having the same orientation as A.
%x = dirichlet_sample(ones(d,1),n);
% So each column of x is a record.
x = [ones(size(x)(1),1),x];
x = x';
% rand(1,n) return a matrix(1,n)
y = y';     % y(i) in       {0 ,  1}
y = 2*y-1;  % shift y(i) to {-1, +1}

[d,n] = size(x);

xy = x.*(ones(rows(x),1)*y(:)')
% function xy = scale_cols(x, y)
%%  SCALE_COLS(x,y) returns a matrix (xy) of same size as x, 
%%  such that xy(:,i) = x(:,i)*y(i)
%%  = x*diag(y)
% xy = x.*(ones(rows(x),1)*y(:)');
%%  rows(curs) returns the number of rows in curs.
w0 = zeros(d,1);

% Written by Thomas P Minka
[d,n] = size(x);
h = (x*x')/4;

x = xy;
w = w0;

MAX_ITER = 100;
W = zeros(d,MAX_ITER);
E = zeros(1,MAX_ITER);
for iter = 1:MAX_ITER
  old_w = w;
  % s1 = 1-sigma(-w'*x)
  s1 = 1./(1+exp(w'*x));
  g = x*s1';
  % u = H\g
  u = inv(h)*g;
  
  w = w + u;
  
  % compute the log likelihood
  % function p = logProb(x,w)
  % x is premultiplied by y
  s = w'*x;
  p = -log(1 + exp(-s));
  i = find(s > 36);
  if ~isempty(i)
    p(i) = -exp(-s(i));
  end
  p = sum(p);
  % try to maximize the log likelihood
  E(iter) = p;
  W(:,iter) = w;  
end

E
figure(2)
plot(E)

