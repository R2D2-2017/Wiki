 /**
 * \file
 * \brief     Combination of the work of sprint 1
 * \author    Tim IJntema, Stefan de Beer, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
 
#include "mysql.hh"
#include "mfrc522.hh"
#include "encryption.hh"
#include "led-controller.hh"

#include <wiringPi.h>
#include <wiringPiSPI.h>
 
#include <iostream>

int main(int argc, char **argv) {
    MySql connection;

    if(!connection.connectTo("192.168.2.50", "R2D2", "BB8")){
        std::cout << "Can not connect\n";
        exit(0);
    }
    
    if(!connection.selectDatabase("R2D2")){
        std::cout << "Database unknown\n";
        exit(0);
    }
    
    wiringPiSetup();
    wiringPiSPISetup(0, 10000000);//max speed for mfrc522 is 10Mhz
    Mfrc522 rfid;
    rfid.init();

    Encryptie encryption(65341);

    LedController led;

    while(1){
        std::cout << "\n\nWaiting for rfid tag: \n";

        while(!rfid.isTagPresent()){}
        
        std::cout<<"Hello tag\n";
        
        if(!connection.executeQuery("SELECT * FROM RFID")){
            std::cout << "Can not execute query\n";
            exit(0);
        }
        
        std::cout << "Database information: "
                  << connection.getPreviousResponseColumn("CARD_ID")
                  << '\n';
        
        std::cout << "String before encryption: R2D2 project\n";
        std::cout << "String after encryption: "
                  << encryption.Encrypt("R2D2 project")
                  << '\n';

        led.blinkLed(0, 5000);
    }
    return 0;
}