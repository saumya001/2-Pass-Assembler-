# 2-Pass-Assembler-
Code in C  for generating machine code of self designed ISA using 2 pass Assembler Logic which was done as a project for COA ( Computer Organization and Architecture ) 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

struct opcodetable
{
        char opc[9];             //mnemonic name
        char opr1[6];            //operand 1
        char opr2[6];            //operand 2
        char opr3[6];            //operand 3
        char hexd[7];            //hexadecimal code of mnemonic
        int len;                 //instruction length
        int ins_class;           //instruction class
};

int main()
{
	FILE *f1, *f2,*fh;
	struct opcodetable s[73] = {   {"add","reg","reg","reg","0",1,1}, {"addf","reg","reg","reg","1",1,1},   {"sub","reg","reg","reg","2",1,1},
    {"subf","reg","reg","reg","3",1,1},     {"mul","reg","reg","reg","4",1,1},    {"mulf","reg","reg","reg","5",1,1},
    {"div","reg","reg","reg","6",1,1},    {"divf","reg","reg","reg","7",1,1},    {"load","reg","reg","reg","8",1,5},
    {"store","reg","reg","reg","9",1,5},   {"and","reg","reg","reg","A0",1,1},     {"or","reg","reg","reg","A1",1,1},
    {"xor","reg","reg","reg","A2",1,1},  {"adi","reg","reg","imm","A3",2,2},      {"subi","reg","reg","imm","A4",2,2},
    {"mov","reg","reg","none","A5",1,1},    {"movi","reg","imm","none","A6",2,2},
    {"inr","reg","reg","none","A7",1,1},   {"dcr","reg","reg","none","A8",1,1},   {"not","reg","reg","none","A90",1,1},
    {"cmp","reg","reg","none","A91",1,1},   {"shiftr","reg","reg","none","A92",1,1},   {"shiftl","reg","reg","none","A93",1,1},
    {"rotater","reg","reg","none","A94",1,1},  {"rotatel","reg","reg","none","A95",1,1},   {"rotaterc","reg","reg","none","A96",1,1},
    {"rotatelc","reg","reg","none","A97",1,1},   {"cmpi","reg","reg","none","A98",1,1},   {"call","reg","none","none","A99",1,4},
    {"cz","reg","none","none","A9A",1,4},  {"cnz","reg","none","none","A9B",1,4},  {"cp","reg","none","none","A9C",1,4},
	{"cm","reg","none","none","A9D",1,4}, {"cc","reg","none","none","A9E",1,4}, {"cnc","reg","none","none","A9F0",1,4},
	{"cpo","reg","none","none","A9F1",1,4}, {"cpe","reg","none","none","A9F2",1,4}, {"callov","reg","none","none","A9F3",1,4},
	{"jump","reg","none","none","A9F4",1,4}, {"jz","reg","none","none","A9F5",1,4}, {"jnz","reg","none","none","A9F6",1,4},
	{"jp","reg","none","none","A9F7",1,4}, {"jm","reg","none","none","A9F8",1,4}, {"jc","reg","none","none","A9F9",1,4},
	{"jnc","reg","none","none","A9FA",1,4}, {"jpo","reg","none","none","A9FB",1,4}, {"jpe","reg","none","none","A9FC",1,4},
	{"jumpov","reg","none","none","A9FD",1,4},{"in","reg","none","none","A9FE",1,4}, {"out","reg","none","none","A9FF0",1,5},
	{"push","reg","none","none","A9FF1",1,4}, {"pop","reg","none","none","A9FF2",1,4}, {"calli","imm","none","none","A9FF3",2,3},
	{"jumpi","imm","none","none","A9FF4",2,3}, {"ini","imm","none","none","A9FF5",2,3},{"outi","imm","none","none","A9FF6",2,3},
	{"pushi","imm","none","none","A9FF7",2,3}, {"popi","imm","none","none","A9FF8",2,3}, {"ret","none","none","none","A9FF9",1,6},
	{"rz","none","none","none","A9FFA",1,6}, {"rnz","none","none","none","A9FFB",1,6}, {"rp","none","none","none","A9FFC",1,6},
	{"rm","none","none","none","A9FFD",1,6}, {"rc","none","none","none","A9FFE",1,6}, {"rnc","none","none","none","A9FFF0",1,6},
	{"rpo","none","none","none","A9FFF1",1,6}, {"rpe","none","none","none","A9FFF2",1,6}, {"retov","none","none","none","A9FFF3",1,6},
	{"ei","none","none","none","A9FFF4",1,6}, {"di","none","none","none","A9FFF5",1,6}, {"nop","none","none","none","A9FFF6",1,6},
	{"hlt","none","none","none","A9FFF7",1,6}, {"start","none","none","none","A9FFF8",1,6}};

	f1 = fopen("abc.txt", "r");		//file containing assembly language codes using new ISA opened in read mode

	f2 = fopen("abc1.txt","w");		//pass one file opened in write mode

	char str[10],colon[10];
	int z,i,j,k,ilc=-1, flag = 0, flag3 = 0; //ilc is initialized to -1 sice we are incrementing it later since ilc of program starts from 0

    char c ,ch, sh,opcd[9];


	fprintf(f2,"LABEL NAME\tILC\n");

	while((c = fgetc(f1)) != EOF)
	{
		if(c == '\n')
		{
			fscanf(f1,"%s",str);
            for(i=0;i<73;i++)                       //calculating ilc
			{
                strcpy(opcd,s[i].opc);
				flag =0;
				if((strcmp( str,opcd)) == 0)
				{
					ilc+=s[i].len;
                    flag = 1;
					break;
				}
			}
	        if(flag == 0)                           //printing label name and ilc (Symbol Table)
	        {

	        	fscanf(f1,"%s",colon);
	        if (strcmp(colon,":") == 0)
	        	{
	        		fprintf(f2,"%s\t",str);
					fprintf(f2,"\t%d\n",++ilc);
				}
				else                   //if illegal opcode is encountered program is terminated
				{
					flag3 = 1;
					printf ("Error not valid OPCODE\nCan't proceed\n");
					printf("Press 1 to see valid opcodes\n");
					scanf("%d",&z);
						if(z==1)
						{
				printf("\nISA Opcodes\n");
				fh=fopen("help.txt", "r");
				while(1)
   				{
     					ch = fgetc(fh);
      					if( feof(fh) )
      					{
          					break ;
      					}
      					printf("%c", ch);
   				}
				fclose(fh);
				break;
				break;
			}
					return;
				}

            }
		}
	}
	rewind(f1);
	fprintf(f2,"\n\n\t\t   \t\t\tOPCODE TABLE\n\n");
	fprintf(f2,"MNEMONIC \tOPR1 \t\tOPR2 \t\tOPR3 \t\tHEX. CODE \tINSTR LENGTH \tINSTR CLASS\n");
	for(i=0; i<73; i++)       //printing opcode table
	{
		rewind(f1);
		while((c = fgetc(f1)) != EOF)
	    {
		     if(c == '\n')
		     {
		        	fscanf(f1,"%s",str);
		        	strcpy(opcd,s[i].opc);
		        	if((strcmp( str,opcd)) == 0)
				    {
	                     fprintf(f2,"%s \t\t%s \t\t%s \t\t%s \t\t%s \t\t    %d \t\t   %d\n",s[i].opc,s[i].opr1,s[i].opr2,s[i].opr3,s[i].hexd,s[i].len,s[i].ins_class);
	                     break;
                    }
			}
		}
	}


	fclose(f1);
	fclose(f2);
	getch();
}



