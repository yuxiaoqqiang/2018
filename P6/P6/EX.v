`timescale 1ns / 1ps
`include"CTRL.v"
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:46:21 11/25/2015 
// Design Name: 
// Module Name:    EX 
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
module EX(clk,reset,instr, InputA, InputB, result,over,m_d_busy);
	 input clk;
	 input reset;
    input [31:0] instr;
    input [31:0] InputA;
    input [31:0] InputB;
    output [31:0] result;
	 output over;
	 output m_d_busy;
	 
	 wire overout;
	 wire log;
	 wire [31:0] alu_result;
	 wire [16:0] Op;
	 
	 assign overout = `add(instr) | `addi(instr) | `sub(instr);  
	 assign log = `sll(instr) | `srl(instr) | `sra(instr);
	 
	 assign Op[0] = `sub(instr) | `subu(instr);//-
	 assign Op[1] = `_and(instr) | `andi(instr);//&
	 assign Op[2] = `_or(instr) | `ori(instr);//|
	 assign Op[3] = `_xor(instr) | `xori(instr);//xor
	 assign Op[4] = `_nor(instr);//nor
	 assign Op[5] = `lui(instr);//lui
	 assign Op[6] = `sll(instr) | `sllv(instr);//logic<-
	 assign Op[7] = `srl(instr) | `srlv(instr);//logic->
	 assign Op[8] = `sra(instr) | `srav(instr);//sul->
	 assign Op[9] = `sltu(instr) | `sltiu(instr);//cmp
	 assign Op[10] = `slt(instr) | `slti(instr);//cmp
	 assign Op[11] = `seb(instr);//seb
	 assign Op[12] = `seh(instr);//seh
	 assign Op[13] = `wsbh(instr);//wsbh
	 assign Op[14] = (`movn(instr) & (InputB != 32'h00000000)) | (`movz(instr) & (InputB == 32'h00000000));//movn,movz
	 assign Op[15] = `clo(instr);//clo
	 assign Op[16] = `clz(instr);//clz
	 
	 
	 
    wire [6:0] m_d_op;
    wire start;
    wire we;
    wire busy;
    wire [31:0] HI_RD;
    wire [31:0] LO_RD;

    assign start = `m_d(instr) & ~busy;
    assign we = `w_h_l(instr);
	 assign m_d_op[0] = `multu(instr);
	 assign m_d_op[1] = `mult(instr);
	 assign m_d_op[2] = `divu(instr);
	 assign m_d_op[3] = `div(instr);
	 assign m_d_op[4] = `madd(instr);
	 assign m_d_op[5] = `maddu(instr);
	 assign m_d_op[6] = `msub(instr);
	 
    assign m_d_busy = `m_d(instr) | busy;
  
	 ALU ex_alu(InputA,InputB,instr[10:6],overout,log,Op,alu_result,over);
	 
	 M_D ex_m_d(clk,reset,InputA,InputB,`mthi(instr),`mtlo(instr),m_d_op,start,we,busy,HI_RD,LO_RD);
	 
	 assign result = `mfhi(instr) ? HI_RD : (`mflo(instr) ? LO_RD : alu_result);
  
endmodule

module ALU(InputA, InputB,InputC,overout,log,Op,alu_result,over);
    input [31:0] InputA;
    input [31:0] InputB;
	 input [4:0] InputC;
	 input overout;
	 input log;
	 input [16:0] Op;
    output [31:0] alu_result;
	 output over;
	 
	 wire over1;
	 wire [32:0] temp1;
	 wire [32:0] temp2;
	 wire [31:0] r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22;
	 
	 assign temp1 = {InputA[31], InputA} + {InputB[31], InputB};
	 assign temp2 = {InputA[31], InputA} - {InputB[31], InputB};
	 assign over1 = temp1[32] == temp1[31];
	 
	 integer i,j;
	 reg [31:0] temp3,temp4;
	 
	 initial begin
	 i=0;
	 j=0;
	 temp3=32'h00000000;
	 temp4=32'h00000000;
	 end
	 
	 always@(InputA || Op[15] || Op[16] )begin
	 temp3=32;
	 temp4=32;
	 for(i=31;i>=0;i=i-1)begin
		if(InputA[i]==1'b0 & temp3==32)begin
		temp3=31-i;
		end
	 end
	 for(j=31;j>=0;j=j-1)begin
		if(InputA[j]==1'b1 & temp4==32)begin
		temp4=31-j;
		end 
	 end
	 end
	 
    assign r0 = InputA + InputB;//addu,addiu
	 assign r1 = temp1[31:0];//add,addi
	 assign r2 = InputA - InputB;//subu
	 assign r3 = temp2[31:0];//sub
	 assign r4 = InputA & InputB;//and,andi
	 assign r5 = InputA | InputB;//or,ori
	 assign r6 = InputA ^ InputB;//xor,xori
	 assign r7 = ~(InputA | InputB);//nor
	 assign r8 = InputB << InputC;//sll
	 assign r9 = InputB << InputA[4:0];//sllv
	 assign r10 = InputB >> InputC;//srl
	 assign r11 = InputB >> InputA[4:0];//srlv
	 assign r12 = $signed(InputB) >>> InputC;//sra
    assign r13 = $signed(InputB) >>> InputA[4:0];//srav
	 assign r14 = {31'h00000000, InputA<InputB};//sltu,sltui
    assign r15 = {31'h00000000, $signed(InputA)<$signed(InputB)};//slt,slti
	 assign r16 = {InputB[15:0], 16'h0000};//lui
	 assign r17 = {{24{InputB[7]}},InputB[7:0]};//seb
	 assign r18 = {{16{InputB[15]}},InputB[15:0]};//seh
	 assign r19 = {InputB[23:16],InputB[31:24],InputB[7:0],InputB[15:8]};//wsbh
	 assign r20 = InputA;
	 assign r21 = temp3;
	 assign r22 = temp4;

	 assign alu_result = (Op[0] & ~overout) ? r2 :
	                     ((Op[0] & overout) ? r3 :
								(Op[1] ? r4 :
								(Op[2] ? r5 :
								(Op[3] ? r6 :
								(Op[4] ? r7 :
								(Op[5] ? r16 :
								((Op[6] & log) ? r8 :
								((Op[6] & ~log) ? r9 :
								((Op[7] & log) ? r10 :
								((Op[7] & ~log) ? r11 :
								((Op[8] & log) ? r12 :
								((Op[8] & ~log) ? r13 :
								(Op[9] ? r14 :
								(Op[10] ? r15 :
								((Op==17'b0 & ~overout) ? r0 :
								((Op==17'b0 & overout) ? r1 : 
								(Op[11] ? r17 :
								(Op[12] ? r18 :
								(Op[13] ? r19 : 
								(Op[14] ? r20 : 
								(Op[15] ? r21 :
								(Op[16] ? r22 : 32'h00000000))))))))))))))))))))));
								
	assign over = (overout & Op[0]) ? ~over1 : ((overout & ~Op[0]) ? over1 : 1'b0);

endmodule


module M_D(clk,reset,D1,D2,ifhi,iflo,op,start,we,busy,hi,lo);
    input clk;
    input reset;
    input [31:0] D1;
    input [31:0] D2;
    input ifhi;
	 input iflo;
    input [6:0] op;
    input start; 
    input we; 
    output reg busy; 
    output  [31:0] hi; 
    output  [31:0] lo; 

    reg [3:0] counter;
	 
	 reg [31:0] HI,LO;
	 
	 assign hi=HI;
	 assign lo=LO;
 
    initial begin
        busy=0;
        HI=0;
        LO=0;
        counter=0;
    end

    always @ (posedge clk | reset) begin 
		  if(reset)begin
		      busy<=0;
            HI<=0;
            LO<=0;
            counter<=0;
        end

        else if(start & ~reset) begin
				busy<=1;
            if(op[2] | op[3])begin
                counter=9;
            end
            else begin
                counter=4;
            end
				if(op[0])begin
				    {HI,LO}<={1'b0,D1}*{1'b0,D2};
				end
				else if(op[1])begin
					 {HI,LO}<=$signed(D1)*$signed(D2);
				end
				else if(op[2])begin
					 LO<={1'b0,D1}/{1'b0,D2};
                HI<={1'b0,D1}%{1'b0,D2};
				end
				else if(op[3])begin
					 LO<=$signed(D1)/$signed(D2);
                HI<=$signed(D1)%$signed(D2);
				end
				else if(op[4]|op[5])begin
					 {HI,LO}<={HI,LO}+({1'b0,D1}*{1'b0,D2});
			   end
				else if(op[6])begin
					 {HI,LO}<={HI,LO}-({1'b0,D1}*{1'b0,D2});
			   end
				
        end
		  else if(we & ~reset) begin
            if(ifhi) begin
                HI<=D1;
            end
            else if(iflo) begin
                LO<=D1;
            end
        end
		  else if(busy & ~reset) begin
            counter<=counter-1;
            if(counter==0) begin
                busy<=0;
            end
        end
    end
    
endmodule



