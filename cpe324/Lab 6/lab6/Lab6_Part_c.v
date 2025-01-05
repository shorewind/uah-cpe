// lab6 Template
// Waveform Generation using Pulse Density Modulation

`timescale 1ns/1ps


module Lab6_Part_c (input clk, output reg d_bit);


   reg en;
	reg signed [1:-14] wave_out1, wave_out2;


   // 16 bit signed integer 50 point
	// lookup table for wave function	
   reg signed [1:-14] out_table[0:49];
	reg signed [1:-14] audio[0:100035];
	
	initial
		begin:wave_table_init
			$readmemh("uah_fight_song_8_offset.txt", audio);
	
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


		end

		
   always @(posedge clk)
      begin:Audio_Out

	      reg [12:0] count;
			reg [12:0] base_count;
			reg [16:0] index;
			
			base_count = 13'd6250;  // 50MHz/8kHz
			if (count)
				begin
					count = count - 13'd1;
				end
			else
				begin
					if (index >= 17'd100035) index = 17'd0;
					else index = index + 17'd1;
					wave_out2 = {1'd0, audio[index], 7'd0};  // {audio[index], 8'd0} for 8-bit
					count = base_count;
				end
				
		end
		
   always @(posedge clk)
      begin:Wave_Out
			reg [5:0] index;
			
			if (index >= 6'd49) index = 6'd0;
			else index = index + 6'd1;
			wave_out1 = out_table[index];
				
		end
				
   always @ (posedge clk)
      begin:DtoA_convert
		   // declaring local variable to
			// named section DtoA_convert
         reg signed [3:-28] ge; // error term	
			
	      pdm(d_bit,wave_out1,wave_out2,ge);
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
