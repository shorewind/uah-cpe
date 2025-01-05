// Verilog  Module to input temperature data from the DS 1620 
// temperature IC
// template by
// B. Earl Wells, ECE Department University of Alabama in Huntsville
// inputs:
//    CLR an active high clear input which will reset internal signals 
//    and restart the temperature acquisition process
//    CLK_IN the input clock (must be less than 1 MHZ)
//    DQ_IN the input signal that is used to input data from the
//        external DS 1620 IC. The 1620 only produces this data in
//        response to a command issued from the external device that
//        occurred over the "three wire" communication port. When data
//        is sent from the DS 1620, it is in a bit serial manner. Such 
//        data is assumed to be valid at the rising edge of the CLK_OUT
//        signal. In this design the DQ_IN signal is used to receive
//        the 9 bit Celcius temperature from the DS 1620
// outputs:
//    TEMP the temperature acquired from the DS 1620 in 9 bit two's
//        complement format. (Output Resolution is 1/2 degree C)
//    CLK_OUT the clocking signal that drives the DS 1620 during its
//        "three wire" communication and the start conversion signal
//        that causes the DS 1620 to make the next temperature
//        conversion
//    RST the reset control line of the DS 1620 which is high during 
//        "three wire" communication but low in all other cases
//    TRI_EN the controling signal for the external tristate buffer.
//        This signal indicates when the DQ input of the external 
//        DS 1620 will be driven by DQ_OUT (this occurs when TRI_EN='1')
//        or when the DS 1620 will drive the DQ_IN input (this occurs 
//        when TRI_EN='0') 
//    DQ_OUT the output signal that drives the DS 1620 during "three 
//        wire" communication. Communication along this signal occurs 
//        in close coordination with the CLK_OUT signal. Such 
//        communication is bit serial with the valid logic value being 
//        placed on the DQ_OUT line at least 50 ns before the rising 
//        edge of CLK_OUT. Note in this design DQ_OUT is used to send 
//        the read temperature command to the DS 1620.

module DS1620_INTERFACE(input CLR, CLK_IN, DQ_IN, 
   output CLK_OUT,RST,TRI_EN, output reg DQ_OUT, output reg [8:0] TEMP);

	reg and_mask=1, or_mask=1;
	reg[4:0] cycle_count=5'd0;
	reg[8:0] next_temp;
	reg rst=0;
	reg tri_en=0;
	reg dq_out=1'bz;
	
	// rising edge signals
	always @(posedge CLK_IN)
	begin
		// CLR
		if(CLR)
			cycle_count = 5'd0;
		else begin
			// cycle counter
			if (cycle_count < 5'd31)
				cycle_count = cycle_count + 5'd1;
			else
				cycle_count = 5'd1;
		end
				
		// or_mask
		if (cycle_count >= 5'd2 && cycle_count <= 5'd18)
			or_mask = 0;  // or_mask on the CLK_OUT
		else
			or_mask = 1;
			
		// latch in the next_temp
		if (cycle_count >= 5'd11 && cycle_count <= 5'd19)
			next_temp[cycle_count - 5'd11] = DQ_IN;  // receive serial bit values of temp
			
	end

	// falling edge signals
	always @(negedge CLK_IN)
	begin	
		// RST
		if (cycle_count >= 5'd1 && cycle_count <= 5'd19)
			rst = 1;
		else
			rst = 0;
		
		// DQ_OUT
		if (cycle_count == 5'd3 || cycle_count == 5'd5 || cycle_count == 5'd7 || cycle_count == 5'd9)
			dq_out = 1;
		else if (cycle_count == 5'd2 || cycle_count == 5'd4 || cycle_count == 5'd6 || cycle_count == 5'd8)
			dq_out = 0;
		else
			dq_out = 1'bz;
		
		// TRI_EN
		if (cycle_count >= 5'd2 && cycle_count <= 5'd9)
			tri_en = 1;  // send read temperature command to sensor
		else
			tri_en = 0;
			
		// TEMP
		if (cycle_count == 5'd19)
			TEMP = next_temp;  // output new temperature data
			
		// and_mask
		if (cycle_count == 5'd26)
			and_mask = 0;  // and_mask on the CLK_OUT
		else
			and_mask = 1;
	end

	// assign outputs
	assign CLK_OUT = (CLK_IN || or_mask) && and_mask;
	assign TRI_EN = tri_en;
	assign RST = rst;
	always @(*) begin
		DQ_OUT = dq_out;
	end
endmodule
