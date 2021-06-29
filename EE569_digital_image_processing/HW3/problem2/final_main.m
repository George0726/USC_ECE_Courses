% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/12/2021
clear; close all;
clc;
%%
% use SURF feature detector to detect feature
left = imread('left.png');
middle = imread('middle.png');
right = imread('right_updated.png');

left_gray = rgb2gray(left);
middle_gray = rgb2gray(middle);
right_gray = rgb2gray(right);

points_left = detectSURFFeatures(left_gray);
points_middle = detectSURFFeatures(middle_gray);
points_right = detectSURFFeatures(right_gray);

[f_left,vpts_left] = extractFeatures(left_gray,points_left);
[f_middle,vpts_middle] = extractFeatures(middle_gray,points_middle);
[f_right,vpts_right] = extractFeatures(right_gray,points_right);

indexPairs_right2middle = matchFeatures(f_right,f_middle);
matchedPoints_right = vpts_right(indexPairs_right2middle(:,1));
matchedPoints_middle_right = vpts_middle(indexPairs_right2middle(:,2));

indexPairs_left2middle = matchFeatures(f_left,f_middle);
matchedPoints_left = vpts_left(indexPairs_left2middle(:,1));
matchedPoints_middle_left = vpts_middle(indexPairs_left2middle(:,2));


figure;showMatchedFeatures(left,middle,matchedPoints_left,matchedPoints_middle_left,'montage');
figure;showMatchedFeatures(middle,right,matchedPoints_middle_right,matchedPoints_right,'montage');



%%
% selected key point manually
% [2,5,19,21] 2:[4,8,11,18]
selected_key_left =  matchedPoints_left([2,5,19,21],:);
selected_key_mid_left = matchedPoints_middle_left([2,4,19,21],:);

selected_key_right = matchedPoints_right([4,8,11,18],:);
selected_key_mid_right = matchedPoints_middle_right([4,8,11,18],:);
figure;
showMatchedFeatures(left, middle, selected_key_left, selected_key_mid_left, 'montage'); 

figure;
showMatchedFeatures(middle, right, selected_key_mid_right, selected_key_right, 'montage'); 

%%
% initialize the canvas show the mapping to the canvas
[left_x,left_y] = size(left_gray);
[mid_x,mid_y] = size(middle_gray);
[right_x,right_y] = size(right_gray);


canvas_mask = zeros(1500,2000,3);
for k =1:3
    for x = 1:1500
        for y = 1:2000
            if((y>200)&&(y<=left_y+200)&&(x>500)&&(x<=left_x+500))
                canvas_mask(x,y,k) = left(x-500,y-200,k);
            end

            if((y>750)&&(y<=mid_y+750)&&(x>500)&&(x<=mid_x+500))
                canvas_mask(x,y,k) = middle(x-500,y-750,k);
            end

            if((y>1300)&&(y<=right_y+1300)&&(x>500)&&(x<=right_x+500))
                canvas_mask(x,y,k) = right(x-500,y-1300,k);
            end
        end
    end
end
figure
imshow(uint8(canvas_mask))
%%
% convert the selected points to cartesian coordinates
cvs_left =[];
for i =1:4
    pts = selected_key_left(i,:).Location;
    x = pts(1) + 200 - 0.5;
    y = 1500 -500- pts(2) + 0.5;
    cvs_left = [cvs_left;x,y];
end

cvs_mid_left =[];
for i =1:4
    pts = selected_key_mid_left(i,:).Location;
    x = pts(1) + 750-0.5;
    y = 1000 - pts(2) + 0.5;
    cvs_mid_left = [cvs_mid_left;x,y];
end

cvs_right =[];
for i =1:4
    pts = selected_key_right(i,:).Location;
    x = pts(1) + 1300-0.5;
    y = 1000 - pts(2) + 0.5;
    cvs_right = [cvs_right;x,y];
end

cvs_mid_right =[];
for i =1:4
    pts = selected_key_mid_right(i,:).Location;
    x = pts(1) + 750-0.5;
    y = 1000 - pts(2) + 0.5;
    cvs_mid_right = [cvs_mid_right;x,y];
end
%%
% calculate the transfer matrix on cartesian coordinates
left2mid_matrix = solve_matrix(cvs_left,cvs_mid_left);
right2mid_matrix = solve_matrix(cvs_right,cvs_mid_right);

reverse_left = eye(3)/left2mid_matrix;
reverse_right = eye(3)/right2mid_matrix;

reverse_left =reverse_left./reverse_left(3,3);
reverse_right =reverse_right./reverse_right(3,3);
%%
% inverse mapping the points onto canvase
canvas_final = zeros(1500,2000,3);
for k =1:3
    for i = 1:1500
        for j = 1:2000
            iter = 0;
            temp = 0.0;
            x = j-0.5;
            y = 1500+0.5-i;

            vector = reverse_left*[x y 1]';
            cart_x = vector(1)/vector(3);
            cart_y = vector(2)/vector(3);

            i0 = 1000.5-cart_y;
            j0 = cart_x-200+0.5;

            if((i0>1)&&(i0<left_x)&&(j0>1)&&(j0<left_y))
                temp = temp+left(floor(i0),floor(j0),k);
                iter = iter+1;
            end


            x = j-0.5;
            y = 1500-0.5-i;
            vector_right = reverse_right*[x y 1]';
            cart_x = vector_right(1)/vector_right(3);
            cart_y = vector_right(2)/vector_right(3);

            i0 = 1000.5-cart_y;
            j0 = cart_x-1300+0.5;

            if((i0>1)&&(i0<right_x)&&(j0>1)&&(j0<right_y))
                temp = temp+right(floor(i0),floor(j0),k);
                iter = iter+1;
            end
            
            if((j>750)&&(j<=mid_y+750)&&(i>500)&&(i<=mid_x+500))%&&(temp==0))
                temp = temp + middle(i-500,j-750,k);
                iter =iter+1;
            end

            
            if (iter >0)
                canvas_final(i,j,k) = temp/iter;
            end
        end
    end
end

figure
imshow(uint8(canvas_final))
% imwrite(uint8(canvas_final),'stitich.png')
