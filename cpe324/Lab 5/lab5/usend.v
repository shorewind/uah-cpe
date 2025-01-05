// Single Button Texter -- usend driver module -- usend.v file
// (c) 2/5/2024 B. Earl Wells, University of Alabama in Huntsville
// all rights reserved -- for academic use only.
//
// This module outputs to the asynchronous serial output
// the character that is specified by the ascii_in value whenever
// the input ds is strobed high for one clock cycle.
// It will also send the ASCII backspace character whenever the back_sp 
// signal is strobed high for one clock cycle.
// Cursor is returned to the begining position and the LCD is cleared
// whenever the reset signal is at a logic high.
// Module is written behaviorally
module usend (input clk, reset, ds, back_sp,
   input [7:0] ascii_in, output reg sout);

   parameter CLK_FREQ =  50000000;
   parameter BAUD_RATE = 9600;
   parameter NUM_CNT_BITS = 13;
   reg [6:0] col_count;
   reg [7:0]  clear_seq [0:6];
   reg [7:0] nl_seq [0:2];

   reg [3:0] bit_number;
   reg [NUM_CNT_BITS-1:0] clks_per_baud_period;
   reg [NUM_CNT_BITS-1:0] clk_count;
   reg [3:0] clear_seq_idx; // terminal clear sequence index
   reg [2:0] nl_seq_idx;    // new line sequence index
   initial
      begin
      bit_number = 4'd10;
      sout=1;
      clks_per_baud_period = (CLK_FREQ/BAUD_RATE);
      clear_seq_idx = 4'd7;
      
      // new line sequence (line feed/charage return)
      nl_seq[0] = 8'd10;
      nl_seq[1] = 8'd13;

      // ASCII Terminal Escape Sequence to Clear screen
      clear_seq[0] = 8'h4A; // 'J'
      clear_seq[1] = 8'h32; // '2'
      clear_seq[2] = 8'h5B; // [
      clear_seq[3] = 8'h1B; // Esc
      
      // ASII Sequence to bring cursor to position 0,0
      clear_seq[4] = 8'h48; // 'H'
      clear_seq[5] = 8'h5B; // [
      clear_seq[6] = 8'h1B; // Esc
      nl_seq_idx = 2'd2;
      col_count = 7'd0;      
      end

   // main loop 
   always @(posedge clk)
      begin:main
      reg [9:0] out_10_bit;
      reg ds_buf=0;
      if (ds) ds_buf=1;
      if (reset) 
         begin
         bit_number = 4'd10;
         sout=1;
         clear_seq_idx = 4'd7;
         col_count = 7'd0;
         nl_seq_idx = 2'd2; 
         end
      else 
         if (bit_number>=4'd10)
            // End of line sequence
            if (clear_seq_idx)
               begin
               clear_seq_idx = clear_seq_idx-4'd1;
               out_10_bit = {1'b1,clear_seq[clear_seq_idx],1'b0};
               bit_number = 4'd0;
               clk_count = 0;
               end
            else
            // New line sequence
            if (col_count >= 7'd78)
               begin
               nl_seq_idx = nl_seq_idx-2'd1;
               out_10_bit = {1'b1,nl_seq[nl_seq_idx],1'b0};
               bit_number = 4'd0;
               clk_count = 0;
               if (nl_seq_idx==0) 
                  begin
                  nl_seq_idx = 2'd2;
                  col_count = 7'd0;
                  end
               end
            else
            // Backspace sequence
            if (back_sp)
               begin
               out_10_bit = {1'b1,8'b00001000,1'b0};
               bit_number = 4'd0;
               clk_count = 0;
               end
            else
               // Output ascii_in data byte
               begin	
               if (ds_buf)
                  begin
                  out_10_bit = {1'b1,ascii_in,1'b0};
                  bit_number = 4'd0;
                  clk_count = 0;
                  col_count = col_count + 7'd1;
                  ds_buf=0;
                  end
               end
         // Continue to send send asynchronous output until all 10 bits are sent
         else
            if (clk_count<clks_per_baud_period) 
               clk_count = clk_count + 1;
            else
               begin
               clk_count = 0;
               sout=out_10_bit[bit_number];
               bit_number = bit_number+4'd1;
               end
      end
endmodule          
   
      



