// ds1620 testbench
`timescale 1us/100ps

module lab8_tb2;

	parameter CLK_PERIOD = 1000;  // 1000us = 1ms period = 1kHz freq

	// inputs
	reg CLR = 1'b0;
	reg DQ_IN;
	reg CLK_IN = 1'b1;
	wire [8:0] temp1 = 9'b000110010;  // 25*C with 0 LSB for .0 decimal
	wire [8:0] temp2 = 9'b000100010;  // 17*C with 0 LSB for .0 decimal

	// outputs
	wire CLK_OUT;
	wire RST;
	wire TRI_EN;
	wire DQ_OUT;
	wire [7:0] TEMP;
	integer i;  // for loop counter

	// CLK_IN
	always #((CLK_PERIOD / 2)) CLK_IN = ~CLK_IN;  // toggle CLK_IN every half period for 50% duty cycle

	// unit under test
	DS1620_INTERFACE UUT (
		.CLR(CLR), .CLK_IN(CLK_IN), .DQ_IN(DQ_IN),
		.CLK_OUT(CLK_OUT), .RST(RST), .TRI_EN(TRI_EN),
		.DQ_OUT(DQ_OUT), .TEMP(TEMP)
	);

	initial begin
		// set CLR to logic 1 for one clock cycle
		CLR = 1'b1;
		#(CLK_PERIOD);
		// drive CLR to logic 0
		CLR = 1'b0;
		// start of first 31 cycle waveform
		#(9*CLK_PERIOD);
		#(CLK_PERIOD / 2);  // align with falling edge
		for (i = 0; i < 9; i = i + 1) begin
			DQ_IN = temp1[i];  // set DQ_IN with bit of input temp
			#(CLK_PERIOD);     // delay one clock cycle until next read
		end
		#(CLK_PERIOD / 2);  // align with rising edge
		#(12*CLK_PERIOD);   // finish
		// start of second 31 cycle waveform
		#(9*CLK_PERIOD);
		#(CLK_PERIOD / 2);  // align with falling edge
		for (i = 0; i < 9; i = i + 1) begin
			DQ_IN = temp2[i];  // set DQ_IN with bit of input temp
			#(CLK_PERIOD);     // delay one clock cycle until next read
		end
		#(CLK_PERIOD / 2);  // align with rising edge
		#(12*CLK_PERIOD);   // finish
	end

endmodule
