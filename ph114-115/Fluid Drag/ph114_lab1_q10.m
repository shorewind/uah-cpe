m = 1.0; % mass in Kg
radius = 0.1; % in meters
A = pi*(radius)^2; % cross sectional area in m^2
V = (4/3)*pi*(radius)^3;  % volume in m^3
C = 0.47; % aerodynamic coef. of sphere Unitless
p = 998.2; % density of water at 20 degrees C in kg/m^3
g = 9.8; % m/s^2
n = 1.002*10^(-3); % coefficient of viscosity for water at 20 degrees C in kg m/s
Vy_0 = 0.0; % m/s initial speed along the y-axis
B = 6*pi*n*radius ; % our “all-inclusive” coef. for drag in a fluid
dt = 0.5; %the time-step over which the solution will be computed.
max_duration = 5000; % the simulation will end at 5000 seconds
duration_sim = 0:dt:max_duration; 
[dum1,time_span] = size(duration_sim); % time_span is the number of time steps to be taken during the simulation. SCALAR
Vy = zeros(1,time_span); % create an array of vertical speed values which are going to be calculated
Vy(1,1) = Vy_0; % the initial speed
for i=2:time_span
    Vy(i) = Vy(i-1) + ay*dt;
    ay = (m*g - B*Vy(i)- p*V*g)/m;
end
plot(duration_sim,Vy,'b')
xlabel('time (s)')
ylabel('vertical speed (ms-1)')