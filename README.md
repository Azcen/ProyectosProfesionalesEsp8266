# ProyectosProfesionalesEsp8266
Programa cargado a la tablilla de desarrollo ESP8266


Los requisitos para la instalacion son los siguientes:
  - Se requiere agregar el siguiente link en "preferencias/Gestor de URLS Adicionales de Tarjetas" para poder detectar y usar arduinoIDE para programar el ESP8266
      - "http://arduino.esp8266.com/stable/package_esp8266com_index.json"
 
  
  Instalacion:
  - Cargar el programa en la tablilla con arduinoIDE
  
  Detalles adicionales:
  Existen algunos parametros que van a variar por el dispositivo que se utilice como servidor, independientemente de lo que sea se debe cambiar la siguiente linea de codigo, lo que se debe remplazar es la ip del dispositivo, en windows se puede ver la ip del dispositivo abriendo la consola cmd y ecribiendo el comando "ipconfig", la ip que se debe de tomar es la Ipv4 del equipo.
  - "const char* serverName = "http://AQUI VA LA IPV4 DEL EQUIPO:8085/history";"
 
      
