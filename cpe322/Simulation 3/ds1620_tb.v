// ds1620 testbench
`timescale 1us/100ps

module lab8_tb1;

	parameter CLK_PERIOD = 1000;  // 1ms period = 1kHz freq

	// inputs
	reg CLR = 1'b0;
	reg DQ_IN;
	reg CLK_IN = 1'b1;

	// outputs
	wire CLK_OUT;
	wire RST;
	wire TRI_EN;
	wire DQ_OUT;
	wire [7:0] TEMP;

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
		// two periods of the 31 cycle waveform
		#(31*CLK_PERIOD);
	end
endmodule
