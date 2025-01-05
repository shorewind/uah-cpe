// Single Button Texter -- AM tone Generation module -- am_tone.v file
// (c) 2/5/2024 B. Earl Wells, University of Alabama in Huntsville
// all rights reserved -- for academic use only.
// 
// This module creates an 440 Hz Amplitude Modulated Sinusoidal Waveform
// that has a carrier frequency of 1 Mhz. The carrier wave is generated
// continuously with the 440 Hz modulating tone being present whenever
// the key input is at a logic high. The module uses pulse density modulation
// to use a digital port to emulate the functionality of an analog one.

module am_tone(input clk, key, output reg d_bit);
  reg signed [1:-14] wave_out1,wave_out2;

  // 16 bit signed integer 50
  // point lookup table for sine wave
  reg signed [1:-14] out_table[0:49];

  // 16 bit integer offset 50 point
  // lookup table for sine wave
  reg signed [1:-14] audio[0:49];
	
   initial
      begin:table_init
      // 16 bit integer 50 point sine function
      // lookup table -- signed values
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
		
      // 16 bit integer 50 point sine function
      // lookup table positive offset         
      //             Fixed-Point    Aprox Val		
      audio[0] = 16'h4000; // 0.000000
      audio[1] = 16'h4805; // 0.125333
      audio[2] = 16'h4fea; // 0.248690
      audio[3] = 16'h578f; // 0.368125
      audio[4] = 16'h5ed4; // 0.481754
      audio[5] = 16'h659d; // 0.587785
      audio[6] = 16'h6bcf; // 0.684547
      audio[7] = 16'h714f; // 0.770513
      audio[8] = 16'h7609; // 0.844328
      audio[9] = 16'h79e8; // 0.904827
      audio[10] = 16'h7cdd; // 0.951057
      audio[11] = 16'h7edd; // 0.982287
      audio[12] = 16'h7fdf; // 0.998027
      audio[13] = 16'h7fdf; // 0.998027
      audio[14] = 16'h7edd; // 0.982287
      audio[15] = 16'h7cdd; // 0.951057
      audio[16] = 16'h79e8; // 0.904827
      audio[17] = 16'h7609; // 0.844328
      audio[18] = 16'h714f; // 0.770513
      audio[19] = 16'h6bcf; // 0.684547
      audio[20] = 16'h659d; // 0.587785
      audio[21] = 16'h5ed4; // 0.481754
      audio[22] = 16'h578f; // 0.368125
      audio[23] = 16'h4fea; // 0.248690
      audio[24] = 16'h4805; // 0.125333
      audio[25] = 16'h4000; // -0.000000
      audio[26] = 16'h37fb; // -0.125333
      audio[27] = 16'h3016; // -0.248690
      audio[28] = 16'h2871; // -0.368125
      audio[29] = 16'h212c; // -0.481754
      audio[30] = 16'h1a63; // -0.587785
      audio[31] = 16'h1431; // -0.684547
      audio[32] = 16'h0eb1; // -0.770513
      audio[33] = 16'h09f7; // -0.844328
      audio[34] = 16'h0618; // -0.904827
      audio[35] = 16'h0323; // -0.951057
      audio[36] = 16'h0123; // -0.982287
      audio[37] = 16'h0021; // -0.998027
      audio[38] = 16'h0021; // -0.998027
      audio[39] = 16'h0123; // -0.982287
      audio[40] = 16'h0323; // -0.951057
      audio[41] = 16'h0618; // -0.904827
      audio[42] = 16'h09f7; // -0.844328
      audio[43] = 16'h0eb1; // -0.770513
      audio[44] = 16'h1431; // -0.684547
      audio[45] = 16'h1a63; // -0.587785
      audio[46] = 16'h212c; // -0.481754
      audio[47] = 16'h2871; // -0.368125
      audio[48] = 16'h3016; // -0.248690
      audio[49] = 16'h37fb; // -0.125333

      end

// outputs 440 Hz audio portion of output
// when key is at a logic high 
    
always @(posedge clk)

   begin:Audio_Out
      // declaring local variables to
      // named section Clock_en
		
		// 16 bit signed fixed point encoding of 1.0 assuming a 
		//1 bit mantisa and a 14 bit fraction	
	   reg signed [1:-14] ONE_16 = {1'b0,1'b1,14'b0}; 
		// {sign bit, mantisa, fraction}
		
      // number of 50 Mhz clocks in a 440Hz period
//      reg BASE_COUNT = 113636; 
 
      reg  [31:0] count;
      reg[5:0] index;
		
      if (!key) 
         // if key is pressed supply 440Hz sine wave to wave2
         begin
         if (count>0)
            begin
            count = count - 1;
            end
         else
            begin
            if (index>=6'd50) index = 6'd0;
            else index = index + 6'd1;
            wave_out2 = audio[index];				
            count = 2272;
            end
         end
      else
         // when key is not pressed output a value of one to
         // allow original carrier wave to proceed unabated.
         begin
         index = 6'd0;
         count = 2272;
         wave_out2 = ONE_16;
         end 
   end

   // outputs 1 MHz carier portion       
   always @(posedge clk)
      begin:Waveform_Gen
      // declaring local variable to
      // named section Waveform_Gen			
      reg[5:0] index;
      if (index>=6'd50) index = 6'd0;
      else index = index + 6'd1;
      wave_out1 = out_table[index];
      end
		
   // main digital to analog conversion
   // portion -- uses pulse width modulation
   // to produce analog output by multiplying
   // in the time domain wave_out1 and wave_out2
   // waveforms
   always @ (posedge clk)
      begin:DtoA_convert
      // declaring local variable to
      // named section DtoA_convert
      reg signed [3:-28] ge; // error term	
      pdm(d_bit,wave_out1,wave_out2,ge);
	   end
           
   // Pulse Density Modulation Task
   task pdm(output d_out, input signed [1:-14] x, input signed [1:-14] scale, 
	   inout signed [3:-28] ge);
		
      // 32 bit fixed point encoding of 1.0 assuming a signed 3 bit
      // mantisa and a 28 bit fraction	
	   `define ONE_32 {1'b0,3'b001,28'b0} // {sign bit, mantisa, fraction}
		
      // 32 bit holder of x * scale data
      reg signed [3:-28] x_total;
      reg ret_val;

	   begin

	   x_total = x*scale; // scaling value
		
		if (x_total >= ge)
		   begin
		   ret_val = 1;
		   ge = ge + (`ONE_32 - x_total);
		   end
		else
	      begin
		   ret_val = 0;
		   ge = ge - (`ONE_32 + x_total); 
		   end	
	   d_out = ret_val;
		end
   endtask

   
endmodule   
