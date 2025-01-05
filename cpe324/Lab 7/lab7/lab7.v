// CPE 324 Video Driver Template File -- Laboratory Assignment 7
// (c) B. Earl Wells, University of Alabama in Huntsville 2/25/2024

// This is the top level module of the SVGA DE-2 Display
// driver. The module is designed to utilize the 50 Mhz
// clock on the DE2-115 board and to diplay various translations
// of the image of the DE2-115 board in response to the buttons
// labeled KEY[0] through KEY[3] being pressed.
// For the final part of this laboratory the image should be displayed
// in its true form, 90 degree CCW rotated form, upside down, and in 
// its normal orientation but at twice its size. Only a single image 
// should appear on the screen in each of these cases.
// To accomphish this students must be able to alter the svga_sync
// module and the translate module.
module lab7(input CLOCK_50, input [3:0] KEY,
   output VGA_SYNC, VGA_BLANK, VGA_CLK, VGA_H, VGA_V,
   output [7:0] VGA_B, VGA_G, VGA_R);

   wire clock_40;
   wire n0,n1,n2,n3,n4,n5;
   wire [15:0] b0;
   wire [9:0] b1,b2;
   wire [7:0] b3;

   assign VGA_SYNC = 1'b1;

   color_palette CP1(.color(b3),.blue(VGA_B),
      .green(VGA_G),.red(VGA_R));

   de2_picture PIC1(.blank_in(n3),.h_sync_in(n4),.v_sync_in(n5),.address(b0),
       .clock(clock_40),.blank_out(VGA_BLANK),.h_sync_out(VGA_H),
       .v_sync_out(VGA_V),.q(b3));

   pll_clk_50_to_40 PLL1(.clk_in(CLOCK_50),.clk_out(clock_40));

   svga_sync SVGA1( .clk(clock_40),.v_clk(VGA_CLK),.blank_out(n0),
      .h_sync_out(n1),.v_sync_out(n2),.pixel_rw(b1),
      .pixel_col(b2));

   translate TR1(.sw(KEY),.blank_in(n0),.h_sync_in(n1),.v_sync_in(n2),
      .col_in(b2),.row_in(b1),.clk(clock_40),.blank_out(n3),.h_sync_out(n4),
      .v_sync_out(n5),.address_out(b0));

endmodule

// In order to make this template work correctly to drive the SVGA 
// monitor students must enter the appropriate vertical and horizonal
// count values in the conditional statements that are used in this 
// model. These values can be determined by understanding the basic 
// operation of this Verilog HDL file and carefully examining the SVGA
// timing diagram provided in the Laboratory 7 Assignment Sheet. In 
// this analysis it can be assumed that the clock frequency that that
// will drive this module will be 40 MHZ.
module svga_sync (input clk, output v_clk,blank_out,
   output reg h_sync_out,v_sync_out,
   output reg [9:0] pixel_rw, pixel_col);

   // video active flags -- false during retraces 
   reg video_on_h, video_on_v; 

   // wait until rising edge of the DE2-115s 40 Mhz clock
   always @ (posedge clk) 
      begin:main_loop
         reg [10:0] col_count = 11'd0;
         reg [9:0]  row_count = 10'd0;

         // reset or increment horizonal column counter
         if (col_count==1056)  // n = 26.4us(40MHz)
             col_count <= 11'd0;
         else
             col_count <= col_count + 11'd1;

         // generate negative going horizonal synchronization pulse
         // (see timing diagram in lab #7 assignment sheet)
         // Total Time = 26.4us (Total time - hsync pulse - back porch) and 
         // [(total time) - (back porch)]
         if (col_count >= 840 && col_count <= 968) 
            h_sync_out <= 1'b0;
         else
            h_sync_out <= 1'b1;

         // reset or increment vertical row counter
         if (row_count == 631 && col_count == 1056) 
            row_count <= 10'd0;
         else 
            if (col_count == 1056)
               row_count <= row_count + 10'd1;
 
         // generate negative going vertical synchronization pulse
         if (row_count >= 601 && row_count <= 606) 
            v_sync_out <= 1'b0;
         else
            v_sync_out <= 1'b1;

         // send current horizonal column pixel count value to the 
         // pixel_col output bus if at data output phase of horizonal 
         // refresh cycle. Also indicate whether or not monitor is in 
         // horizonal blanking phase, where it turns off all three 
         // electron guns. 
         // after counting all the pixels. equivalent to the no.of columns
         if ((col_count < 800) && (col_count >= 0)) 
            begin
               video_on_h <=1'b1;
               pixel_col <= col_count[9:0];
            end
         else
            video_on_h <= 1'b0;

         // send current vertical row pixel count value to the
         //  pixel_rw output bus if at data output phase of vertical
         // refresh cycle. Also indicate whether or not monitor is in 
         // vertical blanking phase, where it turns off all three 
         // electron guns.
              if ((row_count < 600) && (row_count >= 0))
                 begin
                     video_on_v <= 1'b1;
                     pixel_rw <= row_count;
                 end
              else
                 video_on_v <= 1'b0;
      end

      // set blank signal true during either horizonal or vertical 
      // retrace periods
      assign blank_out = video_on_h && video_on_v;

      // v_clk is 180 degrees out of phase with clk
      assign v_clk = ~clk; 

endmodule

// User written Module to perform the four specified image translations
//      image is assumed to be 178 rows x 213 columns in size with the
//      rows being referenced using the upper 8 most significant bits 
//      of the address bus and the columns being referenced by the 8 
//      least significant bits of the address bus
//      case 1: when the SW[0] is pressed a centered image should be
//         displayed that is twice the size of the normal image i.e.
//         356 x 426 pixels in size
//      case 2: when the SW[1] button is pressed a centered image should
//         be displayed that is the normal size and orientation.
//      case 3: when the SW[2] button is pressed a centered image should
//         be displayed that is normal size but is rotated 90 degree
//         counter clockwise.
//      case 4: when the SW[3] button is pressed a centered image should
//         be displayed that is normal size but is upsized down (rotated
//         180 degrees
//      In each case there should be only one copy of the image that is 
//      displayed on the screen.
//      The default implementation simply passes through the 8 low 
//      ordered pixel row and column bits and appends them together to
//      form the 16 bit address that is to be fed to the de2_picture 
//      map lookup table
module translate (input [3:0] sw, input blank_in,h_sync_in,v_sync_in,
    input [9:0] row_in,col_in, input clk, output blank_out, 
    output reg h_sync_out, v_sync_out, output reg [15:0] address_out);
	
    // active low signal inside translate modue that blanks the screen
    // when raster scan is over portions of the viewable screen that 
    // the Video mode desires to be blanked and not display the picture
    // This signal is ANDed with the blank_in signal to produce the
    // blank_out signal which comes from the module
    reg blank_out_translate=1'b1;

	// Video mode -- case 1 = 0, case 2 = 1, case 3  2 and case 4 = 3
	reg [1:0] video_mode = 1; // set case 1 as default

   // change mode when a key button is pressed
	always @ (negedge clk)
	   if (sw[0]==0) video_mode=2'd0;
		else if (sw[1]==0) video_mode=2'd1;
		else if (sw[2]==0) video_mode=2'd2;
		else if (sw[3]==0) video_mode=2'd3;

   // one clock cycle delay of horizonal and
   // vertical sync signals to account for the extra 
   // clock cycle needed to output the translated 
   // address to color memory
   always @ (posedge clk)
      begin
      h_sync_out=h_sync_in;
      v_sync_out=v_sync_in;
      end

   // update blank_out signal of module so that the value of
   // the active low blank_out signal is a Logic 0 whenever 
   // either input blank_in signal is low and/or the internal
   // blank_out_translate signal is low. A Logic 0 causes the
   // display to not display a pixel value   
   assign blank_out = blank_out_translate & blank_in;

   // Translate Image to a new size or orientation
   always @(posedge clk) 
      begin:mainloop
         reg [9:0] row_out,col_out;

         // temporary portion of model that in effect concatenates the lower 8-bits
         // of the row_in, and col_in lines to allow the 256 x 256 element picture
         // to appear multiple times on the larger 800 x 600 element screen in order
         // to verify that the timing parameters are correct in the svga_sync module
         address_out = {row_in[7:0],col_in[7:0]}; blank_out_translate=1'b1;

         // Uncomment this region and enter remaining model that responds to switches and 
         // performs translation after svga_sync module has been verified. (Also remove 
         // the above always block that performs the concatenation operation.)
         
         case (video_mode)			
         // if sw0 is pressed then display a single centered image that is twice its normal size 
         0 : 
            // if pixel count is in appropriate (centered) area of screen
            // then output image where each image pixel is represented by
            // four pixels in the actual image -- two along the row and
            // two along the column
            if(row_in[9:1] >= 10'd22 && row_in[9:1] < 10'd278 &&
               col_in[9:1] >= 10'd72 && col_in[9:1] < 10'd328)
               begin
                  blank_out_translate=1'b1; // turn display on

                  row_out=(row_in[9:0]-44)/2;  // row_in[9:1]-22
						col_out=(col_in[9:0]-144)/2;  // col_in[9:1]-72
						address_out={row_out[7:0], col_out[7:0]};
               end
            else
               begin
                  // portion of screen where display is blanked (turned off)
                  blank_out_translate = 1'b0;
               end

         // if sw1 is pressed then display a single centered image that is of normal size
			1 :	
            if(row_in >= 10'd172 && row_in < 10'd428 &&
               col_in >= 10'd272 && col_in < 10'd528)
               begin
                  blank_out_translate=1'b1; // turn display on

                  row_out=row_in[9:0]-172;
						col_out=col_in[9:0]-272;
						address_out={row_out[7:0], col_out[7:0]};
               end
				else
					begin
						// portion of screen where display is blanked (turned off)
						blank_out_translate = 1'b0;
					end
         
         // if sw2 is pressed then display a single centered image that is rotated
         // CCW 90 degrees  
		   2:
				if(row_in >= 10'd172 && row_in < 10'd428 &&
					col_in >= 10'd272 && col_in < 10'd528)
					begin
						blank_out_translate=1'b1; // turn display on

						row_out=col_in[9:0]-272;
						col_out=172-row_in[9:0];
						address_out={row_out[7:0], col_out[7:0]};
					end
				else
					begin
						// portion of screen where display is blanked (turned off)
						blank_out_translate = 1'b0;
					end
			
         // if sw3 is pressed then display a single centered image that is 
         // upside down 
		   3:		       
				if(row_in >= 10'd172 && row_in < 10'd428 &&
					col_in >= 10'd272 && col_in < 10'd528)
					
						begin
							blank_out_translate=1'b1; // turn display on
							
							row_out=172-row_in[9:0];
							col_out=272-col_in[9:0];
							address_out={row_out[7:0], col_out[7:0]};
						end
				else
					begin
						// portion of screen where display is blanked (turned off)
						blank_out_translate = 1'b0;
					end	
					
		   endcase
		
		end			
           
    
endmodule

// This is the model of the clock converter device that utilizes 
// one of the PLL elements in the Cyclone IV E to multiply the 
// external clock by a factor of 4/5. This results in a 40 Mhz
// clock being produced whenever the module is driven by a 50Mhz
// Signal. This is the frequency needed to obtain 800 x 600 60 Hz SVGA 
// resolution
module pll_clk_50_to_40(input clk_in,output clk_out);

	wire [4:0] clockgrp;
	assign  clk_out = clockgrp[0:0];

	altpll	altpll_component (
				.inclk ({1'h0, clk_in}),
				.clk (clockgrp),
				.activeclock (),
				.areset (1'b0),
				.clkbad (),
				.clkena ({6{1'b1}}),
				.clkloss (),
				.clkswitch (1'b0),
				.configupdate (1'b0),
				.enable0 (),
				.enable1 (),
				.extclk (),
				.extclkena ({4{1'b1}}),
				.fbin (1'b1),
				.fbmimicbidir (),
				.fbout (),
				.fref (),
				.icdrclk (),
				.locked (),
				.pfdena (1'b1),
				.phasecounterselect ({4{1'b1}}),
				.phasedone (),
				.phasestep (1'b1),
				.phaseupdown (1'b1),
				.pllena (1'b1),
				.scanaclr (1'b0),
				.scanclk (1'b0),
				.scanclkena (1'b1),
				.scandata (1'b0),
				.scandataout (),
				.scandone (),
				.scanread (1'b0),
				.scanwrite (1'b0),
				.sclkout0 (),
				.sclkout1 (),
				.vcooverrange (),
				.vcounderrange ());
	defparam
		altpll_component.bandwidth_type = "AUTO",
		altpll_component.clk0_divide_by = 5,
		altpll_component.clk0_duty_cycle = 50,
		altpll_component.clk0_multiply_by = 4,
		altpll_component.clk0_phase_shift = "0",
		altpll_component.compensate_clock = "CLK0",
		altpll_component.inclk0_input_frequency = 20000,
		altpll_component.intended_device_family = "Cyclone IV E",
		altpll_component.lpm_hint = "CBX_MODULE_PREFIX=altpll0",
		altpll_component.lpm_type = "altpll",
		altpll_component.operation_mode = "NORMAL",
		altpll_component.pll_type = "AUTO",
		altpll_component.port_activeclock = "PORT_UNUSED",
		altpll_component.port_areset = "PORT_UNUSED",
		altpll_component.port_clkbad0 = "PORT_UNUSED",
		altpll_component.port_clkbad1 = "PORT_UNUSED",
		altpll_component.port_clkloss = "PORT_UNUSED",
		altpll_component.port_clkswitch = "PORT_UNUSED",
		altpll_component.port_configupdate = "PORT_UNUSED",
		altpll_component.port_fbin = "PORT_UNUSED",
		altpll_component.port_inclk0 = "PORT_USED",
		altpll_component.port_inclk1 = "PORT_UNUSED",
		altpll_component.port_locked = "PORT_UNUSED",
		altpll_component.port_pfdena = "PORT_UNUSED",
		altpll_component.port_phasecounterselect = "PORT_UNUSED",
		altpll_component.port_phasedone = "PORT_UNUSED",
		altpll_component.port_phasestep = "PORT_UNUSED",
		altpll_component.port_phaseupdown = "PORT_UNUSED",
		altpll_component.port_pllena = "PORT_UNUSED",
		altpll_component.port_scanaclr = "PORT_UNUSED",
		altpll_component.port_scanclk = "PORT_UNUSED",
		altpll_component.port_scanclkena = "PORT_UNUSED",
		altpll_component.port_scandata = "PORT_UNUSED",
		altpll_component.port_scandataout = "PORT_UNUSED",
		altpll_component.port_scandone = "PORT_UNUSED",
		altpll_component.port_scanread = "PORT_UNUSED",
		altpll_component.port_scanwrite = "PORT_UNUSED",
		altpll_component.port_clk0 = "PORT_USED",
		altpll_component.port_clk1 = "PORT_UNUSED",
		altpll_component.port_clk2 = "PORT_UNUSED",
		altpll_component.port_clk3 = "PORT_UNUSED",
		altpll_component.port_clk4 = "PORT_UNUSED",
		altpll_component.port_clk5 = "PORT_UNUSED",
		altpll_component.port_clkena0 = "PORT_UNUSED",
		altpll_component.port_clkena1 = "PORT_UNUSED",
		altpll_component.port_clkena2 = "PORT_UNUSED",
		altpll_component.port_clkena3 = "PORT_UNUSED",
		altpll_component.port_clkena4 = "PORT_UNUSED",
		altpll_component.port_clkena5 = "PORT_UNUSED",
		altpll_component.port_extclk0 = "PORT_UNUSED",
		altpll_component.port_extclk1 = "PORT_UNUSED",
		altpll_component.port_extclk2 = "PORT_UNUSED",
		altpll_component.port_extclk3 = "PORT_UNUSED",
		altpll_component.width_clock = 5;


endmodule

// The purpose of this module is to convert each of the 256 possible
// colors to eight bit intensity values that can be used to drive the 
// VGA_R, VGA_B, and VGA_G inputs to the SVGA monitor.
 
module color_palette(input [7:0] color, output reg [7:0] red, 
   green, blue);

   reg [7:0] red_palette [0:255], green_palette[0:255], 
      blue_palette [0:255]; 

   initial
      begin
         red_palette[0] = 8'd0;
         red_palette[1] = 8'd128;
         red_palette[2] = 8'd0;
         red_palette[3] = 8'd128;
         red_palette[4] = 8'd0;
         red_palette[5] = 8'd128;
         red_palette[6] = 8'd0;
         red_palette[7] = 8'd192;
         red_palette[8] = 8'd192;
         red_palette[9] = 8'd166;
         red_palette[10] = 8'd64;
         red_palette[11] = 8'd96;
         red_palette[12] = 8'd128;
         red_palette[13] = 8'd160;
         red_palette[14] = 8'd192;
         red_palette[15] = 8'd224;
         red_palette[16] = 8'd0;
         red_palette[17] = 8'd32;
         red_palette[18] = 8'd64;
         red_palette[19] = 8'd96;
         red_palette[20] = 8'd128;
         red_palette[21] = 8'd160;
         red_palette[22] = 8'd192;
         red_palette[23] = 8'd224;
         red_palette[24] = 8'd0;
         red_palette[25] = 8'd32;
         red_palette[26] = 8'd64;
         red_palette[27] = 8'd96;
         red_palette[28] = 8'd128;
         red_palette[29] = 8'd160;
         red_palette[30] = 8'd192;
         red_palette[31] = 8'd224;
         red_palette[32] = 8'd0;
         red_palette[33] = 8'd32;
         red_palette[34] = 8'd64;
         red_palette[35] = 8'd96;
         red_palette[36] = 8'd128;
         red_palette[37] = 8'd160;
         red_palette[38] = 8'd192;
         red_palette[39] = 8'd224;
         red_palette[40] = 8'd0;
         red_palette[41] = 8'd32;
         red_palette[42] = 8'd64;
         red_palette[43] = 8'd96;
         red_palette[44] = 8'd128;
         red_palette[45] = 8'd160;
         red_palette[46] = 8'd192;
         red_palette[47] = 8'd224;
         red_palette[48] = 8'd0;
         red_palette[49] = 8'd32;
         red_palette[50] = 8'd64;
         red_palette[51] = 8'd96;
         red_palette[52] = 8'd128;
         red_palette[53] = 8'd160;
         red_palette[54] = 8'd192;
         red_palette[55] = 8'd224;
         red_palette[56] = 8'd0;
         red_palette[57] = 8'd32;
         red_palette[58] = 8'd64;
         red_palette[59] = 8'd96;
         red_palette[60] = 8'd128;
         red_palette[61] = 8'd160;
         red_palette[62] = 8'd192;
         red_palette[63] = 8'd224;
         red_palette[64] = 8'd0;
         red_palette[65] = 8'd32;
         red_palette[66] = 8'd64;
         red_palette[67] = 8'd96;
         red_palette[68] = 8'd128;
         red_palette[69] = 8'd160;
         red_palette[70] = 8'd192;
         red_palette[71] = 8'd224;
         red_palette[72] = 8'd0;
         red_palette[73] = 8'd32;
         red_palette[74] = 8'd64;
         red_palette[75] = 8'd96;
         red_palette[76] = 8'd128;
         red_palette[77] = 8'd160;
         red_palette[78] = 8'd192;
         red_palette[79] = 8'd224;
         red_palette[80] = 8'd0;
         red_palette[81] = 8'd32;
         red_palette[82] = 8'd64;
         red_palette[83] = 8'd96;
         red_palette[84] = 8'd128;
         red_palette[85] = 8'd160;
         red_palette[86] = 8'd192;
         red_palette[87] = 8'd224;
         red_palette[88] = 8'd0;
         red_palette[89] = 8'd32;
         red_palette[90] = 8'd64;
         red_palette[91] = 8'd96;
         red_palette[92] = 8'd128;
         red_palette[93] = 8'd160;
         red_palette[94] = 8'd192;
         red_palette[95] = 8'd224;
         red_palette[96] = 8'd0;
         red_palette[97] = 8'd32;
         red_palette[98] = 8'd64;
         red_palette[99] = 8'd96;
         red_palette[100] = 8'd128;
         red_palette[101] = 8'd160;
         red_palette[102] = 8'd192;
         red_palette[103] = 8'd224;
         red_palette[104] = 8'd0;
         red_palette[105] = 8'd32;
         red_palette[106] = 8'd64;
         red_palette[107] = 8'd96;
         red_palette[108] = 8'd128;
         red_palette[109] = 8'd160;
         red_palette[110] = 8'd192;
         red_palette[111] = 8'd224;
         red_palette[112] = 8'd0;
         red_palette[113] = 8'd32;
         red_palette[114] = 8'd64;
         red_palette[115] = 8'd96;
         red_palette[116] = 8'd128;
         red_palette[117] = 8'd160;
         red_palette[118] = 8'd192;
         red_palette[119] = 8'd224;
         red_palette[120] = 8'd0;
         red_palette[121] = 8'd32;
         red_palette[122] = 8'd64;
         red_palette[123] = 8'd96;
         red_palette[124] = 8'd128;
         red_palette[125] = 8'd160;
         red_palette[126] = 8'd192;
         red_palette[127] = 8'd224;
         red_palette[128] = 8'd0;
         red_palette[129] = 8'd32;
         red_palette[130] = 8'd64;
         red_palette[131] = 8'd96;
         red_palette[132] = 8'd128;
         red_palette[133] = 8'd160;
         red_palette[134] = 8'd192;
         red_palette[135] = 8'd224;
         red_palette[136] = 8'd0;
         red_palette[137] = 8'd32;
         red_palette[138] = 8'd64;
         red_palette[139] = 8'd96;
         red_palette[140] = 8'd128;
         red_palette[141] = 8'd160;
         red_palette[142] = 8'd192;
         red_palette[143] = 8'd224;
         red_palette[144] = 8'd0;
         red_palette[145] = 8'd32;
         red_palette[146] = 8'd64;
         red_palette[147] = 8'd96;
         red_palette[148] = 8'd128;
         red_palette[149] = 8'd160;
         red_palette[150] = 8'd192;
         red_palette[151] = 8'd224;
         red_palette[152] = 8'd0;
         red_palette[153] = 8'd32;
         red_palette[154] = 8'd64;
         red_palette[155] = 8'd96;
         red_palette[156] = 8'd128;
         red_palette[157] = 8'd160;
         red_palette[158] = 8'd192;
         red_palette[159] = 8'd224;
         red_palette[160] = 8'd0;
         red_palette[161] = 8'd32;
         red_palette[162] = 8'd64;
         red_palette[163] = 8'd96;
         red_palette[164] = 8'd128;
         red_palette[165] = 8'd160;
         red_palette[166] = 8'd192;
         red_palette[167] = 8'd224;
         red_palette[168] = 8'd0;
         red_palette[169] = 8'd32;
         red_palette[170] = 8'd64;
         red_palette[171] = 8'd96;
         red_palette[172] = 8'd128;
         red_palette[173] = 8'd160;
         red_palette[174] = 8'd192;
         red_palette[175] = 8'd224;
         red_palette[176] = 8'd0;
         red_palette[177] = 8'd32;
         red_palette[178] = 8'd64;
         red_palette[179] = 8'd96;
         red_palette[180] = 8'd128;
         red_palette[181] = 8'd160;
         red_palette[182] = 8'd192;
         red_palette[183] = 8'd224;
         red_palette[184] = 8'd0;
         red_palette[185] = 8'd32;
         red_palette[186] = 8'd64;
         red_palette[187] = 8'd96;
         red_palette[188] = 8'd128;
         red_palette[189] = 8'd160;
         red_palette[190] = 8'd192;
         red_palette[191] = 8'd224;
         red_palette[192] = 8'd0;
         red_palette[193] = 8'd32;
         red_palette[194] = 8'd64;
         red_palette[195] = 8'd96;
         red_palette[196] = 8'd128;
         red_palette[197] = 8'd160;
         red_palette[198] = 8'd192;
         red_palette[199] = 8'd224;
         red_palette[200] = 8'd0;
         red_palette[201] = 8'd32;
         red_palette[202] = 8'd64;
         red_palette[203] = 8'd96;
         red_palette[204] = 8'd128;
         red_palette[205] = 8'd160;
         red_palette[206] = 8'd192;
         red_palette[207] = 8'd224;
         red_palette[208] = 8'd0;
         red_palette[209] = 8'd32;
         red_palette[210] = 8'd64;
         red_palette[211] = 8'd96;
         red_palette[212] = 8'd128;
         red_palette[213] = 8'd160;
         red_palette[214] = 8'd192;
         red_palette[215] = 8'd224;
         red_palette[216] = 8'd0;
         red_palette[217] = 8'd32;
         red_palette[218] = 8'd64;
         red_palette[219] = 8'd96;
         red_palette[220] = 8'd128;
         red_palette[221] = 8'd160;
         red_palette[222] = 8'd192;
         red_palette[223] = 8'd224;
         red_palette[224] = 8'd0;
         red_palette[225] = 8'd32;
         red_palette[226] = 8'd64;
         red_palette[227] = 8'd96;
         red_palette[228] = 8'd128;
         red_palette[229] = 8'd160;
         red_palette[230] = 8'd192;
         red_palette[231] = 8'd224;
         red_palette[232] = 8'd0;
         red_palette[233] = 8'd32;
         red_palette[234] = 8'd64;
         red_palette[235] = 8'd96;
         red_palette[236] = 8'd128;
         red_palette[237] = 8'd160;
         red_palette[238] = 8'd192;
         red_palette[239] = 8'd224;
         red_palette[240] = 8'd0;
         red_palette[241] = 8'd32;
         red_palette[242] = 8'd64;
         red_palette[243] = 8'd96;
         red_palette[244] = 8'd128;
         red_palette[245] = 8'd160;
         red_palette[246] = 8'd255;
         red_palette[247] = 8'd160;
         red_palette[248] = 8'd128;
         red_palette[249] = 8'd255;
         red_palette[250] = 8'd0;
         red_palette[251] = 8'd255;
         red_palette[252] = 8'd0;
         red_palette[253] = 8'd255;
         red_palette[254] = 8'd0;
         red_palette[255] = 8'd255;

         green_palette[0] = 8'd0;
         green_palette[1] = 8'd0;
         green_palette[2] = 8'd128;
         green_palette[3] = 8'd128;
         green_palette[4] = 8'd0;
         green_palette[5] = 8'd0;
         green_palette[6] = 8'd128;
         green_palette[7] = 8'd192;
         green_palette[8] = 8'd220;
         green_palette[9] = 8'd202;
         green_palette[10] = 8'd32;
         green_palette[11] = 8'd32;
         green_palette[12] = 8'd32;
         green_palette[13] = 8'd32;
         green_palette[14] = 8'd32;
         green_palette[15] = 8'd32;
         green_palette[16] = 8'd64;
         green_palette[17] = 8'd64;
         green_palette[18] = 8'd64;
         green_palette[19] = 8'd64;
         green_palette[20] = 8'd64;
         green_palette[21] = 8'd64;
         green_palette[22] = 8'd64;
         green_palette[23] = 8'd64;
         green_palette[24] = 8'd96;
         green_palette[25] = 8'd96;
         green_palette[26] = 8'd96;
         green_palette[27] = 8'd96;
         green_palette[28] = 8'd96;
         green_palette[29] = 8'd96;
         green_palette[30] = 8'd96;
         green_palette[31] = 8'd96;
         green_palette[32] = 8'd128;
         green_palette[33] = 8'd128;
         green_palette[34] = 8'd128;
         green_palette[35] = 8'd128;
         green_palette[36] = 8'd128;
         green_palette[37] = 8'd128;
         green_palette[38] = 8'd128;
         green_palette[39] = 8'd128;
         green_palette[40] = 8'd160;
         green_palette[41] = 8'd160;
         green_palette[42] = 8'd160;
         green_palette[43] = 8'd160;
         green_palette[44] = 8'd160;
         green_palette[45] = 8'd160;
         green_palette[46] = 8'd160;
         green_palette[47] = 8'd160;
         green_palette[48] = 8'd192;
         green_palette[49] = 8'd192;
         green_palette[50] = 8'd192;
         green_palette[51] = 8'd192;
         green_palette[52] = 8'd192;
         green_palette[53] = 8'd192;
         green_palette[54] = 8'd192;
         green_palette[55] = 8'd192;
         green_palette[56] = 8'd224;
         green_palette[57] = 8'd224;
         green_palette[58] = 8'd224;
         green_palette[59] = 8'd224;
         green_palette[60] = 8'd224;
         green_palette[61] = 8'd224;
         green_palette[62] = 8'd224;
         green_palette[63] = 8'd224;
         green_palette[64] = 8'd0;
         green_palette[65] = 8'd0;
         green_palette[66] = 8'd0;
         green_palette[67] = 8'd0;
         green_palette[68] = 8'd0;
         green_palette[69] = 8'd0;
         green_palette[70] = 8'd0;
         green_palette[71] = 8'd0;
         green_palette[72] = 8'd32;
         green_palette[73] = 8'd32;
         green_palette[74] = 8'd32;
         green_palette[75] = 8'd32;
         green_palette[76] = 8'd32;
         green_palette[77] = 8'd32;
         green_palette[78] = 8'd32;
         green_palette[79] = 8'd32;
         green_palette[80] = 8'd64;
         green_palette[81] = 8'd64;
         green_palette[82] = 8'd64;
         green_palette[83] = 8'd64;
         green_palette[84] = 8'd64;
         green_palette[85] = 8'd64;
         green_palette[86] = 8'd64;
         green_palette[87] = 8'd64;
         green_palette[88] = 8'd96;
         green_palette[89] = 8'd96;
         green_palette[90] = 8'd96;
         green_palette[91] = 8'd96;
         green_palette[92] = 8'd96;
         green_palette[93] = 8'd96;
         green_palette[94] = 8'd96;
         green_palette[95] = 8'd96;
         green_palette[96] = 8'd128;
         green_palette[97] = 8'd128;
         green_palette[98] = 8'd128;
         green_palette[99] = 8'd128;
         green_palette[100] = 8'd128;
         green_palette[101] = 8'd128;
         green_palette[102] = 8'd128;
         green_palette[103] = 8'd128;
         green_palette[104] = 8'd160;
         green_palette[105] = 8'd160;
         green_palette[106] = 8'd160;
         green_palette[107] = 8'd160;
         green_palette[108] = 8'd160;
         green_palette[109] = 8'd160;
         green_palette[110] = 8'd160;
         green_palette[111] = 8'd160;
         green_palette[112] = 8'd192;
         green_palette[113] = 8'd192;
         green_palette[114] = 8'd192;
         green_palette[115] = 8'd192;
         green_palette[116] = 8'd192;
         green_palette[117] = 8'd192;
         green_palette[118] = 8'd192;
         green_palette[119] = 8'd192;
         green_palette[120] = 8'd224;
         green_palette[121] = 8'd224;
         green_palette[122] = 8'd224;
         green_palette[123] = 8'd224;
         green_palette[124] = 8'd224;
         green_palette[125] = 8'd224;
         green_palette[126] = 8'd224;
         green_palette[127] = 8'd224;
         green_palette[128] = 8'd0;
         green_palette[129] = 8'd0;
         green_palette[130] = 8'd0;
         green_palette[131] = 8'd0;
         green_palette[132] = 8'd0;
         green_palette[133] = 8'd0;
         green_palette[134] = 8'd0;
         green_palette[135] = 8'd0;
         green_palette[136] = 8'd32;
         green_palette[137] = 8'd32;
         green_palette[138] = 8'd32;
         green_palette[139] = 8'd32;
         green_palette[140] = 8'd32;
         green_palette[141] = 8'd32;
         green_palette[142] = 8'd32;
         green_palette[143] = 8'd32;
         green_palette[144] = 8'd64;
         green_palette[145] = 8'd64;
         green_palette[146] = 8'd64;
         green_palette[147] = 8'd64;
         green_palette[148] = 8'd64;
         green_palette[149] = 8'd64;
         green_palette[150] = 8'd64;
         green_palette[151] = 8'd64;
         green_palette[152] = 8'd96;
         green_palette[153] = 8'd96;
         green_palette[154] = 8'd96;
         green_palette[155] = 8'd96;
         green_palette[156] = 8'd96;
         green_palette[157] = 8'd96;
         green_palette[158] = 8'd96;
         green_palette[159] = 8'd96;
         green_palette[160] = 8'd128;
         green_palette[161] = 8'd128;
         green_palette[162] = 8'd128;
         green_palette[163] = 8'd128;
         green_palette[164] = 8'd128;
         green_palette[165] = 8'd128;
         green_palette[166] = 8'd128;
         green_palette[167] = 8'd128;
         green_palette[168] = 8'd160;
         green_palette[169] = 8'd160;
         green_palette[170] = 8'd160;
         green_palette[171] = 8'd160;
         green_palette[172] = 8'd160;
         green_palette[173] = 8'd160;
         green_palette[174] = 8'd160;
         green_palette[175] = 8'd160;
         green_palette[176] = 8'd192;
         green_palette[177] = 8'd192;
         green_palette[178] = 8'd192;
         green_palette[179] = 8'd192;
         green_palette[180] = 8'd192;
         green_palette[181] = 8'd192;
         green_palette[182] = 8'd192;
         green_palette[183] = 8'd192;
         green_palette[184] = 8'd224;
         green_palette[185] = 8'd224;
         green_palette[186] = 8'd224;
         green_palette[187] = 8'd224;
         green_palette[188] = 8'd224;
         green_palette[189] = 8'd224;
         green_palette[190] = 8'd224;
         green_palette[191] = 8'd224;
         green_palette[192] = 8'd0;
         green_palette[193] = 8'd0;
         green_palette[194] = 8'd0;
         green_palette[195] = 8'd0;
         green_palette[196] = 8'd0;
         green_palette[197] = 8'd0;
         green_palette[198] = 8'd0;
         green_palette[199] = 8'd0;
         green_palette[200] = 8'd32;
         green_palette[201] = 8'd32;
         green_palette[202] = 8'd32;
         green_palette[203] = 8'd32;
         green_palette[204] = 8'd32;
         green_palette[205] = 8'd32;
         green_palette[206] = 8'd32;
         green_palette[207] = 8'd32;
         green_palette[208] = 8'd64;
         green_palette[209] = 8'd64;
         green_palette[210] = 8'd64;
         green_palette[211] = 8'd64;
         green_palette[212] = 8'd64;
         green_palette[213] = 8'd64;
         green_palette[214] = 8'd64;
         green_palette[215] = 8'd64;
         green_palette[216] = 8'd96;
         green_palette[217] = 8'd96;
         green_palette[218] = 8'd96;
         green_palette[219] = 8'd96;
         green_palette[220] = 8'd96;
         green_palette[221] = 8'd96;
         green_palette[222] = 8'd96;
         green_palette[223] = 8'd96;
         green_palette[224] = 8'd128;
         green_palette[225] = 8'd128;
         green_palette[226] = 8'd128;
         green_palette[227] = 8'd128;
         green_palette[228] = 8'd128;
         green_palette[229] = 8'd128;
         green_palette[230] = 8'd128;
         green_palette[231] = 8'd128;
         green_palette[232] = 8'd160;
         green_palette[233] = 8'd160;
         green_palette[234] = 8'd160;
         green_palette[235] = 8'd160;
         green_palette[236] = 8'd160;
         green_palette[237] = 8'd160;
         green_palette[238] = 8'd160;
         green_palette[239] = 8'd160;
         green_palette[240] = 8'd192;
         green_palette[241] = 8'd192;
         green_palette[242] = 8'd192;
         green_palette[243] = 8'd192;
         green_palette[244] = 8'd192;
         green_palette[245] = 8'd192;
         green_palette[246] = 8'd251;
         green_palette[247] = 8'd160;
         green_palette[248] = 8'd128;
         green_palette[249] = 8'd0;
         green_palette[250] = 8'd255;
         green_palette[251] = 8'd255;
         green_palette[252] = 8'd0;
         green_palette[253] = 8'd0;
         green_palette[254] = 8'd255;
         green_palette[255] = 8'd255;

         blue_palette[0] = 8'd0;
         blue_palette[1] = 8'd0;
         blue_palette[2] = 8'd0;
         blue_palette[3] = 8'd0;
         blue_palette[4] = 8'd128;
         blue_palette[5] = 8'd128;
         blue_palette[6] = 8'd128;
         blue_palette[7] = 8'd192;
         blue_palette[8] = 8'd192;
         blue_palette[9] = 8'd240;
         blue_palette[10] = 8'd0;
         blue_palette[11] = 8'd0;
         blue_palette[12] = 8'd0;
         blue_palette[13] = 8'd0;
         blue_palette[14] = 8'd0;
         blue_palette[15] = 8'd0;
         blue_palette[16] = 8'd0;
         blue_palette[17] = 8'd0;
         blue_palette[18] = 8'd0;
         blue_palette[19] = 8'd0;
         blue_palette[20] = 8'd0;
         blue_palette[21] = 8'd0;
         blue_palette[22] = 8'd0;
         blue_palette[23] = 8'd0;
         blue_palette[24] = 8'd0;
         blue_palette[25] = 8'd0;
         blue_palette[26] = 8'd0;
         blue_palette[27] = 8'd0;
         blue_palette[28] = 8'd0;
         blue_palette[29] = 8'd0;
         blue_palette[30] = 8'd0;
         blue_palette[31] = 8'd0;
         blue_palette[32] = 8'd0;
         blue_palette[33] = 8'd0;
         blue_palette[34] = 8'd0;
         blue_palette[35] = 8'd0;
         blue_palette[36] = 8'd0;
         blue_palette[37] = 8'd0;
         blue_palette[38] = 8'd0;
         blue_palette[39] = 8'd0;
         blue_palette[40] = 8'd0;
         blue_palette[41] = 8'd0;
         blue_palette[42] = 8'd0;
         blue_palette[43] = 8'd0;
         blue_palette[44] = 8'd0;
         blue_palette[45] = 8'd0;
         blue_palette[46] = 8'd0;
         blue_palette[47] = 8'd0;
         blue_palette[48] = 8'd0;
         blue_palette[49] = 8'd0;
         blue_palette[50] = 8'd0;
         blue_palette[51] = 8'd0;
         blue_palette[52] = 8'd0;
         blue_palette[53] = 8'd0;
         blue_palette[54] = 8'd0;
         blue_palette[55] = 8'd0;
         blue_palette[56] = 8'd0;
         blue_palette[57] = 8'd0;
         blue_palette[58] = 8'd0;
         blue_palette[59] = 8'd0;
         blue_palette[60] = 8'd0;
         blue_palette[61] = 8'd0;
         blue_palette[62] = 8'd0;
         blue_palette[63] = 8'd0;
         blue_palette[64] = 8'd64;
         blue_palette[65] = 8'd64;
         blue_palette[66] = 8'd64;
         blue_palette[67] = 8'd64;
         blue_palette[68] = 8'd64;
         blue_palette[69] = 8'd64;
         blue_palette[70] = 8'd64;
         blue_palette[71] = 8'd64;
         blue_palette[72] = 8'd64;
         blue_palette[73] = 8'd64;
         blue_palette[74] = 8'd64;
         blue_palette[75] = 8'd64;
         blue_palette[76] = 8'd64;
         blue_palette[77] = 8'd64;
         blue_palette[78] = 8'd64;
         blue_palette[79] = 8'd64;
         blue_palette[80] = 8'd64;
         blue_palette[81] = 8'd64;
         blue_palette[82] = 8'd64;
         blue_palette[83] = 8'd64;
         blue_palette[84] = 8'd64;
         blue_palette[85] = 8'd64;
         blue_palette[86] = 8'd64;
         blue_palette[87] = 8'd64;
         blue_palette[88] = 8'd64;
         blue_palette[89] = 8'd64;
         blue_palette[90] = 8'd64;
         blue_palette[91] = 8'd64;
         blue_palette[92] = 8'd64;
         blue_palette[93] = 8'd64;
         blue_palette[94] = 8'd64;
         blue_palette[95] = 8'd64;
         blue_palette[96] = 8'd64;
         blue_palette[97] = 8'd64;
         blue_palette[98] = 8'd64;
         blue_palette[99] = 8'd64;
         blue_palette[100] = 8'd64;
         blue_palette[101] = 8'd64;
         blue_palette[102] = 8'd64;
         blue_palette[103] = 8'd64;
         blue_palette[104] = 8'd64;
         blue_palette[105] = 8'd64;
         blue_palette[106] = 8'd64;
         blue_palette[107] = 8'd64;
         blue_palette[108] = 8'd64;
         blue_palette[109] = 8'd64;
         blue_palette[110] = 8'd64;
         blue_palette[111] = 8'd64;
         blue_palette[112] = 8'd64;
         blue_palette[113] = 8'd64;
         blue_palette[114] = 8'd64;
         blue_palette[115] = 8'd64;
         blue_palette[116] = 8'd64;
         blue_palette[117] = 8'd64;
         blue_palette[118] = 8'd64;
         blue_palette[119] = 8'd64;
         blue_palette[120] = 8'd64;
         blue_palette[121] = 8'd64;
         blue_palette[122] = 8'd64;
         blue_palette[123] = 8'd64;
         blue_palette[124] = 8'd64;
         blue_palette[125] = 8'd64;
         blue_palette[126] = 8'd64;
         blue_palette[127] = 8'd64;
         blue_palette[128] = 8'd128;
         blue_palette[129] = 8'd128;
         blue_palette[130] = 8'd128;
         blue_palette[131] = 8'd128;
         blue_palette[132] = 8'd128;
         blue_palette[133] = 8'd128;
         blue_palette[134] = 8'd128;
         blue_palette[135] = 8'd128;
         blue_palette[136] = 8'd128;
         blue_palette[137] = 8'd128;
         blue_palette[138] = 8'd128;
         blue_palette[139] = 8'd128;
         blue_palette[140] = 8'd128;
         blue_palette[141] = 8'd128;
         blue_palette[142] = 8'd128;
         blue_palette[143] = 8'd128;
         blue_palette[144] = 8'd128;
         blue_palette[145] = 8'd128;
         blue_palette[146] = 8'd128;
         blue_palette[147] = 8'd128;
         blue_palette[148] = 8'd128;
         blue_palette[149] = 8'd128;
         blue_palette[150] = 8'd128;
         blue_palette[151] = 8'd128;
         blue_palette[152] = 8'd128;
         blue_palette[153] = 8'd128;
         blue_palette[154] = 8'd128;
         blue_palette[155] = 8'd128;
         blue_palette[156] = 8'd128;
         blue_palette[157] = 8'd128;
         blue_palette[158] = 8'd128;
         blue_palette[159] = 8'd128;
         blue_palette[160] = 8'd128;
         blue_palette[161] = 8'd128;
         blue_palette[162] = 8'd128;
         blue_palette[163] = 8'd128;
         blue_palette[164] = 8'd128;
         blue_palette[165] = 8'd128;
         blue_palette[166] = 8'd128;
         blue_palette[167] = 8'd128;
         blue_palette[168] = 8'd128;
         blue_palette[169] = 8'd128;
         blue_palette[170] = 8'd128;
         blue_palette[171] = 8'd128;
         blue_palette[172] = 8'd128;
         blue_palette[173] = 8'd128;
         blue_palette[174] = 8'd128;
         blue_palette[175] = 8'd128;
         blue_palette[176] = 8'd128;
         blue_palette[177] = 8'd128;
         blue_palette[178] = 8'd128;
         blue_palette[179] = 8'd128;
         blue_palette[180] = 8'd128;
         blue_palette[181] = 8'd128;
         blue_palette[182] = 8'd128;
         blue_palette[183] = 8'd128;
         blue_palette[184] = 8'd128;
         blue_palette[185] = 8'd128;
         blue_palette[186] = 8'd128;
         blue_palette[187] = 8'd128;
         blue_palette[188] = 8'd128;
         blue_palette[189] = 8'd128;
         blue_palette[190] = 8'd128;
         blue_palette[191] = 8'd128;
         blue_palette[192] = 8'd192;
         blue_palette[193] = 8'd192;
         blue_palette[194] = 8'd192;
         blue_palette[195] = 8'd192;
         blue_palette[196] = 8'd192;
         blue_palette[197] = 8'd192;
         blue_palette[198] = 8'd192;
         blue_palette[199] = 8'd192;
         blue_palette[200] = 8'd192;
         blue_palette[201] = 8'd192;
         blue_palette[202] = 8'd192;
         blue_palette[203] = 8'd192;
         blue_palette[204] = 8'd192;
         blue_palette[205] = 8'd192;
         blue_palette[206] = 8'd192;
         blue_palette[207] = 8'd192;
         blue_palette[208] = 8'd192;
         blue_palette[209] = 8'd192;
         blue_palette[210] = 8'd192;
         blue_palette[211] = 8'd192;
         blue_palette[212] = 8'd192;
         blue_palette[213] = 8'd192;
         blue_palette[214] = 8'd192;
         blue_palette[215] = 8'd192;
         blue_palette[216] = 8'd192;
         blue_palette[217] = 8'd192;
         blue_palette[218] = 8'd192;
         blue_palette[219] = 8'd192;
         blue_palette[220] = 8'd192;
         blue_palette[221] = 8'd192;
         blue_palette[222] = 8'd192;
         blue_palette[223] = 8'd192;
         blue_palette[224] = 8'd192;
         blue_palette[225] = 8'd192;
         blue_palette[226] = 8'd192;
         blue_palette[227] = 8'd192;
         blue_palette[228] = 8'd192;
         blue_palette[229] = 8'd192;
         blue_palette[230] = 8'd192;
         blue_palette[231] = 8'd192;
         blue_palette[232] = 8'd192;
         blue_palette[233] = 8'd192;
         blue_palette[234] = 8'd192;
         blue_palette[235] = 8'd192;
         blue_palette[236] = 8'd192;
         blue_palette[237] = 8'd192;
         blue_palette[238] = 8'd192;
         blue_palette[239] = 8'd192;
         blue_palette[240] = 8'd192;
         blue_palette[241] = 8'd192;
         blue_palette[242] = 8'd192;
         blue_palette[243] = 8'd192;
         blue_palette[244] = 8'd192;
         blue_palette[245] = 8'd192;
         blue_palette[246] = 8'd240;
         blue_palette[247] = 8'd164;
         blue_palette[248] = 8'd128;
         blue_palette[249] = 8'd0;
         blue_palette[250] = 8'd0;
         blue_palette[251] = 8'd0;
         blue_palette[252] = 8'd255;
         blue_palette[253] = 8'd255;
         blue_palette[254] = 8'd255;
         blue_palette[255] = 8'd255;
      end

   always @ (color)
      begin
         red   <= red_palette[color];
         green <= green_palette[color];
         blue  <= blue_palette[color];
      end

endmodule
      
// This is the DE-2 picture rom that that is implemented using a 256 
// color bit map. The upper 8 bits represent the row address and the
// lower 8 bits represent the column address. The bit map data 
// represents the color value 0 to 255 that is present at each pixel
// location. (This color value is converted into Red/Green/Blue color
// intensities by the COLOR_PALETTE module.) The viewable region is
// approximately 178 x 213 pixels centered in the middle of the 256x256
// region with the pixels that are not in the viewable region being
// set to black. Data for the module is contained in the
// de2_pict_hx.txt file which is expected
// to reside with the other design files under the main project folder. 
module de2_picture (input blank_in,h_sync_in,v_sync_in,
    input [15:0] address, input clock,
    output reg blank_out,h_sync_out,v_sync_out, output reg [7:0] q);

   reg [7:0] data[0:65535];

   // directive to read data into memory
   initial
      begin
         $readmemh("de2_pict_hx.txt",data);
      end

   // synchronous memory model that will use the FPGA's Embedded
   // Block Synchronous RAMs
   always @ (posedge clock)	
      q = data[address];

   // one clock cycle delay of blanking & horizonal &
   // vertical sync signals so that they will be driven when
   // the pixel color data is retrieved from synchronous memory
   always @ (posedge clock)
      begin
      blank_out=blank_in;
      h_sync_out=h_sync_in;
      v_sync_out=v_sync_in;
      end    
		
endmodule

