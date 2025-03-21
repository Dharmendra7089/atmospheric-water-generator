const int sensorPin = A0;  // Analog pin for water level sensor
const int relayPin = 7;    // Digital pin for relay

const int maxLevel = 1023;  // Maximum sensor reading (adjust as needed)
const int minLevel = 0;     // Minimum sensor reading

bool draining = false;

void setup() {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW); // Ensure relay is off initially
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(sensorPin);
    int waterLevel = map(sensorValue, minLevel, maxLevel, 0, 100); // Convert to percentage
    
    Serial.print("Water Level: ");
    Serial.print(waterLevel);
    Serial.println("%");
    
    if (!draining && waterLevel >= 90) {
        digitalWrite(relayPin, HIGH); // Turn relay ON
        draining = true;
    }
    
    if (draining && waterLevel <= 10) {
        digitalWrite(relayPin, LOW); // Turn relay OFF
        draining = false;
    }
    
    delay(1000); // Delay for stability
}
