% //Qirui Sun
% //USC ID: 1140685892
% //qiruisun@usc.edu
% //Submission Date: 2/23/2021
clear;clc;
img1 = imread('ski_person.jpg');
% img1 = imread('elephant.jpg');
[a,b,c] = size(img1);
image = 255.0.*ones(a,b);

% gray = zeros(a,b);
gray = 0.2989 * img1(:,:,1)+ 0.5870 *img1(:,:,2) + 0.1140*img1(:,:,3);

max_value = max(max(gray));
min_value = min(min(gray));

figure;
[edge1, threshold] = edge(gray,'canny',[0.07,0.25]);
[edge2, threshold2] = edge(gray,'canny',[0.13,0.5]);
[edge3, threshold] = edge(gray,'canny',[0.05,0.2]);
% For example, if the threshold is [0.1 0.15] then the edge pixels above the upper limit(0.15)
%     are considered and edge pixel below the threshold(0.1) are discarded.
subplot(1,3,1);
imshow(uint8(image - edge1*255.0))

subplot(1,3,2);
imshow(uint8(image - edge2*255.0))

subplot(1,3,3);
imshow(uint8(image - edge3*255.0))
