% my sine program

% housekeeping commands
    clc; close all; clear;
    
% x drum head

    x_ft = 0:0.01:5;
    
% make a y-vector displacement of the drum head sine

    y_ft = zeros(1, length(x_ft));  % initialize vector of zeros
    y2_ft = zeros(1, length(x_ft));
    
    for idx = 1:length(x_ft)
        y_ft(idx) = sin(2*pi*x_ft(idx));
        y2_ft(idx) = sin(4*pi*x_ft(idx));  % transformation
    end
    
% display

    plot(x_ft, y_ft)
    grid on
    xlabel('x-dist [ft]')
    ylabel('y-dist [ft]')
    title('my first graph')
    
    hold on
    plot(x_ft, y2_ft)
    