% //Qirui Sun
% //USC ID: 1140685892
% //qiruisun@usc.edu
% //Submission Date: 2/23/2021

clear;
clc;
load('elephant_canny_stat.mat');
% load('elephant_st_stat.mat');

sigma = 0.000;

P = cntP./sumP+sigma;
R = cntR./sumR+sigma;

% filter Nan
% 
% P= P(1:64,:);
% R = R(1:64,:);
%%
% FOR EACH GT
meanp1 = mean(P,1);
meanr1= mean(R,1);

meanF = 2.*meanp1.*meanr1./(meanp1+meanr1);
%%
% FOR EACH THRESHOLD
meanp2 = mean(P,2);
meanr2= mean(R,2);

F = 2 .* meanp2.*meanr2./(meanp2+meanr2);
figure;
plot(0.01:0.01:0.64,F)
xlabel('threshold')
ylabel('F score')
[m,index]=max(F);
axis([0 1 0 1])
