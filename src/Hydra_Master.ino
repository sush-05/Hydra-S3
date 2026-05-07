#include <Arduino.h>
#include "Hydra_Config.h"
#include "driver/i2s.h"

void setup() {
    Serial.begin(115200);
    pinMode(PIN_READY, INPUT);
    pinMode(PIN_DONE, INPUT);

    // Using I2S in Parallel LCD Mode for Classic ESP32
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_LCD),
        .sample_rate = 100000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_8BIT,
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 2,
        .dma_buf_len = TENSOR_SIZE,
    };
    
    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    // Pin mapping for Parallel I2S would go here...
    Serial.println(">>> HYDRA MASTER (ESP32-DEV) ONLINE");
}

void loop() {
    if (digitalRead(PIN_READY) == HIGH) {
        uint8_t tensor[TENSOR_SIZE];
        for(int i=0; i<TENSOR_SIZE; i++) tensor[i] = random(0, 255);

        size_t bytes_written;
        unsigned long start = micros();
        
        // Direct DMA Blast over I2S Parallel
        i2s_write(I2S_NUM_0, tensor, TENSOR_SIZE, &bytes_written, portMAX_DELAY);
        
        while(digitalRead(PIN_DONE) == LOW);
        Serial.printf("Cycle Complete: %lu us\n", micros() - start);
    }
}
