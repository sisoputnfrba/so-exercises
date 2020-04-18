# Ejercicio 9

Estamos en fecha estelar 85785.9, y el capitán Kirk está muy preocupado últimamente. Envió a Spock a una misión crítica para la seguridad espacial, pero Scotty (el ingeniero de la nave) estuvo haciendo updates al sistema de teletransportación, y Spock nunca llegó a destino

Investigando el sistema Scotty encontró un archivo flatSpock.bin, luego de horas de investigación terminaron descubriendo que la falla se encontraba en el sistema de de-serialización y que ese archivo corresponde a la teletransportación fallida de Spock.

Se le pide al alumno hacer un programa que lea el archivo .bin y lo deserialize correctamente para poder recuperar a Spock.

El capitán Kirk quiere mandar a toda costa a Spock a esa misión, sin embargo, a pesar que la tripulación del Enterprise posee ART, el capitán no quiere volver a arriesgarse, así que ha dejado a su cargo  también rehacer el sistema de serialización.

Para que no vuelva a pasar lo mismo, comparar el hash md5 del archivo *flatSpock.bin*, con el que genere su programa, ambos deberían dar el mismo código.

Se adjunta el sistema original de teletransportación para hacer los cambios que el alumno crea pertinentes y así poder cumplir esta misión.

Estructura de spock en el archivo *flatSpock.bin*


Campo | Longitud | Tipo
---| --- | ---
Edad | 1 byte | Numérico
Nombre | Variable (n + 1) | String (termina en ‘\0’)
Mascota_Edad | 1 byte | Numérico
Mascota_Da_Vueltas | 1 byte | Booleano
Mascota_Apodo | Variable (n + 1) | String (termina en ‘\0’)
Mision_Informacion | Variable (n + 1) | String (termina en ‘\0’)
Mision_Longitud | 4 byte | Numérico sin signo
Villanos_Cantidad | 4 byte | Numérico sin signo
Villanos | (n veces * tamaño villano) bytes | 
Villano_Nombre | 25 bytes | String (termina en ‘\0’)
Villano_Edad | 2 bytes | Numérico sin signo
