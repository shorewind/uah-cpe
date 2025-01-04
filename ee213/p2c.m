function [n] = p2c(m,a)
% converts polar number (angle in deg) to cartesian
  
r = m*cosd(a);
i = m*sind(a);
n = r + i*j;

end

