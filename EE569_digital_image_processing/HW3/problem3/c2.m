% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/12/2021
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
% [m,n] = size(img);
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
img_output = img;
figure; imshow(img_output)
%%
% record the index
index = [];
[m,n] = size(img_output);
for i = 1:m
    for j =1:n
        if img_output(i,j)> 0 
            index = [index;,i,j];
        end
    end
end
%%
% according to the comparing, filtering the wrong points
index1 = index;
index1([1,64],:) = [];
%%
img = quantize_img(img_input, threshold);
img = zero_padding(img);
img = inverse_img(img);
pre_img = ones(size(img));

iter = 0;
[k,n] = size(index1);
record = zeros(k,1);
%%
% ma,~_iter = 30;
while sum(sum(pre_img)) ~= sum(sum((img)))
    iter = iter+1;
    pre_img = img;
    bond = cal_bond(img);
    
    surrond_img = cal_surronding(img);
    M = step1_shrink(surrond_img,bond);
    
    update_pattern = step2_shrink(M);
    img = update_img(img,update_pattern);
    
    is_complete = 1;
    for i = 1:k
        if record(i)>0
            continue;
        end
        is_complete = 0;
        if check_alone(index1(i,:),img) == 1
            record(i) = iter;
        end
    end
    if is_complete
        break;
    end
end
% img_output = img;
% figure; imshow(img_output)
%%
figure;
histogram(record)
xlabel('Frequency')
ylabel('Number of defects')
%%
save('defects_location','index1')





