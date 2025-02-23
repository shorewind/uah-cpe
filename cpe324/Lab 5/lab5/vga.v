// Single Button Texter -- testbench vga driver module
// -- vga.v file
// (c) 2/5/2024 B. Earl Wells, University of Alabama in Huntsville
// all rights reserved -- for academic use only.
//
// This Verilog HDL module represents an VGA driver implementation
// The module outputs on the VGA at the current cursor location
// the character that is specified by the ascii_in value whenever
// the input ds is driven high for one clock cycle.
// It will also backspace one position whenever the ASCII backspace
// character is sent or whenever the back_sp signal is strobed high
// for one clock cycle.
// Cursor is returned to the begining position and the VGA is cleared
// whenever the reset signal is at a logic high.
// Note: this implementation is not bit mapped but instead uses a 
// separate screen memory that is 7 bits wide and has 240 elements. 
// This memory is then used as an input to the Character ROM which 
// supplies the pixel data.
module vga (input  clk,reset,ds,back_sp, input [7:0] ascii_in,
    output [7:0] vga_r, vga_g, vga_b, output vga_hs, vga_vs,
    vga_clk, vga_blank, vga_syn);

   // Character font ROM 
   reg [8191:0] font;

   // Screen Character RAM
   reg [6:0] scr_data [0:239];

   wire [9:0] pixel_rw, pixel_col;
   reg red, green, blue; 

   initial
      begin:MEM_SETUP

      reg [15:0] i; // local index pointer

      // character font ROM Initialization
      font[31:0]      = 32'b00000000000000000000000000000000;
      font[63:32]     = 32'b00000000000000000000000000000000;
      font[95:64]     = 32'b00000000000000000000000000000000;
      font[127:96]    = 32'b00000000000000000000000000000000;
      font[159:128]   = 32'b00000000000000000000000000000000;
      font[191:160]   = 32'b00000000000000000000000000000000;
      font[223:192]   = 32'b00000000000000000000000000000000;
      font[255:224]   = 32'b00000000000000000000000000000000;
      font[287:256]   = 32'b00000000000000000000000000000000;
      font[319:288]   = 32'b00000000000000000000000000000000;
      font[351:320]   = 32'b00000000000000000000000000000000;
      font[383:352]   = 32'b00000000000000000000000000000000;
      font[415:384]   = 32'b00000000000000000000000000000000;
      font[447:416]   = 32'b00000000000000000000000000000000;
      font[479:448]   = 32'b00000000000000000000000000000000;
      font[511:480]   = 32'b00000000000000000000000000000000;
      font[543:512]   = 32'b00000000000000000000000000000000;
      font[575:544]   = 32'b00000000000000000000000000000000;
      font[607:576]   = 32'b00000000000000000000000000000000;
      font[639:608]   = 32'b00000000000000000000000000000000;
      font[671:640]   = 32'b00000000000000000000000000000000;
      font[703:672]   = 32'b00000000000000000000000000000000;
      font[735:704]   = 32'b00000000000000000000000000000000;
      font[767:736]   = 32'b00000000000000000000000000000000;
      font[799:768]   = 32'b00000000000000000000000000000000;
      font[831:800]   = 32'b00000000000000000000000000000000;
      font[863:832]   = 32'b00000000000000000000000000000000;
      font[895:864]   = 32'b00000000000000000000000000000000;
      font[927:896]   = 32'b00000000000000000000000000000000;
      font[959:928]   = 32'b00000000000000000000000000000000;
      font[991:960]   = 32'b00000000000000000000000000000000;
      font[1023:992]  = 32'b00000000000000000000000000000000;
      font[1055:1024] = 32'b00000000000000000000000000000000;
      font[1087:1056] = 32'b00000000000000000000000000000000;
      font[1119:1088] = 32'b00000000000000000000000000000000;
      font[1151:1120] = 32'b00000000000000000000000000000000;
      font[1183:1152] = 32'b00000000000000000000000000000000;
      font[1215:1184] = 32'b00000000000000000000000000000000;
      font[1247:1216] = 32'b00000000000000000000000000000000;
      font[1279:1248] = 32'b00000000000000000000000000000000;
      font[1311:1280] = 32'b00000000000000000000000000000000;
      font[1343:1312] = 32'b00000000000000000000000000000000;
      font[1375:1344] = 32'b00000000000000000000000000000000;
      font[1407:1376] = 32'b00000000000000000000000000000000;
      font[1439:1408] = 32'b00000000000000000000000000000000;
      font[1471:1440] = 32'b00000000000000000000000000000000;
      font[1503:1472] = 32'b00000000000000000000000000000000;
      font[1535:1504] = 32'b00000000000000000000000000000000;
      font[1567:1536] = 32'b00000000000000000000000000000000;
      font[1599:1568] = 32'b00000000000000000000000000000000;
      font[1631:1600] = 32'b00000000000000000000000000000000;
      font[1663:1632] = 32'b00000000000000000000000000000000;
      font[1695:1664] = 32'b00000000000000000000000000000000;
      font[1727:1696] = 32'b00000000000000000000000000000000;
      font[1759:1728] = 32'b00000000000000000000000000000000;
      font[1791:1760] = 32'b00000000000000000000000000000000;
      font[1823:1792] = 32'b00000000000000000000000000000000;
      font[1855:1824] = 32'b00000000000000000000000000000000;
      font[1887:1856] = 32'b00000000000000000000000000000000;
      font[1919:1888] = 32'b00000000000000000000000000000000;
      font[1951:1920] = 32'b00000000000000000000000000000000;
      font[1983:1952] = 32'b00000000000000000000000000000000;
      font[2015:1984] = 32'b00000000000000000000000000000000;
      font[2047:2016] = 32'b00000000000000000000000000000000;
      font[2079:2048] = 32'b00000000000000000000000000000000;
      font[2111:2080] = 32'b00000000000000000000000000000000;
      font[2143:2112] = 32'b00011000000110000001100000000000;
      font[2175:2144] = 32'b00000000000110000000000000011000;
      font[2207:2176] = 32'b01100110011001100110011000000000;
      font[2239:2208] = 32'b00000000000000000000000000000000;
      font[2271:2240] = 32'b01100110111111110110011000000000;
      font[2303:2272] = 32'b00000000011001101111111101100110;
      font[2335:2304] = 32'b00111100000001100111110000011000;
      font[2367:2336] = 32'b00000000000110000011111001100000;
      font[2399:2368] = 32'b00011000001101100110011000000000;
      font[2431:2400] = 32'b00000000011000100110011000001100;
      font[2463:2432] = 32'b00011100001110000110110000111000;
      font[2495:2464] = 32'b00000000110111000110011011110110;
      font[2527:2496] = 32'b00011000000110000001100000000000;
      font[2559:2528] = 32'b00000000000000000000000000000000;
      font[2591:2560] = 32'b00011000001110000111000000000000;
      font[2623:2592] = 32'b00000000011100000011100000011000;
      font[2655:2624] = 32'b00011000000111000000111000000000;
      font[2687:2656] = 32'b00000000000011100001110000011000;
      font[2719:2688] = 32'b11111111001111000110011000000000;
      font[2751:2720] = 32'b00000000000000000110011000111100;
      font[2783:2752] = 32'b01111110000110000001100000000000;
      font[2815:2784] = 32'b00000000000000000001100000011000;
      font[2847:2816] = 32'b00000000000000000000000000000000;
      font[2879:2848] = 32'b00001100000110000001100000000000;
      font[2911:2880] = 32'b01111110000000000000000000000000;
      font[2943:2912] = 32'b00000000000000000000000000000000;
      font[2975:2944] = 32'b00000000000000000000000000000000;
      font[3007:2976] = 32'b00000000000011000000110000000000;
      font[3039:3008] = 32'b00011000001100000110000000000000;
      font[3071:3040] = 32'b00000000000000100000011000001100;
      font[3103:3072] = 32'b01110110011001100011110000000000;
      font[3135:3104] = 32'b00000000001111000110011001101110;
      font[3167:3136] = 32'b00011000000111000001100000000000;
      font[3199:3168] = 32'b00000000011111100001100000011000;
      font[3231:3200] = 32'b00110000011001100011110000000000;
      font[3263:3232] = 32'b00000000011111100000110000011000;
      font[3295:3264] = 32'b00011000001100000111111000000000;
      font[3327:3296] = 32'b00000000001111000110011000110000;
      font[3359:3328] = 32'b00111100001110000011000000000000;
      font[3391:3360] = 32'b00000000001100000111111000110110;
      font[3423:3392] = 32'b00111110000001100111111000000000;
      font[3455:3424] = 32'b00000000001111000110011001100000;
      font[3487:3456] = 32'b00111110000001100011110000000000;
      font[3519:3488] = 32'b00000000001111000110011001100110;
      font[3551:3520] = 32'b00110000011000000111111000000000;
      font[3583:3552] = 32'b00000000000011000000110000011000;
      font[3615:3584] = 32'b00111100011001100011110000000000;
      font[3647:3616] = 32'b00000000001111000110011001100110;
      font[3679:3648] = 32'b01111100011001100011110000000000;
      font[3711:3680] = 32'b00000000000111000011000001100000;
      font[3743:3712] = 32'b00011000000110000000000000000000;
      font[3775:3744] = 32'b00000000000110000001100000000000;
      font[3807:3776] = 32'b00011000000110000000000000000000;
      font[3839:3808] = 32'b00001100000110000001100000000000;
      font[3871:3840] = 32'b00001100000110000011000001100000;
      font[3903:3872] = 32'b00000000011000000011000000011000;
      font[3935:3904] = 32'b00000000011111100000000000000000;
      font[3967:3936] = 32'b00000000000000000111111000000000;
      font[3999:3968] = 32'b00110000000110000000110000000110;
      font[4031:4000] = 32'b00000000000001100000110000011000;
      font[4063:4032] = 32'b00110000011001100011110000000000;
      font[4095:4064] = 32'b00000000000110000000000000011000;
      font[4127:4096] = 32'b01110110011001100011110000000000;
      font[4159:4128] = 32'b00000000011111000000011001110110;
      font[4191:4160] = 32'b01100110001111000001100000000000;
      font[4223:4192] = 32'b00000000011001100111111001100110;
      font[4255:4224] = 32'b00111110011001100011111000000000;
      font[4287:4256] = 32'b00000000001111100110011001100110;
      font[4319:4288] = 32'b00000110011001100011110000000000;
      font[4351:4320] = 32'b00000000001111000110011000000110;
      font[4383:4352] = 32'b01100110001101100001111000000000;
      font[4415:4384] = 32'b00000000000111100011011001100110;
      font[4447:4416] = 32'b00111110000001100111111000000000;
      font[4479:4448] = 32'b00000000011111100000011000000110;
      font[4511:4480] = 32'b00111110000001100111111000000000;
      font[4543:4512] = 32'b00000000000001100000011000000110;
      font[4575:4544] = 32'b00000110000001100111110000000000;
      font[4607:4576] = 32'b00000000011111000110011001110110;
      font[4639:4608] = 32'b01111110011001100110011000000000;
      font[4671:4640] = 32'b00000000011001100110011001100110;
      font[4703:4672] = 32'b00011000000110000111111000000000;
      font[4735:4704] = 32'b00000000011111100001100000011000;
      font[4767:4736] = 32'b01100000011000000110000000000000;
      font[4799:4768] = 32'b00000000001111000110011001100000;
      font[4831:4800] = 32'b00011110001101100110011000000000;
      font[4863:4832] = 32'b00000000011001100011011000011110;
      font[4895:4864] = 32'b00000110000001100000011000000000;
      font[4927:4896] = 32'b00000000011111100000011000000110;
      font[4959:4928] = 32'b11111110111011101100011000000000;
      font[4991:4960] = 32'b00000000110001101100011011010110;
      font[5023:4992] = 32'b01111110011011100110011000000000;
      font[5055:5024] = 32'b00000000011001100111011001111110;
      font[5087:5056] = 32'b01100110011001100011110000000000;
      font[5119:5088] = 32'b00000000001111000110011001100110;
      font[5151:5120] = 32'b01100110011001100011111000000000;
      font[5183:5152] = 32'b00000000000001100000011000111110;
      font[5215:5184] = 32'b01100110011001100011110000000000;
      font[5247:5216] = 32'b00000000011011000011011001100110;
      font[5279:5248] = 32'b01100110011001100011111000000000;
      font[5311:5280] = 32'b00000000011001100011011000111110;
      font[5343:5312] = 32'b00111100000001100011110000000000;
      font[5375:5344] = 32'b00000000001111000110000001100000;
      font[5407:5376] = 32'b00011000000110000111111000000000;
      font[5439:5408] = 32'b00000000000110000001100000011000;
      font[5471:5440] = 32'b01100110011001100110011000000000;
      font[5503:5472] = 32'b00000000011111100110011001100110;
      font[5535:5504] = 32'b01100110011001100110011000000000;
      font[5567:5536] = 32'b00000000000110000011110001100110;
      font[5599:5568] = 32'b11010110110001101100011000000000;
      font[5631:5600] = 32'b00000000110001101110111011111110;
      font[5663:5632] = 32'b00111100011001100110011000000000;
      font[5695:5664] = 32'b00000000011001100110011000111100;
      font[5727:5696] = 32'b00111100011001100110011000000000;
      font[5759:5728] = 32'b00000000000110000001100000011000;
      font[5791:5760] = 32'b00011000001100000111111000000000;
      font[5823:5792] = 32'b00000000011111100000011000001100;
      font[5855:5824] = 32'b00011000000110000111100000000000;
      font[5887:5856] = 32'b00000000011110000001100000011000;
      font[5919:5888] = 32'b00001100000001100000001000000000;
      font[5951:5920] = 32'b00000000011000000011000000011000;
      font[5983:5952] = 32'b00011000000110000001111000000000;
      font[6015:5984] = 32'b00000000000111100001100000011000;
      font[6047:6016] = 32'b01101100001110000001000000000000;
      font[6079:6048] = 32'b00000000000000000000000011000110;
      font[6111:6080] = 32'b00000000000000000000000000000000;
      font[6143:6112] = 32'b00000000000110000001100000000000;
      font[6175:6144] = 32'b00000000000000000000000000000000;
      font[6207:6176] = 32'b00000000000000000000000000000000;
      font[6239:6208] = 32'b01100000001111000000000000000000;
      font[6271:6240] = 32'b00000000011111000110011001111100;
      font[6303:6272] = 32'b00111110000001100000011000000000;
      font[6335:6304] = 32'b00000000001111100110011001100110;
      font[6367:6336] = 32'b00000110001111000000000000000000;
      font[6399:6368] = 32'b00000000001111000000011000000110;
      font[6431:6400] = 32'b01111100011000000110000000000000;
      font[6463:6432] = 32'b00000000011111000110011001100110;
      font[6495:6464] = 32'b01100110001111000000000000000000;
      font[6527:6496] = 32'b00000000001111000000011001111110;
      font[6559:6528] = 32'b01111100000110000111000000000000;
      font[6591:6560] = 32'b00000000000110000001100000011000;
      font[6623:6592] = 32'b01100110011111000000000000000000;
      font[6655:6624] = 32'b00111110011000000111110001100110;
      font[6687:6656] = 32'b00111110000001100000011000000000;
      font[6719:6688] = 32'b00000000011001100110011001100110;
      font[6751:6720] = 32'b00011100000000000001100000000000;
      font[6783:6752] = 32'b00000000001111000001100000011000;
      font[6815:6784] = 32'b01100000000000000110000000000000;
      font[6847:6816] = 32'b00111100011000000110000001100000;
      font[6879:6848] = 32'b00110110000001100000011000000000;
      font[6911:6880] = 32'b00000000011001100011011000011110;
      font[6943:6912] = 32'b00011000000110000001110000000000;
      font[6975:6944] = 32'b00000000001111000001100000011000;
      font[7007:6976] = 32'b11111110011001100000000000000000;
      font[7039:7008] = 32'b00000000110001101101011011111110;
      font[7071:7040] = 32'b01100110001111100000000000000000;
      font[7103:7072] = 32'b00000000011001100110011001100110;
      font[7135:7104] = 32'b01100110001111000000000000000000;
      font[7167:7136] = 32'b00000000001111000110011001100110;
      font[7199:7168] = 32'b01100110001111100000000000000000;
      font[7231:7200] = 32'b00000110000001100011111001100110;
      font[7263:7232] = 32'b01100110011111000000000000000000;
      font[7295:7264] = 32'b01100000011000000111110001100110;
      font[7327:7296] = 32'b01100110001111100000000000000000;
      font[7359:7328] = 32'b00000000000001100000011000000110;
      font[7391:7360] = 32'b00000110011111000000000000000000;
      font[7423:7392] = 32'b00000000001111100110000000111100;
      font[7455:7424] = 32'b00011000011111100001100000000000;
      font[7487:7456] = 32'b00000000011100000001100000011000;
      font[7519:7488] = 32'b01100110011001100000000000000000;
      font[7551:7520] = 32'b00000000011111000110011001100110;
      font[7583:7552] = 32'b01100110011001100000000000000000;
      font[7615:7584] = 32'b00000000000110000011110001100110;
      font[7647:7616] = 32'b11010110110001100000000000000000;
      font[7679:7648] = 32'b00000000011011000111110011111110;
      font[7711:7680] = 32'b00111100011001100000000000000000;
      font[7743:7712] = 32'b00000000011001100011110000011000;
      font[7775:7744] = 32'b01100110011001100000000000000000;
      font[7807:7776] = 32'b00011110001100000111110001100110;
      font[7839:7808] = 32'b00110000011111100000000000000000;
      font[7871:7840] = 32'b00000000011111100000110000011000;
      font[7903:7872] = 32'b00000000000000000000000000000000;
      font[7935:7904] = 32'b00000000000000000000000000000000;
      font[7967:7936] = 32'b00011000000110000001100000011000;
      font[7999:7968] = 32'b00011000000110000001100000011000;
      font[8031:8000] = 32'b00000000000000000000000000000000;
      font[8063:8032] = 32'b00000000000000000000000000000000;
      font[8095:8064] = 32'b00000000000000000000000000000000;
      font[8127:8096] = 32'b00000000111111110000000000000000;
      font[8159:8128] = 32'b00000000000000000000000000000000;
      font[8191:8160] = 32'b00000000000000000000000000000000;

      // Screen Character RAM -- initialized to ASCII Spaces
      for (i=0;i<240;i=i+1) scr_data[i] = 7'b0100000;
          
      end


   //  procedural area that updates the screen RAM (add character, 
   // perform a backspace, or clear screen)
   always @ (posedge clk)
      begin:SCR_RAM_UPDATE
         reg [31:0] index=0;
         reg [15:0] i; // local index pointer
         if (reset)
            begin
            // clear screen and return to beginning of screen RAM
            index = 0;
            for (i=0;i<240;i=i+1) scr_data[i] = 7'b0100000;
            end
         else 
            if (back_sp)
               // backspace on place on screen if BACK_SP signal active
               // circular buffer
               begin
               if (index > 0)
                  index = index - 1;
               else
                  index = 239;
               // write an ASCII space at previous position
               scr_data[index] = 7'b0100000;
               end 
            else
               if (ds)
                  // backpace if ASCII backspace character received
                  if (ascii_in[6:0] == 8)
                     begin
                     // circular buffer
                     if (index > 0)
                        index = index - 1;
                     else
                        index = 239;
                     // write an ASCII space at previous position
                     scr_data[index] = 7'b0100000;
                     end
                  else
                     begin
                     // if no backspace or reset write ASCII character 
                     scr_data[index] =  ascii_in[6:0];
                     // circular buffer -- go forward to next character
                     if (index < 239)
                        index = index + 1;
                     else
                        index = 0;
                     end
      end

   // procedural region to continuously update the VGA monitor with 
   // character information taken from the ASCII screen data using the 
   // character font lookup table
   always @ (posedge clk)
      begin:VGA_DISPLAY
         reg [8:0] ch_addr;
         reg [4:0] col_st;
         reg [6:0] ascii_out;
         reg gun_out,gun_out_bl;
         if (pixel_col[9:5] > 0 && pixel_col[9:5]<17)
            begin
            // character address of a function of one pixel row and 
            //  pixel column
            col_st = pixel_col[9:5] - 1;
            ch_addr = {pixel_rw[9:5],col_st[3:0]};
            // screen memory supplies ASCII value
            // ASCII out forms 7 MSB of font index with other 6 
            // elements coming from the rw and col inputs
            ascii_out = scr_data[ch_addr];
            gun_out=font[{ascii_out, pixel_rw[4:2], pixel_col[4:2]}]; 
            gun_out_bl = 1;
            end
         else
            begin
            gun_out = 0;        
            gun_out_bl = 0;
            end
         // update red,green,blue signals
         red   = gun_out;
         green = gun_out;  
         blue  = gun_out_bl;
      end 

   vga_sync C1 (.clk(clk), .blank_out(vga_blank),.v_clk(vga_clk),
      .h_sync_out(vga_hs),.v_sync_out(vga_vs),
      .pixel_rw(pixel_rw), .pixel_col(pixel_col));

   assign vga_r[0] = red;
   assign vga_r[1] = red;
   assign vga_r[2] = red;
   assign vga_r[3] = red;
   assign vga_r[4] = red;  // red
   assign vga_r[5] = red;
   assign vga_r[6] = red;
   assign vga_r[7] = red;


   assign vga_g[0] = green;
   assign vga_g[1] = green;
   assign vga_g[2] = green;
   assign vga_g[3] = green;
   assign vga_g[4] = green;  // green
   assign vga_g[5] = green;
   assign vga_g[6] = green;
   assign vga_g[7] = green;

   assign vga_b[0] = blue;
   assign vga_b[1] = blue;
   assign vga_b[2] = blue;
   assign vga_b[3] = blue;
   assign vga_b[4] = blue;  // blue
   assign vga_b[5] = blue;
   assign vga_b[6] = blue;
   assign vga_b[7] = blue;


   assign vga_syn = 1;

endmodule

// This routine drives the VGA monitor on the DE2-115 board providing
// The necessary vertical, horizional synchronization, blanking, and
// DtoA clocking signals to the monitor.
// Inputs:
//    CLK: 50 MHZ system clock
// Outputs:
//    h_sync_out,v_sync_out // Horizional/Vertical Synch Lines
//    pixel_rw, pixel_col   // Current pixel row/column 
//    v_clk                 // digital to analog clock
//    blank_out             // display blanking signal
module vga_sync (input clk, output blank_out,v_clk,
   output reg h_sync_out,v_sync_out,
   output reg [9:0] pixel_rw, pixel_col);

   // video active flags -- false during retraces 
   reg video_on_h, video_on_v, clk_25=0; 
	
	// divide the DE2-115's clock by 2 so it is in effect a 25 Mhz clock
	   always @ (posedge clk)
	      clk_25 = ~clk_25;	

   // wait until rising edge of the 25 Mhz clock
   always @ (posedge clk_25) 
      begin:main_loop
         reg [10:0] col_count = 11'd0;
         reg [9:0]  row_count = 10'd0;

         // reset or increment horizonal column counter
         if (col_count==11'd797) 
             col_count <= 11'd0;
         else
             col_count <= col_count + 11'd1;

         // generate negative going horizonal synchronization pulse
         if (col_count >= 11'd655 && col_count <= 11'd702)
            h_sync_out <= 1'b0;
         else
            h_sync_out <= 1'b1;

         // reset or increment vertical row counter
         if (row_count == 10'd525 && col_count == 11'd797)
            row_count <= 10'd0;
         else 
            if (col_count == 11'd797) 
               row_count <= row_count + 10'd1;
 
         // generate negative going vertical synchronization pulse
         if (row_count >= 10'd491 && row_count <= 10'd492)
            v_sync_out <= 1'b0;
         else
            v_sync_out <= 1'b1;

         // send current horizonal column pixel count value to the 
         // pixel_col output bus if at data output phase of horizonal 
         // refresh cycle. Also indicate whether or not monitor is in 
         // horizonal blanking phase, where it turns off all three 
         // electron guns. 
         if (col_count < 11'd639)
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
	      if (row_count < 10'd479) 
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

      // v_clk is 180 degrees out of phase with clk_25
      assign v_clk = ~clk_25; 

endmodule

