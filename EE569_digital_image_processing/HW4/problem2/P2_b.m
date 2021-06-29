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

pca_feature  = pca(record(:,1:24),'NumComponents',3);
feature= bsxfun(@minus,record(:,1:24),mean(record(:,1:24),1));
PCA_feature_vector= feature*pca_feature;
%%
class_img_before = zeros(m,n);
first_axis = record(:,25);
secord_axis = record(:,26);
label_map = kmeans(PCA_feature_vector,5,'MaxIter', 10000);
% label_map = kmeans(record(:,1:24),5,'MaxIter', 2000);

[num_pixel,~] = size(record);
for i = 1:num_pixel
    if label_map(i) == 1
        class_img_before(first_axis(i),secord_axis(i)) = label_map(i);
    else
        class_img_before(first_axis(i),secord_axis(i)) = 64*(label_map(i)-2)+63;
    end
end

% class_img = class_img_before;
%%

figure;
imwrite(uint8(class_img_before),'output/img_step0.png')
imshow(uint8(class_img_before));
class_img =class_img_before;

class1 = class_img(99,125);
class2 = class_img(222,99);
class3 = class_img(213,215);

class_label = [1, 63, 127, 191, 255];
reassigned_label = [];
for i =1:5
    if class_label(i) ~= class1 && class_label(i) ~= class2 && class_label(i) ~= class3
        reassigned_label = [reassigned_label;class_label(i)];
    end
end

edge1 = edge(img,'sobel');
imwrite(edge1,'output/edge.png')

[m,n] = size(class_img);
for i = 1:m
    for j = 1:n
        if i +m/n*j -m <0 && class_img(i,j) == class2 && class_img(i,j) ~= class3
            class_img(i,j) = reassigned_label(1);
        end
    end
end

class_img_s1 = class_img;
figure;
imshow(uint8(class_img_s1));
imwrite(uint8(class_img_s1),'output/img_step1.png')
%%
bitmap = zeros(m,n);
for i = 1:m
    for j = 1:n
        if i +m/n*j -m >0 && class_img(i,j) ~= class2 && class_img(i,j) ~= class3
            if edge1(i,j) == 1
                class_img(i,j) = reassigned_label(2);
                bitmap(i,j) = 255;
            else
                 class_img(i,j) = class2;
            end
        end
    end
end

class_img_s2 = class_img;
figure;
imshow(uint8(class_img_s2));
imwrite(uint8(class_img_s2),'output/img_step2.png')

se = offsetstrel('ball',3,3);
dilatedI = imdilate(bitmap,se);

for i = 1:m
    for j = 1:n
        if j > n/2 && dilatedI(i,j) > 128
            class_img(i,j) = reassigned_label(2);
        end
    end
end

figure;
imshow(uint8(class_img));
imwrite(uint8(class_img),'output/advanced.png')