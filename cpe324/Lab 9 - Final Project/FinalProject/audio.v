module audio (input clk, input [7:0] vol, output reg d_bit);

	reg signed [1:-14] wave_out;
	reg signed [1:-14] audio[0:4873];
	
	initial
		begin:wave_table_init
			$readmemh("audio_16_signed.txt", audio);
	
		// 16 bit signed fixed point encoding of 1.0 assuming a 
		//1 bit mantisa and a 14 bit fraction	
	   `define ONE_16 {1'b0,1'b1,14'b0} 

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
					if (index >= 17'd4873) index = 17'd0;
					else index = index + 17'd1;
					wave_out = audio[index];  // {audio[index], 8'd0} for 8-bit
					count = base_count;
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