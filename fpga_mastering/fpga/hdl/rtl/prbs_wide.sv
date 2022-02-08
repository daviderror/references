/*--------------------------------------------------
| engineer : A. Shimko
|
| module   : prbs_wide.sv
| testbench: prbs_wide_tb.sv
| 21.11.21 : created
*/

/*
prbs_wide #
(
    .PN    (7 ), //integer: 3, 4, 5, 6, 7, 9, 11, 15, 17, 23, 31, 32, 36, 41
    .WIDTH (16)
)
prbs_wide_inst
(
    .i_clk     (), //1 bits width
    .i_s_rst_n (), //1 bits width
    .i_en      (), //1 bits width

    .o_prbs    (), //WIDTH bits width
    .o_prbs_n  ()  //WIDTH bits width
);
*/

`timescale 1ns / 1ps

module prbs_wide #
(
    parameter integer PN = 7, //3, 4, 5, 6, 7, 9, 11, 15, 17, 23, 31, 32, 36, 41
    parameter integer WIDTH = 16
)
(
    input  logic                 i_clk,
    input  logic                 i_s_rst_n,
    input  logic                 i_en,

    output logic [WIDTH - 1 : 0] o_prbs,
    output logic [WIDTH - 1 : 0] o_prbs_n
);
    localparam integer TAP_1 = (PN == 3) ? 2 :
                               (PN == 4) ? 3 :
                               (PN == 5) ? 4 :
                               (PN == 6) ? 5 :
                               (PN == 7) ? 6 :
                               (PN == 9) ? 8 :
                               (PN == 10) ? 9 :
                               (PN == 11) ? 10 :
                               (PN == 15) ? 14 :
                               (PN == 17) ? 16 :
                               (PN == 18) ? 17 :
                               (PN == 20) ? 19 :
                               (PN == 21) ? 20 :
                               (PN == 22) ? 21 :
                               (PN == 23) ? 22 :
                               (PN == 25) ? 24 :
                               (PN == 28) ? 27 :
                               (PN == 29) ? 28 :
                               (PN == 31) ? 30 :
                               (PN == 33) ? 32 :
                               (PN == 35) ? 34 :
                               (PN == 36) ? 35 :
                               (PN == 39) ? 38 :
                               (PN == 41) ? 40 : 0;

    localparam integer TAP_0 = (PN == 3) ? 1 :
                               (PN == 4) ? 2 :
                               (PN == 5) ? 2 :
                               (PN == 6) ? 4 :
                               (PN == 7) ? 5 :
                               (PN == 9) ? 4 :
                               (PN == 10) ? 6 :
                               (PN == 11) ? 8 :
                               (PN == 15) ? 13 :
                               (PN == 17) ? 13 :
                               (PN == 18) ? 10 :
                               (PN == 20) ? 16 :
                               (PN == 21) ? 18 :
                               (PN == 22) ? 20 :
                               (PN == 23) ? 17 :
                               (PN == 25) ? 21 :
                               (PN == 28) ? 24 :
                               (PN == 29) ? 27 :
                               (PN == 31) ? 27 :
                               (PN == 33) ? 19 :
                               (PN == 35) ? 23 :
                               (PN == 36) ? 24 :
                               (PN == 39) ? 34 :
                               (PN == 41) ? 37 : 0;

    logic [PN - 1 : 0] lfsr;
    logic [PN - 1 : 0] r_lfsr;  
    logic [WIDTH - 1 : 0] tmp;  
    
    always_comb begin
        lfsr = r_lfsr;

        for (int i = WIDTH - 1; i >= 0; i = i - 1) begin
            lfsr   = {lfsr[PN - 2 : 0], lfsr[TAP_1] ^ lfsr[TAP_0]};
            tmp[i] = lfsr[TAP_1] ^ lfsr[TAP_0];
        end
    end                 

    always_ff @ (posedge i_clk) begin
        if (i_s_rst_n == 1'h0) begin
            r_lfsr   <= '1;

            o_prbs   <= '0;
            o_prbs_n <= '1;
        end
        else if (i_en == 1'h1) begin
            r_lfsr <= lfsr;

            o_prbs   <= tmp;
            o_prbs_n <= ~tmp;
        end
    end
endmodule