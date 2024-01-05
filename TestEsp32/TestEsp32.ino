
#include "esp_camera.h"

// Define the GPIO pin for the button
const int buttonPin = 0;  // Change this to the GPIO pin where your button is connected

// Variables for capturing photo
const int captureInterval = 5000;  // Capture a photo every 5 seconds (adjust as needed)
unsigned long lastCaptureTime = 0;

void setup() {
  Serial.begin(115200);

  // Configure the button pin
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize the camera
  camera_config_t config;
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // Print Camera Information
  sensor_t *sensor = esp_camera_sensor_get();
  Serial.println("Camera Ready!");
  Serial.printf("Resolution: %dx%d\n", sensor->max_width, sensor->max_height);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    // Check if enough time has passed since the last capture
    if (millis() - lastCaptureTime >= captureInterval) {
      Serial.println("Button pressed! Capturing photo...");
      capturePhoto();
      lastCaptureTime = millis();
    }
  }
}

void capturePhoto() {
  // Capture a photo
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Failed to capture photo");
    return;
  }

  // Create a file to save the photo on the SPIFFS filesystem
  File file = SPIFFS.open("/photo.jpg", FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    esp_camera_fb_return(fb);
    return;
  }

  // Write the photo to the file
  file.write(fb->buf, fb->len);
  Serial.println("Photo saved: /photo.jpg");

  // Close the file and release the frame buffer
  file.close();
  esp_camera_fb_return(fb);
}