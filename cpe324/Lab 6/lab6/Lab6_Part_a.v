// lab6 Template
// Waveform Generation using Pulse Density Modulation

`timescale 1ns/1ps


module Lab6_Part_a (input clk,  input [11:0] freq,  input [7:0] vol, output reg d_bit);


   reg en;
	reg signed [1:-14] wave_out;

   // 16 bit signed integer 50 point
	// lookup table for wave function	
   reg signed [1:-14] out_table[0:49];

	initial
	   begin:wave_table_init
	
		// 16 bit signed fixed point encoding of 1.0 assuming a 
		//1 bit mantisa and a 14 bit fraction	
	   `define ONE_16 {1'b0,1'b1,14'b0} 
		// {sign bit, mantisa, fraction}

/*
		// load out_table with 50 point 16 bit integer
      // sqaure wave lookup table information
      // using signed notation
		// Note: lookup table would not be really be needed
      // for such a simple waveform but is used for the
		// sake of generality.
      reg [5:0] i;
      for (i=6'd0; i<6'd25;i=i+6'd1) out_table[i] =   `ONE_16;
      for (i=6'd25;i<6'd50;i=i+6'd1) out_table[i] = -`ONE_16;
*/

/*

      // load out_table with 50 point 16 bit integer
		// triangle wave lookup table information
		// using signed notation
      reg [5:0] i;
      reg signed [1:-14] delta, val;
		delta=`ONE_16*2 /25;
		val=`ONE_16;
		for (i=6'd0; i<6'd25;i=i+6'd1)
		   begin
			   out_table[i]= val;
				val = val - delta;
			end
		for (i=6'd25; i<6'd50;i=i+6'd1)
		   begin
			   out_table[i]= val;
				val = val + delta;
			end
*/

/*

      // load out_table with  
      // 16 bit integer 50 point sine function
	   // lookup table
      //             Fixed-Point    Aprox Val		
      out_table[0]  = 16'h0000; //  0.000000
      out_table[1]  = 16'h0805; //  0.125333
      out_table[2]  = 16'h0fea; //  0.248690
      out_table[3]  = 16'h178f; //  0.368125
      out_table[4]  = 16'h1ed4; //  0.481754
      out_table[5]  = 16'h259d; //  0.587785
      out_table[6]  = 16'h2bcf; //  0.684547
      out_table[7]  = 16'h314f; //  0.770513
      out_table[8]  = 16'h3609; //  0.844328
      out_table[9]  = 16'h39e8; //  0.904827
      out_table[10] = 16'h3cdd; //  0.951057
      out_table[11] = 16'h3edd; //  0.982287
      out_table[12] = 16'h3fdf; //  0.998027
      out_table[13] = 16'h3fdf; //  0.998027
      out_table[14] = 16'h3edd; //  0.982287
      out_table[15] = 16'h3cdd; //  0.951057
      out_table[16] = 16'h39e8; //  0.904827
      out_table[17] = 16'h3609; //  0.844328
      out_table[18] = 16'h314f; //  0.770513
      out_table[19] = 16'h2bcf; //  0.684547
      out_table[20] = 16'h259d; //  0.587785
      out_table[21] = 16'h1ed4; //  0.481754
      out_table[22] = 16'h178f; //  0.368125
      out_table[23] = 16'h0fea; //  0.248690
      out_table[24] = 16'h0805; //  0.125333
      out_table[25] = 16'h0000; //  0.000000
      out_table[26] = 16'hf7fb; // -0.125333
      out_table[27] = 16'hf016; // -0.248690
      out_table[28] = 16'he871; // -0.368125
      out_table[29] = 16'he12c; // -0.481754
      out_table[30] = 16'hda63; // -0.587785
      out_table[31] = 16'hd431; // -0.684547
      out_table[32] = 16'hceb1; // -0.770513
      out_table[33] = 16'hc9f7; // -0.844328
      out_table[34] = 16'hc618; // -0.904827
      out_table[35] = 16'hc323; // -0.951057
      out_table[36] = 16'hc123; // -0.982287
      out_table[37] = 16'hc021; // -0.998027
      out_table[38] = 16'hc021; // -0.998027
      out_table[39] = 16'hc123; // -0.982287
      out_table[40] = 16'hc323; // -0.951057
      out_table[41] = 16'hc618; // -0.904827
      out_table[42] = 16'hc9f7; // -0.844328
      out_table[43] = 16'hceb1; // -0.770513
      out_table[44] = 16'hd431; // -0.684547
      out_table[45] = 16'hda63; // -0.587785
      out_table[46] = 16'he12c; // -0.481754
      out_table[47] = 16'he871; // -0.368125
      out_table[48] = 16'hf016; // -0.248690
      out_table[49] = 16'hf7fb; // -0.125333
	
*/

     // Sawtooth Wave
/*

      // load out_table with 50 point 16 bit integer
		// sawtooth wave lookup table information
		// using signed notation
      reg [5:0] i;
      reg signed [1:-14] delta, val;
		delta=`ONE_16*2 /50;
		val=-`ONE_16;
		for (i=6'd0; i<6'd50;i=i+6'd1)
		   begin
			   out_table[i]= val;
				val = val + delta;
			end
*/


		end

   always @(posedge clk)
      begin:Clock_en
		   // declaring local variables to
			// named section clock_en
	      reg [19:0] count;
			reg [19:0] base_count;
			if (freq) 
			   begin
 			   base_count = 20'd1000000/freq;
			   if (count)
				   begin
			      count = count - 20'd1;
               en=1'b0;
					end
			   else
			      begin
				   en = 1'b1;
			      count = base_count;	
				   end
				end
		end
		
   always @(posedge clk)
	   begin:Waveform_Gen
         // declaring local variable to
			// named section Waveform_Gen			
		   reg[5:0] index;
			
			if (en)
		      begin	
			   if (index>=6'd49) index = 6'd0;
			   else index = index + 6'd1;
            wave_out = out_table[index];
				end
	   end			
				
   always @ (posedge clk)
      begin:DtoA_convert
		   // declaring local variable to
			// named section DtoA_convert
         reg signed [3:-28] ge; // error term	
			
	      pdm(d_bit,wave_out,{2'b00,vol,6'd0},ge);
		end

	        
   // Pulse Density Modulation Task
   task pdm(output d_out, input signed [1:-14] x, scale, 
	   inout signed [3:-28] ge);
		
      // 32-bit fixed point encoding of 1.0 assuming a
      // signed 3 bit mantisa and a 28 bit fraction
      `define ONE_32 {1'b0,3'b001,28'b0} 

      // 32 bit fixed-point holder of x * scale data
      reg signed [3:-28] x_total; 

      begin

      x_total = x*scale; // signal multiplication		

      if (x_total >= ge)
         begin
         d_out = 1;
         ge = ge + (`ONE_32 - x_total);
         end
      else
         begin
         d_out = 0;
         ge = ge - (`ONE_32 + x_total); 
         end
      end
   endtask
	
endmodule	
