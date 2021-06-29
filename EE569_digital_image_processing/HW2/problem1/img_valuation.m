% //Qirui Sun
% //USC ID: 1140685892
% //qiruisun@usc.edu
% //Submission Date: 2/23/2021

clear; clc;
addpath(genpath('C:\Users\Sunqr\OneDrive - University of Southern California\USC\EE569\HW2\problem1\edge  structure\edges/toolbox/')); savepath;
% load('ski_person_canny_edge.mat');
load('elephant_canny_edge.mat')
%%
edge1 = single(edge1);
edge2 = single(edge2);
edge3 = single(edge3);

%%
% [thrs,cntR,sumR,cntP,sumP,V,K] = edgesEvalImg_modified( edge1, 'ski_person_GT.mat');

% [thrs,cntR1,sumR1,cntP1,sumP1,V,K] = edgesEvalImg_modified_canny( edge1, 'ski_person_GT.mat');
% [thrs,cntR2,sumR2,cntP2,sumP2,V,K] = edgesEvalImg_modified_canny( edge2, 'ski_person_GT.mat');
% [thrs,cntR3,sumR3,cntP3,sumP3,V,K] = edgesEvalImg_modified_canny( edge3, 'ski_person_GT.mat');

[thrs,cntR1,sumR1,cntP1,sumP1,V,K] = edgesEvalImg_modified_canny( edge1, 'elephant_GT.mat');
[thrs,cntR2,sumR2,cntP2,sumP2,V,K] = edgesEvalImg_modified_canny( edge2, 'elephant_GT.mat');
[thrs,cntR3,sumR3,cntP3,sumP3,V,K] = edgesEvalImg_modified_canny( edge3, 'elephant_GT.mat');

% [thrs,cntR,sumR,cntP,sumP,V,K] = edgesEvalImg_modified( E_ski, 'ski_person_GT.mat');
% save('elephant_sobel_stat.mat','cntP','cntR','sumP','sumR')

cntR = [cntR1;cntR2;cntR3];
cntP = [cntP1;cntP2;cntP3];
sumR = [sumR1;sumR2;sumR3];
sumP = [sumP1;sumP2;sumP3];
save('elephant_canny_stat.mat','cntP','cntR','sumP','sumR')