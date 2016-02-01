#include <stdio.h>
#include <stdlib.h>
#include <string.h>


volatile int * reg_32= (int *) 0xFF200018;
volatile int * FPGA_onchip = (int *) 0xC4000000;
volatile int * FPGA_sdram = (int *) 0xC0000000;
volatile int * HPS_onchip = (int *) 0xFFFF0000;
volatile int * HPS_sdram = (int *) 0x00100000;

static inline unsigned int getCycles()
{
	unsigned int cycleCount;
	asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(cycleCount));
	return cycleCount;
}

static inline void initCounters ()
{
	asm volatile ("MCR p15, 0, %0, c9, c14, 0\t\n":: "r"(1));
	int MCRP15ResetAll = 23;
	asm volatile ("MCR p15, 0, %0, c9, c12, 0\t\n":: "r"(MCRP15ResetAll));
	
	asm volatile ("MCR p15, 0, %0, c9, c12, 1\t\n":: "r"(0x8000000f));
	asm volatile ("MCR p15, 0, %0, c9, c14, 2\t\n":: "r"(0x8000000f));
	asm volatile ("MCR p15, 0, %0, c9, c12, 3\t\n":: "r"(0x8000000f));
}

int main(void) {

  (*reg_32)=0xabcd;

  char input_str[64];
  int i;
  int write_arr[8192];
//  short write_arr16[8192];
  int read_arr[8192];
//  short read_arr16[8192];

  for (i = 0; i < 8192; i++) {
	write_arr[i] = i;
//	write_arr16[i] = i;
  }
  while (1) {
	  printf("Type 'mem' to perform memory test, anything else for hex display: ");
	  scanf("%s", input_str);

	  if (!strcmp(input_str, "mem")) 
	  {
		printf("Type '1' to test FPGA On-CHIP memory.\n");
		printf("Type '2' to test FPGA SDRAM memory.\n");
		printf("Type '3' to test HPS On-CHIP memory.\n");
		printf("Type anything else to test HPS On-CHIP memory.\n");
		scanf("%s", input_str);
		
		volatile int * mem_addr;
		if (!strcmp(input_str, "1")) mem_addr = FPGA_onchip;
		else if (!strcmp(input_str, "2")) mem_addr = FPGA_sdram;
		else if (!strcmp(input_str, "3")) mem_addr = HPS_onchip;
		else mem_addr = HPS_sdram;

		//unsigned int i = 0;
		initCounters();

		// Clear memory
		for (i = 0; i < 8192; i++) {
			(*mem_addr) = 0;
			mem_addr += 1;
			read_arr[i] = 0;
//			read_arr16[i] = 0;
		}
		mem_addr -= 8192;

		printf("Writing to memory...\n");
		unsigned int time = getCycles();
		for (i = 0; i < 8192; i++) {
//			if (!strcmp(input_str,"2")) {
//				(*mem_addr) = write_arr16[i];
//			}
//			else 
				(*mem_addr) = write_arr[i];
			mem_addr += 1;
		}

		time = getCycles() - time;
		printf("Elapsed Time: %d cycles\n", time);


		mem_addr -= 8192;
		//unsigned int read_mem;
		printf("Reading from memory...\n");
		time = getCycles();
		for (i = 0; i < 8192; i++) {
//			if (!strcmp(input_str,"2"))  {
//				read_arr16[i] = (*mem_addr);
//				if (read_arr16[i] != write_arr16[i])
//					printf("Incorrect value read. Read %i, expected %i\n", read_arr16[i], write_arr16[i]);
//			}	
//			else {
				read_arr[i] = (*mem_addr);
				if (read_arr[i] != write_arr[i])
					printf("Incorrect value read. Read %i, expected %i\n", read_arr[i], write_arr[i]);
//			}	
			mem_addr += 1; 
		}
		time = getCycles() - time;
		printf("Elapsed Time: %d cycles\n", time);

		
	  }
	  else 
	  {
		unsigned int int32;
		int valid = 1;

		
		  printf("Enter a 32 bit hexadecimal integer: ");
		  scanf("%s", input_str);

		  valid = 1;

		    for (i=0; input_str[i] != 0; i++) {
		      if ((input_str[i] >= '0' && input_str[i] <= '9') ||
			  (input_str[i] >= 'A' && input_str[i] <= 'F') ||
			  (input_str[i] >= 'a' && input_str[i] <= 'f')) {
			continue;
		      }
		      else {
			printf("Invalid input.\n");
			valid = 0;
			break;
		      }
		    }
		    if (strlen(input_str) > 9) {
		      printf("Integer is greater than 32 bits\n");
		      valid = 0;
		    }
		    if (valid) {

		      int32 = strtoul(input_str, NULL, 16);
		      (*reg_32) = int32;

		    }

		  
	  }
	  printf("Would you like to quit? (type 'y' to exit)\n");
	  scanf("%s", input_str);

	  if (!strcmp(input_str, "y"))
	  	break;

  }
  return 0;
}

