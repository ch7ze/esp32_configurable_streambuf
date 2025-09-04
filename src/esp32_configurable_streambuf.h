#pragma once
#include <Arduino.h>
#include <streambuf>
#include <vector>
#include <functional>
#include <iostream>

namespace cs {

	class ConfigurableStreambuf : public std::streambuf {
        private:
            static constexpr size_t bufferSize = 128;
            char buffer[bufferSize];
            using OutputFunc = std::function<void(const char*, size_t)>;
            
            struct OutputEntry {
                int id;
                OutputFunc func;
            };
            
            std::vector<OutputEntry> outputFunctions;
            int nextId = 1;
            
        public:
            ConfigurableStreambuf();
            
            int addOutputFunction(std::function<void(const char*, size_t)> outputFunction);
            bool removeOutputFunction(int id);
            
            
        protected:
            virtual int_type overflow(int_type c) override;
            virtual int sync() override;
    };
        
        // Globale Instanz-Deklaration (Definition in .cpp)
        inline ConfigurableStreambuf configurableStreambuf;

		void serialOut(const char* data, size_t len);

}