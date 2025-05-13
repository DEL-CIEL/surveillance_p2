/**
 * @file CSon.h
 * @brief Déclaration de la classe CSon pour l'acquisition et le traitement audio
 * @author Delos
 * @date 03/04/2025
 * @version 1.0
 */

#include <Arduino.h>
#include <esp_err.h>
#include <driver/i2s.h>
#include "arduinoFFT.h"

#define SAMPLES 512                 ///< Nombre d'échantillons
#define SAMPLING_FREQUENCY 44100    ///< Fréquence d'échantillonnage en Hz
#define DMA_BUF_LEN 512             ///< Taille du buffer DMA en échantillons
#define DMA_BUF_COUNT 8             ///< Nombre de buffers DMA

/**
 * @class CSon
 * @brief Classe pour l'acquisition et le traitement des données audio via I2S
 */
class CSon {
public:
    float niveauSonoreMoyen;        ///< Niveau sonore moyen calculé
    float niveauSonoreCrete;        ///< Niveau sonore crête détecté
    float vReal[SAMPLES];           ///< Partie réelle des échantillons pour FFT
    float vImag[SAMPLES];           ///< Partie imaginaire des échantillons pour FFT
    float tempsEchantillon;
    /**
     * @brief Constructeur par défaut
     */
    CSon();

    /**
     * @brief Initialise le périphérique I2S
     * @return esp_err_t Code d'erreur ESP32
     */
    esp_err_t Setup();

    /**
     * @brief Acquiert des échantillons audio via DMA
     * @return esp_err_t Code d'erreur ESP32
     */
    esp_err_t SamplesDmaAcquisition();

private:
    i2s_config_t i2sConfig;
    i2s_pin_config_t pinConfig;
    ArduinoFFT<float> FFT;
    size_t bytesRead;
    int32_t i2sData[SAMPLES];
};