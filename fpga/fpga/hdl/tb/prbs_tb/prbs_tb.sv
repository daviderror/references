/*--------------------------------------------------
| engineer : A. Shimko
|
| module   : prbs.sv
| testbench: prbs_tb.sv
| 21.11.21 : created
*/

`timescale 1ns / 1ps

module prbs_tb; 
    localparam integer PN             = 7; //3, 4, 5, 6, 7, 9, 11, 15, 17, 23, 31, 32, 36, 41
    localparam integer PERIOD         = 2 ** PN;

    localparam integer CLOCK_PERIOD   = 100;

    localparam integer TEST_ITERATION = 1000;
    localparam integer CHANGE_EN_VAL  = 100;

    logic clk     = '0;
    logic s_rst_n = '0;
    logic en      = '0;
    logic prbs    = '0;
    logic prbs_n  = '0;

    integer tick = 0;

    prbs #
    (
        .PN (PN)
    )
    prbs_dut
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
            if ((i % PERIOD) == (PERIOD - 1)) begin
                en   <= ~en;
                tick = 0;
            end
            else begin
                tick++;
            end

            @(posedge clk);
        end
        
        $finish;
    end
endmodule
