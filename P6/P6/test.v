`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:46:49 12/08/2015
// Design Name:   MIPS
// Module Name:   C:/Users/P6/test.v
// Project Name:  P6
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: MIPS
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test;

	// Inputs
	reg clk;
	reg reset;
	wire [31:0] IR_D,IR_E,IR_M,IR_W;
	wire RSD_M,RSD_W,RSE_M,RSE_W;
	wire rsdturn,rtdturn,rseturn,rteturn,dinturn;
	wire [31:0] ALUout_M;
	wire busy;

	// Instantiate the Unit Under Test (UUT)rsdturn,rtdturn,rseturn,rteturn,dinturn
	MIPS uut (
		.clk(clk), 
		.reset(reset),
		.IR_D(IR_D),
		.IR_E(IR_E),
		.IR_M(IR_M),
		.IR_W(IR_W),
		.RSD_M(RSD_M),
		.RSD_W(RSD_W),
		.RSE_M(RSE_M),
		.RSE_W(RSE_W),
		.rsdturn(rsdturn),
		.rtdturn(rtdturn),
		.rseturn(rseturn),
		.rteturn(rteturn),
		.dinturn(dinturn),
		.ALUout_M(ALUout_M),
		.busy(busy)
		
		
	);

	always #10 clk=~clk;
	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

