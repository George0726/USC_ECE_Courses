## EE 546 HW IV


![image-20201114171106098](C:\Users\Sunqr\AppData\Roaming\Typora\typora-user-images\image-20201114171106098.png)


![image-20201114171147604](C:\Users\Sunqr\AppData\Roaming\Typora\typora-user-images\image-20201114171147604.png)

~~~matlab
% implement matlab code for the problem
clear
clc
~~~

~~~matlab
%(i) normalize the data
load('aca2.mat')
X = X(:,1:2:end);
s = s(1:2:end);
num_cluster = max(s);

[m,n]=size(X);

for i = 1:n
    X(:,i) = X(:,i)./sqrt(sum(X(:,i).^2));
~~~

![image-20201114171627442](C:\Users\Sunqr\AppData\Roaming\Typora\typora-user-images\image-20201114171627442.png)

~~~matlab
%%
% (ii) Build the following kernel
gamma = 2;
k = 8;

K = ones(n,n);
for i = 1:n
    for j = 1:n
        K(i,j) = exp(-gamma * norm(X(:,i) - X(:,j)).^2);
    end
end
W = K;

for j = 1:n
    temp = sort(W(:,j),'descend');
    for i = 1:n
      if  W(i,j) < temp(k) 
          W(i,j) = 0;
      end
    end
end

W = 1/2 .*(W +W');
~~~

![image-20201114171826412](C:\Users\Sunqr\AppData\Roaming\Typora\typora-user-images\image-20201114171826412.png)

~~~matlab
%%
% run the spectral clustering
record_matrix = [];
err = 0;

for gamma = [0.1:0.1:1,1:100]
    for k = 2:50
        
    idx = SpectralCluster(X,gamma,k,num_cluster);
    err = Misclassification(idx,s);
    record_matrix = [record_matrix;gamma,k,err];  
    end
end
%%
save('record_matrix_5.mat','record_matrix')
%%
load("record_matrix.mat")
min(record_matrix)
minimum = min(min(record_matrix));
[x,y]=find(record_matrix==minimum);
~~~



### Supplementary Function 

~~~matlab
% This function focus attribute to do the SpectralCluster
function idx3 = SpectralCluster(X,gamma,k,num_cluster)

[m,n]=size(X);

K = zeros(n,n);
for i = 1:n
    for j = 1:n
        K(i,j) = exp(-gamma * norm(X(:,i) - X(:,j)).^2);
    end
end
W = K;

for j = 1:n
    temp = sort(W(:,j),'descend');
    for i = 1:n
      if  W(i,j) < temp(k) 
          W(i,j) = 0;
      end
    end
end

W = 1/2 .*(W +W');

D = zeros(n);

for i = 1:n
    D(i,i) = sum(W(i,:));
end

I = eye(size(W,1));
% 
% laplacian_raw = D - W;
% laplacian_norm = I-W;
laplacian_rw = (D^(-1/2))*W*(D^(-1/2));
% 
% [V1, D1] = eigs(laplacian_raw,k);
% [V2, D2] = eigs(laplacian_norm,k);
[V3, D3] = eigs(laplacian_rw, k);
% 
% V1 = V1(:,1:k);
% V2 = V2(:,1:k);
V3 = V3(:,1:k);

for i = 1:n
%     V1(i,:) = V1(i,:)./sqrt(sum(V1(i,:).^2));
%     V2(i,:) = V2(i,:)./sqrt(sum(V2(i,:).^2));
    V3(i,:) = V3(i,:)./sqrt(sum(V3(i,:).^2));
end

% idx1 = kmeans(V1,num_cluster);
% idx2 = kmeans(V2,num_cluster);
idx3 = kmeans(V3,num_cluster);


end
~~~



### Results

- i)  for aca2.mat Data:

     When gamma = 67 and k = 8 or gamma = 99 and k = 9, the minimum error rate is 0.0862

- ii) for aca5.mat Data:
  
     When gamma = 65, k = 15, minimum error rate is 0.095
