clear all; close all; clc

data  = csvread('data103x1579.csv',1,0);
[row,col] = size(data);
xData = data(:,2:col);
yData = data(:,1);

x = xData; 
y = yData;

[m, n] = size(x);
% Add intercept term to x
x = [ones(m, 1), x];

% So each column of x is a record.
x = x';
y = y';     % y(i) in       {0 ,  1}
y = 2*y-1;  % shift y(i) to {-1, +1}

[d,n] = size(x);

xy = x.*(ones(rows(x),1)*y(:)');
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

