const int moistureSensorPin = A0;
const int relayPin = 2;
const int pumpDuration = 10000; // 10 seconds (in milliseconds)

int moistureLevel = 0;
int threshold = 600; // Adjust this threshold based on your soil moisture level readings
unsigned long lastWateringTime = 0;

void setup() {
  pinMode(moistureSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure relay is off initially

  Serial.begin(9600);
}

void loop() {
  moistureLevel = analogRead(moistureSensorPin);
  Serial.print("Moisture Level: ");
  Serial.println(moistureLevel);

  // Check if it's time to water or if the moisture level is below the threshold
  if (needsWatering() || moistureLevel < threshold) {
    digitalWrite(relayPin, HIGH); // Activate relay
    Serial.println("Watering...");
    delay(pumpDuration); // Wait for the pump duration
    digitalWrite(relayPin, LOW); // Deactivate relay
    Serial.println("Watering complete");
    lastWateringTime = millis(); // Update last watering time
  } else {
    digitalWrite(relayPin, LOW); // Deactivate relay
    Serial.println("No Watering Needed");
  }

  delay(10000); // Update every 2 seconds
}

bool needsWatering() {
  // Check if it's been more than pumpDuration milliseconds since the last watering
  return millis() - lastWateringTime >= pumpDuration;
}
