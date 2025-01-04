% ph115 lab 6 question 6
[data, fs] = audioread('boiling_water.m4a');
t = 0:1/fs:(length(data)-1)/fs;
figure
plot(t, data)
xlabel('Time (s)'); 
ylabel('Amplitude');
title('[Q6] Amplitude vs. Time');

m = length(data); 
n = pow2(nextpow2(m));
y = fft(data,n);

f = (0:n-1)*(fs/n); % frequency vector
power = abs(y).^2/n;   % power spectrum      

figure
plot(f(1:floor(n/2)),power(1:floor(n/2)))
xlabel('Frequency (Hz)')
ylabel('Power')
title('[Q6] Power vs. Frequency')

% y = fft(data);
% f = (0:length(y)-1)*fs/length(y);
% figure
% plot(f, y)