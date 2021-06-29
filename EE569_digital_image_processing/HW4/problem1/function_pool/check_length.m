function output = check_length(input,length)
if input<1
    output = 2 - input;
elseif input>length
        output = 2*length - input;
else
    output = input;
end
end
        