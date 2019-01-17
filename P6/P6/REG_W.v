`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:50:16 11/25/2015 
// Design Name: 
// Module Name:    REG_W 
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
module REG_W(clk, Instr_in, ALUout_in, DR_in,PC_in,Instr_out, ALUout_out,DR_out,PC_out);
    input clk;
    input [31:0] Instr_in;
    input [31:0] ALUout_in;
    input [31:0] DR_in;
	 input [31:0] PC_in;
    output reg [31:0] Instr_out;
    output reg [31:0] ALUout_out;
    output reg [31:0] DR_out;
	 output reg [31:0] PC_out;
	 initial begin
        Instr_out=0;
        ALUout_out=0;
        DR_out=0;
		  PC_out=0;
    end

    always@(posedge clk) begin
        Instr_out<=Instr_in;
        ALUout_out<=ALUout_in;
        DR_out<=DR_in;
		  PC_out<=PC_in;
    end
    
   
endmodule
