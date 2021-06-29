% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/12/2021
clear;clc 
close all
%  Count the total number of disconnected defects in the image
addpath('function_pool');
img_iuput = rgb2gray(imread('horse.png'));
threshold = 30;
figure;imshow(img_iuput)
%%
img = quantize_img(img_iuput, threshold);
img = zero_padding(img);
img = inverse_img(img);
% img = zero_padding(img);
pre_img = ones(size(img));
figure;imshow(img)
%%
iter = 0;
% max_iter = 30;
while sum(sum(pre_img)) ~= sum(sum((img)))
    pre_img = img;
    bond = cal_bond(img);
    
    surrond_img = cal_surronding(img);
    M = step1_shrink(surrond_img,bond);
    
    update_pattern = step2_shrink(M);
    img = update_img(img,update_pattern);
    
    iter = iter+1;
end
figure; imshow(img)
%%
total_defect = sum(sum(img));
% the defect points 65 - 2

