`timescale 1ns / 1ps

module axis_bit_rate_tb;

    localparam integer DATA_WIDTH   = 32;
    localparam integer CLOCK_PERIOD = 100;

    logic [DATA_WIDTH - 1 : 0] bit_rate       = '0;
    logic                      bit_rate_valid = 1'h0;

    logic                      clk            = 1'h0;
    logic                      rst_n          = 1'h0;
    logic                      en             = 1'h0;

    logic                      valid          = 1'h0;
    logic                      ready          = 1'h0;
    logic                      last           = 1'h0;

    logic [DATA_WIDTH - 1 : 0] counter        = 0;

    integer errors   = 0;

    axis_bit_rate #
    (
        .DATA_WIDTH (DATA_WIDTH)
    )
    axis_bit_rate_dut
    (
        .i_clk            (clk),
        .i_rst_n          (rst_n),
        .i_en             (en),

        .i_valid          (valid),
        .i_ready          (ready),
        .i_last           (last),

        .o_bit_rate       (bit_rate),
        .o_bit_rate_valid (bit_rate_valid)
    );

    initial begin
        clk = 1'h0;

        forever begin
            #( CLOCK_PERIOD / 2 ) clk = !clk;
        end 
    end

    task get_bit_rate; begin
        en <= 1'h1;
        
         

        repeat(1000) begin
            valid   <= $urandom_range(0, 1);
            ready   <= $urandom_range(0, 1);
            counter <= $urandom_range(100, 500);
            @(posedge clk);
            
      

            if (valid && ready) begin
                for(int i = 0; i < counter; i++) begin
                
            
                    if (i == counter - 2) begin
                        last <= 1'h1;
                    end
                    else begin
                        last <= 1'h0; 
                    end
                    
                    @(posedge clk);
                    
                end
                

                if (bit_rate_valid == 1'h1) begin
                    if (bit_rate != counter) begin
                    $error("A value has to be %d, but is %d", counter, bit_rate);
                    errors++;
                    end
                     else  $display("%d",bit_rate);
                end
               
            end
        end
    end
    endtask

    initial begin 
        rst_n <= 1'h0;
        @(posedge clk);
        rst_n <= 1'h1;
         
        get_bit_rate;
        @(posedge clk);

        if (errors == 0) begin
            $display("Test passed.");
        end 
        else begin
            $display("Test failed with %d errors.", errors);
        end

        $stop();
    end
endmodule
