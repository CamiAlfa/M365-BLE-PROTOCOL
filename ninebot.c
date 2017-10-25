/****************************************************************************/
//  Function: C file ninebot communication
//  Author:   Camilo Ruiz
//  Date:    october 10 2017
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
// I am not responsible of any damage caused by the misuse of this library
// use at your own risk
//
// If you modify this or use this, please don't delete my name and give me the credits
// Greetings from Colombia :) 
/****************************************************************************/

#include "ninebot.h"
#include "m365_register_map.h"

//si size es =20 es posible que el mensaje sea mas largo habria que ver la longitud de las datos declarada en el paquete, mas adelante
//uint16_t data_index=0;
//uint16_t checksum=0;
//uint8_t dataUART_NB_buffer[256];
//It takes an array that comes from serial and tranforms it into a pack
uint8_t ninebot_parse(uint8_t *dataUART, uint8_t size, NinebotPack *message){
		static uint16_t data_index=0;
		static uint16_t checksum=0;
    int16_t uart_index=-1;
    if (data_index==0){
        checksum=0;
        if (size<9) return 3;
        if (dataUART[0]!=NinebotHeader0) return 2;
        if (dataUART[1]!=NinebotHeader1) return 2;
        if (dataUART[2]<3) return 2;//messaje deforme
            else message->len=dataUART[2];
        checksum=checksum+dataUART[2];
        message->direction=dataUART[3];
        checksum=checksum+dataUART[3];
        message->RW=dataUART[4];
        checksum=checksum+dataUART[4];
        message->command=dataUART[5];
        checksum=checksum+dataUART[5];
        data_index=0;
        uart_index=5;
    }
    while(data_index<(message->len)){
        uart_index++;
        if (uart_index > 19 | uart_index==size) return 1;//mensaje incompleto, espera nuevo
        if(data_index==(message->len-2)) 
            message->CheckSum[0]=dataUART[uart_index];
        else if(data_index==(message->len-1)) 
            message->CheckSum[1]=dataUART[uart_index];
        else {
            message->data[data_index]=dataUART[uart_index];
            checksum=checksum+dataUART[uart_index];
        }
        data_index++;
    }
    data_index=0;
    checksum= checksum ^ 0xFFFF;//xor
    if (((checksum>>8)== message->CheckSum[1] )&& ((checksum & 0xff)== message->CheckSum[0])) return 0;
    else return 3;
}

//used in the scooter emu to answer the app. Diseñada para el emulador, aqui no se usa
uint8_t ninebot_slave_answer(NinebotPack *inmessage, NinebotPack *outmessage){
	uint16_t checksum=0;
	uint16_t *mem_activa;
	//NinebotPack outmessage;
	if (inmessage->RW==Ninebotread){ 
		//*outsize = inmessage->data[0]+8;
    outmessage->len=inmessage->data[0]+2;
		outmessage->RW=Ninebotread;//la respuesta siempre es read
		outmessage->command=inmessage->command;
		if (inmessage->direction==MastertoM365){
			outmessage->direction=M365toMaster;
			mem_activa=ninebot_mem_scooter;
		} else if (inmessage->direction==MastertoBATT){
			outmessage->direction=BATTtoMaster;
			mem_activa=ninebot_mem_batt;
		}
		
		checksum=checksum + outmessage->len;
		checksum=checksum + outmessage->direction;
		checksum=checksum + outmessage->RW;
		checksum=checksum + outmessage->command;
		
		uint8_t retrieve_len=(inmessage->data[0])/2;
		for (uint8_t retrieve_index=0;retrieve_index<retrieve_len;retrieve_index++){
			outmessage->data[(retrieve_index*2)]=(mem_activa[inmessage->command+retrieve_index]&0xff);
			checksum=checksum + outmessage->data[(retrieve_index*2)];
			outmessage->data[1+(retrieve_index*2)]=(mem_activa[inmessage->command+retrieve_index]>>8);
			checksum=checksum + outmessage->data[1+(retrieve_index*2)];
		}
		
		checksum= checksum ^ 0xFFFF;//xor
		outmessage->CheckSum[0]=(checksum & 0xff);
		outmessage->CheckSum[1]=(checksum>>8);
		return outmessage->len+8;
	} else if (inmessage->RW==0x03){
    //escribir, no implementado, aun asi, en el patinete real no hay respuesta
		return 0;
	}   
return 0;
}
//creates a pack ready to serialyze
uint8_t ninebot_create_pack(uint8_t direction, uint8_t RW,uint8_t command, uint8_t len, uint8_t *payload, NinebotPack *message){
		static uint16_t checksum=0;
		static uint16_t data_index=0;
		checksum=0;
	
		if ((len<3) || (len>(NinebotMaxPayload+2))) return 2;//mensaje deforme o demasiado grande
    else message->len=len;
		checksum=checksum+len;
	
		message->direction=direction;
    checksum=checksum+direction;
	
    message->RW=RW;
    checksum=checksum+RW;
	
    message->command=command;
    checksum=checksum+command;
	
	  for(data_index = 0; data_index< (len-2); data_index++){
			message->data[data_index]=payload[data_index];
			checksum=checksum+payload[data_index];
		}
		checksum= checksum ^ 0xFFFF;//xor
		message->CheckSum[0]=(checksum & 0xff);
		message->CheckSum[1]=(checksum>>8);
		return 0;
}
//creates a pack in order to request info from the scooter
uint8_t ninebot_create_request(uint8_t direction, uint8_t RW,uint8_t command, uint8_t len, NinebotPack *message){
		static uint16_t checksum=0;
		checksum=0;
	
		//esto es un request, asi que su longitud es de 3
		message->len=0x03;
		checksum=checksum+0x03;
	
		message->direction=direction;
    checksum=checksum+direction;
	
    message->RW=RW;
    checksum=checksum+RW;

    message->command=command;
    checksum=checksum+command;
	
		//el payload de este mensaje contiene el numero de bytes esperados en la respuesta, 
		//pide min 2, max NinebotMaxPayload
		if ((len<2) || (len>(NinebotMaxPayload))) return 2;//menssaje deforme
    else message->data[0]=len;
		checksum=checksum+len;
	
		checksum= checksum ^ 0xFFFF;//xor
		message->CheckSum[0]=(checksum & 0xff);
		message->CheckSum[1]=(checksum>>8);
		return 0;
}
//it takes a pack an transforms it into an array ready to send trough serial
uint8_t ninebot_serialyze(NinebotPack *message, uint8_t *dataUART){
	//uint16_t checksum=0; //no revisaremos el checksum aqui
	static uint16_t data_index=0;
	
	dataUART[0]=NinebotHeader0;
	dataUART[1]=NinebotHeader1;
	dataUART[2]=message->len;
	dataUART[3]=message->direction;
	dataUART[4]=message->RW;
	dataUART[5]=message->command;
	for(data_index = 0; data_index< (message->len-2); data_index++){
			dataUART[6+data_index]=message->data[data_index];
	}
	dataUART[message->len+4]=message->CheckSum[0];
	dataUART[message->len+5]=message->CheckSum[1];
  return message->len+6;

}
