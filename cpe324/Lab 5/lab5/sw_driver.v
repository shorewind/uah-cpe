// Single Button Texter -- automated switch driver module
// -- sw_driver.v file
// (c) 2/5/2024 B. Earl Wells, University of Alabama in Huntsville
// all rights reserved -- for academic use only.
//
// Switch Drive module for testbench (to validate single button 
// texter design)
module sw_driver (input clk, sp_up, sp_dwn, reset,
   output reg sw_out, output reg [7:0] ledr);

   reg sp_up_os, sp_dwn_os;
   reg [2:0] sp_index;
   reg [22:0] m_clk_range [0:7];
   reg [1:0]  sw_out_tm [0:3228];

   initial
      begin
      // these values represent 7.5, 10, 13, 15, 17, 20, 25, and 
      // 30 WPM of code
      m_clk_range[0] = 7999998;
      m_clk_range[1] = 5999998;
      m_clk_range[2] = 4615383;
      m_clk_range[3] = 3999998;		
      m_clk_range[4] = 3333331;
      m_clk_range[5] = 2999999;
      m_clk_range[6] = 2399999;
      m_clk_range[7] = 1999999;

      // on/off keying timing where
      // 2'b01 => one unit pulse, 2'b10 => three unit pulses,  
      // 2'b11 >= space timing 2'b00 => restart at the beginning of the array
      $readmemb("test_messages.txt",sw_out_tm);

      // set speed range and other parmeters
      sp_index = 3'd2;
      ledr = 8'd0; // clear out all Speed LED's

      end

   // one shot model for the up button
   // this model will result in the sp_up_os signal pulsing one clock 
   // cycle from 1 to 0 and back to 1 whenever the input signal sp_up_os
   //  goes from 1 to 0
   always @ (posedge clk)
      begin:UP
         reg state = 0;
         if (reset)
            if (!state)
               if (!sp_up)
                  begin
                  sp_up_os <= 0;
                  state <= 1;
                  end 
               else
                  sp_up_os <= 1;
            else
               begin
               sp_up_os <= 1;
                if (sp_up)
                   state <= 0;
               end
         else
            sp_up_os <= 1;
      end

   // one shot model for the down button
   // this model will result in the sp_dwn_os signal pulsing one clock
   // cycle from 1 to 0 and back to 1 whenever the input signal sp_dwn
   // goes from 1 to 0
   always @ (posedge clk)
      begin:DWN
         reg state = 0; 
         if (reset)
            if (!state) 
               if (!sp_dwn)
                  begin
                  sp_dwn_os <= 0;
                  state <= 1;
                  end
               else
                  sp_dwn_os <= 1;
            else
               begin
               sp_dwn_os <= 1;
               if (sp_dwn)
                  state <= 0;
               end
         else
            sp_dwn_os <= 1;
      end

   // this process allows the speed of the sending routine to be
   // changed by the sp_up and the sp_dwn signals
   always @ (posedge clk)
      begin:SPEED_CH
         ledr = 8'd0; // clear out all Speed LED's
         if (reset)
            begin

            if (!sp_up_os) 
               if (sp_index < 3'd7) 
                  sp_index = sp_index + 3'd1;
               else
                  sp_index = 3'd0;
            else
               if (!sp_dwn_os)
                  if (sp_index > 3'd0) 
                     sp_index = sp_index - 3'd1;
                  else
                     sp_index = 3'd7;

            ledr[sp_index] = 1'd1;
            end
      end

   // this process outputs the proper timing for a pre-recorded message.
   // The message is encoded as an array of time durations in the 
   // sw_out_tm array where the values of 1 represents one unit, 2 
   // represents 2 units, 3 represents 3 units, and 0 indicates that
   // the message should start over again. The sw_out output should
   // begin at a logic 1 and toggle between a logic 0 and 1 after each
   // time duration. The message has been designed to represent valid 
   // encodings.
   always @ (posedge clk)
      begin:PLAY_BK
         reg [11:0] nxt_unit = 12'd0;
         reg [3:0] unit_cnt = 4'd0;
         reg [1:0] unit_val;
         reg [22:0] m_clk = 23'd0;
         reg key_out = 1'd0;

         // on/off keying timing where
         // 1 => one unit pulse, 2 => three unit pulses, 
         // 3 >= space timing 
         // 0 => restart at the beginning of the array

         // if reset button is pressed go back from the beginning and
         // make sure key switch is not pressed
         if (!reset)
            begin
               nxt_unit = 12'd0; // go back to beginning
               key_out = 1'd0;   // unpress key switch
            end
         else           
            if (m_clk < m_clk_range[sp_index])
               m_clk = m_clk + 1;
            else
               begin 
               m_clk = 23'd0;
               if (unit_cnt == 4'd0)
                  begin
                  key_out = ~key_out; // toggle sw to other state
                  sw_out = key_out;
                  unit_val = sw_out_tm[nxt_unit];
                  if (unit_val == 2'd0)
                     begin
                     nxt_unit = 12'd0;
                     unit_val = sw_out_tm[0];
                     end 
                  if (unit_val == 2'd1)
                     // time for dit or between dits and dashes in 
                     // a character
                     unit_cnt = 4'd1; 
                  else 
                     // time for a dash or time characters
                     if (unit_val == 2'd2) 
                        unit_cnt = 4'd3; 
                     else 
                        // space timing a bit longer than the 
                        // required 7 units
                        unit_cnt = 4'd10;
                  nxt_unit = nxt_unit + 12'd1;
                  end
               else
                  unit_cnt = unit_cnt - 4'd1;
               end
      end
 
endmodule
      

