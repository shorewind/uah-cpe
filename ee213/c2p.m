function [y] = c2p(x)
% converts cartesian number to polar (angle in deg)

m = abs(x);
a = angle(x)*180/pi;
y = [m,a];

end

