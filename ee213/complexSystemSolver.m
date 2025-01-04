% solves systems of complex equations

% example with results in polar form
syms v1 v2 is
eq1 = 0 == -p2c(4,0)+v1/(5-j)-is; 
eq2 = 0 == -p2c(2,0)+v2/(8+j*2)+is;
eq3 = 0 == v1-v2-p2c(10,-90);
[v1, v2, is] = vpasolve([eq1,eq2,eq3], [v1, v2, is]);
vx = double(c2p(-v1*5/(5-j)))
v1 = c2p(double(v1))
v2 = c2p(double(v2))
is = c2p(double(is))
