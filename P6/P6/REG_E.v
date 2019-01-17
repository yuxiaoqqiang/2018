`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:44:30 11/25/2015 
// Design Name: 
// Module Name:    REG_E 
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
module REG_E(clk,stop, Instr_in, RS_in, RT_in, PC_in,Ext_in, Instr_out, RS_out, RT_out,PC_out, Ext_out);
    input clk;
	 input stop;
    input [31:0] Instr_in;
    input [31:0] RS_in;
    input [31:0] RT_in;
	 input [31:0] PC_in;
    input [31:0] Ext_in;
    output reg [31:0] Instr_out;
    output reg [31:0] RS_out;
    output reg [31:0] RT_out;
	 output reg [31:0] PC_out;
    output reg [31:0] Ext_out;
	 initial begin
        Instr_out=0;
        RS_out=0;
        RT_out=0;
		  PC_out=0;
        Ext_out=0;
    end

    always@(posedge clk) begin
	 if(stop)begin
			  Instr_out<=0;
           RS_out<=0;
           RT_out<=0;
			  PC_out<=0;
           Ext_out<=0;
	 end
	 else begin
           Instr_out<=Instr_in;
           RS_out<=RS_in;
           RT_out<=RT_in;
			  PC_out<=PC_in+4;			  			  
           Ext_out<=Ext_in;
    end
	 end

endmodule
