#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include <ugpio/ugpio.h>
#include "functions.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv, char **envp)
{
	int i;
	int rq0;
	int rq1;
	int rq2;
	int rq3;
	int rq4;
	int rv;
	int value;
	int end = 0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
		
	
	// check if gpio 0  is already exported
	if ((rq0 = gpio_is_requested(0)) < 0)
	{
		perror("gpio_is_requested");
		return EXIT_FAILURE;
	}
	// export the gpio
	if (!rq0) {
		printf("> exporting gpio\n");
		if ((rv = gpio_request(0, NULL)) < 0)
		{
			perror("gpio_request");
			return EXIT_FAILURE;
		}
	}

	// check if gpio 1  is already exported
	if ((rq1 = gpio_is_requested(1)) < 0)
	{
		perror("gpio_is_requested");
		return EXIT_FAILURE;
	}
	// export the gpio
	if (!rq1) {
		printf("> exporting gpio\n");
		if ((rv = gpio_request(1, NULL)) < 0)
		{
			perror("gpio_request");
			return EXIT_FAILURE;
		}
	}

	// check if gpio 2  is already exported
	if ((rq2 = gpio_is_requested(2)) < 0)
	{
		perror("gpio_is_requested");
		return EXIT_FAILURE;
	}
	// export the gpio
	if (!rq2) {
		printf("> exporting gpio\n");
		if ((rv = gpio_request(2, NULL)) < 0)
		{
			perror("gpio_request");
			return EXIT_FAILURE;
		}
	}

	// check if gpio 3  is already exported
	if ((rq3 = gpio_is_requested(3)) < 0)
	{
		perror("gpio_is_requested");
		return EXIT_FAILURE;
	}

	// export the gpio
	if (!rq3) {
		printf("> exporting gpio\n");
		if ((rv = gpio_request(3, NULL)) < 0)
		{
			perror("gpio_request");
			return EXIT_FAILURE;
		}
	}
	
	//Startup Pattern
	for (int i = 0; i < 10; i++){
		if(gpio_direction_output(0,1) < 0){
			return 0;
		}
		if(gpio_direction_output(3,0) < 0){
			return 0;
		}
		usleep(100000);
		if(gpio_direction_output(1,1) < 0){
			return 0;
		}
		if(gpio_direction_output(0,0) < 0){
			return 0;
		}
		usleep(100000);
		if(gpio_direction_output(2,1) < 0){
			return 0;
		}
		if(gpio_direction_output(1,0) < 0){
			return 0;
		}
		usleep(100000);
		if(gpio_direction_output(3,1) < 0){
			return 0;
		}
		if(gpio_direction_output(2,0) < 0){
			return 0;
		}
		usleep(100000);
	}
	if(gpio_direction_output(2,0) < 0){
		return 0;
	}
	if(gpio_direction_output(3,0) < 0){
		return 0;
	}
	FILE *fp = fopen("Log.txt","a");
	fprintf(fp, "%d/%d/%d %d:%d\n", tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	fprintf(fp, "\n");
	fclose(fp);
	
	

	printf("Welcome to Light Tricks\n");
	printf("Available Functions:\n");
	printf("	on: on gpio\n");
	printf("	off: off gpio\n");
	printf("	blink: gpio numBlinks timePerBlink\n");
	printf("	add: add num1 num2\n");
	printf("	subtract: subtract num1 num2\n");
	printf("	multiply: multiply num1 num2\n");
	printf("	divide: divide num1 num2\n");
	printf("	morse: gpio sentence\n");
	printf("\n");
	printf("To us all GPIO enter 4 or 'all' as gpio value\n");
	printf("Arithmetic operations require integer input and will output integer results\n");
	printf("Any input without a space will terminate the program\n");
	//keeps looping
	while (!end)
	{
		char input[64];
		char command[10];
		char* space = NULL;
		char test = 32;

		char All[] = "all";
		char On[] = "on";
		char Off[] = "off";
		char Blink[] = "blink";
		char Add[] = "add";
		char Subtract[] = "subtract";
		char Multiply[] = "multiply";
		char Divide[] = "divide";
		char Morse[] = "morse";

		//gets user input for action of the LEDS 
		fgets(input, 64, stdin);
		input[strlen(input)-1] = 0;
		int spaceNum = 0;
		int counter = 0;
		while(input[counter] != 0){
			if (input[counter] == ' '){
				spaceNum++;
			}
		counter++;
		}
		space = strchr(input, test);


		//ends loop on any input without space
		if(space){
			memcpy(command,input,space-input);
			command[space-input] = 0;
			//turns selected gpio on
			if (strcmp(command,On) == 0 && spaceNum == 1){
				char gpio[10];				
				char* endLine;
				endLine = strchr(input,0);
				
				memcpy(gpio,&input[space-input+1],endLine-space-1);
				gpio[endLine-space-1] = 0;
				if(strcmp(gpio,All) == 0){
					if (on(4) == 0){
						perror("Unable to turn on");
					}
				}
				else if(!isNum(gpio)){
					perror("gpio input is not a number.");
				}
				else{
					int param = atoi(gpio);
					if (on(param) == 0){
						perror("Unable to turn on");
					}
				}
			}
			//turns selected gpio off
			else if (strcmp(command,Off) == 0 && spaceNum == 1){
				char gpio[10];				
				char* endLine;
				endLine = strchr(input,0);

				memcpy(gpio,&input[space-input+1],endLine-space-1);
				gpio[endLine-space-1] = 0;
				if(strcmp(gpio,All) == 0){
					if (off(4) == 0){
						perror("Unable to turn off");
					}
				}
				else if (!isNum(gpio)){
					perror("gpio input is not a number.");
				}
				else{
					int param = atoi(gpio);
					if(off(param) == 0){
						perror("Unable to turn off");
					}
				}
			}
			//blinks selected gpio selected amount of times
			else if(strcmp(command,Blink) == 0 && spaceNum == 3){
				//gets the gpio number, number of blinks, and time of each blink, converts to int and blinks
				char gpio[10];
				char num[10];
				char time[10];
				char* space2;
				space2 = strchr(&input[space-input+1],test);
				char* space3;
				space3 = strchr(&input[space2-input+1],test);
				char* endLine;
				endLine = strchr(input,0);

				memcpy(gpio,&input[space-input+1],space2-space-1);
				gpio[space2-space-1] = 0;

				memcpy(num,&input[space2-input+1],space3-space2-1);
				num[space3-space2-1] = 0;
				
				memcpy(time,&input[space3-input+1],endLine-space3-1);
				num[endLine-space3-1] = 0;

				if (!isNum(num)){
					perror("number input is not a number");
				}
				else{
					int param2 = atoi(num);
					float Time = atof(time)*1000000;
					unsigned int param3 = Time;
				
					if(strcmp(gpio,All) == 0){
						if (blink(4,param2,param3) == 0){
							perror("Unable to blink");
						}
					}
					else if (!isNum(gpio)){
						perror("gpio input is not a number");
					}
					else{
						int param1 = atoi(gpio);
						if(blink(param1,param2,param3) == 0){
							perror("Unable to blink");
						}
					}
				}
			}
			//adds two numbers and display them on the LED'S
			else if (strcmp(command,Add) == 0 && spaceNum == 2){
				//finds the two numbers, get substrings, convert to inegers and add
				char num1[10];
				char num2[10];
				char* space2;
				space2 = strchr(&input[space-input+1],test);
				char* endLine;
				endLine = strchr(input,0);

				memcpy(num1,&input[space-input+1],space2-space-1);
				num1[space2-space-1] = 0;

				memcpy(num2,&input[space2-input+1],endLine-space2-1);
				num2[endLine-space2-1] = 0;
				
				if(!isNum(num1) || !isNum(num2)){
					perror("number input is not a number");
				}
				else{
					int param1 = atoi(num1);
					int param2 = atoi(num2);
					if(add(param1,param2) == 0){
						perror("Unable to add");
					}
				}
			}
			//subtract two numbers and display them on the LED's
			else if (strcmp(command,Subtract) == 0 && spaceNum == 2){
				//finds the two numbers, get substrings, convert to inegers and subtract
				char num1[10];
				char num2[10];
				char* space2;
				space2 = strchr(&input[space-input+1],test);
				char* endLine;
				endLine = strchr(input,0);

				memcpy(num1,&input[space-input+1],space2-space-1);
				num1[space2-space-1] = 0;

				memcpy(num2,&input[space2-input+1],endLine-space2-1);
				num2[endLine-space2-1] = 0;
				
				if (!isNum(num1) || !isNum(num2)){
					perror("number input is not a number");
				}
				else{
					int param1 = atoi(num1);
					int param2 = atoi(num2);
					if(subtract(param1,param2) == 0){
						perror("Unable to subtract");
					}
				}
			}
			//multiply two numbers and display them on the LED's
			else if (strcmp(command,Multiply) == 0 && spaceNum == 2){
				//finds the two numbers, get substrings, convert to inegers and multiply
				char num1[10];
				char num2[10];
				char* space2;
				space2 = strchr(&input[space-input+1],test);
				char* endLine;
				endLine = strchr(input,0);

				memcpy(num1,&input[space-input+1],space2-space-1);
				num1[space2-space-1] = 0;

				memcpy(num2,&input[space2-input+1],endLine-space2-1);
				num2[endLine-space2-1] = 0;
				
				if (!isNum(num1) || !isNum(num2)){
					perror("number input is not a number");
				}
				else{
					int param1 = atoi(num1);
					int param2 = atoi(num2);
					if(multiply(param1,param2) == 0){
						perror("Unable to multiply");
					}
				}
			}	
			//multiply two numbers and display them on the LED's
			else if (strcmp(command,Divide) == 0 && spaceNum == 2){
				//finds the two numbers, get substrings, convert to integers and divide
				char num1[10];
				char num2[10];
				char* space2;
				space2 = strchr(&input[space-input+1],test);
				char* endLine;
				endLine = strchr(input,0);

				memcpy(num1,&input[space-input+1],space2-space-1);
				num1[space2-space-1] = 0;

				memcpy(num2,&input[space2-input+1],endLine-space2-1);
				num2[endLine-space2-1] = 0;
				
				if(!isNum(num1) || !isNum(num2)){
					perror("number input is not a number");
				}
				else{
					int param1 = atoi(num1);
					int param2 = atoi(num2);
					if(divide(param1,param2) == 0){
						perror("Unable to divide");
					}
				}
			}
			//Display morse code on the LED's
			else if(strcmp(command,Morse) == 0 && spaceNum >= 2){
				//gets the gpio number and sentence to convert to morse
				char gpio[10];
				char sentence[64];
				char* space2;
				space2 = strchr(&input[space-input+1],test);
				char* endLine;
				endLine = strchr(input,0);

				memcpy(gpio,&input[space-input+1],space2-space-1);
				gpio[space2-space-1] = 0;

				memcpy(sentence,&input[space2-input+1],endLine-space2-1);
				sentence[endLine-space2-1] = 0;
				
				if(strcmp(gpio,All) == 0){
					if (morse(4,sentence) == 0){
						perror("Unable convert to morse");
					}
				}
				else if (!isNum(gpio)){
					perror("gpio input is not a number");
				}
				else{
					int param1 = atoi(gpio);
					if(morse(param1,sentence) == 0){
						perror("Unable to convert to morse");
					}
				}
			}
			else if(spaceNum > 0){
				perror("Invalid Input, follow function declaration rules");
			}
		}
		//end loop if any user input without space is detected
		else{
			end = 1;
		}

	}

	for (int i = 0; i < 5; i++){
		if(gpio_direction_output(0,1) < 0){
			return 0;
		}
		if(gpio_direction_output(1,0) < 0){
			return 0;
		}
		usleep(100000);
		if(gpio_direction_output(1,1) < 0){
			return 0;
		}
		if(gpio_direction_output(0,0) < 0){
			return 0;
		}
		usleep(100000);
		if(gpio_direction_output(2,1) < 0){
			return 0;
		}
		if(gpio_direction_output(1,0) < 0){
			return 0;
		}
		usleep(100000);
		if(gpio_direction_output(3,1) < 0){
			return 0;
		}
		if(gpio_direction_output(2,0) < 0){
			return 0;
		}
		usleep(100000);
		if(gpio_direction_output(2,1) < 0){
			return 0;
		}
		if(gpio_direction_output(3,0) < 0){
			return 0;
		}
		usleep(100000);
		if(gpio_direction_output(1,1) < 0){
			return 0;
		}
		if(gpio_direction_output(2,0) < 0){
			return 0;
		}
		usleep(100000);

	}
	if(gpio_direction_output(0,1) < 0){
		return 0;
	}
	if(gpio_direction_output(1,0) < 0){
		return 0;
	}
	usleep(100000);
	if(gpio_direction_output(0,0) < 0){
		return 0;
	}
	
	// unexport gpios 
	

	if (!rq0) {
		printf("> unexporting gpio\n");
		if (gpio_free(0) < 0)
		{
			perror("gpio_free");
		}
	}
	if (!rq1) {
		printf("> unexporting gpio\n");
		if (gpio_free(1) < 0)
		{
			perror("gpio_free");
		}
	}
	if (!rq2) {
		printf("> unexporting gpio\n");
		if (gpio_free(2) < 0)
		{
			perror("gpio_free");
		}
	}
	if (!rq3) {
		printf("> unexporting gpio\n");
		if (gpio_free(3) < 0)
		{
			perror("gpio_free");
		}
	}
        
	return 0;
}


