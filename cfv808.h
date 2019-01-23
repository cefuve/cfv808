/*
  cfv808.h - Library for SIM808 module.
  Created by César Fuenzalida Vergara, Enero 18, 2019.
*/
#ifndef cfv808_h
#define cfv808_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class cfv808
{
  public:
    struct GPS
    {
        int RunStatus;
        int FixStatus;
        double longitude, latitude;
        float altitude;
        char UTC[18];
        int sat;
        float speed;
        float course;
    };

    cfv808(int rx, int tx):sim808(rx,tx){}
    int begin(int baudRate);

    bool command(const char *command, char *output, unsigned long timeout);
    String reply(char *reply, unsigned long timeout);
    bool ingresarPIN(char* pin);
    bool iniciar(void);

    bool enviarSMS(char* number, char* data);
    String leerSMS(int* index);
    bool llamar(char* number);
    bool colgar();

    bool  encenderGPS();
	  bool  apagarGPS();
    bool  leerGPS();

  private:
    SoftwareSerial sim808;
    bool _reply;
};

#endif