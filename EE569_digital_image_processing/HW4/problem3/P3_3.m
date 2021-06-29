% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/28/2021
clear
clc
close all
%%
run('D:\vlfeat-0.9.21-bin.tar\vlfeat-0.9.21-bin\vlfeat-0.9.21\toolbox\vl_setup.m')
vl_version verbose
%%

img1 = imread('Dog_1.png');
img2 = imread('Dog_2.png');
img3 = imread('Dog_3.png');
img4 = imread('Cat.png');

img1_gray = single(rgb2gray(img1));
img2_gray = single(rgb2gray(img2));
img3_gray = single(rgb2gray(img3));
img4_gray = single(rgb2gray(img4));


[~,d1] = vl_sift(img1_gray) ;
[~,d2] = vl_sift(img2_gray) ;
[~,d3] = vl_sift(img3_gray) ;
[~,d4] = vl_sift(img4_gray) ;

%%
% lib_patch = double([d1,d2,d3,d4]);
% 
% lib_patch =lib_patch';
% pca_coeff = pca(lib_patch, 'NumComponents',20);
% center_feature= bsxfun(@minus,lib_patch,mean(lib_patch,1));
% PCA_feature= center_feature*pca_coeff;
% 
% [idx,C,sumd,D] = kmeans(PCA_feature,8);
%%
d1 =double(d1');
pca_coeff = pca(d1, 'NumComponents',20);
center_feature= bsxfun(@minus,d1,mean(d1,1));
PCA_feature_d1= center_feature*pca_coeff;

d2 =double(d2');
pca_coeff = pca(d2, 'NumComponents',20);
center_feature= bsxfun(@minus,d2,mean(d2,1));
PCA_feature_d2= center_feature*pca_coeff;

d3 = double(d3');
pca_coeff = pca(d3, 'NumComponents',20);
center_feature= bsxfun(@minus,d3,mean(d3,1));
PCA_feature_d3= center_feature*pca_coeff;

d4 = double(d4');
pca_coeff = pca(d4, 'NumComponents',20);
center_feature= bsxfun(@minus,d4,mean(d4,1));
PCA_feature_d4= center_feature*pca_coeff;

PCA_feature = [PCA_feature_d1;PCA_feature_d2;PCA_feature_d3;PCA_feature_d4];
[idx,C,sumd,D] = kmeans(PCA_feature,8);
%%
num_total = size(PCA_feature,1);
category = zeros(num_total,1);
for i =1:num_total
    C0 = (C-PCA_feature(i,:)).^2;
    sum0 = sum(C0,2);
    [~,idx] = min(sum0);
    category(i) = idx;
end
%%
count1 = zeros(8,1);
num1 = size(d1,1);

for i = 1:num1
    count1(category(i)) = count1(category(i))+1;
end
figure;
bar(count1)
title('Dog1 histogram')
%%
count2 = zeros(8,1);
num2 = size(d2,1);

for i =num1+1:num1+num2
    count2(category(i)) = count2(category(i))+1;
end
figure;
bar(count2)
title('Dog2 histogram')
%%
count3 = zeros(8,1);
num3 = size(d3,1);

for i =num1+num2+1:num1+num2+num3
    count3(category(i)) = count3(category(i))+1;
end
figure;
bar(count3)
title('Dog3 histogram')
%%
count4 = zeros(8,1);
num4 = size(d4,1);

for i =num1+num2+num3+1:num1+num2+num3+num4
    count4(category(i)) = count4(category(i))+1;
end
figure;
bar(count4)
title('Cat histogram')
%%
% Calculate similarity
sim_index1_max = 0 ;
sim_index1_min = 0 ;
sim_index2_max = 0 ;
sim_index2_min = 0 ;
sim_index4_max = 0 ;
sim_index4_min = 0 ;

for i =1:8
    sim_index1_max = sim_index1_max+ max([count1(i),count3(i)]);
    sim_index1_min = sim_index1_min+ min([count1(i),count3(i)]);
    sim_index2_max = sim_index2_max+ max([count2(i),count3(i)]);
    sim_index2_min = sim_index2_min+ min([count2(i),count3(i)]);
    sim_index4_max = sim_index4_max+ max([count4(i),count3(i)]);
    sim_index4_min = sim_index4_min+ min([count4(i),count3(i)]);
end
    
sim_index1 = sim_index1_min/sim_index1_max;
sim_index2 = sim_index2_min/sim_index2_max;
sim_index4 = sim_index4_min/sim_index4_max;
    
disp(sim_index1);
disp(sim_index2);
disp(sim_index4);
    
    
