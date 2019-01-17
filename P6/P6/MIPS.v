`timescale 1ns / 1ps

`include "CTRL.v"
`include "IF.v"
`include "ID.v"
`include "EX.v"
`include "MEM.v"
`include "WB.v"
`include "REG_D.v"
`include "REG_E.v"
`include "REG_M.v"
`include "REG_W.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:15:27 11/25/2015 
// Design Name: 
// Module Name:    MIPS 
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
module MIPS(clk, reset,IR_D,IR_E,IR_M,IR_W,RSD_M,RSD_W,RSE_M,RSE_W,rsdturn,rtdturn,rseturn,rteturn,dinturn,ALUout_M,busy);
    input clk;
    input reset;
    
    output [31:0] IR_D;
    wire [31:0] PC_D;
    output [31:0] IR_E;
    wire [31:0] RS_E;
    wire [31:0] RT_E;
    wire [31:0] EXT_E;
    output [31:0] IR_M;
    output [31:0] ALUout_M;
    wire [31:0] RT_M;
    output [31:0] IR_W;
    wire [31:0] ALUout_W;
    wire [31:0] DR_W;
	 wire [31:0] inputA;
	 wire [31:0] inputB; 
    wire [31:0] rdata;
    wire [31:0] wdata; 
    wire [31:0] instr;
	 wire [31:0] rs;
    wire [31:0] rt;
    wire [31:0] pc_4;
    wire [31:0] rd1;
    wire [31:0] rd2;
    wire [31:0] ext_data;
    wire [31:0] alu_out;
    wire [31:0] dr;
	 wire [31:0] din;
    wire [31:0] npc;
    wire npc_sel;
    wire regwrite;	
    wire [4:0] addr;
	 wire over;
	 output busy;

	 
	 output RSD_M,RSD_W,RSE_M,RSE_W;
	 wire RTD_M,RTD_W,RTE_M,RTE_W;
	 wire JRSD_E,JRSD_M,JRSD_W,JRSE_M,JRSE_W;
	 wire JRTD_E,JRTD_M,JRTD_W,JRTE_M,JRTE_W;
	 wire DINM_W;
	 wire JDINM_W;
	 wire pause;
	 wire pause1;
	 wire pause2;
	 wire pause3;
	 wire pause4;
	 wire [31:0] PC_E,PC_M,PC_W;
	 wire wr,wi;
	 wire mr,mi;
	 wire er,ei;
	 wire el,ml,wl;
	 output rsdturn,rtdturn,rseturn,rteturn,dinturn;
	 
	 assign wr = `cal_r(IR_W);
	 assign wi = `cal_i(IR_W);
	 assign mr = `cal_r(IR_M);
	 assign mi = `cal_i(IR_M);
	 assign er = `cal_r(IR_E);
	 assign ei = `cal_i(IR_E);
	 assign el = `load(IR_E);
	 assign ml = `load(IR_M);
	 assign wl = `load(IR_W);

	 assign inputB = (ei|el|`store(IR_E)) ? EXT_E : rdata;
	 
	 assign pause1 = ((`cal_r(IR_D) | `m_d(IR_D)) & (el & (IR_D[25:21] == IR_E[20:16] | IR_D[20:16] == IR_E[20:16]))) | ((`cal_i(IR_D)|`load(IR_D)|`store(IR_D)|`w_h_l(IR_D)) & (el & IR_D[25:21] == IR_E[20:16]));
	 assign pause2 =`branch1(IR_D) & (((er|`r_h_l(IR_E))& (IR_D[25:21] == IR_E[15:11] | IR_D[20:16] == IR_E[15:11])) | ((ei|el) & (IR_D[25:21] == IR_E[20:16] | IR_D[20:16] == IR_E[20:16])) | (ml & (IR_D[25:21] == IR_M[20:16] | IR_D[20:16] == IR_M[20:16])));
	 assign pause3 = (`branch2(IR_D)|`jr(IR_D)|`jalr(IR_D)) & (((er|`r_h_l(IR_E)) & (IR_D[25:21] == IR_E[15:11])) | ((ei|el) & (IR_D[25:21] == IR_E[20:16])) | (ml & (IR_D[25:21] == IR_M[20:16])));
	 assign pause4 = busy & (`m_d(IR_D) | `r_h_l(IR_D) | `w_h_l(IR_D));
	 assign pause = pause1 | pause2 | pause3 | pause4; 
	  
	 assign rsdturn = `branch(IR_D) | `jr(IR_D) | `cal_r(IR_D) | `cal_i(IR_D) | `load(IR_D) | `store(IR_D) | `jalr(IR_D) | `m_d(IR_D) | `w_h_l(IR_D);			
	 assign rtdturn = `branch1(IR_D) | `cal_r(IR_D) | `store(IR_D) | `m_d(IR_D); 
	 assign rseturn = ei|er|el|`store(IR_E) | `w_h_l(IR_E) | `m_d(IR_E);
	 assign rteturn = er|`store(IR_E) | `m_d(IR_E);
	 assign dinturn = `store(IR_M);

	 assign RSD_M = rsdturn & ((((mr|`r_h_l(IR_M)) & IR_M[15:11]!=5'b00000) & IR_D[25:21] == IR_M[15:11]) | ((mi&IR_M[20:16]!=5'b00000) & IR_D[25:21] == IR_M[20:16]));
	 assign RSD_W = rsdturn & ((((wr|`r_h_l(IR_W)) & IR_W[15:11]!=5'b00000) & IR_D[25:21] == IR_W[15:11]) | (((wi|wl)&IR_W[20:16]!=5'b00000) & IR_D[25:21] == IR_W[20:16]));	
	 assign JRSD_E = rsdturn & ((`jal(IR_E) |`jalr(IR_E)) & IR_D[25:21] == 5'b11111);
	 assign JRSD_M = rsdturn & ((`jal(IR_M) |`jalr(IR_M)) & IR_D[25:21] == 5'b11111);
	 assign JRSD_W = rsdturn & ((`jal(IR_W) |`jalr(IR_W)) & IR_D[25:21] == 5'b11111);
	 	 
	 assign RTD_M = rtdturn & ((((mr|`r_h_l(IR_M)) & IR_M[15:11]!=5'b00000) & IR_D[20:16] == IR_M[15:11]) | ((mi&IR_M[20:16]!=5'b00000) & IR_D[20:16] == IR_M[20:16])); 
	 assign RTD_W = rtdturn & ((((wr|`r_h_l(IR_W)) & IR_W[15:11]!=5'b00000) & IR_D[20:16] == IR_W[15:11]) | (((wi|wl)&IR_W[20:16]!=5'b00000) & IR_D[20:16] == IR_W[20:16]));	
	 assign JRTD_E = rtdturn & ((`jal(IR_E) |`jalr(IR_E)) & IR_D[20:16] == 5'b11111);
	 assign JRTD_M = rtdturn & ((`jal(IR_M) |`jalr(IR_M)) & IR_D[20:16] == 5'b11111);
	 assign JRTD_W = rtdturn & ((`jal(IR_W) |`jalr(IR_W)) & IR_D[20:16] == 5'b11111);
	 
	 assign RSE_M = rseturn & ((((mr|`r_h_l(IR_M)) & IR_M[15:11]!=5'b00000) & IR_E[25:21] == IR_M[15:11]) | ((mi&IR_M[20:16]!=5'b00000) & IR_E[25:21] == IR_M[20:16]));
	 assign RSE_W = rseturn & ((((wr|`r_h_l(IR_W)) & IR_W[15:11]!=5'b00000) & IR_E[25:21] == IR_W[15:11]) | (((wi|wl)&IR_W[20:16]!=5'b00000) & IR_E[25:21] == IR_W[20:16]));	
	 assign JRSE_M = rseturn & ((`jal(IR_M) |`jalr(IR_M)) & IR_E[25:21] == 5'b11111);
	 assign JRSE_W = rseturn & ((`jal(IR_W) |`jalr(IR_W)) & IR_E[25:21] == 5'b11111);
	 		
	 assign RTE_M = rteturn & ((((mr|`r_h_l(IR_M)) & IR_M[15:11]!=5'b00000) & IR_E[20:16] == IR_M[15:11]) | ((mi&IR_M[20:16]!=5'b00000) & IR_E[20:16] == IR_M[20:16]));
	 assign RTE_W = rteturn & ((((wr|`r_h_l(IR_W)) & IR_W[15:11]!=5'b00000) & IR_E[20:16] == IR_W[15:11]) | (((wi|wl)&IR_W[20:16]!=5'b00000) & IR_E[20:16] == IR_W[20:16]));	
	 assign JRTE_M = rteturn & ((`jal(IR_M) |`jalr(IR_M)) & IR_E[20:16] == 5'b11111);
	 assign JRTE_W = rteturn & ((`jal(IR_W) |`jalr(IR_W)) & IR_E[20:16] == 5'b11111); 
	 
	 assign DINM_W = dinturn & ((((wr|`r_h_l(IR_W)) & IR_W[15:11]!=5'b00000) & IR_M[20:16] == IR_W[15:11]) | (((wi|wl)&IR_W[20:16]!=5'b00000) & IR_M[20:16] == IR_W[20:16]));
	 assign JDINM_W = dinturn & ((`jal(IR_W) |`jalr(IR_W)) & IR_M[20:16] == 5'b11111);
	  
	 assign rs = RSD_M ? ALUout_M : (RSD_W ? wdata : (JRSD_E ? PC_E : (JRSD_M ? PC_M : (JRSD_W ? PC_W :rd1)))); 
	 assign rt = RTD_M ? ALUout_M : (RTD_W ? wdata : (JRTD_E ? PC_E : (JRTD_M ? PC_M : (JRTD_W ? PC_W :rd2))));
	 assign inputA = RSE_M ? ALUout_M : (RSE_W ? wdata : (JRSE_M ? PC_M : (JRSE_W ? PC_W :RS_E))); 
    assign rdata = RTE_M ? ALUout_M : (RTE_W ? wdata : (JRTE_M ? PC_M : (JRTE_W ? PC_W :RT_E)));
	 assign din = DINM_W ? wdata : (JDINM_W ? PC_W :RT_M);	
	 					  
	 IF mips_if(clk,reset,~pause,npc_sel,npc,instr,pc_4);

	 REG_D mips_reg_d(clk,~pause,instr,pc_4,IR_D,PC_D);

	 ID mips_id(clk,reset,PC_D,regwrite,IR_D,rs,rt,addr,wdata,npc,npc_sel,rd1,rd2,ext_data);

	 REG_E mips_reg_e(clk,pause,IR_D,rs,rt,PC_D,ext_data,IR_E,RS_E,RT_E,PC_E,EXT_E);

	 EX mips_ex(clk,reset,IR_E,inputA,inputB,alu_out,over,busy);

	 REG_M mips_reg_m(clk,IR_E,alu_out,rdata,PC_E,IR_M,ALUout_M,RT_M,PC_M);

	 MEM mips_mem(clk,IR_M,ALUout_M,din,dr);

	 REG_W mips_reg_w(clk,IR_M,ALUout_M,dr,PC_M,IR_W,ALUout_W,DR_W,PC_W);
 
	 WB mips_wb(IR_W,ALUout_W,DR_W,PC_W,addr,wdata,regwrite);
	 
endmodule
