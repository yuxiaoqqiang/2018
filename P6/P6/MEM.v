`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:48:35 11/25/2015 
// Design Name: 
// Module Name:    MEM 
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
module MEM(clk, instr, addr, din, dout);
    input clk;
    input [31:0] instr;
    input [31:0] addr;
    input [31:0] din;
    output [31:0] dout;
	 
	 wire [31:0] memword;
	 wire [2:0] op1;
	 wire [4:0] op2;
	 wire [6:0] op;
	 
	 assign op1[0] = `sb(instr);
	 assign op1[1] = `sh(instr);
	 assign op1[2] = `sw(instr);
	 assign op2[0] = `lb(instr);
	 assign op2[1] = `lbu(instr);
	 assign op2[2] = `lh(instr);
	 assign op2[3] = `lhu(instr);
	 assign op2[4] = `lw(instr);
	 assign op[0] = op1[2];
	 assign op[1] = op1[0] & (addr[1:0] == 2'b00);
    assign op[2] = op1[0] & (addr[1:0] == 2'b01);
	 assign op[3] = op1[0] & (addr[1:0] == 2'b10);
	 assign op[4] = op1[0] & (addr[1:0] == 2'b11);
	 assign op[5] = op1[1] & (addr[1] == 0);
	 assign op[6] = op1[1] & (addr[1] == 1);
	 
	 DM mem_dm(clk,addr[12:2],din,op,`store(instr),memword);
	 
	 EXT1 mem_ext(addr[1:0],memword,op2,dout);
	 
endmodule

module DM(clk, addr,din,op,write, memword);
    input clk;
    input [12:2] addr;
    input [31:0] din;
	 input [6:0] op;
	 input write;
    output [31:0] memword;
    
    reg [31:0] memory[2047:0];
    

    integer i;
    initial begin
        for(i=0;i<2048;i=i+1) begin
            memory[i]=0;
        end
    end
	 
    assign memword=memory[addr[12:2]];
    
	 always@(posedge clk) begin
        if(write)begin
				 if(op[0])begin
				     memory[addr]<=din;
				 end
				 else if(op[1])begin
				     memory[addr][7:0]<=din[7:0];
				 end
				 else if(op[2])begin
					  memory[addr][15:8]<=din[7:0];
				 end
             else if(op[3])begin
					  memory[addr][23:16]<=din[7:0];
				 end
				 else if(op[4])begin
					  memory[addr][31:24]<=din[7:0];
				 end
				 else if(op[5])begin
					  memory[addr][15:0]<=din[15:0];
				 end
				 else if(op[6])begin
					  memory[addr][31:16]<=din[15:0];
				 end
        end
    end
endmodule

module EXT1(_byte,din,op2,dout);
    input [1:0] _byte;
    input [31:0] din;
	 input [4:0] op2;
    output [31:0] dout;
	 
	 wire [31:0] dout0,dout1,dout2,dout3,dout4,dout5,dout6,dout7,dout8,dout9,dout10,dout11,dout12;
	 wire lw;
	 wire lb_s0,lb_s1,lb_s2,lb_s3;
	 wire lb_u0,lb_u1,lb_u2,lb_u3;
	 wire lh_s0,lh_s1;
	 wire lh_u0,lh_u1;
	 
	 assign lw = op2[4];
	 assign lb_s0 = op2[0] & (_byte==2'b00);
	 assign lb_s1 = op2[0] & (_byte==2'b01);
	 assign lb_s2 = op2[0] & (_byte==2'b10);
	 assign lb_s3 = op2[0] & (_byte==2'b11);
	 assign lb_u0 = op2[1] & (_byte==2'b00);
	 assign lb_u1 = op2[1] & (_byte==2'b01);
	 assign lb_u2 = op2[1] & (_byte==2'b10);
	 assign lb_u3 = op2[1] & (_byte==2'b11);
	 assign lh_s0 = op2[2] & (_byte[1]==0);
	 assign lh_s1 = op2[2] & (_byte[1]==1);
	 assign lh_u0 = op2[3] & (_byte[1]==0);
	 assign lh_u1 = op2[3] & (_byte[1]==1);

	 assign dout0 = din;
	 
	 assign dout1 = {{24{din[7]}},din[7:0]};
      
    assign dout2 = {{24{din[15]}},din[15:8]};
      
    assign dout3 = {{24{din[23]}},din[23:16]};
         
    assign dout4 = {{24{din[31]}},din[31:24]};
     
    assign dout5 = {24'h000000,din[7:0]};
       
    assign dout6 = {24'h000000,din[15:8]};
      
    assign dout7 = {24'h000000,din[23:16]};
   
    assign dout8 = {24'h000000,din[31:24]};

    assign dout9 = {{16{din[15]}},din[15:0]};

    assign dout10 = {{16{din[31]}},din[31:16]};

    assign dout11 = {16'h0000,din[15:0]};
                  
	 assign dout12 = {16'h0000,din[31:16]};
	 
	 assign dout = lw ? dout0 : (lb_s0 ? dout1 : (lb_s1 ? dout2 : (lb_s2 ? dout3 : (lb_s3 ? dout4
						: (lb_u0 ? dout5 : (lb_u1 ? dout6 : (lb_u2 ? dout7 : (lb_u3 ? dout8
						: (lh_s0 ? dout9 : (lh_s1 ? dout10 : (lh_u0 ? dout11 : (lh_u1 ? dout12 : 32'h00000000))))))))))));
						

endmodule
