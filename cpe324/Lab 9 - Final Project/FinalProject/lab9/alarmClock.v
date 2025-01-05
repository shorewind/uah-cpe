module alarmClock(
		input CLK, set_clock, set_alarm, set_sec, set_min, set_hr, increment, reset,
		output reg alarm_indicator,
		output audio_out_bit,
		output [6:0] HH, hh, MM, mm, SS, ss
	);

	// internal signals
	reg [23:0] clock_in;
	wire [23:0] clock_out;
	reg [23:0] alarm_time;
	reg [23:0] display_time;
	wire reset_clock=1'b0;
	wire clk_1hz;
	reg set_time=1'b1;
	reg alarm_active=1'b0;
	reg alarm_en=1'b0;
	reg [7:0] vol=8'b00000000;
	
	initial begin
		clock_in = 24'h000000;
		alarm_time = 24'h000000;
	end
	
	// generate 1 Hz clk signal from 50 MHz CLK
	fiftyM_to_one_clk one_hz_clk(.clk(CLK), .clk_out(clk_1hz));
	
	// generate alarm sound from txt data file
	audio alarm_sound(.clk(CLK), .vol(vol), .d_bit(audio_out_bit));
 
	// KEY0: increment time based on switch settings
	// SW0: set clock mode
	// SW1: set seconds, SW2: set minutes, SW3: set hours
	// SW4: set alarm mode
	always @(posedge increment) begin
		if (set_clock && !set_alarm) begin  // set clock
			if (set_sec && !set_min && !set_hr) begin  // increment seconds
				if (clock_out[7:0] == 8'h59)
					clock_in[7:0] = 8'h00;
				else if (clock_out[3:0] == 4'h9) begin
					clock_in[7:4] = clock_out[7:4] + 4'h1;
					clock_in[3:0] = 4'h0;
				end else
					clock_in = clock_out + 24'h000001;
			end else if (!set_sec && set_min && !set_hr) begin  // increment minutes
				if (clock_out[15:8] == 8'h59)
					clock_in[15:8] = 8'h00;
				else if (clock_out[11:8] == 4'h9) begin
					clock_in[15:12] = clock_out[15:12] + 4'h1;
					clock_in[11:8] = 4'h0;
				end else
					clock_in = clock_out + 24'h000100;
			end else if (!set_sec && !set_min && set_hr) begin  // increment hours
				if (clock_out[23:16] == 8'h23)
					clock_in[23:16] = 8'h00;
				else if (clock_out[19:16] == 4'h9) begin
					clock_in[23:20] = clock_out[23:20] + 4'h1;
					clock_in[19:16] = 4'h0;
				end else
					clock_in = clock_out + 24'h010000;
			end else
				clock_in = clock_out;  // load stored time
		end else if (!set_clock && set_alarm) begin  // set alarm
			if (set_sec && !set_min && !set_hr) begin  // increment seconds
				if (display_time[7:0] == 8'h59)
					alarm_time[7:0] = 8'h00;
				else if (display_time[3:0] == 4'h9) begin
					alarm_time[7:4] = alarm_time[7:4] + 4'h1;
					alarm_time[3:0] = 4'h0;
				end else
					alarm_time = display_time + 24'h000001;
			end else if (!set_sec && set_min && !set_hr) begin  // increment minutes
				if (display_time[15:8] == 8'h59)
					alarm_time[15:8] = 8'h00;
				else if (display_time[11:8] == 4'h9) begin
					alarm_time[15:12] = display_time[15:12] + 4'h1;
					alarm_time[11:8] = 4'h0;
				end else
					alarm_time = display_time + 24'h000100;
			end else if (!set_sec && !set_min && set_hr) begin  // increment hours
				if (display_time[23:16] == 8'h23)
					alarm_time[23:16] = 8'h00;
				else if (display_time[19:16] == 4'h9) begin
					alarm_time[23:20] = display_time[23:20] + 4'h1;
					alarm_time[19:16] = 4'h0;
				end else
					alarm_time = display_time + 24'h010000;
			end else
				alarm_time = clock_out;  // set alarm to current time
		end else begin
			clock_in = clock_out;  // store current time if not in set mode
		end
	end

	always @(posedge CLK) begin
		alarm_indicator = alarm_active;  // LEDG8: alarm status
		if (set_clock && !set_alarm) begin  // set clock
			set_time = 1'b1;
			display_time = clock_out;
			vol = 8'b00000000;
		end else begin
			set_time = 1'b0;     // active clock
			if (!set_clock && set_alarm) begin  // set alarm
				display_time = alarm_time;
				alarm_active = 1'b1;
				vol = 8'b00000000;
			end else if (!set_clock && !set_alarm) begin  // not setting clock or alarm
				display_time = clock_out;
				if (reset == 0) begin  // KEY2: reset
					vol = 8'b00000000;
					alarm_active = 1'b0;  // no sound and alarm inactive
				end else if (clock_out == alarm_time && alarm_active)  // trigger alarm
					vol = 8'b10000000;  // alarm sounds!
				else if (vol == 8'b10000000 && (clock_out - alarm_time > 24'h000010)) begin  // if over 5 minutes alarm sound
					vol = 8'b00000000;
					alarm_active = 1'b0;  // no sound and alarm inactive
				end
			end
		end
	end
	
	// 24 hour clock
	Clock_24_Hour_behavioral clock_24(.clk(clk_1hz), .reset_time(reset_clock), .set_time(set_time), .inc_sec(inc_sec), .time_in(clock_in), .time_out(clock_out));
	
	// convert digits to hex display
	hex_seven 	Hr(.n(display_time[23:20]), .hex(HH)), 
					hr(.n(display_time[19:16]), .hex(hh)), 
					Mi(.n(display_time[15:12]), .hex(MM)), 
					mi(.n(display_time[11:8]), .hex(mm)), 
					Se(.n(display_time[7:4]), .hex(SS)), 
					se(.n(display_time[3:0]), .hex(ss));

endmodule


module hex_seven(n,hex);
   input [3:0] n;
   output reg [6:0] hex;

	always @ (n)
	   case (n)
		   0  : hex <= 7'b1000000;
		   1  : hex <= 7'b1111001;
		   2  : hex <= 7'b0100100;
		   3  : hex <= 7'b0110000;
		   4  : hex <= 7'b0011001;
		   5  : hex <= 7'b0010010;
		   6  : hex <= 7'b0000010;
		   7  : hex <= 7'b1111000;
         8  : hex <= 7'b0000000;
		   9  : hex <= 7'b0011000;
		   10 : hex <= 7'b0001000;
		   11 : hex <= 7'b0000011;
		   12 : hex <= 7'b1000110;
		   13 : hex <= 7'b0100001;
		   14 : hex <= 7'b0000110;
		   15 : hex <= 7'b0001110;
		   default : hex <= 7'bx;
		endcase

endmodule


module fiftyM_to_one_clk (
    input clk,
    output reg clk_out
);

	reg [24:0] counter;

	always @(posedge clk) begin
		 if (counter == 24999999) begin // 50 MHz / 2 = 25M for half period
			  counter <= 0;
			  clk_out <= ~clk_out;  // toggle
		 end else begin
			  counter <= counter + 1;
		 end
	end

endmodule
