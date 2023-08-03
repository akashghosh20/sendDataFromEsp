#include <ESP8266WiFi.h>
#include <FirebaseESP32.h> // Include the Firebase ESP32 library

const char* ssid = "ASL";
const char* password = "aslmec2023";

// Replace with your Firebase project credentials
// Replace with your Firebase project credentials
#define FIREBASE_HOST "https://iotapp-83d9d-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyD47qYIOgYkqDCu4wrU3GTfQGqvA56D6DI"


FirebaseData firebaseData;  // Create a FirebaseData object to hold data
FirebaseJson jsonData;      // Create a FirebaseJson object to store the JSON data

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Not connected");
  }
  Serial.println();
  Serial.println("Connected to WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // Initialize Firebase with your credentials
}

void loop() {
  // Simulate data (you can replace this with actual sensor readings)
  int sensorValue = random(0, 1024);
  Serial.println(sensorValue);

  // Set the path where you want to store the data in Firebase
  String path = "/sensor_data"; // Change this to your desired path

  // Clear the previous JSON data
  jsonData.clear();

  // Add the "value" field to the JSON data
  jsonData.add("value", sensorValue);

  // Send the data to Firebase
  if (Firebase.setJSON(firebaseData, path, jsonData)) {
    Serial.println("Data sent to Firebase successfully!");
  } else {
    Serial.println("Failed to send data to Firebase");
    Serial.println("Reason: " + firebaseData.errorReason());
  }

  delay(5000); // Adjust the delay time based on your data sending frequency
}
