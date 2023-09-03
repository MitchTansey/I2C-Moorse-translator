#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_timer.h"

#include "driver/adc.h"
#include "esp_system.h"

#define BUTTON_GPIO 0

static void button_task(void *arg){

    int counter = 0;

    int last_state = 1;
    while(1){
	int button_state = gpio_get_level(BUTTON_GPIO);
	if(!button_state && last_state == 1){
	    ++counter;
	}
	last_state = button_state;
	printf("Button state: %d counter: %d\n", button_state, counter);
	vTaskDelay(pdMS_TO_TICKS(100));
    }
}

static void init_gpio(){
	gpio_config_t button_config = {
	    .pin_bit_mask = 1ULL << BUTTON_GPIO,
	    .mode = GPIO_MODE_INPUT,
	    .pull_up_en = GPIO_PULLUP_ENABLE,
	    .intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&button_config);
}

#define ADC_CHANNEL ADC_CHANNEL_0

static int l_counter = 0;
static int i_counter = 0;
static char output[100] = "";

 
#include <stdio.h>
#include <string.h>

// Function to convert a single Morse code letter to English
char* morseLetterToEnglish(const char* morseLetter) {
    // Define the Morse code alphabet
    const char* morseAlphabet[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                                    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                                    "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--",
                                    "....-", ".....", "-....", "--...", "---..", "----.", "-----",
                                    ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.",
                                    "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-",
                                    ".-..-.", "...-..-", ".--.-.", ".-.-"};

    // Define the English alphabet and special characters
    const char* englishAlphabet[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                                      "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                                      "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                                      ".", ",", "?", "'", "!", " ", "(", ")", "&", ":",
                                      ";", "=", "+", "-", "_", "\"", "$", "@", " " };

    // Search for the Morse code letter in the Morse alphabet
    int i;
    for (i = 0; i < 54; i++) {
        if (strcmp(morseLetter, morseAlphabet[i]) == 0) {
            //printf("%s", englishAlphabet[i]);
            return englishAlphabet[i];
        }
    }
    
    // If the Morse code letter is not found, print an error message
    //printf("[ERROR]");
    return "";
}

void app_main(void){
    printf("start\n");
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

    while(1){
	int avg = 0;
	for(int j = 0; j < 50; j++){
	    avg += adc1_get_raw(ADC_CHANNEL);
	}
	
	int val = avg / 50;

	if(val >= 30){
	    l_counter++;
	    if(l_counter >= 1){
                i_counter = 0;
            }
	} else{
	    if(l_counter >= 2){
		//printf("DASH\n");
		strcat(output, "-");
	    } else if(l_counter >= 1){
		strcat(output, ".");
		//printf("DOT\n");
	    }
	    l_counter = 0;
	}
	if(val < 30){
	    i_counter++;
	}
	if(i_counter >= 6){
	    //printf("ahk");
	    printf(morseLetterToEnglish(output));
	    printf("\n");

	    i_counter = 0;
	    memset(output, 0, sizeof(output));
	}
	
	

//	printf("raw: %d l_counter: %d i_counter: %d\n", val, l_counter, i_counter);

	vTaskDelay(pdMS_TO_TICKS(10));
    }
}

//    init_gpio();

//    xTaskCreate(button_task, "button_task", 2048, NULL, tskIDLE_PRIORITY, NULL);
//}

