clear
clc
M = csvread('bilateral.csv');
X = M(:,1);
Y = M(:,2);
Z = M(:,3); 


XI=linspace(min(X),max(X),25);
YI=linspace(min(Y),max(Y),25); 
ZI=griddata(X,Y,Z,XI,YI.');
imagesc(XI,YI,ZI);colorbar;
colormap(hot);
ylabel("\sigma_s")
xlabel("\sigma_c")
% best 31,6