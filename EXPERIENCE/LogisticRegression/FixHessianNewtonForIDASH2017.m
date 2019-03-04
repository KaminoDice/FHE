% Exercise 4 -- Logistic Regression

clear all; close all; clc

data  = csvread('data103x1579.csv',1,0);
[row,col] = size(data)
xData = data(:,2:col);
yData = data(:,1);
size(xData)
size(yData)
[yData(1:6,1), xData(1:6,:)]

x = xData; 
y = yData;

[m, n] = size(x);

% Add intercept term to x
x = [ones(m, 1), x]; 

% Initialize fitting parameters
theta = zeros(n+1, 1);

% Define the sigmoid function
g = inline('1.0 ./ (1.0 + exp(-z))'); 

% Newton's method
MAX_ITR = 7;
J = zeros(MAX_ITR, 1);
H = (-1/4).* transpose(x) * x;
B = zeros(size(H));
for i = 1:size(H)(1)
    for j = 1:size(H)(2)
        B(i,i) = sum(H(i,:))+0.00001;
    endfor
endfor
H_ = inv(B);

for i = 1:MAX_ITR
    % Calculate the hypothesis function
    z = x * theta;
    h = g(z);
    
    % Calculate gradient and hessian.
    % The formulas below are equivalent to the summation formulas
    % given in the lecture videos.
    grad = (1/m).*x' * (h-y);
    G = (1/m).*x' * diag(h) * diag(1-h) * x;
    
    % Calculate J (for testing convergence)
    J(i) =(1/m)*sum(-y.*log(h) - (1-y).*log(1-h));
    
    theta = theta - H_*grad;
    %theta = theta - G\grad;
end
% Display theta
theta

% Plot J
figure
plot(0:MAX_ITR-1, J, 'o--', 'MarkerFaceColor', 'r', 'MarkerSize', 8)
xlabel('Iteration'); ylabel('J')
% Display J
J