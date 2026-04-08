#include <stdint.h>//adding header files
void delay_ms(uint32_t ms);// declaring the delay_ms variable and passing uint32_t type of value as ms as input
int main(void){
	volatile uint32_t *RCC_APB2ENR = (volatile uint32_t*)0x40021018; //RCC clock APB2 region address binding using pointer variable casting
					*RCC_APB2ENR |= ((1<<2)|(1<<3)); //enabling clock to GPIOA and GPIOB regions bit2 is GPIOA, bit3 is GPIOB
	volatile uint32_t *GPIOA_CRL = (volatile uint32_t*)0x40010800;// Pointer type casting and address binding of GPIOA peripheral CRL register.
	volatile uint32_t *GPIOB_CRL = (volatile uint32_t*)0x40010C00;// Pointer type casting and address binding of GPIOB peripheral CRL register.
	volatile uint32_t *GPIOB_CRH = (volatile uint32_t*)0x40010C04; // Pointer type casting and address binding of GPIOB Peripheral CRL register.
					  *GPIOA_CRL &= ~((0xF<<20)|(0xF<<16)|(0xF<<12)); //Clearing the PA5,PA4, PA3 pins from default input mode.
					  *GPIOA_CRL |= ((0x2<<20)|(0x2<<16)|(0x2<<12)); //Setting the Mode and CNF of pins PA5,PA4, PA3 , MODE : 10 , CNF : 00.
					  *GPIOB_CRL &= ~((0xF<<00)|(0xF<<04)|(0xF<<20)|(0xF<<24)|(0xF<<28)); //Clearing the default input mode of PB0, PB1,PB5,PB6,PB7
					  *GPIOB_CRL |= ((0x2<<00)|(0x2<<04)|(0x2<<20)|(0x2<<24)|(0x2<<28));// Writing Mode and CNF of pins PB0, PB1,PB5,PB6,PB7.
					  *GPIOB_CRH &= ~((0xF<<0)|(0xF<<4)|(0xF<<8)|(0xF<<12)); // Clearing the default input mode of PB8,PB9,PB10,PB11.
					  *GPIOB_CRH |= ((0x2<<0)|(0x2<<4)|(0x2<<8)|(0x2<<12));// Writing Mode and CNF of pins PB8,PB9,PB10,PB11.
	volatile uint32_t *GPIOA_ODR = (volatile uint32_t*)0x4001080C; // Pointer type casting and address binding of GPIOA Peripheral ODR refister.
	volatile uint32_t *GPIOB_ODR = (volatile uint32_t*)0x40010C0C;// Pointer type casting and address binding of GPIOB peripheral ODR register.
	for(;;){
		uint32_t seg[10] = {(1<<0)|(1<<1)|(1<<8)|(1<<5)|(1<<6)|(1<<7), // Declaring an Array for digit patterns.
				(1<<0)|(1<<7),
				(1<<0)|(1<<1)|(1<<9)|(1<<5)|(1<<6),
				(1<<0)|(1<<1)|(1<<9)|(1<<6)|(1<<7),
				(1<<0)|(1<<8)|(1<<9)|(1<<7),
				(1<<1)|(1<<8)|(1<<9)|(1<<6)|(1<<7),
				(1<<1)|(1<<8)|(1<<9)|(1<<5)|(1<<6)|(1<<7),
				(1<<0)|(1<<1)|(1<<7),
				(1<<0)|(1<<1)|(1<<8)|(1<<9)|(1<<5)|(1<<6)|(1<<7),
				(1<<0)|(1<<1)|(1<<8)|(1<<9)|(1<<6)|(1<<7)};
			for(int j=25; j>0; j--){ //Outer for loop to run the running the loop for 25 times.
				int a = j / 10;  //Quotient division to display tens digits.
				int b = j % 10; // Reminder division to display Unit numbers.
				for(int o = 0; o<60; o++){ // Inner for loop to run the loop for 60 secs.
				for(int k=0; k<500; k++){ // Innermost loop to run this loop for 500 times.
										*GPIOB_ODR = seg[a]|(1<<11); //1ms for display 1.
										delay_ms(1);
										*GPIOB_ODR = seg[b]|(1<<10); //1ms for display 2.   //Actually the 2 displays take 2ms.
										delay_ms(1); //so if we run this loop for 500 time then 2ms x500 = 1000ms
					if(k<250){ //if loop for blinking LED for first 250 iterations that means for 500ms and stopijng for next 250 iterations.
							*GPIOA_ODR |= (1<<5); // Writing PA5 PIN HIGH Using ODR register to glow the LED.
							}else{
							*GPIOA_ODR &= ~(1<<5); // Clearing PA5 PIN Using ODR Register to off the LED.
							}

				}}
			}
			*GPIOA_ODR |=(1<<3); // Writing PA3 PIN HIGH to ring the BUzzer.
			delay_ms(500); // delay to ring the buzzer for half sec.
			*GPIOA_ODR &= ~(1<<3); // Clearing the PIN PA3 to stop the Buzzer.
			for(int i=5; i>0; i--){ // Outer for Loop to run the timer for 5 Mins.
				*GPIOB_ODR = seg[i]|(1<<10); // Writing thr ODR Register to display Break time Except PB10 pin that means it is OFF.
				for(int j=0; j<60; j++){// Inner loop to Flow RED with 500ms Delay time.
					*GPIOA_ODR |= (1<<4); //Making PA4 high to glow the RED LED.
					delay_ms(500);
					*GPIOA_ODR &= ~(1<<4); //Clearing PA4 to turn off the RED LED.
					delay_ms(500);
			}	}
			*GPIOA_ODR |=(1<<3); // Writing PA3 PIN HIGH to ring the BUzzer.
						delay_ms(500);
						*GPIOA_ODR &= ~(1<<3);// Clearing the PIN PA3 to stop the Buzzer.
	}
	}


	void delay_ms(uint32_t ms){
	    volatile uint32_t *SYST_CSR = (volatile uint32_t*)0xE000E010;// Pointer type Casting and address binding of CSR
	    volatile uint32_t *SYST_RVR = (volatile uint32_t*)0xE000E014;// Pointer type Casting and address binding of RVR
	    volatile uint32_t *SYST_CVR = (volatile uint32_t*)0xE000E018;// Pointer type Casting and address binding of CVR

	    *SYST_RVR = 8000-1; //SEtting the Countdown. 7999 time is equal to 1ms so we that 1ms and multiply it for our requied timing.
	    *SYST_CVR = 0; //Setting current Count fresh start , It checks and updates the current count value 7999 7998 7997.
	    *SYST_CSR = 5; //The CSR regsiter has 0 bit is for Enabling it is ON/OFF switch 1 for TImer start, 0 for Tier Stop.
	    				// Bit 1 to check interrupt 1 for Interrupt generate and 0 for NO interrupt.
	    				// Bit 2 is to select CPU clock or External Clock 1 for CPU clock and 0 for external Clock.
	    				// Bit 16 is for Countflag 0 is say that the count still running and 1 means the count reached to 0.
	    for(uint32_t i=0; i<ms; i++){
	        while(!(*SYST_CSR & (1<<16))); // for every microsecond it checks the countflag if it used NOT operator it means if 16th bit is 1 not operator changes it to 0 that menas count completed
	    }									// if the 16th bit of CSR register is 0 NOT operator changes it to 1 that means the condition is true still need to count.
	}


