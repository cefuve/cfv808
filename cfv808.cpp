/*
  cfv808.h - Library for SIM808 module.
  Created by César Fuenzalida Vergara, Enero 18, 2019.
*/

#include "cfv808.h"

int cfv808::begin(int baudRate)
{
    sim808.begin(baudRate);
}

bool cfv808::command(const char *toSend, char *output, unsigned long timeout) {
    String result;
    Serial.print("->");
    Serial.println(toSend);
    sim808.println(toSend);
    unsigned long startTime = millis();
    Serial.write("<-");
    while (millis() - startTime < timeout) {
        if (sim808.available()) {
        char c = sim808.read();
        result += c;
        delay(5);
        }
        if (result.indexOf(output) >=0){
            delay(500);
            return true;
        }
    }
    Serial.flush();
    return false;
}

String cfv808::reply(char *reply, unsigned long timeout)
{
    String result;
    unsigned long startTime = millis();
    Serial.write("<-");
    while (millis() - startTime < timeout) {
        if (sim808.available()) {
        char c = sim808.read();
        result += c;
        delay(5);
        }
    }
    Serial.flush();
    if(result.indexOf(reply) >= 0){
        _reply = true;
    }else{
        _reply = false;
    }
    return result;
}

bool cfv808::ingresarPIN(char *pin)
{
  char atsend[14] = "AT+CPIN=";
  atsend[8] = pin[0];
  atsend[9] = pin[1];
  atsend[10] = pin[2];
  atsend[11] = pin[3];
  atsend[12] = '\0';

  return command(atsend, "OK", 500);
}

bool cfv808::iniciar(void)
{
    if(!command("AT","OK",300)) return false;
    if(!command("ATE0", "OK", 500)) return false;
    if(!command("AT+CVHU=0", "OK", 500)) return false;
    if(!command("ATI", "OK", 500)) return false;
    if(!command("AT+CPMS=\"SM\",\"SM\",\"SM\"", "OK", 1000)) return false;
    return true;
}

bool cfv808::enviarSMS(char *number, char *data)
{
    if (!command("AT+CMGF=1", "OK", 500)) return false;

    char atsend[30] = "AT+CMGS=\"";
    strncpy(atsend+9, number, 30-9-2);
    atsend[strlen(atsend)] = '\"';

    if (!command(atsend, "> ", 500)) return false;

    sim808.println(data);
    Serial.println(data);
    sim808.println();
    //sim808.write(0x1A);
    if(command("\u001a", "OK", 15000)){
        return true;
    }else{
        return false;
    }
}

String cfv808::leerSMS(int *index)
{
    
}

bool cfv808::llamar(char *number)
{
    char atsend[35] = "ATD";
    strncpy(atsend+3, number, min(30, (int)strlen(number)));
    uint8_t x = strlen(atsend);
    atsend[x] = ';';
    atsend[x+1] = 0;

    return command(atsend, "OK", 1000);
}

bool cfv808::colgar(void)
{
    return command("ATH", "OK", 500);
}

bool cfv808::encenderGPS()
{
    /*
	 if(!sim808_check_with_cmd("AT+CGNSPWR=1\r\n", "OK\r\n", CMD)) { 
        return false;
    }
	 if(!sim808_check_with_cmd("AT+CGNSINF\r\n", "OK\r\n", CMD)) { 
        return false;
    }
	return true;
    */
}

bool cfv808::apagarGPS()
{
    /*
	 if(!sim808_check_with_cmd("AT+CGNSPWR=0\r\n", "OK\r\n", CMD)) { 
        return false;
    }
	return true;
    */
}

bool cfv808::leerGPS() 
{

}