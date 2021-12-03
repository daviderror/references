`timescale 1ns / 1ps

module xc7z045_pcie_v_1
(
     inout  logic [14:0] DDR_addr,
     inout  logic [2:0]  DDR_ba,
     inout  logic        DDR_cas_n,
     inout  logic        DDR_ck_n,
     inout  logic        DDR_ck_p,
     inout  logic        DDR_cke,
     inout  logic        DDR_cs_n,
     inout  logic [3:0]  DDR_dm,
     inout  logic [31:0] DDR_dq,
     inout  logic [3:0]  DDR_dqs_n,
     inout  logic [3:0]  DDR_dqs_p,
     inout  logic        DDR_odt,
     inout  logic        DDR_ras_n,
     inout  logic        DDR_reset_n,
     inout  logic        DDR_we_n,
            
     inout  logic        FIXED_IO_ddr_vrn,
     inout  logic        FIXED_IO_ddr_vrp,
     inout  logic [53:0] FIXED_IO_mio,
     inout  logic        FIXED_IO_ps_clk,
     inout  logic        FIXED_IO_ps_porb,
     inout  logic        FIXED_IO_ps_srstb,
            
     output logic        pcie_link_up_led,
     input  logic [3:0]  pcie_rx_n,
     input  logic [3:0]  pcie_rx_p,
     input  logic [0:0]  pcie_sys_clk_100M_n,
     input  logic [0:0]  pcie_sys_clk_100M_p,
     input  logic        pcie_sys_rst_n,
     output logic [3:0]  pcie_tx_n,
     output logic [3:0]  pcie_tx_p,
     
     output logic        pcie_heart_beat_led
);
     localparam integer SPEED_GRADE     = 2;


     logic pcie_axi_clk;
     logic pcie_axi_rst_n;
     
     xc7z045_pcie_v_1_bd_wrapper
     xc7z045_pcie_v_1_bd_wrapper_inst
     (
         .DDR_addr            (DDR_addr           ),
         .DDR_ba              (DDR_ba             ),
         .DDR_cas_n           (DDR_cas_n          ),
         .DDR_ck_n            (DDR_ck_n           ),
         .DDR_ck_p            (DDR_ck_p           ),
         .DDR_cke             (DDR_cke            ),
         .DDR_cs_n            (DDR_cs_n           ),
         .DDR_dm              (DDR_dm             ),
         .DDR_dq              (DDR_dq             ),
         .DDR_dqs_n           (DDR_dqs_n          ),
         .DDR_dqs_p           (DDR_dqs_p          ),
         .DDR_odt             (DDR_odt            ),
         .DDR_ras_n           (DDR_ras_n          ),
         .DDR_reset_n         (DDR_reset_n        ),
         .DDR_we_n            (DDR_we_n           ), 
         
         .FIXED_IO_ddr_vrn    (FIXED_IO_ddr_vrn   ),
         .FIXED_IO_ddr_vrp    (FIXED_IO_ddr_vrp   ),
         .FIXED_IO_mio        (FIXED_IO_mio       ),
         .FIXED_IO_ps_clk     (FIXED_IO_ps_clk    ),
         .FIXED_IO_ps_porb    (FIXED_IO_ps_porb   ),
         .FIXED_IO_ps_srstb   (FIXED_IO_ps_srstb  ),
         
         .pcie_axi_clk        (pcie_axi_clk      ),
         .pcie_axi_rst_n      (pcie_axi_rst_n     ),
         .pcie_link_up_led    (pcie_link_up_led   ),   
         .pcie_rx_n           (pcie_rx_n          ),          
         .pcie_rx_p           (pcie_rx_p          ),          
         .pcie_sys_clk_100M_n (pcie_sys_clk_100M_n),
         .pcie_sys_clk_100M_p (pcie_sys_clk_100M_p),
         .pcie_sys_rst_n      (pcie_sys_rst_n     ),      
         .pcie_tx_n           (pcie_tx_n          ),          
         .pcie_tx_p           (pcie_tx_p          )          
     );
     
     heart_beat #
     (
         .SPEED_GRADE   (SPEED_GRADE),
         .IS_DEBUG      ("false"    ),
         .IS_BLINK      ("false"    )
     )
     heart_beat_inst
     (
         .i_clk        (pcie_axi_clk       ),
         .i_s_rst_n    (pcie_axi_rst_n     ),
                   
         .o_heart_beat (pcie_heart_beat_led)
     );
    
endmodule
