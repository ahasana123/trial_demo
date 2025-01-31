#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
// Define the I2C address for the LCD
#define I2C_ADDR 0x27 // Common address for most modules; use a scanner if unsure
#define LCD_COLUMNS 16
#define LCD_ROWS 2
// Define DHT11 sensor pin
#define DHT_PIN 4
#define DHT_TYPE DHT11
// Initialize the DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);
// Define MQ135 sensor pin
#define MQ135_PIN 25
// Initialize the LCD
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);
void setup() {
  // Initialize the LCD and set up the dimensions
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.init();
  lcd.backlight(); // Turn on the backlight
  // Initialize the DHT sensor
  dht.begin();
  // Display a welcome message
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("WELCOME");
  delay(2000); // Wait for 2 seconds before starting the readings
}
void loop() {
  // Read the temperature and humidity from the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  // Read the MQ135 sensor value
  int mq135Value = analogRead(MQ135_PIN);
  int aqi = map(mq135Value, 0, 1023, 0, 500); // Map the MQ135 value to AQI scale (0-500)
  // Determine air quality description
  String airQualityDescription;
  if (aqi <= 50) {
    airQualityDescription = "Good";
  } else if (aqi <= 100) {
    airQualityDescription = "Moderate";
  } else if (aqi <= 150) {
    airQualityDescription = "Bad";
  } else if (aqi <= 200) {
    airQualityDescription = "V Bad";
  } else if (aqi <= 300) {
    airQualityDescription = "Unhealthy";
  } else {
    airQualityDescription = "Hazardous";
  }
  // Display temperature on the LCD
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C ");
  // Display humidity on the LCD
  lcd.setCursor(0, 1); // Set cursor to column 0, row 1
  lcd.print("Humi: ");
  lcd.print(humidity);
  lcd.print("% ");
  delay(2000); // Wait for 2 seconds before refreshing values
  // Display AQI and description on the LCD
  lcd.clear(); // Clear the LCD for new information
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("AQI: ");
  lcd.print(aqi);
  lcd.setCursor(0, 1); // Set cursor to column 0, row 1
  lcd.print(airQualityDescription);
  delay(2000); // Wait for 2 seconds before starting the next loop
}