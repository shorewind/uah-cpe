// 4-bit to 4-bit keypad code converter model
// converts 4-bit keypad code into a 4-bit 
// value expressed by Table 1 in Lab 4 
// assignment
module code_cnv(O,I);
   input [3:0] I;
   output reg [3:0] O;

	// add your modeling code here
	always @ (I)
             // straight-through connection
      O = I; // add remove and replace with
             // code conversion model

endmodule 