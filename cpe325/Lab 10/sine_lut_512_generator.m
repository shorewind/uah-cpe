x=(0:2*pi/512:2*pi);
y=2.0*(sin(x)+1);
dac12=y*4095/4;
dac12r = round(dac12);
dlmwrite('sine_lut_512.h',dac12r, ',');