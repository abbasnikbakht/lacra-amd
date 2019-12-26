#ifndef GPSLIBV18_H
#define GPSLIBV18_H

#include "ESP32NodeLibV18.h"
#include <TinyGPS++.h>

#ifdef __cplusplus
extern "C" {
#endif

// #define BUF_SIZE                (1024)
#define GPS_PIN_RX              (12)                //(GPIO_NUM_12)             //(39)     //(GPIO_NUM_9)
#define GPS_PIN_TX              (15)                //(GPIO_NUM_15)            //(36)     //(GPIO_NUM_10)
#define GPS_PIN_VBAT            (35)                // GPIO35 - pino para leitura da Vpp da bateria

#define GPS_TYPE                (1)                 // Codigo dos dados sobre GPS
#define GPS_UTC_OFFSET          (-3)
#define GPS_INTERVAL            (1)
#define GPS_EPOCH_TIME_2019     (1546300800)        // 00:00:00 01/01/2019

#define GPS_DEBUG_MAIN          (true)
#define GPS_DEBUG_GETDATA       (false)
#define GPS_DEBUG_TIME_SERIAL   (120000)            // intervalo entre cada envio de uma string pela porta serial para debug da lib
#define GPS_DEBUG_MESSAGE       ("GPS_TASK: ")
#define GPS_TASK_DELAY_MS       (1000)
#define GPS_SEND_INTERVAL       (120)               // Intervalo (em segundos) para envio dos dados GPS para o Gateway

#define GPS_POSITION_ACCURACY   (2)                 // A (Horizontal position accuracy) para o modulo NEO 6M eh de 2,5 metros

typedef struct {
    float latitude;
    float longitude;
    float altitude;
    float speed;
    String date;
    String time;
    uint32_t satellites;
    int32_t hdop;
} gps_t;

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} gps_time_t;

class GPSLib
{
    public:

        GPSLib();     // construtor

        boolean begin(void);
        boolean read(void);
        String getDataString(uint64_t unixTime);
        boolean avaliable(void);
        boolean requestSync(void);
        // boolean checkMovement(gps_t initialPoint, gps_t endPoint);
        boolean checkMovement(void);

        boolean gpsDebugMain;
        boolean gpsDebugGetData;
        uint32_t gpsDebugTimeSerial;
        uint32_t gpsTaskDelayMS;
        gps_t parametersGPS;
        // uint32_t tsSendIntervalGPS = GPS_SEND_INTERVAL * 1000;                 // em segundos
        uint32_t tsSendIntervalGPS;                 // em segundos

    private:
        float getVBat(void);

        gps_time_t timeGPSNow;
        const int UTC_offset = GPS_UTC_OFFSET;
        time_t unixtimeGPS;
        uint32_t tsLastReportGPS = 0;
        uint16_t tsIntervalGPS = (GPS_INTERVAL - 1) * 1000;             // em segundos
        const uint8_t vbatPin = GPS_PIN_VBAT;

};

#ifdef __cplusplus
}
#endif

#endif // GPSLIBV18_H