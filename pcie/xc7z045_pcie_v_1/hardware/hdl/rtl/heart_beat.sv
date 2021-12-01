/*--------------------------------------------------
| engineer : A. Shimko
|
| module   : heart_beat.sv
| testbench: heart_beat_tb.sv
| 01.12.21 : created
*/

`timescale 1ns / 10ps

module heart_beat #
(
    parameter CLK_VALUE   = 100000000,
    parameter SPEED_GRADE = 2
)
(
    input  logic i_clk,
    input  logic i_srst_n,
    
    output logic o_heart_beat
);

    localparam integer COUNTER_WIDTH = $clog2(CLK_VALUE / SPEED_GRADE);
 
    logic                        heart_beat;
    logic [COUNTER_WIDTH - 1: 0] counter;
    
    assign o_heart_beat = heart_beat;
    
    always_ff @ (posedge i_clk) begin
        if (1'h0 == i_srst_n) begin
            counter    <= {COUNTER_WIDTH {1'h0}};
            heart_beat <= 1'h0;
        end
        else begin
            if ({COUNTER_WIDTH {1'h0}} == counter) begin
                heart_beat <= ~heart_beat;
            end
            
            counter <= counter + 1'h1;
        end
    end
endmodule
