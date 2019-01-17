`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:47:28 11/25/2015 
// Design Name: 
// Module Name:    REG_M 
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
module REG_M(clk, Instr_in, ALUout_in, RT_in,PC_in ,Instr_out, ALUout_out, RT_out,PC_out);
    input clk;
    input [31:0] Instr_in;
    input [31:0] ALUout_in;
    input [31:0] RT_in;
	 input [31:0] PC_in;
    output reg [31:0] Instr_out;
    output reg [31:0] ALUout_out;
    output reg [31:0] RT_out;
	 output reg [31:0] PC_out;
	 initial begin
        Instr_out=0;
        ALUout_out=0;
        RT_out=0;
		  PC_out=0;
    end

    always@(posedge clk) begin
        Instr_out<=Instr_in;
        ALUout_out<=ALUout_in;
        RT_out<=RT_in;
		  PC_out=PC_in;
    end
    
    
endmodule
