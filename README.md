Matilda The Plant
====================================

Hola! Soy Matilda y soy una planta. Mi nombre real es [Crassula ovata](https://es.wikipedia.org/wiki/Crassula_ovata), comúnmente llamada árbol de jade y soy originaria de África del Sur.
Hablo con el mundo mediante un [Adafruit HUZZAH ESP8266](http://tienda.bricogeek.com/placas-adafruit-feather/979-adafruit-feather-huzzah-esp8266-wifi.html) que tengo conectado todo el tiempo y envío los datos a Thingspeak. De esta forma, puedo informar de mi estado de ánimo y cómo está mi ambiente.

Puedes ver más información sobre éste proyecto aquí:
[http://blog.bricogeek.com/noticias/arduino/matilda-the-plant-planta-conectada-con-esp8266-a-thingspeak/](http://blog.bricogeek.com/noticias/arduino/matilda-the-plant-planta-conectada-con-esp8266-a-thingspeak/)

Componentes
-----------
Estos son los componentes que utilizo:

* [Sensor de temperatura y humedad DHT11](http://tienda.bricogeek.com/sensores-temperatura/986-sensor-de-humedad-y-temperatura-dht11.html)
* [Sensor de humedad del suelo](http://tienda.bricogeek.com/sensores-humedad/651-sensor-de-humedad-del-suelo.html)
* [Dos resistencias](http://tienda.bricogeek.com/arduino/175-kit-de-resistencias-1-4w.html). Una de 2.2K Ohm y otra de 1K Ohm

Para alimentar la electrónica, simplemente tengo un adaptador MicroUSB de pared que proporciona 5V al Adafruit HUZZAH.

Matilda The Code
----------------

Si quieres más información o hacer lo mismo con otras compañeras de familia, puedes consultar mi código fuente en éste repositorio. 

* [Instalación y configuración de Adafruit HUZZAH ESP8266](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266)
* [Arduino IDE] (https://www.arduino.cc/en/Main/Software). Necesitas la versión 1.8.3 o superior del IDE de Arduino.

La conexión de los sensores es muy sencilla:

* DHT11 Pin 1 ->	3.3V
* DHT11 Pin 2 -> 2
* DHT11 Pin 3 -> No connectedado
* DHT11 Pin 4 -> GND
   
Sensor de humedad de la tierra:
* Conectar VCC y GND. El pin de salida mediante una resistencia de 2.2K al pin 2 del ESP8266 y otra resistencia de 1K desde el pin 2 a GND.

Matilda Wifi
----------------
Ajusta las variables **"ssid"** y **"password"** con los parámetro de tu conexión Wifi.

Matilda ThingSpeak
------------------
Debes disponer de una cuenta de usuario en [ThingSpeak](https://thingspeak.com) y crear un canal (channel). Una vez hecho, necesitas el *channelID* y *writeAPIKey* para poder enviar los datos al feed.
Puedes ver mis gráficas [aquí](https://thingspeak.com/channels/305320)

Cómo utilizar GitHub
--------------------

Guía de uso de GitHub de Sparkfun:
* [Using GitHub](https://learn.sparkfun.com/tutorials/using-github)


License Information
-------------------

Released under the [Creative Commons ShareAlike 4.0 International](https://creativecommons.org/licenses/by-sa/4.0/) license. 
**You are welcome to use this code for commercial purposes.**
