% Qirui Sun
% USC ID: 1140685892
% qiruisun@usc.edu
% Submission Date: 3/12/2021

function [result]  = solve_matrix(cvs_in,cvs_out)
    syms h11 h12 h13 h21 h22 h23 h31 h32
    eqns = [h11*cvs_in(1,1) + h12*cvs_in(1,2) + h13 == cvs_out(1,1)*(h31*cvs_in(1,1) + h32*cvs_in(1,2) + 1),...
            h21*cvs_in(1,1) + h22*cvs_in(1,2) + h23 == cvs_out(1,2)*(h31*cvs_in(1,1) + h32*cvs_in(1,2) + 1),...
            h11*cvs_in(2,1) + h12*cvs_in(2,2) + h13 == cvs_out(2,1)*(h31*cvs_in(2,1) + h32*cvs_in(2,2) + 1),...
            h21*cvs_in(2,1) + h22*cvs_in(2,2) + h23 == cvs_out(2,2)*(h31*cvs_in(2,1) + h32*cvs_in(2,2) + 1),...
            h11*cvs_in(3,1) + h12*cvs_in(3,2) + h13 == cvs_out(3,1)*(h31*cvs_in(3,1) + h32*cvs_in(3,2) + 1),...
            h21*cvs_in(3,1) + h22*cvs_in(3,2) + h23 == cvs_out(3,2)*(h31*cvs_in(3,1) + h32*cvs_in(3,2) + 1),...
            h11*cvs_in(4,1) + h12*cvs_in(4,2) + h13 == cvs_out(4,1)*(h31*cvs_in(4,1) + h32*cvs_in(4,2) + 1),...
            h21*cvs_in(4,1) + h22*cvs_in(4,2) + h23 == cvs_out(4,2)*(h31*cvs_in(4,1) + h32*cvs_in(4,2) + 1)];
    vars = [h11 h12 h13 h21 h22 h23 h31 h32];
    [solh11, solh12, solh13, solh21, solh22, solh23, solh31, solh32] = solve(eqns, vars);
    result = [double(solh11), double(solh12), double(solh13); double(solh21), double(solh22),double(solh23); double(solh31),double(solh32),1];
end
