`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:33:16 11/25/2015 
// Design Name: 
// Module Name:    REG_D 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module REG_D(clk, cont, Instr_in, PC4_in, Instr_out, PC4_out);
    input clk;
	 input cont;
    input [31:0] Instr_in;
    input [31:0] PC4_in;
    output reg [31:0] Instr_out;
    output reg [31:0] PC4_out;

	 initial begin
        Instr_out=0;
        PC4_out=0;
    end

    always@(posedge clk) begin
				if(cont)begin
            Instr_out<=Instr_in;
            PC4_out<=PC4_in;
    end
	 end
   
endmodule
