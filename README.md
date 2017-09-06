# M365-BLE-PROTOCOL
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

Si usan los datos que publico en este repositorio o lo publican en otro lugar, por favor indiquen la fuente y darme los creditos.
Saludos
Camilo
