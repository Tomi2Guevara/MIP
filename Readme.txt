INSTRUCCIONES SERVER
se lanza desde mainServer.py
es necesario ejecutar "rcp true" para conectar un cliente

INSTRUCCIONES CLIENTE
En la carpeta scripts estan todos los archivos: cliente_main y todas las clases que utiliza junto con la libreria XMLRPC++
esta libreria funciona en windows porque tiene algunas modificaciones, para linux ver la del aula abierta
Se deben compilar todos los archivos cpp

INSTRUCCIONES INTERFAZ
Para lanzar la versión del cliente que acepta comandos a través de la interfaz gráfica, se debe repetir lo indicado en "INSTRUCCIONES CLIENTE", pero entrando a la carpeta /lib en vez que /libreria. 
Luego, dentro de la carpeta /build_gui, se debe lanzar gui.py para desplegar la ventana de la interfaz gráfica.
Importante: se deben actualizar las rutas tanto en el cliente como en la interfaz para que el pipe (comunicación) se genere y se lea en la misma ubicación.

INSTRUCCIONES ARDUINO
Hay un problema con el comando M114 devuelve "INFO:  URRENT POSITION: [X:0.00 Y:170.00 Z:120.00 E:0.00]"
Modificando el codigo en arduino agregando un espacio antes de la C funciona bien
"INFO: CURRENT POSITION: [X:0.00 Y:170.00 Z:120.00 E:0.00]" 
Subo el firmware de arduino modificado
