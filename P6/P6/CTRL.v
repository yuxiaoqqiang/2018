`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:52:18 11/25/2015 
// Design Name: 
// Module Name:    CTRL 
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

////R:number:21
`define add(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b100000) 
`define addu(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b100001)
`define sub(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b100010) 
`define subu(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b100011)
`define _or(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b100101)
`define _xor(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b100110)
`define _and(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b100100)
`define _nor(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b100111)
`define sll(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b000000 & instr[15:11] != 5'b00000)
`define srl(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b000010)
`define sra(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b000011)
`define sllv(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b000100)
`define srlv(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b000110)
`define srav(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b000111)
`define slt(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b101010)
`define sltu(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b101011)
`define seb(instr) (instr[31:26] == 6'b011111 & instr[5:0] == 6'b100000 & instr[10:6] == 5'b10000)
`define seh(instr) (instr[31:26] == 6'b011111 & instr[5:0] == 6'b100000 & instr[10:6] == 5'b11000)
`define wsbh(instr) (instr[31:26] == 6'b011111 & instr[5:0] == 6'b100000 & instr[10:6] == 5'b00010)
`define movn(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b001011)
`define movz(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b001010)
`define clo(instr) (instr[31:26] == 6'b011100 & instr[5:0] == 6'b100001)
`define clz(instr) (instr[31:26] == 6'b011100 & instr[5:0] == 6'b100000)

////I:number:8
`define addi(instr) (instr[31:26] == 6'b001000)
`define addiu(instr) (instr[31:26] == 6'b001001)
`define andi(instr) (instr[31:26] == 6'b001100)
`define ori(instr) (instr[31:26] == 6'b001101)
`define xori(instr) (instr[31:26] == 6'b001110)
`define lui(instr) (instr[31:26] == 6'b001111)
`define slti(instr) (instr[31:26] == 6'b001010)
`define sltiu(instr) (instr[31:26] == 6'b001011)

////L:number:5
`define lb(instr) (instr[31:26] == 6'b100000)
`define lbu(instr) (instr[31:26] == 6'b100100)
`define lh(instr) (instr[31:26] == 6'b100001)
`define lhu(instr) (instr[31:26] == 6'b100101)
`define lw(instr) (instr[31:26] == 6'b100011)

////S:number:3
`define sb(instr) (instr[31:26] == 6'b101000)
`define sh(instr) (instr[31:26] == 6'b101001)
`define sw(instr) (instr[31:26] == 6'b101011)

////B:number:7
`define beq(instr) (instr[31:26] == 6'b000100)
`define bne(instr) (instr[31:26] == 6'b000101)
`define blez(instr) (instr[31:26] == 6'b000110 & instr[20:16] == 5'b00000)
`define bgtz(instr) (instr[31:26] == 6'b000111 & instr[20:16] == 5'b00000)
`define bltz(instr) (instr[31:26] == 6'b000001 & instr[20:16] == 5'b00000)
`define bgez(instr) (instr[31:26] == 6'b000001 & instr[20:16] == 5'b00001)
`define bgezal(instr) (instr[31:26] == 6'b000001 & instr[20:16] == 5'b10001)
`define bltzal(instr) (instr[31:26] == 6'b000001 & instr[20:16] == 5'b10000) 

////M_D:number:4
`define mult(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b011000)
`define multu(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b011001)
`define div(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b011010)
`define divu(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b011011)
`define madd(instr) (instr[31:26] == 6'b011100 & instr[5:0] == 6'b000000)
`define maddu(instr) (instr[31:26] == 6'b011100 & instr[5:0] == 6'b000001)
`define msub(instr) (instr[31:26] == 6'b011100 & instr[5:0] == 6'b000100)

////H_L:number:4
`define mfhi(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b010000)
`define mflo(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b010010)
`define mthi(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b010001)
`define mtlo(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b010011)

////J:number:4
`define j(instr) (instr[31:26] == 6'b000010)
`define jal(instr) (instr[31:26] == 6'b000011)
`define jr(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b001000)
`define jalr(instr) (instr[31:26] == 6'b000000 & instr[5:0] == 6'b001001)

////////////////////////////////////////////////////////////////////////////////

`define cal_r(instr) (`add(instr) |`addu(instr) |`sub(instr) | `subu(instr) | `_or(instr) | `_xor(instr) | `_and(instr) | `_nor(instr) | `sll(instr) | `srl(instr) | `sra(instr) | `sllv(instr) | `srlv(instr) | `srav(instr) | `slt(instr) | `sltu(instr) | `seb(instr) | `seh(instr) | `wsbh(instr) | `movn(instr) | `movz(instr) | `clo(instr) | `clz(instr))
		  
`define cal_i(instr) (`addi(instr) | `addiu(instr) | `andi(instr) | `ori(instr) | `xori(instr) | `lui(instr) | `slti(instr) | `sltiu(instr))

`define branch(instr) (`beq(instr) | `bne(instr) | `blez(instr) | `bgtz(instr) | `bltz(instr) | `bgez(instr) | `bgezal(instr) | `bltzal(instr))

`define branch1(instr) (`beq(instr) | `bne(instr))

`define branch2(instr) (`blez(instr) | `bgtz(instr) | `bltz(instr) | `bgez(instr) | `bgezal(instr)) | `bltzal(instr)

`define load(instr) (`lb(instr) | `lbu(instr) | `lh(instr) | `lhu(instr) | `lw(instr))

`define store(instr) (`sb(instr) | `sh(instr) | `sw(instr))

`define m_d(instr) (`mult(instr) | `multu(instr) | `div(instr) | `divu(instr) | `madd(instr) | `maddu(instr) | `msub(instr))

`define r_h_l(instr) (`mfhi(instr) | `mflo(instr))

`define w_h_l(instr) (`mthi(instr) | `mtlo(instr))
