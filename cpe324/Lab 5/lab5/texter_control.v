// Single Button Texter -- texter control module
// -- texter_control.v file
// (c) 4/5/2017 B. Earl Wells, University of Alabama in Huntsville
// all rights reserved -- for academic use only.
//
// This is the main texter_control module for the single button texter.
// This module should implement the design that was described by the
// ASM Chart that was presented in Laboratory 10 of the CPE 324 class. 
// The design is to be reset to state S0 whenever the reset signal is
// at a logic high. Whenever the reset signal is at a logic low it 
// should fully implement the state machine specified by the SM chart. 
// The clock signal is assumed to be a 50% duty cycle clock that is the
// same clock that drives the other functional units that
// are being controlled by this module (50 Mhz on the DE2-115). The other
// input and output signals are all assumed to be active high. The 
// input signal, sw, is controlled by the user and the other inputs 
// are status inputs that come directly from the functional units
// that are being controlled. These inputs will change their states in
// direct response to your controlling outputs that you provide. The 
// outputs are all assumed to be active for a one clock duration as 
// indicated by the ASM chart.
module texter_control(input clk, reset, sw, space, dash_dit, dc_error,
   output reg nxt_bit, nxt_char, out_char, out_space, tm_reset,
   sp_load, back_sp);
	
	reg [2:0] state=0, next_state=0;

	// S0 to S5 states (6 cases)
	always @ (state, reset, sw, space, dash_dit, dc_error)
		begin
			nxt_bit=0; nxt_char=0; out_char=0; out_space=0; tm_reset=0; sp_load=0; back_sp=0;
		
			if (reset) next_state=0;
			else
				case(state)
					0: if (sw) begin tm_reset=1; nxt_char=1; next_state=1; end
						else begin next_state=0; end
					1: if (sw) next_state=1;
						else
							if (space) begin back_sp=1; next_state=0; end
							else
								begin
								nxt_bit=1;
								if (dash_dit) begin sp_load=1; next_state=2; end
								else next_state=2;
								end
					2: begin tm_reset=1; next_state=3; end
					3: if (sw) begin sp_load=1; next_state=4; end
						else
							if (!dash_dit) next_state=3;
							else
								if (dc_error) next_state=0;
								else begin out_char=1; next_state=5; end
					4: begin tm_reset=1; next_state=1; end
					5: if (sw) begin nxt_char=1; tm_reset=1; next_state=1; end
						else
							if (space) begin out_space=1; next_state=0; end
							else next_state=5;	
				endcase
					
		end		

	always @ (posedge clk)
		state = next_state;
   
endmodule
