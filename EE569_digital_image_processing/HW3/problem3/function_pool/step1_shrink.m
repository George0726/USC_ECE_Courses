function M = step1_shrink(img,bond)
    [m,n] = size(img);
    M = zeros(m,n);
    for i=1:m
        for j=1:n
%             if img(i,j) == bin2dec('00000000')
%                 M(i,j) = 0;
%                 continue;
%             end
            switch bond(i,j)
                case 1 
                    M(i,j) = img(i,j) == bin2dec('00100000') || ...
                          img(i,j) == bin2dec('10000000') || ...
                          img(i,j) == bin2dec('00000100') || ...
                          img(i,j) == bin2dec('00000001');
                case 2 
                    M(i,j) = img(i,j) == bin2dec('00001000') || ...
                          img(i,j) == bin2dec('01000000') || ...
                          img(i,j) == bin2dec('00010000') || ...
                          img(i,j) == bin2dec('00000010');
                case 3 
                    M(i,j) = img(i,j) == bin2dec('00101000') || ...
                          img(i,j) == bin2dec('01100000') || ...
                          img(i,j) == bin2dec('11000000') || ...
                          img(i,j) == bin2dec('10010000') || ...
                          img(i,j) == bin2dec('00010100') || ...
                          img(i,j) == bin2dec('00000110') || ...
                          img(i,j) == bin2dec('00000011') || ...
                          img(i,j) == bin2dec('00001001');
                case 4 
                    M(i,j) = img(i,j) == bin2dec('00101001') || ...
                          img(i,j) == bin2dec('11100000') || ...
                          img(i,j) == bin2dec('10010100') || ...
                          img(i,j) == bin2dec('00000111');
                case 5 
                    M(i,j) = img(i,j) == bin2dec('11001000') || ...
                          img(i,j) == bin2dec('01001001') || ...
                          img(i,j) == bin2dec('01110000') || ...
                          img(i,j) == bin2dec('00101010') || ...
                          ... 
                          img(i,j) == bin2dec('01101000') || ...
                          img(i,j) == bin2dec('11010000') || ...
                          img(i,j) == bin2dec('00010110') || ...
                          img(i,j) == bin2dec('00001011');
                case 6 
                    M(i,j) = img(i,j) == bin2dec('11001001') || ...
                          img(i,j) == bin2dec('01110100') || ...
                          img(i,j) == bin2dec('11101000') || ...
                          img(i,j) == bin2dec('01101001') || ...
                          img(i,j) == bin2dec('11110000') || ...
                          img(i,j) == bin2dec('11010100') || ...
                          img(i,j) == bin2dec('10010110') || ...
                          img(i,j) == bin2dec('00010111') || ...
                          img(i,j) == bin2dec('00001111') || ...
                          img(i,j) == bin2dec('00101011');
                case 7 
                    M(i,j) = img(i,j) == bin2dec('11101001') || ...
                          img(i,j) == bin2dec('11110100') || ...
                          img(i,j) == bin2dec('10010111') || ...
                          img(i,j) == bin2dec('00101111');
                case 8 
                    M(i,j) = img(i,j) == bin2dec('01101011') || ...
                          img(i,j) == bin2dec('11111000') || ...
                          img(i,j) == bin2dec('11010110') || ...
                          img(i,j) == bin2dec('00011111');
                case 9 
                    M(i,j) = img(i,j) == bin2dec('11101011') || ...
                          img(i,j) == bin2dec('01101111') || ...
                          img(i,j) == bin2dec('11111100') || ...
                          img(i,j) == bin2dec('11111001') || ...
                          img(i,j) == bin2dec('11110110') || ...
                          img(i,j) == bin2dec('11010111') || ...
                          img(i,j) == bin2dec('10011111') || ...
                          img(i,j) == bin2dec('00111111');
                case 10
                    M(i,j) = img(i,j) == bin2dec('11101111') || ...
                          img(i,j) == bin2dec('11111101') || ...
                          img(i,j) == bin2dec('11110111') || ...
                          img(i,j) == bin2dec('10111111');
                otherwise
                    M(i,j) = 0;
            end
        end
    end
end
    