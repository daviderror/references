//todo: heart beat
/*--------------------------------------------------
| engineer : A. Shimko
|
| module   : heart_beat.sv
| testbench: heart_beat_tb.sv
+--------------------------------------------------
| 01.12.21 : 1. created
+--------------------------------------------------
| 03.12.21 : 1. CLK_VALUE -> CLK_VALUE_MHZ
|            2. i_srst_n  -> i_s_rst_n
|            3. added a reset for "counter" by 
|               (counter == MAX_COUNTER_VAL) and 
|               "if else" for this logic
|            4. IS_DEBUG was added
|            5. IS_BLINK was added
*/

/*
heart_beat #
(
    .SPEED_GRADE   (2      ), // a just divider, integer, 2, 3, 5, 6
    .IS_DEBUG      ("false"), // for debugging, it reduces iteration  number of CLK_VALUE_MHZ, "true"/"false"
    .IS_BLINK      ("false")  // blink or hear beat mod, "true"/"false"
)
heart_beat_inst
(
    .i_clk        (), // 1 bit width
    .i_s_rst_n    (), // 1 bit width
                  
    .o_heart_beat ()  // 1 bit width
);
*/

`timescale 1ns / 10ps

module heart_beat #
(
    parameter integer SPEED_GRADE   = 2,
    parameter         IS_DEBUG      = "false",
    parameter         IS_BLINK      = "false"
)
(
    input  logic i_clk,
    input  logic i_s_rst_n,
    
    output logic o_heart_beat
);
    localparam integer                RATE            = (IS_DEBUG == "true") ? 120 : 120_000_000;
    localparam integer                MAX_COUNTER_VAL = RATE / (((SPEED_GRADE != 2 ) && 
                                                                 (SPEED_GRADE != 3 ) &&
                                                                 (SPEED_GRADE != 5 ) &&
                                                                 (SPEED_GRADE != 6 )) ? 2 : SPEED_GRADE);
                                                        
    localparam integer                COUNTER_WIDTH   = $clog2(MAX_COUNTER_VAL);
                                                            
    localparam [COUNTER_WIDTH - 1: 0] CMP_COUNTER_VAL = MAX_COUNTER_VAL - 1'h1;
    
 
    logic                        heart_beat;
    logic                        mask;
    logic [COUNTER_WIDTH - 1: 0] counter;

    assign o_heart_beat = heart_beat & ((IS_BLINK == "true") ? '1 : mask);
    
    always_ff @ (posedge i_clk) begin
        if (i_s_rst_n == '0) begin
            counter    <= '0;
            heart_beat <= '0;
        end
        else begin
            if (counter == CMP_COUNTER_VAL) begin
                heart_beat <= !heart_beat;
                counter    <= '0;
            end
            else begin
                counter++;
            end  
        end
    end
    
    generate 
         if (IS_BLINK == "false") begin
             localparam integer                MASK_COUNTER_PRE     = 4;
             localparam integer                MASK_MAX_COUNTER_VAL = (MAX_COUNTER_VAL / MASK_COUNTER_PRE);
    
             localparam integer                MASK_COUNTER_WIDTH   = $clog2(MASK_MAX_COUNTER_VAL);
             localparam [COUNTER_WIDTH - 1: 0] MASK_CMP_COUNTER_VAL = MASK_MAX_COUNTER_VAL - 1'h1;
             
             logic [MASK_COUNTER_WIDTH - 1: 0] mask_counter;
    
             always_ff @ (posedge i_clk) begin
                 if (i_s_rst_n == '0) begin
                     mask <= '0;
                     mask_counter <= '0;
                 end
                 else begin
                     if (mask_counter == MASK_CMP_COUNTER_VAL) begin
                         mask         <= !mask;
                         mask_counter <= '0;
                     end  
                     else begin
                         mask_counter++;
                     end
                 end
             end
         end
    endgenerate
endmodule
