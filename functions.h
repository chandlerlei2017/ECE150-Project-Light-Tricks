#include <unistd.h>
#include <ugpio/ugpio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <stdio.h>
//turns the lights on 

//checks if a string is a number
int isNum(char* check){
	int index = 0;	
	int isaNum = 1;
	while(check[index] != 0){
		if (!isdigit(check[index]) && check[index] != '-' && check[index] != '+'){
			isaNum = 0;
		}
	index++;
	}
	return isaNum;
}
int on(int gpio){
	FILE * fp = fopen("Log.txt","a");	
	//turns on all the lights
	if(gpio == 4){
		if(gpio_direction_output(0,1) < 0){
			return 0;
		}	
		if(gpio_direction_output(1,1) < 0){
			return 0;
		}
		if(gpio_direction_output(2,1) < 0){
			return 0;
		}
		if(gpio_direction_output(3,1) < 0){
			return 0;
		}
		fprintf(fp, "Turned all LED lights on\n");

	}
	//turns on select lights
	else if (gpio >= 0 && gpio <=3){
		if(gpio_direction_output(gpio,1) < 0){
			return 0;
		}
		fprintf(fp, "Turned LED light at gpio %d on\n",gpio);
	}
	else{
		perror("Invalid gpio");
		fprintf(fp, "Could not turn LED light(s) on \n");
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}
//turns the lights off
int off(int gpio){
	FILE * fp = fopen("Log.txt","a");
	//turns off all the lights
	if(gpio == 4){
		if(gpio_direction_output(0,0) < 0){
			return 0;
		}	
		if(gpio_direction_output(1,0) < 0){
			return 0;
		}
		if(gpio_direction_output(2,0) < 0){
			return 0;
		}
		if(gpio_direction_output(3,0) < 0){
			return 0;
		}
		fprintf(fp, "Turned all LED lights off\n");
	}
	//turns off select lights
	else if (gpio >= 0 && gpio <= 3){
		if(gpio_direction_output(gpio,0) < 0){
			return 0;
		}
		fprintf(fp, "Turned LED light at gpio %d off\n",gpio);
	}
	else{
		perror("Invalid gpio");
		fprintf(fp, "Could not turn LED light(s) off \n");
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}

//blinks the light
int blink(int gpio, int num, unsigned int time){
	//blink all if 4 is inputted 
	FILE * fp = fopen("Log.txt","a");
	if(gpio == 4){
		for (int i = 0; i < num; i++){
			//direction of 1 means produce current, 0 means to stop current
			if(gpio_direction_output(0,1) < 0){
				return 0;
			}	
			if(gpio_direction_output(1,1) < 0){
				return 0;
			}
			if(gpio_direction_output(2,1) < 0){
				return 0;
			}
			if(gpio_direction_output(3,1) < 0){
				return 0;
			}
			//delays for half second to simulate blinks
			usleep(time);
			if(gpio_direction_output(0,0) < 0){
				return 0;
			}
			if(gpio_direction_output(1,0) < 0){
				return 0;
			}
			if(gpio_direction_output(2,0) < 0){
				return 0;
			}
			if(gpio_direction_output(3,0) < 0){
				return 0;
			}
			usleep(time);
		}
		fprintf(fp, "Blinked all LED lights %d times at %d microseconds per blink\n",num,time);
		
	}
	//blinks selected gpio
	else if(gpio >= 0 && gpio <= 3){
		for (int i = 0; i < num; i++){
			if(gpio_direction_output(gpio,1) < 0){
				return 0;
			}
			usleep(time);
			if(gpio_direction_output(gpio,0) < 0){
				return 0;
			}
			usleep(time);
		}
		fprintf(fp, "Blinked LED light at gpio %d %d times at %d seconds per blink\n",gpio,num,time);
	}
	else {
		fprintf(fp, "Could not Blink LED Light(s)\n");
		perror("Invalid gpio");
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}
int morseblink(int gpio, int num, unsigned int time){
	//blink all if 4 is inputted 
	if(gpio == 4){
		for (int i = 0; i < num; i++){
			//direction of 1 means produce current, 0 means to stop current
			if(gpio_direction_output(0,1) < 0){
				return 0;
			}	
			if(gpio_direction_output(1,1) < 0){
				return 0;
			}
			if(gpio_direction_output(2,1) < 0){
				return 0;
			}
			if(gpio_direction_output(3,1) < 0){
				return 0;
			}
			//delays for half second to simulate blinks
			usleep(time);
			if(gpio_direction_output(0,0) < 0){
				return 0;
			}
			if(gpio_direction_output(1,0) < 0){
				return 0;
			}
			if(gpio_direction_output(2,0) < 0){
				return 0;
			}
			if(gpio_direction_output(3,0) < 0){
				return 0;
			}
		}
	}
	//blinks selected gpio
	else if(gpio >= 0 && gpio <= 3){
		for (int i = 0; i < num; i++){
			if(gpio_direction_output(gpio,1) < 0){
				return 0;
			}
			usleep(time);
			if(gpio_direction_output(gpio,0) < 0){
				return 0;
			}
		}
	}
	else {
		perror("Invalid gpio");
		return 0;
	}
	return 1;
}
//adds two numbers and displays them using the LEDS
int add(int num1,int num2){
	FILE * fp = fopen("Log.txt","a");
	int sum = num1 + num2;
	int temp = sum;
	int temp2 = sum;
	int count = 0;	
	//store the individual digits of sum in an array
	while(temp != 0){
		temp /= 10;
		count++;
	}
	int nums[count];
	for (int i = count-1; i > -1; i--){
		nums[i] = temp2 % 10;
		temp2 /= 10; 	
	}
	//first light blinks once if positive, twice if negative
	if (sum == 0){
		return 1;
	}	
	else if (sum > 0){
		if (blink(0,1,500000) == 0){
			perror("Could not blink");
			return 0;
		}
	}
	else if (sum < 0){
		if (blink(0,2,500000) == 0){
			perror("Could not blink");
			return 0;
		}
	}
	usleep(50000);
	//blink the lights based on individual digits
	for (int i = 0; i < count; i++){
		if (blink((i+1) % 4, abs(nums[i]),500000) == 0){
			perror("Could not blink");
			return 0;
		}
		usleep(50000);
	}
	int index = count-1;
	while (nums[index] == 0){
		if (blink(4,1,500000) == 0){
			perror("Could not blink");
			return 0;
		}
		index--;
	}

	fprintf(fp, "Added %d and %d: got %d\n",num1,num2,sum);
	fclose(fp);
	return 1;
	
}
//Subtracts two numbers and displays them using the LEDS
int subtract(int num1,int num2){
	FILE * fp = fopen("Log.txt","a");
	int diff = num1 - num2;
	int temp = diff;
	int temp2 = diff;
	int count = 0;	
	//stores the individual digits of the difference in an array
	while(temp != 0){
		temp /= 10;
		count++;
	}
	int nums[count];
	for (int i = count-1; i> -1; i--){
		nums[i] = temp2 % 10;
		temp2 /= 10; 	
	}
	//first light blinks once if positive, twice if negative
	if (diff == 0){
		return 1;
	}	
	else if (diff > 0){
		if (blink(0,1,500000) == 0){
			perror("Could not blink");
			return 0;
		}
	}
	else if (diff < 0){
		if (blink(0,2,500000) == 0){
			perror("Could not blink");
			return 0;
		}
	}
	usleep(500000);
	//blink the lights based on the digits
	for (int i = 0; i < count; i++){
		if (blink((i+1) % 4, abs(nums[i]),500000) == 0){
			perror("Could not blink");
			return 0;
		}
		usleep(500000);
	}
	int index = count-1;
	while (nums[index] == 0){
		if (blink(4,1,500000) == 0){
			perror("Could not blink");
			return 0;
		}
		index--;
	}
	fprintf(fp, "Subtracted %d from %d: got %d\n",num2,num1,diff);
	fclose(fp);
	return 1;
	
}
//Multiply two numbers and displays them using the LEDS
int multiply(int num1,int num2){
	FILE * fp = fopen("Log.txt","a");
	int product = num1*num2;
	int temp = product;
	int temp2 = product;
	int count = 0;	
	//stores the individual digits of the difference in an array
	while(temp != 0){
		temp /= 10;
		count++;
	}
	int nums[count];
	for (int i = count-1; i > -1; i--){
		nums[i] = temp2 % 10;
		temp2 /= 10; 	
	}
	//first light blinks once if positive, twice if negative
	if (product == 0){
		return 1;
	}	
	else if (product > 0){
		if (blink(0,1,500000) == 0){
			perror("Could not blink");
			return 0;
		}
	}
	else if (product < 0){
		if (blink(0,2,500000) == 0){
			perror("Could not blink");
			return 0;
		}
	}
	usleep(500000);
	//blink the lights based on the digits
	for (int i = 0; i < count; i++){
		if (blink((i+1) % 4, abs(nums[i]),500000) == 0){
			perror("Could not blink");
			return 0;
		}
		usleep(500000);
	}
	int index = count-1;
	while (nums[index] == 0){
		if (blink(4,1,500000) == 0){
			perror("Could not blink");
			return 0;
		}
		index--;
	}
	fprintf(fp, "Multiplied %d and %d: got %d\n",num1,num2,product);
	fclose(fp);
	return 1;
	
}
//Divide two numbers and displays them using the LEDS
int divide(int num1,int num2){
	FILE * fp = fopen("Log.txt","a");
	if(!num2){
		perror("Cannot divide by zero");
		fprintf(fp, "Could not divide: x/0\n");
		fclose(fp);
		return 0;	
	}
	int quotient = num1/num2;
	int temp = quotient;
	int temp2 = quotient;
	int count = 0;	
	//stores the individual digits of the difference in an array
	while(temp != 0){
		temp /= 10;
		count++;
	}
	int nums[count];
	for (int i = count-1; i > -1; i--){
		nums[i] = temp2 % 10;
		temp2 /= 10; 	
	}
	//first light blinks once if positive, twice if negative
	if (quotient == 0){
		return 1;
	}
	else if (quotient > 0){
		if (blink(0,1,500000) == 0){
			perror("Could not blink");
			return 0;
		}
	}
	else if (quotient < 0){
		if (blink(0,2,500000) == 0){
			perror("Could not blink");
			return 0;
		}
	}
	usleep(500000);
	//blink the lights based on the digits
	for (int i = 0; i < count; i++){
		if (blink((i+1) % 4, abs(nums[i]),500000) == 0){
			perror("Could not blink");
			return 0;
		}
		usleep(500000);
	}
	int index = count-1;
	while (nums[index] == 0){
		if (blink(4,1,500000) == 0){
			perror("Could not blink");
			return 0;
		}
		index--;
	}
	fprintf(fp, "Divided %d from %d: got %d\n",num2,num1,quotient);
	fclose(fp);
	return 1;
	
}

//Gets character input and displays onto the LED lights 
//Each character has a specific pattern of dashes and dots 
int morse(int gpio, char* sentence){
	FILE * fp = fopen("Log.txt","a");
	if(gpio > 4 || gpio < 0){
		fprintf(fp, "Invalid gpio value given\n");
		fclose(fp);
		perror("Invalid gpio");
		return 0;
	}
	int count = 0;
	unsigned int time = 500000;
	while(sentence[count]!= 0){
		switch(sentence[count]){
			case 'a':
			case 'A':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'b':
			case 'B':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'c':
			case 'C':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'd':
			case 'D':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'e':
			case 'E':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'f':
			case 'F':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'g':
			case 'G':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'h':
			case 'H':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'i':
			case 'I':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'j':
			case 'J':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'k':
			case 'K':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'l':
			case 'L':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'm':
			case 'M':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'n':
			case 'N':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'o':
			case 'O':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);	
				break;			
			case 'p':
			case 'P':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'q':
			case 'Q':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'r':
			case 'R':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 's':
			case 'S':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 't':
			case 'T':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'u':
			case 'U':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'v':
			case 'V':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'w':
			case 'W':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'x':
			case 'X':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case 'y':
			case 'Y':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
		
			case 'z':
			case 'Z':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case ' ':
				usleep(4*time);
				break;
			case '1':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case '2':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case '3':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;	
			case '4':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case '5':
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case '6':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case '7':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case '8':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case '9':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			case '0':
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(time);
				if (morseblink(gpio,1,3*time) == 0){
					perror("Could not morseblink");
				}
				usleep(3*time);
				break;
			default:
				perror("Character not valid for morse code.");
				return 0;
		}
		count++;
	}
	fprintf(fp, "Converted '%s' to morse\n",sentence);
	fclose(fp);
	return 1;
}



















