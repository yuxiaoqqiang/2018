`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:30:30 11/25/2015 
// Design Name: 
// Module Name:    IF 
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
module IF(clk,reset,cont, npc_sel, npc,instr, pc4);
    input clk;
	 input reset;
	 input cont;
    input npc_sel;
    input [31:0] npc;
    output [31:0] instr;
    output [31:0] pc4;
    
    wire [31:0] pc;
	 
	 assign pc4=pc+4;

	 PC if_pc(clk,reset ,cont, npc_sel , npc , pc4, pc);

	 IM if_im(pc,instr);

endmodule


module PC(clk, reset,cont, npc_sel, npc, pc4 , pc);
    input clk;
	 input reset;
	 input cont;
	 input npc_sel;
    input [31:0] pc4;
	 input [31:0] npc;
    output reg [31:0] pc;
    
    initial begin
        pc=32'h00003000;
    end

    always@(posedge clk) begin
        if(reset) begin
            pc<=32'h00003000;
        end
        else begin 
		  if(cont)begin
		  if(npc_sel)begin
                pc<=npc;
					 end
		  else begin
					 pc<=pc4;
					 end
        end
		  end
    end
	 
endmodule

module IM(addr, dout);
    input [31:0] addr;
    output [31:0] dout;

    reg [31:0] im[2047:0];
    integer i;

    initial begin
    for(i=0;i<2048;i=i+1)begin
            im[i]=0;
    end
	 $readmemh("code.txt", im);
end
    assign dout=im[{~addr[12],addr[11:2]}];
    
endmodule
