#ifndef HYDRA_CONFIG_H
#define HYDRA_CONFIG_H

/* 
 * HYDRA-S3 ARCHITECTURE (ADAPTED FOR ESP32 DEV MODULE)
 * Interface: I2S Parallel Data Bus
 * Target: High-Speed inter-chip tensor sharding
 */

// --- Parallel Bus Pins (Classic ESP32) ---
const int HYDRA_DATA_BUS[] = {12, 13, 14, 15, 16, 17, 18, 19}; 
const int PIN_WR     = 21;  // Write Clock
const int PIN_READY  = 22;  // Handshake: Ready
const int PIN_DONE   = 23;  // Handshake: Done

#define TENSOR_SIZE 1024 
#endif
