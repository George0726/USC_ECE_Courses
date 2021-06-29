% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/12/2021
clear;clc 
close all
addpath('function_pool');
img_input = rgb2gray(imread('maze.png'));
% jar.png threshold =30
figure;imshow(img_input)
threshold = 0;
% choose 100 iter
%%
img = quantize_img(img_input, threshold);
iter = 0;
max_iter = 760;
pre_img = ones(size(img));
[m,n] = size(img);
mat = zeros(m,n,760);
% img =inverse_img(img);

while sum(sum(pre_img)) ~= sum(sum((img)))
    iter = iter+1;
    pre_img = img;
    bond = cal_bond(img);
    
    surrond_img = cal_surronding(img);
    M = step1_shrink(surrond_img,bond);
    surrounding_M = cal_surronding(M);
    
    update_pattern = step2_shrink(M);
    img = update_img(img,update_pattern);
    
    mat(:,:,iter) = img;
    if iter > max_iter
        break;
    end
end
figure; imshow(img)
%%
% iterations 755
% close all
% for i =1:15
%     figure;imshow(mat(:,:,i))
% end

figure;imshow(mat(:,:,754))

