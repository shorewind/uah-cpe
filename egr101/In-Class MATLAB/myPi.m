% pi estimation
clear; clc;

N = 1000;
oddSeries = 1:2:N;
signs = 0:(length(oddSeries)-1);
altSigns = (-1).^signs;
4*sum(altSigns./oddSeries)
