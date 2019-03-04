% Exercise 4 -- Logistic Regression

clear all; close all; clc


% Change the filenames if you've saved the files under different names
% On some platforms, the files might be saved as 
% train-images.idx3-ubyte / train-labels.idx1-ubyte
images = loadMNISTImages('train-images.idx3-ubyte');
labels = loadMNISTLabels('train-labels.idx1-ubyte');
 
% We are using display_network from the autoencoder code
%display_network(images(:,1:100)); % Show the first 100 images
disp(labels(1));
threes = find(labels==3);
eights = find(labels==8);
% SET three=0, eight=1;
yData = [threes ; eights];
images = images';
xData = [images(yData,:)];
yData = [zeros(size(threes)(1),1);ones(size(eights)(1),1)];

image = xData(6131,:);
'its column comes first';
for i = 1:28
    for j = 0:27
      if 0==int32(image(1,i + j*28));
        fprintf('   ');
      else
        fprintf(' @ ');
      end
    endfor
    fprintf('\n')
endfor
image = xData(6131+5851,:);
'its column comes first';
for i = 1:28
    for j = 0:27
      if 0==int32(image(1,i + j*28));
        fprintf('   ');
      else
        fprintf(' @ ');
      end
    endfor
    fprintf('\n')
endfor



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
MAX_ITR = 3;
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
    
    %theta = theta - H_*grad;
    theta = theta - G\grad;
end
% Display theta
theta

% Plot J
figure
plot(0:MAX_ITR-1, J, 'o--', 'MarkerFaceColor', 'r', 'MarkerSize', 8)
xlabel('Iteration'); ylabel('J')
% Display J
J