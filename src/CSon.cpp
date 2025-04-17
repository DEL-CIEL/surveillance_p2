#include "CSon.h"
#include <iostream>
#include <string.h>
#include "arduinoFFT.h"

/**
 * @brief Constructeur de la classe CSon
 * Initialise les attributs et configure les pins I2S
 */
CSon::CSon() 
    : niveauSonoreMoyen(0.0f),
      niveauSonoreCrete(0.0f),
      bytesRead(0) 
{
    // Initialisation des tableaux
    memset(vReal, 0, sizeof(vReal));
    memset(vImag, 0, sizeof(vImag));
    memset(i2sData, 0, sizeof(i2sData));

    // Configuration des pins I2S
    this->pinConfig = {
    .bck_io_num = 14,   //  ? 
    .ws_io_num = 13, //  ? 
    .data_out_num = I2S_PIN_NO_CHANGE, // Pas de data out 
    .data_in_num = 12  //  ? 
    }; 

    // Configuration du mode I2S
    this->i2sConfig = { 
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // ? 
    .sample_rate = SAMPLING_FREQUENCY, // ? 
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, // Bits par échantillon 
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,  // ?  
    .communication_format =  i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S), 
    .intr_alloc_flags = 0,//ESP_INTR_FLAG_LEVEL1,  // Niveau d'interruption 
    .dma_buf_count = 8,  // Nombre de buffers DMA 
    .dma_buf_len = DMA_BUF_LEN,  // Taille du buffer DMA 
    .use_apll = false, 
    .tx_desc_auto_clear = false, 
    .fixed_mclk = 0
    };

    this->FFT = ArduinoFFT<float>(this->vReal, this->vImag, SAMPLES, SAMPLING_FREQUENCY);
}

esp_err_t CSon::Setup()
{
    float result = i2s_driver_install(I2S_NUM_0, &this->i2sConfig, 0, NULL); 
    result = i2s_set_pin(I2S_NUM_0, &this->pinConfig); 
    result = i2s_zero_dma_buffer(I2S_NUM_0); 
    return result;
}