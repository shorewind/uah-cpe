clear all
k=0.54;% wild guess
Ta=20;
IC=37;
tspan=[0 10];
f= @(t,x) (-k*(x(1)-Ta)); %define cooling law as a function. t is time and x is the temperature
[t,x]=ode45(f,tspan,IC);
plot(t,x)
title('[Q4] Temperature vs. Time')
xlabel('Time (hrs)')
ylabel('Temperature (°C)')