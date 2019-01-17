`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:17:13 11/25/2015 
// Design Name: 
// Module Name:    WB 
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
module WB(instr, ALUout_W, DR_W,PC_in, waddr, wback, regwrite);
    input [31:0] instr;
    input [31:0] ALUout_W;
	 input [31:0] DR_W;
	 input [31:0] PC_in;
    output reg [4:0] waddr;
    output reg [31:0] wback;
    output reg regwrite;
	 always@(*)begin
			 waddr <= (`cal_r(instr) | `r_h_l(instr) | `jalr(instr)) ? instr[15:11] : ((`cal_i(instr) | `load(instr)) ? instr[20:16] : ((`jal(instr) | `bgezal(instr) | `bltzal(instr)) ? 5'b11111 : 5'b00000));
			 wback <= (`cal_r(instr) | `cal_i(instr) | `r_h_l(instr)) ? ALUout_W : (`load(instr) ? DR_W :((`jal(instr) | `bgezal(instr) | `jalr(instr) | `bltzal(instr)) ? PC_in : 32'h00000000));
			 regwrite <= `cal_r(instr) | `cal_i(instr) | `load(instr) | `jal(instr) | `bgezal(instr) | `jalr(instr) | `r_h_l(instr) | `bltzal(instr);
    end

endmodule
