clc;clear;

V = 10;
R = 100;
f = 100;
C = 0.00033;
Xc=1/(2*pi*f*C);
Z=sqrt(100^2+Xc^2);
Vrms=V/sqrt(2);

Imax=V/Z;
Irms=Imax/sqrt(2);

VCrms=Irms*Xc;
VCmax=VCrms*sqrt(2);

VRrms=Irms*100;
VRmax=VRrms*sqrt(2);

theta=atand(Xc/R);
