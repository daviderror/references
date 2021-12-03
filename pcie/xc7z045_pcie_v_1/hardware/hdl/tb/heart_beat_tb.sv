`timescale 1ns / 1ps

module heart_beat_tb;
//-------------------------------------------------- setup
     localparam integer SPEED_GRADE     = 2;
     localparam         IS_DEBUG        = "true";
     localparam         IS_BLINK        = "true";

     localparam integer ITERATION       = 1000;
//-------------------------------------------------- end setup
     
     localparam integer CLOCK_PERIOD    = 120;
   
     localparam integer MAX_COUNTER_VAL = CLOCK_PERIOD - 1;
     localparam integer TEST_ITERATION  = ITERATION * MAX_COUNTER_VAL;

     bit clk        = '0;
     bit s_rst_n    = '1;
     bit heart_beat = '0;
     
     integer counter = 0;

     heart_beat #
     (
         .SPEED_GRADE   (SPEED_GRADE  ),
         .IS_DEBUG      (IS_DEBUG     ),
         .IS_BLINK      (IS_BLINK     ) 
     )
     heart_beat_dut
     (
         .i_clk        (clk       ),
         .i_s_rst_n    (s_rst_n   ),
                       
         .o_heart_beat (heart_beat)
     );
     
     always begin
         #(CLOCK_PERIOD / 2) clk = !clk;
     end

     initial begin
         s_rst_n <= '0;
         @(posedge clk);

         s_rst_n <= '1;
         @(posedge clk);
         
         repeat(TEST_ITERATION) begin
             if (counter == MAX_COUNTER_VAL) begin
                 counter = 0;
             end
             else begin
                 counter++;
             end
            
             @(posedge clk);
         end

         $stop();
     end
endmodule
