#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize the LCD with the pins connected

const int trigPin = 9;  // Trig pin of the ultrasonic sensor
const int echoPin = 10; // Echo pin of the ultrasonic sensor
const int buzzerPin = 6; // Pin connected to the buzzer
const int fanPin = 7;    // Pin connected to the fan
const int ledPin = 8;   // Pin connected to the LED

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.print("Distance:");
  Serial.begin(9600);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distance_cm = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Display distance on LCD
  lcd.setCursor(0, 1); // Set cursor to the second row
  lcd.print("                "); // Clear previous distance value
  lcd.setCursor(0, 1); // Set cursor to the second row
  lcd.print(distance_cm); // Print distance value
  
  // Check if distance is less than threshold
  if (distance_cm < 10) { // Adjust threshold distance here if needed
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(fanPin, HIGH);
    digitalWrite(ledPin, HIGH);
    Serial.println("Obstacle detected!");

      lcd.setCursor(0, 1); // Set cursor to the second row
  lcd.print("                "); // Clear previous distance value
  lcd.setCursor(0, 1); // Set cursor to the second row
  lcd.print("Welcome!!!!!!!!!"); // Print distance value
  
    delay(1000);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(fanPin, LOW);
  }
  
  delay(2000); // Delay between readings
}

