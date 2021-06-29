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
img_gray1 = single(rgb2gray(img1));

img3 = imread('Dog_3.png');
img_gray3 = single(rgb2gray(img3));
% 
[f1,d1] = vl_sift(img_gray1,'PeakThresh',45,'EdgeThresh',20,'Levels', 1, 'Octaves', 5) ;
[f3,d3] = vl_sift(img_gray3, 'PeakThresh',10,'WindowSize',6,'Levels', 1, 'Octaves', 5) ;
% [f1,d1] = vl_sift(img_gray1) ;
% [f3,d3] = vl_sift(img_gray3) ;

%% find the nearest neighbor of largest scale descriptor

[value,index] = max(f3(3,:));
large_scale_descriptor = d3(:,index);

[~,num_feature] = size(f1);

dist_array = zeros(num_feature,1);

for i = 1:num_feature
    dist_array(i) = sqrt(sum(( single(d1(:,i))- single(large_scale_descriptor)).^2));
end

[~,min_index] = min(dist_array);
%%
figure;
imshow(img3);
hold on
h3 = vl_plotframe(f3(:,index)) ; 
% h3 = vl_plotframe(f3) ; 
set(h3,'color','r','linewidth',2);
hold off

figure;
imshow(img1);
hold on
% h1 = vl_plotframe(f1(:,min_index)) ; 
h1 = vl_plotframe(f1(:,min_index)) ; 
set(h1,'color','r','linewidth',2);
hold off


