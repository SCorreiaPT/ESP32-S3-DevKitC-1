// Dependencies
// Fast, easy LED animation library for Arduino
// https://github.com/FastLED/FastLED


#include "arduino.h"
#include <FastLED.h>

// RGB LED Definitions
#define NUM_LEDS 1
#define DATA_PIN 38

// Serial DEBUG Definitions
#define SerialDEBUG		Serial
#define UART_BAUD		115200

// RGB LED Data Structure
CRGB leds[NUM_LEDS];



/************************************************************************/
/* Initialization Function                                                                     */
/************************************************************************/
void setup() {
	
	FastLED.addLeds<SK6812, DATA_PIN, GRB>(leds, NUM_LEDS);
	  
	// Sets the serial channels (DEBUG and GSM modem communications)
	SerialDEBUG.begin(UART_BAUD); 
	delay(100);

	// Model Information
	SerialDEBUG.println();
	SerialDEBUG.println("==================================================");
	SerialDEBUG.println("*************** ESP32-S3-DevKitC-1 ***************");
	SerialDEBUG.println("************ ESP32-S3-WROOM-2-N16R8V *************");
	SerialDEBUG.println("==================================================");	
	SerialDEBUG.printf("ESP32 Model %s with %dx cores at %dMHz\n",ESP.getChipModel(),ESP.getChipCores(),ESP.getCpuFreqMHz());
	SerialDEBUG.println("Firmware v0.0");
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
	uint8_t* B = MEMBuffer;
	bool err = false;
	for (uint32_t i = 1; i<Sz; i++)
	{
		*B = (uint8_t)i;
		B++;
	}
	
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
	SerialDEBUG.println("RGB LED flashing ...");
	
}


/************************************************************************/
/* Main Infinite Loop                                                                     */
/************************************************************************/
void loop() {

  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
	
}
/************************************************************************/