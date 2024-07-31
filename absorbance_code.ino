#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <math.h>

// OLED display configuration
#define i2c_Address 0x3C 
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1   

// Create display object
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

float Vout_ref = 0;  // Variable to store reference voltage (without sample)
bool referenceSet = false;  // Flag to check if reference voltage is set

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  display.begin(i2c_Address, true);  // Initialize the display
  display.display();  // Display initial buffer (Adafruit splash screen)
  display.clearDisplay();  // Clear the display buffer
  delay(1000);  // Wait for a second
  
  Serial.println("Place cuvette without solution to set reference.");  // Prompt user to set reference voltage
}

void loop() {
  // Read the current voltage output from the photodiode (A1 pin)
  float Vout = (analogRead(A1) * 5.0) / 1023.0;

  // Check if reference voltage is set
  if (!referenceSet) {
    Serial.print("Setting reference voltage... ");
    Vout_ref = Vout;  // Set the reference voltage
    Serial.print("Reference Vout: ");
    Serial.println(Vout_ref, 3);  // Print the reference voltage
    referenceSet = true;
    delay(1000);  // Wait for a second
  } 

  // Calculate transmittance T
  float T = Vout / Vout_ref;

  // Calculate absorbance A using Beer-Lambert law
  float Absorbance = -log10(T);
  if (Absorbance < 0) {
    Absorbance = 0;  // Set to 0 if absorbance is negative
  }
  
  // Print values to the serial monitor
  Serial.print("Vout: ");
  Serial.println(Vout, 3);  // Print voltage with 3 decimal places
  Serial.print("Absorbance: ");
  Serial.println(Absorbance, 3);  // Print absorbance with 3 decimal places
  Serial.print("Reference Vout: ");
  Serial.println(Vout_ref, 3);  // Print the reference voltage

  // Display values on the OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 10);
  display.print("Vo: ");
  display.print(Vout, 3);
  display.setCursor(0, 35);
  display.print("Abs: ");
  display.print(Absorbance, 3);
  display.display();  // Update the display with new values

  delay(1000);  // Wait for a second before next reading
}
