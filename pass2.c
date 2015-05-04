#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void hexa_to_binary(char*, FILE*);
void conv_binary(char*, FILE*);


void conv_binary(char* s , FILE *f4)		//conversion of ilc to binary
{
	int arr[32] ={0},i=15,k;
	k =atoi(s);
	while(k !=0)
	{
		arr[i]= k%2;
		k=k/2;
		i--;
	}
	int j;
	for(j=16;j<32;j++)
	{
		fprintf(f4,"%d",arr[j]); }				//printing last 16 bits of 32 bit address
	fprintf(f4,"\n");

	for(j=0;j<16;j++)
	{
		fprintf(f4,"%d",arr[j]); }				//printing first 16 bits of 32 bit address
	fprintf(f4,"\n");
}

void hexa_to_binary(char* arr, FILE *f4)		//function to convert address or data to binary
{

	int length = strlen(arr);
	int i;
	if(arr[length -1] == 'H')
	{
		char arr2[5] = "0000";					//array for immediate data
		char arr1[9] ="00000000";			//array for memory address
		 int j,k;

		if (length == 5)					//loop for immediate data
		{
		for(j=3,k=length -2;k>=0;j--,k--)
		{
			arr2[j]= arr[k];
		}}

		if (length == 9)						//loop for address
		{
		for(j=7,k=length -2;k>=0;j--,k--)
		{
			arr1[j]= arr[k];
		}}


		int i=0;
		fprintf(f4,"\n");
		if(length==9)
		{

		for(i=4;arr1[i] != '\0';i++)				//printing binary values for last four bits of hexadecimal address
		{

			switch(arr1[i])
			{

				case '0': fprintf(f4,"0000");
					break;
				case '1': fprintf(f4,"0001");
					break;
				case '2': fprintf(f4,"0010");
					break;
				case '3': fprintf(f4,"0011");
					break;
				case '4': fprintf(f4,"0100");
					break;
				case '5': fprintf(f4,"0101");
					break;
				case '6': fprintf(f4,"0110");
					break;
				case '7': fprintf(f4,"0111");
					break;
				case '8': fprintf(f4,"1000");
					break;
				case '9': fprintf(f4,"1001");
					break;
				case 'a':
				case 'A': fprintf(f4,"1010");
					break;
				case 'b':
				case 'B':fprintf(f4,"1011");
					break;
				case 'c':
				case 'C':fprintf(f4,"1100");
					break;
				case 'd':
				case 'D':fprintf(f4,"1101");
					break;
				case 'e':
				case 'E': fprintf(f4,"1110");
					break;
				case 'f':
				case 'F': fprintf(f4,"1111");
					break;
			}
		}
	   }

	  	if(length==9)				// printing binary of first 4 bits of hexadecimal binary address
		{
			fprintf(f4,"\n");
		for(i=0;i<=3;i++)
		{


			switch(arr1[i])
			{

				case '0': fprintf(f4,"0000");
					break;
				case '1': fprintf(f4,"0001");
					break;
				case '2': fprintf(f4,"0010");
					break;
				case '3': fprintf(f4,"0011");
					break;
				case '4': fprintf(f4,"0100");
					break;
				case '5': fprintf(f4,"0101");
					break;
				case '6': fprintf(f4,"0110");
					break;
				case '7': fprintf(f4,"0111");
					break;
				case '8': fprintf(f4,"1000");
					break;
				case '9': fprintf(f4,"1001");
					break;
				case 'a':
				case 'A': fprintf(f4,"1010");
					break;
				case 'b':
				case 'B':fprintf(f4,"1011");
					break;
				case 'c':
				case 'C':fprintf(f4,"1100");
					break;
				case 'd':
				case 'D':fprintf(f4,"1101");
					break;
				case 'e':
				case 'E': fprintf(f4,"1110");
					break;
				case 'f':
				case 'F': fprintf(f4,"1111");
					break;
			}
		}
	   }




	   else												//printing binary to hexadecimal for immediate data
	   {
			for(i=0;arr2[i] != '\0';i++)
		{


			switch(arr2[i])
			{

				case '0': fprintf(f4,"0000");
					break;
				case '1': fprintf(f4,"0001");
					break;
				case '2': fprintf(f4,"0010");
					break;
				case '3': fprintf(f4,"0011");
					break;
				case '4': fprintf(f4,"0100");
					break;
				case '5': fprintf(f4,"0101");
					break;
				case '6': fprintf(f4,"0110");
					break;
				case '7': fprintf(f4,"0111");
					break;
				case '8': fprintf(f4,"1000");
					break;
				case '9': fprintf(f4,"1001");
					break;
				case 'a':
				case 'A': fprintf(f4,"1010");
					break;
				case 'b':
				case 'B':fprintf(f4,"1011");
					break;
				case 'c':
				case 'C':fprintf(f4,"1100");
					break;
				case 'd':
				case 'D':fprintf(f4,"1101");
					break;
				case 'e':
				case 'E': fprintf(f4,"1110");
					break;
				case 'f':
				case 'F': fprintf(f4,"1111");
					break;
			}
		}
	   }
		fprintf(f4,"\n");
	}
}
main()
{
	FILE *f1 ,*f2, *f3 , *f4;
	f1 = fopen("abc.txt" , "r");	//assembly code
	f2 = fopen("abc1.txt", "r");	//output of pass1
	f3 = fopen("ISA.txt", "r");	//nmemonics and registers-opcodes
	f4 = fopen("abc2.txt", "w");		//final binary output




	char ch , sh , c ,e, c1,d;

	char arr[17] , arr1[17] , arr2[17] ,arr3[17] ,line1[17],temp[17];
	int i=0, j=0 , k=0; int flag =0 , flag1 =0 , line ,  hexb, l=15;
	while(! feof(f1))
	{
		fscanf(f1 , "%s", arr);

		while(! feof(f3))			//printing opcodes of mnemonics and registers
		{
			flag = 0;
			fscanf(f3 , "%s %s", arr1,temp);

			if(strcmp(arr , arr1) == 0)
			{

				flag =1;
				fprintf(f4 , "%s", temp);
				break;
			}
		}

		rewind(f3);
		if( !strcmp(arr, ";") || !strcmp(arr , ":"))			//encounter new line
		{
		     fprintf(f4,"\n");
		}
		if(flag == 0)			//if hexadecimal(address or immediate data) or label
		{
              while((c = fgetc(f2)) != EOF)
	          {
		           if(c == '\n')				//conversion of labels to binary
		  			{
						flag1=0;
						fscanf(f2,"%s %s",arr2,line1);
						if(strcmp(arr2 , arr) == 0)
						{
								flag1 =1;
								fprintf(f4,"\n");
								conv_binary(line1 ,f4); break;
						}
					}
			}
			rewind(f2);

			if(flag1 ==0)				//conv of addresss and immediate data to binary
			{
				hexa_to_binary(arr , f4);
			}
		}
	}
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);

}


