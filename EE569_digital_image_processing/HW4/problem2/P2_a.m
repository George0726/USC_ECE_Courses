% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/28/2021
clc;clear
close all
addpath('function_pool');
%%
img =imread('composite.png');
feature = law_filter(img);
blurr_feature = blur_feature(feature,31);
%%
blurred_feature =blurr_feature./blurr_feature(:,:,1);
blurred_feature(:,:,1) = [];
%%
% convert 3D to 2D
[m,n,p] = size(blurred_feature);
record = zeros(m*n,26);
for i = 1:m
    for j =1:n 
        record(n*(i-1)+j,:) = [squeeze(blurred_feature(i,j,:))' i j ];
    end
end
%%
class_img = zeros(m,n);
first_axis = record(:,25);
secord_axis = record(:,26);
label_map = kmeans(record(:,1:24),5,'MaxIter',10000);

[num_pixel,~] = size(record);
for i = 1:num_pixel
    if label_map(i) == 1
        class_img(first_axis(i),secord_axis(i)) = label_map(i);
    else
        class_img(first_axis(i),secord_axis(i)) = 64*(label_map(i)-2)+63;
    end
end
%%
figure;
imshow(img)
figure;
imshow(uint8(class_img))    
imwrite(uint8(class_img),'output/mean_31.png')