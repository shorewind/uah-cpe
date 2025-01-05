module Clock_24_Hour_behavioral (
	input clk,
	input reset_time,
	input set_time,
	input inc_sec,
	input [23:0] time_in,
	output reg [23:0] time_out
);

	// internal registers for counters and carry bits
	reg [3:0] hr_tens, hr_ones, min_tens, min_ones, sec_tens, sec_ones;
	reg c_out_sec, c_out_min, c_out_hr;

	// counter and carry logic
	always @(posedge clk or posedge reset_time or posedge set_time)
		begin
			if (reset_time)  // async clear
				begin
					hr_tens <= 4'd0;
					hr_ones <= 4'd0;
					min_tens <= 4'd0;
					min_ones <= 4'd0;
					sec_tens <= 4'd0;
					sec_ones <= 4'd0;
					c_out_sec <= 1'b0;
					c_out_min <= 1'b0;
					c_out_hr <= 1'b0;
				end
			else if (set_time)  // async load
				begin
					hr_tens <= time_in[23:20];
					hr_ones <= time_in[19:16];
					min_tens <= time_in[15:12];
					min_ones <= time_in[11:8];
					sec_tens <= time_in[7:4];
					sec_ones <= time_in[3:0];
					c_out_sec <= 1'b0;
					c_out_min <= 1'b0;
					c_out_hr <= 1'b0;
				end
			else  // synchronous counter
				begin						
					// seconds
					if (sec_ones == 4'd9 && sec_tens == 4'd5)  // threshold value
						begin
							sec_ones <= 4'd0;
							sec_tens <= 4'd0;
							c_out_sec <= 1'b1;  // carry to minutes
							// minutes
							if (min_ones == 4'd9 && min_tens == 4'd5)
								begin
									min_ones <= 4'd0;
									min_tens <= 4'd0;
									c_out_min <= 1'b1;
									// hours
									if (hr_ones == 4'd3 && hr_tens == 4'd2)
										begin
											hr_ones <= 4'd0;
											hr_tens <= 4'd0;
										end
									else if (hr_ones == 4'd9)
										begin
											hr_ones <= 4'd0;
											hr_tens <= hr_tens + 1;
										end
									else hr_ones <= hr_ones + 1;
									c_out_min <= 1'b0;  // reset minutes carry
								end
							else if (min_ones == 4'd9)
								begin
									min_ones <= 4'd0;
									min_tens <= min_tens + 1;
								end
							else min_ones <= min_ones + 1;
							c_out_sec <= 1'b0;  // reset seconds carry
							
						end
					else if (sec_ones == 4'd9)  // carry to tens place
						begin
							sec_ones <= 4'd0;
							sec_tens <= sec_tens + 1;
						end
					else sec_ones <= sec_ones + 1;

				end
		end

		
	// output updated time
	always @(*)
		begin
			time_out = {hr_tens, hr_ones, min_tens, min_ones, sec_tens, sec_ones};
		end

endmodule
