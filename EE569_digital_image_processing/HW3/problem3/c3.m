% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/12/2021s
clear;clc 
close all
%%
%  Count the total number of disconnected defects in the image
addpath('function_pool');
img_input = rgb2gray(imread('horse.png'));
threshold = 30;%60
figure;imshow(img_input)
%%
% shrink
img = quantize_img(img_input, threshold);
img = zero_padding(img);
img = inverse_img(img);
pre_img = ones(size(img));
%%
iter = 0;
% max_iter = 30;
while sum(sum(pre_img)) ~= sum(sum((img)))
    iter = iter+1;
    pre_img = img;
    bond = cal_bond(img);
    
    surrond_img = cal_surronding(img);
    M = step1_shrink(surrond_img,bond);
    
    update_pattern = step2_shrink(M);
    img = update_img(img,update_pattern);
                        
end
img_shrink = img;
figure; imshow(img_shrink)
%%
% record the index
index = [];
[m,n] = size(img_shrink);
for i = 1:m
    for j =1:n
        if img_shrink(i,j)> 0 
            index = [index;i,j];
        end
    end
end
%%
% according to the comparing, filtering the wrong points
% index 1,64
img_shrink(index(1,1),index(1,2)) = 0;
img_shrink(index(64,1),index(64,2)) = 0;
%%
% thin
img = quantize_img(img_input, threshold);
img = zero_padding(img);
img = inverse_img(img);
pre_img = ones(size(img));
%%
iter = 0;
% max_iter = 30;
while sum(sum(pre_img)) ~= sum(sum((img)))
    pre_img = img;
    bond = cal_bond(img);
    
    surrond_img = cal_surronding(img);
    M = step1_thin(surrond_img,bond);
    
    update_pattern = step2_thin(M);
    img = update_img(img,update_pattern);
    
    iter = iter+1;
end
img_thin = img;
figure; imshow(img_thin)
%%
% clear the defect
% total_defect = sum(sum(img));
% the defect points 65 (-2)
% choose the kernel size for defects region

img_pattern = img_input;

[m,n] = size(img_pattern);
num = 0 ;
kernel_size = 7;

for i = 1:m
    for j =  1:n
        if img_pattern(i,j) == 0 && img_thin(i+1,j+1)==1 && img_shrink(i+1,j+1)==1
            for u = -kernel_size:kernel_size
                for v = -kernel_size:kernel_size
                    col = check_length(i+1+u,m);
                    row = check_length(j+1+v,n);
                    img_pattern(col,row) =255;
                end
            end
        end
    end
end
figure;imshow(img_input);
figure;imshow(img_pattern);

        



