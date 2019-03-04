function [w,run] = train_bohning(x,w,lambda)
% Bohning's method

% tiny d = 10;
% medium
d = 100;
% big  d = 500;
n = 3*d;

clear run

% function r = dirichlet_sample(a,n)
% DIRICHLET_SAMPLE(a) returns a probability vector sampled from a 
% Dirichlet distribution with parameter vector A.
% DIRICHLET_SAMPLE(a,n) returns N samples, collected into a matrix, each 
% vector having the same orientation as A.
x = dirichlet_sample(ones(d,1),n);
% So each column of x is a record.

% rand(1,n) return a matrix(1,n)
y = rand(1,n); 
y = y>0.5;  % y(i) in       {0 ,  1}
y = 2*y-1;  % shift y(i) to {-1, +1}

[d,n] = size(x);

xy = scale_cols(x,y);
% function z = scale_cols(x, s)
%%  SCALE_COLS(x,s) returns a matrix (z) of same size as x, 
%%  such that z(:,i) = x(:,i)*s(i)
%%  = x*diag(s)
% z = x.*(ones(rows(x),1)*s(:)');
%%  rows(curs) returns the number of rows in curs.
w0 = zeros(d,1);
[w,run.FixedH] = train_bohning(xy,w0,lambda);

% Written by Thomas P Minka

if nargin < 3
  lambda = 0;
end
lambda = 0;

[d,n] = size(x);
h = (x*x')/4 + lambda*eye(d);
for iter = 1:1000
  old_w = w;
  % s1 = 1-sigma(-w'*x)
  s1 = 1./(1+exp(w'*x));
  g = x*s1' - lambda*w;
  % u = H\g
  u = inv(h)*g;
  
  w = w + u;
  
  % compute the max likelihood
  s = w'*x;
  p = -log(1 + exp(-s));
  i = find(s > 36);
  if ~isempty(i)
    p(i) = -exp(-s(i));
  end
  p = sum(p);
  
  run.w(:,iter) = w;
  run.e(iter) = p - 0.5*lambda*w'*w;

% function p = logProb(x,w)
% x is premultiplied by y
% s = w'*x;
% p = -log(1 + exp(-s));
% i = find(s > 36);
% if ~isempty(i)
  % large s limit
  % p(i) = -exp(-s(i));
% end
% p = sum(p);

  
end
figure(2)
plot(run.e)

