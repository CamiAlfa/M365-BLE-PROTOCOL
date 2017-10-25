# M365-BLE-PROTOCOL

The files and documents in this repository are published under the terms of the 
GNU Lesser General Public License as published by the Free Software Foundation; 
either version 2.1 of the License, or (at your option) any later version.

Los archivos y documentos publicados aquí estan publicados bajo la licencia 
GNU Lesser General Public License.

Si usan los datos de este repositorio, por favor indiquen la fuente y darme los creditos correspondientes.

Reverse engineering of Bluetooth LE protocol used to communicate between mihome APP an the scooter
Ingenieria inversa del protocolo usado para la comunicacion entre el patinete mijia m365 y la aplicacion mihome
El protocolo descrito es para la version 1.3.4 del firmware.

La comunicación esta basada en el protocolo ninebot que ha descrito Paco Gorina aquí
http://forum.electricunicycle.org/topic/2686-unraveling-ninebot-one-e-ble-protocol-success/
y aquí esta una app para un ninebot.
https://github.com/fgorina/9BMetrics

Su trabajo ha facilitado la comprensión del protocolo.

En el repositorio hay un archivo txt, el cual explica la comunicación y un documento excel con los registros.

Hay muchos registros que se pueden leer y escribir en el patinete, en el excel estan descritos y se dividen en colores:
en verde y azul los que hay certeza de su significado.
en amarillo los que hay indicios, pero no certeza de su significado
en rojo los que no se sabe el significado.

Los registros vacios son registros que no se han usado en la APP de MIhome y por tanto no se tiene informacion sobre estos

La idea es ir completando y conocer con certeza el significado de todos los registros. y asi poder crear una APP open source para la telemetria del patinete.

Saludos
Camilo

Libreria:

Ejemplo

#include "ninebot.h"

#include "m365_register_map.h"

...

NinebotPack NB_BLE_data_in,NB_BLE_data_out;

...

uint8_t dataUART_NB_buffer[NinebotMaxPayload+8];

uint8_t data_NB_payload[NinebotMaxPayload];

...
data_NB_payload[1]=0x00;

data_NB_payload[0]=M365cruiseon;

ninebot_create_pack(MastertoM365, Ninebotwrite , M365cruiseREG , (M365cruiseLEN+2), data_NB_payload, &NB_BLE_data_out);

ninebot_serialyze(&NB_BLE_data_out,dataUART_NB_buffer);

send dataUART_NB_buffer via ble

...

ninebot_create_request(MastertoM365,Ninebotread,M365battREG, M365battLEN + M365speedLEN, &NB_BLE_data_out);

ninebot_serialyze(&NB_BLE_data_out,dataUART_NB_buffer);

send dataUART_NB_buffer via ble

...

error = ninebot_parse(Uart_Data_in, Uart_data_len), &NB_BLE_data_in);

if (error ==0){//todo bien

....
