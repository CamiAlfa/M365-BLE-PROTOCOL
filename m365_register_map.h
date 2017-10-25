/****************************************************************************/
//  Function: register map file ninebot communication
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

#define MastertoM365 0x20
#define M365toMaster 0x23

//string
#define M365serialREG 0x10
#define M365serialLEN 14
//string
#define M365pinREG 0x17
#define M365pinLEN 6
//version ex 0x0133 = v1.3.3
#define M365firmverREG 0x1a
#define M365firmverLEN 2
//km restantes, ex 123= 1.23km
#define M365kmremainREG 0x25
#define M365kmremainLEN 2
//segundos de este viaje
#define M365triptimeREG 0x3b
#define M365triptimeLEN 2
//temperatura grados*10 ex 123=12.3 grados C mostrada en el menu
#define M365frametempREG 0x3e
#define M365frametempLEN 2
//Modo ECO, solo lectura
#define M365ecorREG 0x75
#define M365ecorLEN 2
#define M365ecoroff 0
#define M365ecoron 1
//nivel de frenado regenerativo //0 = weak, 1= medium, 2=strong
#define M365kersREG 0x7b
#define M365kersLEN 2
#define M365kersWeak 0
#define M365kersMed 1
#define M365kersStr 2
//Velocidad de crucero
#define M365cruiseREG 0x7c
#define M365cruiseLEN 2
#define M365cruiseoff 0
#define M365cruiseon 1
//Luz trasera
#define M365taillightREG 0x7d
#define M365taillightLEN 2
#define M365taillightoff 0
#define M365taillighton 2
//errores
#define M365errorREG 0xb0
#define M365errorLEN 2
//batería, porcentaje
#define M365battREG 0xb4
#define M365battLEN 2
//velocidad en metros/hora
#define M365speedREG 0xb5
#define M365speedLEN 2
//velocidad promedio en metros/hora
#define M365tripspeedREG 0xb6
#define M365tripspeedLEN 2
//kilometraje patinete metros, los 4 bits estan concatenados 0xb8 es el mas significativo
#define M365totalkmREG 0xb7
#define M365totalkmLEN 4
//km este viaje en km*100
#define M365tripkmREG 0xb9
#define M365tripkmLEN 2
//temperatura grados*10 ex 123=12.3 grados C mostrada en el dashboard
#define M365frametemp2REG 0xbb
#define M365frametemp2LEN 2
/* registros que usa la app desconocidos
    //desconocido 1b-21,3a,67-69,73-74,b0-b3,ba,bc-bf
    
    //ninebot_mem_scooter[0xba]=300;
    //ninebot_mem_scooter[0xb2]=200;
    //ninebot_mem_scooter[0xb3]=100;
    //ninebot_mem_scooter[0xbc]=0xffff;
    //ninebot_mem_scooter[0xbd]=0xfffe;
    //ninebot_mem_scooter[0xbe]=0xfffd;
    //ninebot_mem_scooter[0xbf]=0xfffc;
    //ninebot_mem_scooter[0x67]=0x0115;
    //ninebot_mem_scooter[0x68]=0x0071;
    //ninebot_mem_scooter[0x3a]=400;
    //ninebot_mem_scooter[0xba]=3662;
    
    //ninebot_mem_scooter[0xb9]=0x0005;
    //ninebot_mem_scooter[0x29]=0xbe3c;
    //ninebot_mem_scooter[0x29]=0x0001;
    //48ff:6e06:5266:5455:3539:2587
    //da desconocido
    //ninebot_mem_scooter[0xda]=0xffff;//no effect on serial
    //ninebot_mem_scooter[0xdb]=0xffff;
    //ninebot_mem_scooter[0xdc]=0xffff;
    //ninebot_mem_scooter[0xdd]=0xffff;
    //ninebot_mem_scooter[0xde]=0x3935;//wrong check code726a e4d4 c9a8 26a0 4d40 9a80. OK=9350 3500 5000 8000
    //ninebot_mem_scooter[0xdf]=0x8725;
    //ninebot_mem_scooter[0xda]=0xff48;
    //ninebot_mem_scooter[0xdb]=0x066e;
    //ninebot_mem_scooter[0xdc]=0x6652;
    //ninebot_mem_scooter[0xdd]=0x5554;
    //ninebot_mem_scooter[0xde]=0x3935;
    //ninebot_mem_scooter[0xdf]=0x8725;
    //29 desconocido
    //ninebot_mem_scooter[0x29]=0x00ca;*/
	
//los registros de la bateria se ubican en otra memoria del patinete	
#define MastertoBATT 0x22
#define BATTtoMaster 0x25

//serial bateria string, 
#define BATTserialREG 0x10
#define BATTserialLEN 14
//version bms ex 0x0112 = v1.1.2
#define BATTbmsverREG 0x17
#define BATTbmsverLEN 2
//capacidad de fabrica de bateria en mAh
#define BATTfabcapREG 0x18
#define BATTfabcapLEN 2
//fecha a la batt 7 MSB->año, siguientes 4bits->mes, 5 LSB ->dia ex:
//b 0001_010=10, año 2010
//        b 1_000= 8 agosto
//            b  0_1111=15 
//  0001_0101_0000_1111=0x150F 
#define BATTdateREG 0x20
#define BATTfabcapLEN 2
//mAh restantes en la bateria
#define BATTremaincapREG 0x31
#define BATTremaincapLEN 2
//porcentaje de la batería en porcentaje
#define BATTbattREG 0x32
#define BATTbattLEN 2
//corriente de la batería en amperios*100, puede ser negativo(carga)
#define BATTcurrentREG 0x33
#define BATTcurrentLEN 2
//voltaje bateria en voltios*10
#define BATTvoltREG 0x34
#define BATTvoltLEN 2
//temperatura celdas byte MSB temp1 y LSB temp2, en grados mas 20. ex 31 = 11grados
#define BATTtempREG 0x35
#define BATTtempLEN 2
//Vida de la batería, 0-100, error si es menor a 60
#define BATThealthREG 0x3b
#define BATThealthLEN 2
//voltaje packs del 1 al 10 en miliVoltios
#define BATTpackLEN 2
#define BATTpack1REG 0x40
#define BATTpack2REG 0x41
#define BATTpack3REG 0x42
#define BATTpack4REG 0x43
#define BATTpack5REG 0x44
#define BATTpack6REG 0x45
#define BATTpack7REG 0x46
#define BATTpack8REG 0x47
#define BATTpack9REG 0x48
#define BATTpack10REG 0x49
/* desconocido, usado por la app
//probablemente los ciclos de carga o estado de la batt
//ninebot_mem_batt[0x1c]=5;
//ninebot_mem_batt[0x27]=0x0001;
//ninebot_mem_batt[0x28]=0x0003;

*/
