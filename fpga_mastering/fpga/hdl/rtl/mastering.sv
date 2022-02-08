`timescale 1ns / 1ps
////


module mastering
(
    input logic clk_p,
    input logic clk_n
);

    wire clk;
    
    wire       in_0;
    wire [7:0] in_1;
    
    wire       out_0;      
    wire [7:0] out_1;
    wire [7:0] out_2; 
    wire       out_3;
    wire [7:0] out_4;     
    
    mastering_bd_wrapper
    mastering_bd_inst
    (
        .clk   (clk),
        
        .clk_n (clk_n),
        .clk_p (clk_p),
        
        .in_0  (in_0),
        .in_1  (in_1),
        
        .out_0 (out_0),
        .out_1 (out_1),
        .out_2 (out_2),
        .out_3 (out_3),
        .out_4 (out_4)
    );
    
    simple_dual_port_ram #
    (
        .DATA_WIDTH     (8),
        .ADDR_WIDTH     (8),
        
        .RAM_TYPE       ("block"),     
        .INIT_FILE_NAME ("")
    )
    simple_dual_port_ram_inst
    (
         .wr_clk        (clk),       
         .wr_en         (out_0),        
                              
         .wr_data       (out_1),      
                             
         .wr_addr       (out_2),      
                             
         .rd_clk        (clk),       
         .rd_en         (out_3),        
                             
         .rd_data       (in_1),      
         .rd_data_valid (in_0),
         .rd_addr       (out_4) 
    );

endmodule
