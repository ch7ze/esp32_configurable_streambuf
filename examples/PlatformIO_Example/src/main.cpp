#include <Arduino.h>
#include <esp32_configurable_streambuf.h>

void customLogOutput(const char* data, size_t len) {
  Serial.print("[LOG] ");
  Serial.write(data, len);
}

void fileOutput(const char* data, size_t len) {
  Serial.print("[FILE] ");
  Serial.write(data, len);
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Warte auf Serial-Verbindung
  
  Serial.println("=== ESP32 Configurable Streambuf PlatformIO Example ===");
  
  // Füge verschiedene Output-Funktionen hinzu
  int serialId = cs::configurableStreambuf.addOutputFunction(cs::serialOut);
  int customId = cs::configurableStreambuf.addOutputFunction(customLogOutput);
  int fileId = cs::configurableStreambuf.addOutputFunction(fileOutput);
  
  // Erstelle einen Stream mit unserem konfigurierbaren Streambuf
  std::ostream logStream(&cs::configurableStreambuf);
  
  Serial.println("\n--- Testing multiple outputs ---");
  logStream << "This message goes to all three outputs!" << std::endl;
  
  Serial.println("\n--- Removing custom output ---");
  cs::configurableStreambuf.removeOutputFunction(customId);
  logStream << "Now only Serial and File outputs." << std::endl;
  
  Serial.println("\n--- Removing file output ---");
  cs::configurableStreambuf.removeOutputFunction(fileId);
  logStream << "Now only Serial output." << std::endl;
  
  Serial.println("\n--- Adding lambda output function ---");
  int lambdaId = cs::configurableStreambuf.addOutputFunction([](const char* data, size_t len) {
    Serial.print("[LAMBDA] ");
    for (size_t i = 0; i < len; i++) {
      Serial.print((char)toupper(data[i]));
    }
  });
  
  logStream << "This message will also appear in uppercase!" << std::endl;
  
  Serial.println("\n--- Performance test ---");
  unsigned long startTime = millis();
  for (int i = 0; i < 100; i++) {
    logStream << "Performance test message #" << i << std::endl;
  }
  unsigned long endTime = millis();
  
  Serial.print("Sent 100 messages in ");
  Serial.print(endTime - startTime);
  Serial.println(" ms");
  
  Serial.println("\n=== Setup complete ===");
}

void loop() {
  static unsigned long lastMessage = 0;
  static int counter = 0;
  
  if (millis() - lastMessage > 5000) {
    std::ostream logStream(&cs::configurableStreambuf);
    logStream << "Loop message #" << ++counter << " at " << millis() << "ms" << std::endl;
    lastMessage = millis();
  }
  
  delay(100);
}