// Eight-Bit Sub/Add Test Bench
`timescale 1ns/100ps

module eight_bit_sub_add_tb;
// internal wires and register declarations
wire [7:0] D_S;
wire B_COUT;

reg [7:0] A,B;
reg B_CIN, SUB_ADD;

// unit under test
eight_bit_sub_add  UUT  (.D_S(D_S), .B_COUT(B_COUT),
    .A(A),.B(B), .B_CIN(B_CIN),.SUB_ADD(SUB_ADD));

initial
   begin
	// 1) Add no carry on B_COUT
	SUB_ADD = 0;  // Add mode
	B_CIN = 0;    // No Carry in
	A = 17;       // A = 8'b00010001
	B = 2;        // B = 8'b00000010
		      // D_S = A + B = 19 -- 8'b00010011

	// 2) Subtract no borrrow on B_COUT
	#100  // 100ns delay
	SUB_ADD = 1;  // Subtract mode
	B_CIN = 0;    // No Borrow in
	A = 17;       // A = 8'b00010001
	B = 2;        // B = 8'b00000010
		      // D_S = A - B = 15 -- 8'b00001111

	// 3) Add with pending carry on B_CIN
	#100  // 100ns delay
	SUB_ADD = 0;  // Add mode
	B_CIN = 1;    // Carry in
	A = 17;       // A = 8'b00010001
	B = 2;        // B = 8'b00000010
		      // D_S = A + B + B_CIN = 20 -- 8'b00010100

	// 4) Subtract with pending borrow on B_CIN
	#100  // 100ns delay
	SUB_ADD = 1;  // Subtract mode
	B_CIN = 1;    // Borrow in
	A = 17;       // A = 8'b00010001
	B = 2;        // B = 8'b00000010
		      // D_S = A - B - B_CIN = 14 -- 8'b00001110

	// 5) Add where internal carry propogates from LSB to B_COUT
	#100  // 100ns delay
	SUB_ADD = 0;  // Add mode
	B_CIN = 0;    // No Carry in
	A = 253;      // A = 8'b11111101
	B = 3;        // B = 8'b00000010
		      // D_S = A + B = 256 -- 8'b00000000, B_COUT = 1

	// 6) Subtract where borrow propogates from LSB to borrow request on B_COUT
	#100  // 100ns delay
	SUB_ADD = 1;  // Subtract mode
	B_CIN = 0;    // Borrow in
	A = 2;        // A = 8'b00000010
	B = 3;        // B = 8'b00000011
		      // D_S = A - B = -1 -- 8'b11111111, B_COUT = 1

	// 7) Add that causes an overflow into the carry bit
	#100  // 100ns delay
	SUB_ADD = 0;  // Add mode
	B_CIN = 0;    // No Carry in the input from a previous stage
	A = 128;      // A = 8'b10000000
	B = 128;      // B = 8'b10000000
		      // D_S = A + B = 256 -- 8'b00000000, B_COUT = 1

	// 8) Subtract larger positive number from smaller positive number
	#100  // 100ns delay
	SUB_ADD = 1;  // Subtract mode
	B_CIN = 0;    // No Borrow in the input from a previous stage
	A = 1;        // A = 8'b00000001
	B = 3;        // B = 8'b00000011
		      // D_S = A - B = -2 -- 8'b11111110, B_COUT = 1
   end
endmodule
