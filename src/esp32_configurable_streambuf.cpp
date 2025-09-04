#include "esp32_configurable_streambuf.h"

// Implementierung der ConfigurableStreambuf-Klasse
cs::ConfigurableStreambuf::ConfigurableStreambuf() {
    // Initialisiere den Ausgabepuffer (put area)
    setp(buffer, buffer + bufferSize - 1);
}

int cs::ConfigurableStreambuf::addOutputFunction(std::function<void(const char*, size_t)> outputFunction) {
    int id = nextId++;
    outputFunctions.push_back({id, outputFunction});
    return id;
}

bool cs::ConfigurableStreambuf::removeOutputFunction(int id) {
    auto it = std::find_if(outputFunctions.begin(), outputFunctions.end(),
        [id](const OutputEntry& entry) { return entry.id == id; });
        
    if (it != outputFunctions.end()) {
        outputFunctions.erase(it);
        return true;
    }
    return false;
}

cs::ConfigurableStreambuf::int_type cs::ConfigurableStreambuf::overflow(int_type c) {
    if (c != traits_type::eof()) {
        *pptr() = traits_type::to_char_type(c);
        pbump(1);
        sync();
    }
    return c != traits_type::eof() ? traits_type::to_int_type(c) : traits_type::eof();
}

int cs::ConfigurableStreambuf::sync() {
    size_t len = pptr() - pbase();
    
    if (len > 0) {
        for (const auto& entry : outputFunctions) {
            entry.func(pbase(), len);
        }
        
        // Setze den Puffer zurück
        pbump(-static_cast<int>(len));
    }
    
    return 0;
}

void cs::serialOut(const char* data, size_t len) {
	Serial.write(data, len);
}