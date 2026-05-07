#include <Arduino.h>
#include "Hydra_Config.h"
#include "esp_lcd_panel_io.h"

esp_lcd_panel_io_handle_t hydra_io_handle = NULL;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_READY, INPUT);
    pinMode(PIN_DONE, INPUT);

    // Initializing the High-Speed Parallel i80 Bridge
    esp_lcd_panel_io_i80_config_t bus_cfg = {
        .cs_gpio_num = PIN_CS,
        .pclk_gpio_num = PIN_WR,
        .data_gpio_nums = {1, 2, 3, 4, 5, 6, 7, 8},
        .bus_width = 8,
        .max_transfer_bytes = TENSOR_SIZE,
    };

    // Attach to the ESP32-S3 LCD Peripheral for DMA support
    if (esp_lcd_new_panel_io_i80(&bus_cfg, &hydra_io_handle) == ESP_OK) {
        Serial.println(">>> HYDRA MASTER: Parallel DMA Plane Online.");
    }
}

void loop() {
    // Check if the Accelerator is idle
    if (digitalRead(PIN_READY) == HIGH) {
        
        // Generate/Capture Tensor Data
        uint8_t frame_data[TENSOR_SIZE];
        for(int i=0; i<TENSOR_SIZE; i++) frame_data[i] = random(0, 255);

        unsigned long start_micros = micros();

        // High-Speed DMA Transfer (Moves 1KB in <30 microseconds)
        esp_lcd_panel_io_tx_color(hydra_io_handle, 0x2C, frame_data, TENSOR_SIZE);
        
        // Wait for Hardware "DONE" signal from Accelerator
        while(digitalRead(PIN_DONE) == LOW); 
        
        unsigned long end_micros = micros();
        Serial.printf("[BENCHMARK] Total Inference Cycle: %lu us\n", end_micros - start_micros);
    }
}
