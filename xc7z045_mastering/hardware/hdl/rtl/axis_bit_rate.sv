`timescale 1ns / 1ps

module axis_bit_rate #
(
    parameter integer DATA_WIDTH = 32
)
(
    input  logic                      i_clk,
    input  logic                      i_rst_n,
    input  logic                      i_en,

    input  logic                      i_valid,
    input  logic                      i_ready,
    input  logic                      i_last,

    output logic [DATA_WIDTH - 1 : 0] o_bit_rate,
    output logic                      o_bit_rate_valid
);
    logic clk_counter_en;
    logic clk_counter_rst_n;

    logic [DATA_WIDTH - 1 : 0] clk_counter;

    always_comb begin
        clk_counter_en    = i_valid && i_ready && i_en;
        clk_counter_rst_n = i_rst_n && !i_last;
    end

    always_ff @ (posedge i_clk) begin
        if (i_rst_n == 1'h0) begin
            o_bit_rate_valid <= 1'h0;
            o_bit_rate       <= '0;
        end 
        else if (i_last == 1'h1) begin 
            o_bit_rate      <= clk_counter;
        end

        o_bit_rate_valid <= i_last;        
    end

    always_ff @ (posedge i_clk) begin
        if (clk_counter_rst_n == 1'h0) begin
            clk_counter <= '0; 
        end
        else if (clk_counter_en == 1'h1) begin
            clk_counter++;
        end
    end
endmodule
