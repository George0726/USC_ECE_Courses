% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/12/2021
clear;clc 
close all
addpath('function_pool');
img_iuput = rgb2gray(imread('spring.png'));
threshold = 127;
% jar.png threshold =30
figure;imshow(img_iuput)
%%
img = quantize_img(img_iuput, threshold);
iter = 0;
max_iter = 30;
pre_img = ones(size(img));
while sum(sum(pre_img)) ~= sum(sum((img)))
    pre_img = img;
    bond = cal_bond(img);
    
    surrond_img = cal_surronding(img);
    M = step1_thin(surrond_img,bond);
%     surrounding_M = cal_surronding(M);
    
    update_pattern = step2_thin(M);
    img = update_img(img,update_pattern);
    
%     if (iter > max_iter)
%         break;
%     end
    iter = iter+1;
end
figure; imshow(img)
% imwrite(img,'test.png')
