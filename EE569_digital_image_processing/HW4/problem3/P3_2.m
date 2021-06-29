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
img2 = imread('Cat.png');
% img1 = imread('Dog_2.png');
% img2 = imread('Dog_3.png');

img1_gray = single(rgb2gray(img1));
img2_gray = single(rgb2gray(img2));

[f1,d1] = vl_sift(img1_gray) ;
[f2,d2] = vl_sift(img2_gray) ;
%% 
figure; 
imagesc(cat(2, img1, img2));

[matches,scores] = vl_ubcmatch(d1,d2);
[sorted_score, perm] = sort(scores,'descend');
sorted_match  = matches;%(:,perm(1:10));

x1 = f1(1,sorted_match(1,:));
x2 = f2(1,sorted_match(2,:)) + size(img1,2);
y1 = f1(2,sorted_match(1,:));
y2 = f2(2,sorted_match(2,:));

hold on;
h = line([x1;x2],[y1;y2]);
set(h,'linewidth',1,'color','b');

vl_plotframe(f1(:,matches(1,:))) ;
f2_rectified = f2;
f2_rectified(1,:) = f2_rectified(1,:) + size(img1,2) ;
vl_plotframe(f2_rectified(:,matches(2,:))) ;
% 
%%
% figure;
% imshow(img1);
% hold on
% h3 = vl_plotframe(f1(:,matches(1,:))) ; 
% % h3 = vl_plotframe(f3) ; 
% set(h3,'color','r','linewidth',2);
% hold off
% 
% figure;
% imshow(img2);
% hold on
% % h1 = vl_plotframe(f1(:,min_index)) ; 
% h1 = vl_plotframe(f2(:,matches(2,:))) ; 
% set(h1,'color','r','linewidth',2);
% hold off
% 

