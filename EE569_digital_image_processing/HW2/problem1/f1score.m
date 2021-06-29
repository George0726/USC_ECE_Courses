% //Qirui Sun
% //USC ID: 1140685892
% //qiruisun@usc.edu
% //Submission Date: 2/23/2021

precision = 0:0.01:1;
recall = 0:0.01:1;

[XX,YY] = meshgrid(precision,recall);

F = (2.*XX.*YY)./(XX +YY);
mesh(precision,recall,F);



