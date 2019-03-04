% Change the filenames if you've saved the files under different names
% On some platforms, the files might be saved as 
% train-images.idx3-ubyte / train-labels.idx1-ubyte
images = loadMNISTImages('train-images.idx3-ubyte');
labels = loadMNISTLabels('train-labels.idx1-ubyte');
 
% We are using display_network from the autoencoder code
%display_network(images(:,1:100)); % Show the first 100 images
disp(labels(1));

image = images(:,1);

'its column comes first'
for i = 1:28
    for j = 0:27
      if 0==int32(image(i + j*28))
        fprintf('   ')
      else
        fprintf(' @ ')
      end
    endfor
    fprintf('\n')
endfor

'MAKE its row come first'
im = zeros(size(image));
cnt = 1;
for i = 1:28
    for j = 0:27
      im(cnt) = image(i + j*28);
      cnt = cnt+1;
    endfor
endfor

'so its row comes first'
for i = 0:27
    for j = 1:28
      if im(i*28 + j)>0
        fprintf(' @ ');
      else
        fprintf('   ');
      end
    endfor
    fprintf('\n')
endfor