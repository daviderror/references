/*--------------------------------------------------
| engineer : A. Shimko
|
| module   : prbs_wide.sv
| testbench: prbs_wide_tb.sv
| 21.11.21 : created
*/

`timescale 1ns / 1ps

module prbs_wide_tb;
    localparam integer PN             = 7;
    localparam integer PERIOD         = 2 ** PN - 1;
    localparam integer WIDTH          = 128;

    localparam integer CLOCK_PERIOD   = 100;

    localparam integer TEST_ITERATION = 1000;
    localparam integer CHANGE_EN_VAL  = 100;

    logic                 clk     = '0;
    logic                 s_rst_n = '0;
    logic                 en      = '0;

    logic [WIDTH - 1 : 0] prbs    = '0;
    logic [WIDTH - 1 : 0] prbs_n  = '0;

    prbs_wide #
    (
        .PN    (PN   ),
        .WIDTH (WIDTH)
    )
    prbs_wide_dut
    (
        .i_clk     (clk    ),
        .i_s_rst_n (s_rst_n),
        .i_en      (en     ),

        .o_prbs    (prbs   ),
        .o_prbs_n  (prbs_n )
    );

    initial begin
        forever begin
            #( CLOCK_PERIOD / 2 ) clk = !clk;
        end 
    end

    initial begin
        s_rst_n <= '0;
        @(posedge clk);

        s_rst_n <= '1;
        en      <= '1;
        @(posedge clk);

        for(int i = 0; i < TEST_ITERATION; i++) begin        
            if ((i % PERIOD) == PERIOD - 1) begin
                en <= ~en;
            end
            @(posedge clk);
        end
        
        $finish;
    end
endmodule