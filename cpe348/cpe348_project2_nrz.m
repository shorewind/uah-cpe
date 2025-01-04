% Define the bit sequence
bit_sequence = [1 1 0 0 1 0 1 0 1];

% Define time steps (one timestep per bit)
time_steps = 0:length(bit_sequence);  % One extra time step for the end of the last bit

% Extend the bit sequence to match the stairs plot
extended_sequence = repelem(bit_sequence, 2);

% Plot the bit sequence
stairs(time_steps, [bit_sequence, bit_sequence(end)], 'LineWidth', 2);
xlabel('Time');
ylabel('Bit Value');
title('NRZ Encoding Signal');
grid on;
ylim([-0.5, 1.5]);  % Set Y-axis limits to emphasize bit values
