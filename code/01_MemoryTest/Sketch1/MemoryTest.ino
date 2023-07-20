/************************************************************************/
/* Memory Test for ESP32-S3
/*
/* @brief Performs a memory test and hardware validation for the ESP32-S3 
/*		- Dual 32bit Xtensa LX7 cores running up to 240Mhz
/*		- RISC-V Ultra Low Power Co-processor
/*		- Flash up to 32 MB (Octal), 8 MB PSRAM (Octal)
/*		- Internal 384 KB ROM
/*		- Internal 512 KB SRAM
/*		- Internal 16 KB SRAM in RTC
/*
/* Dependencies
/* Fast, easy LED animation library for Arduino
/* https://github.com/FastLED/FastLED
/*
/* @author Sergio Correia <scorreia@ipportalegre.pt>
/* @version 1.0
/* @date July/2023
/************************************************************************/ 
#include "arduino.h"
#include <FastLED.h>

// RGB LED Definitions
#define NUM_LEDS		1
#define DATA_PIN		38
#define BRIGHTNESS		25

// Serial DEBUG Definitions
#define SerialDEBUG		Serial
#define UART_BAUD		115200

// RGB LED Data Structure
CRGB leds[NUM_LEDS];


/************************************************************************/
/* Initialization Function                                              */
/************************************************************************/
void setup() {

	// RGB LED Initialization	
	FastLED.addLeds<SK6812, DATA_PIN, GRB>(leds, NUM_LEDS);
	FastLED.setBrightness( BRIGHTNESS );

	// Sets the serial channels (DEBUG)
	SerialDEBUG.begin(UART_BAUD); 
	delay(100);

	// Model Information
	SerialDEBUG.println();
	SerialDEBUG.println("==================================================");
	SerialDEBUG.println("*************** ESP32-S3-DevKitC-1 ***************");
	SerialDEBUG.println("************ ESP32-S3-WROOM-2-N16R8V *************");
	SerialDEBUG.println("==================================================");	
	SerialDEBUG.printf("ESP32 Model %s with %dx cores at %dMHz\n",ESP.getChipModel(),ESP.getChipCores(),ESP.getCpuFreqMHz());
	SerialDEBUG.println("Firmware v0.0 (Memory Test)");
	SerialDEBUG.println("==================================================");
	SerialDEBUG.println();
	SerialDEBUG.println();
	
	// Memory Information	
	SerialDEBUG.println("==================================================");
	SerialDEBUG.printf("Flash Memory: %d, at %d MHz \n",ESP.getFlashChipSize(),ESP.getFlashChipSpeed()/1000000);
	SerialDEBUG.println("==================================================");
	SerialDEBUG.printf("PSRAM total size                    : %u \n", esp_spiram_get_size());
	SerialDEBUG.println("--------------------------------------------------");
	SerialDEBUG.printf("PSRAM available size                : %u \n", ESP.getPsramSize());
	SerialDEBUG.printf("PSRAM free size                     : %u \n", ESP.getFreePsram());
	SerialDEBUG.printf("PSRAM maximum allocable size        : %u \n", ESP.getMaxAllocPsram());
	SerialDEBUG.println("==================================================");
	SerialDEBUG.printf("Internal RAM size                   : %u \n", ESP.getHeapSize());
	SerialDEBUG.printf("Internal RAM free                   : %u \n", ESP.getFreeHeap());
	SerialDEBUG.printf("Internal RAM maximum allocable size : %u \n", ESP.getMaxAllocHeap());
	SerialDEBUG.println("==================================================");
	
	
	// PSRAM Memory TEST
	SerialDEBUG.println();
	SerialDEBUG.println("BEFORE PSRAM TEST");
	SerialDEBUG.printf("PSRAM available size          : %u", ESP.getPsramSize());
	SerialDEBUG.printf("\nPSRAM free size               : %u", ESP.getFreePsram());
	SerialDEBUG.printf("\nPSRAM maximum allocable size  : %u", ESP.getMaxAllocPsram());

	uint32_t Sz = 8250000;
	uint8_t* MEMBuffer = (uint8_t*)ps_malloc(Sz*sizeof(uint8_t));
		
	SerialDEBUG.println();
	SerialDEBUG.println();	
	SerialDEBUG.println("AFTER ALLOCATION");
	SerialDEBUG.printf("PSRAM available size          : %u", ESP.getPsramSize());
	SerialDEBUG.printf("\nPSRAM free size               : %u", ESP.getFreePsram());
	SerialDEBUG.printf("\nPSRAM maximum allocable size  : %u", ESP.getMaxAllocPsram());
		
	SerialDEBUG.println();	
	SerialDEBUG.println();
	SerialDEBUG.println("Writing PSRAM ...");	
	
	// PSRAM writing cycle
	uint8_t* B = MEMBuffer;
	bool err = false;
	for (uint32_t i = 1; i<Sz; i++)
	{
		*B = (uint8_t)i;
		B++;
	}
	
	// PSRAM reading cycle
	SerialDEBUG.println("Reading PSRAM ...");
	B = MEMBuffer;
	for (uint32_t i = 1; i<Sz; i++)
	{
		if (*B != (uint8_t)i)
		{
			err = true;
			break;
		}
		B++;
	}	

	SerialDEBUG.print("PSRAM Memory TEST ... ");
	SerialDEBUG.println(err? "ERROR":"OK");

	free(MEMBuffer);
	
	SerialDEBUG.println();
	SerialDEBUG.println("AFTER FREEING MEMORY");
	SerialDEBUG.printf("PSRAM available size          : %u", ESP.getPsramSize());
	SerialDEBUG.printf("\nPSRAM free size               : %u", ESP.getFreePsram());
	SerialDEBUG.printf("\nPSRAM maximum allocable size  : %u", ESP.getMaxAllocPsram());
	
	// Final Information
	SerialDEBUG.println();
	SerialDEBUG.println();	
	SerialDEBUG.println("Memory test finished");
	SerialDEBUG.println();
	SerialDEBUG.println();
	SerialDEBUG.println("RGB LED flashing with 10% brightness ...");
	
}


/************************************************************************/
/* Main Infinite Loop                                                   */
/************************************************************************/
void loop() {

	// LED flashing with RGB colors
	leds[0] = CRGB::Red;					// CRGB(255,0,0)
	FastLED.show();
	delay(1000);
  
	leds[0] = CRGB::Green;				// CRGB(0,255,0)
	FastLED.show();
	delay(1000);
  
	leds[0] = CRGB::Blue;				// CRGB(0,0,255)
	FastLED.show();
	delay(1000); 
  
	leds[0] = CRGB::Black;				// CRGB(0,0,0)
	FastLED.show();
	delay(1000);
	
}
/************************************************************************/