#ifndef HYDRA_CONFIG_H
#define HYDRA_CONFIG_H

/**
 * HYDRA-S3 ARCHITECTURE DEFINITION
 * Protocol: 8-Bit Parallel Intel 8080 (i80)
 * Peak Bandwidth: 40 MB/s @ 40MHz DMA
 */

// --- Parallel Data Bus (Contiguous GPIOs for Speed) ---
// Pins 1-8 mapped to the 8-bit bus
const int HYDRA_DATA_BUS[] = {1, 2, 3, 4, 5, 6, 7, 8}; 

// --- Control & Timing ---
const int PIN_WR     = 9;   // Write Strobe (Bus Clock)
const int PIN_CS     = 10;  // Chip Select
const int PIN_RS     = 11;  // Register Select (Command/Data Toggle)

// --- Hardware Sync Lines ---
const int PIN_READY  = 14;  // Accelerator -> Master (High = Ready)
const int PIN_DONE   = 21;  // Accelerator -> Master (Pulse = Finished)

// --- Tensor Topology ---
#define TENSOR_DIM    32    // 32x32 Grid
#define TENSOR_SIZE   1024  // 1KB per inference pass
#define ALIGNMENT     16    // 16-byte alignment for PIE SIMD instructions

#endif
