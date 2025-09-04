#include <esp32_configurable_streambuf.h>

void setup() {
  Serial.begin(115200);
  
  // Warte bis Serial bereit ist
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("ESP32 Configurable Streambuf Example");
  
  // Füge die Serial-Output-Funktion hinzu
  int serialId = cs::configurableStreambuf.addOutputFunction(cs::serialOut);
  
  // Erstelle einen Stream mit unserem konfigurierbaren Streambuf
  std::ostream logStream(&cs::configurableStreambuf);
  
  // Teste die Ausgabe
  logStream << "Hello from configurable streambuf!" << std::endl;
  logStream << "This message goes to Serial via the output function." << std::endl;
  
  // Füge eine weitere Output-Funktion hinzu (z.B. für eine andere Ausgabe)
  int customId = cs::configurableStreambuf.addOutputFunction([](const char* data, size_t len) {
    Serial.print("[CUSTOM] ");
    Serial.write(data, len);
  });
  
  logStream << "This message goes to both outputs!" << std::endl;
  
  // Entferne die Custom-Output-Funktion
  cs::configurableStreambuf.removeOutputFunction(customId);
  
  logStream << "Back to single output." << std::endl;
}

void loop() {
  // Nichts im Loop
  delay(1000);
}