`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:37:15 11/25/2015 
// Design Name: 
// Module Name:    ID 
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
module ID(clk,reset,pc4, regwrite, instr, rs, rt,addr, wdata, npc, npc_sel, RD1, RD2, extended_data);
    input clk;
	 input reset;
    input [31:0] pc4;
    input regwrite;
    input [31:0] instr;
	 input [31:0] rs;
	 input [31:0] rt;
    input [4:0] addr;
    input [31:0] wdata;
    output [31:0] npc;
    output npc_sel;
    output [31:0] RD1;
    output [31:0] RD2;
    output [31:0] extended_data;
	 
	 wire [7:0] op;
	 wire ifbranch;
	 
	 assign op[0] = `beq(instr);
	 assign op[1] = `bne(instr);
	 assign op[2] = `bgezal(instr);
	 assign op[3] = `bgez(instr);
	 assign op[4] = `bltz(instr);
	 assign op[5] = `bgtz(instr);
	 assign op[6] = `blez(instr);
	 assign op[7] = `bltzal(instr);

	 
	 RF id_rf(clk,reset,instr[25:21],instr[20:16],addr,wdata,regwrite,RD1,RD2);
	 
	 EXT id_ext(instr[15:0],`ori(instr)|`andi(instr)|`xori(instr),extended_data);
	 
	 NPC id_npc(pc4,rs,instr[25:0],`j(instr),`jr(instr),`jal(instr),`jalr(instr),ifbranch,npc,npc_sel);

    CMP id_cmp(rs,rt,op,ifbranch);
endmodule

module RF(Clk, Rst, A1, A2, A3, WD, We, RD1, RD2);
    input Clk;
    input Rst;
    input [4:0] A1;
    input [4:0] A2;
    input [4:0] A3;
    input [31:0] WD;
	 input We;
    output [31:0] RD1;
    output [31:0] RD2;
    
    reg [31:0] _reg[31:0];
    integer i=0;
    
    assign RD1= _reg[A1];
    assign RD2= _reg[A2];

    initial begin
      for(i=0;i<32;i=i+1)begin
           _reg[i]=0;
        end
   end

    always@(posedge Clk) begin
        if(Rst) begin
            for(i=0;i<32;i=i+1)begin
                _reg[i]<=0;
            end
        end
        else if(We) begin
		  if(A3!=5'b00000)begin
           _reg[A3]<=WD;
        end
		  end
   end
endmodule


module NPC(pc4,rs,imme,ifj,ifjr,ifjal,ifjalr,ifbranch,npc,npc_sel);
    input [31:0] pc4;
	 input [31:0] rs;
    input [25:0] imme;
    input ifj;
	 input ifjr;
	 input ifjal;
	 input ifjalr;
	 input ifbranch;
    output [31:0] npc;
    output npc_sel;
    
    wire [31:0] npc_normal;
    wire [31:0] npc_jump;
    wire [31:0] pc;
	 wire [31:0] npc_jr;
	 wire [31:0] npc_branch;
	 
    assign pc=pc4-4;
	 assign npc_jr=rs;
	 assign npc_sel = ifj | ifbranch | ifjr | ifjal | ifjalr;
    assign npc_normal = pc4;
	 assign npc_branch = pc4 + {{14{imme[15]}},imme[15:0],2'b00};
    assign npc_jump = {pc[31:28], imme[25:0], 2'b00};
    assign npc = (ifj|ifjal) ? npc_jump : (ifbranch ? npc_branch : ((ifjr|ifjalr) ? npc_jr : npc_normal));	 
endmodule

module EXT(imm, extop, data);
    input [15:0] imm;
    input extop;
    output [31:0] data;
	 
    assign data = extop ? {16'h0000, imm} : {{16{imm[15]}}, imm};
endmodule

module CMP(A,B,Op,Br);
	input [31:0] A;
	input [31:0] B;
	input [7:0] Op;
	output Br;
	
	wire zero;
	wire zero1;
	wire zero2;

	assign zero = (A==B);
	assign zero1 = (~A[31]);
	assign zero2 = (~A[31] & A!=32'h00000000);
	
	assign Br=((Op[0] & zero) | (Op[1] & ~zero) | ((Op[2]|Op[3]) & zero1) | ((Op[4]|Op[7]) & ~zero1) | (Op[5] & zero2) | (Op[6] & ~zero2));
	
	
endmodule
	