% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/12/2021
clear;clc 
close all
addpath('function_pool');
img_input = rgb2gray(imread('horse.png'));
threshold = 30;
% flower.png threshold=127
% jar.png threshold =30
% spring.png threshold=30
figure;imshow(img_input)
%%
img = quantize_img(img_input, threshold);
img = zero_padding(img);
reverse_img = inverse_img(img);
reverse_img = zero_padding(reverse_img);
figure; imshow(reverse_img)
%%
[labelled_img,num] = CCL_img(reverse_img);
[m,n] = size(labelled_img);
figure;imshow(uint8(labelled_img))
count = zeros(num+1,1);
% num = 64
for i =1:num+1
    for j = 1:m
        for k =1:n
            if labelled_img(j,k) == i-1
                count(i) = count(i) +1;
            end
        end
    end
end
       
%%
% filter the 0 and 1; then calculate the frequency
count_defect = count;
count_defect([1,2],:) = [];
figure;
histogram(count_defect)
xlabel('Size of defect');
ylabel('Number of defect');
% total number of defects is 63
%%
% Count the number of defect size
sorted_count = sort(count_defect);
curse  = sorted_count(1);
size_num = 1;
[ll,~] = size(sorted_count);
for i = 1: ll
    if curse ~= sorted_count(i)
        size_num = size_num+1;
        curse = sorted_count(i);
    end
end

%%
% kernel pattern is  3
img_rectifed = img;

for i = 1:m
    for j =1:n
        if labelled_img(i,j) >1
            for p =-1:1
                for q = -1:1
                    img_rectifed(i+p,j+q) = 1;
                end
            end
        end
    end
end
figure;
imshow(img_rectifed);


                        