fc = 750;
fs = 48000;
k = tan(pi*fc/fs);

% Fix the b coefficient definition - using proper array syntax
b = [k^2/(k^2+2*k+1), 2*(k^2/(k^2+2*k+1)), k^2/(k^2+2*k+1)];
a = [1, (2*(k^2-1)/(k^2+2*k+1)), ((k^2-2*k+1)/(k^2+2*k+1))];

n = 4096;

% https://matrixlab-examples.com/impulse-function.html
function y = diracdelta(n)
    y = zeros(n,1); 
    y(1) = 1;
end

x = diracdelta(n);
y = filter(b, a, x);

% Compute frequency response
[h,w] = freqz(b, a, 4096, fs); % Add fs to get frequency in Hz directly!

% Plot magnitude in dB
subplot(2,1,1);

% logarithmic frequency axis (avoiding w=0 since log(0) is undefined)
% Find indices where w > 0 (excluding DC)
nonzero_indices = w > 0;

% Plot with logarithmic x-axis - w is already in Hz now!
semilogx(w(nonzero_indices), 20*log10(abs(h(nonzero_indices))), 'b-', 'LineWidth', 1.5);

xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
xlim([min(w(nonzero_indices)), fs/2]);  % Scale from minimum positive frequency to Nyquist (fs/2)
grid on;

% vertical line at cutoff frequency
hold on;
xline(fc, 'r--', ['fc = ' num2str(fc) ' Hz'], 'LabelOrientation', 'horizontal', 'FontSize', 10);
hold off;

subplot(2,1,2);
% Phase response
semilogx(w(nonzero_indices), angle(h(nonzero_indices)) * 180/pi, 'b-', 'LineWidth', 1.5);
xlabel('Frequency (Hz)');
ylabel('Phase (degrees)');
xlim([min(w(nonzero_indices)), fs/2]);
grid on;

% Add vertical line at cutoff frequency to phase plot as well
hold on;
xline(fc, 'r--', ['fc = ' num2str(fc) ' Hz'], 'LabelOrientation', 'horizontal', 'FontSize', 10);
hold off;

% figure for pole-zero plot
figure;
sys = tf(b, a, 1/fs);  % Add sample time for discrete-time system
pzmap(sys);
title('Pole-Zero Plot');