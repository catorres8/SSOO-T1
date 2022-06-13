# **T3: PREGUNTA 4: SIMULACIÓN :jack_o_lantern:**
* * *

*Grupo:* Nicole Marín, Cristobal Torres

*Curso:* IIC2333

* * *

## **Parte 1** :closed_book::

###  **Pregunta 1** 
El largo de la dirección IP de destino es de **32 bits**.

###  **Pregunta 2** 
La dirección IP de origen, cuando el paquete se encuentra en el router central, y el último dispositivo visitado es el router gateway de la red Casa Manolito, es **190.190.1.2**.

###  **Pregunta 3** 

La dirección IP de origen, cuando el paquete se encuentra en el router central, y el último dispositivo visitado es el router gateway de la red DNS, es **7.7.0.2**.

###  **Pregunta 4** 

Cuando el paquete se encuentra en el servidor DNS, y el último dispositivo visitado fue el router gateway DNS, lo que ocurre en el paquete es lo siguiente:

**En las CAPAS DE ENTRADA**:

* **Capa 1**: Puerto fastEthernet 0/1
   1. Fe0/1 recibe el frame.

* **Capa 2:** Encabezado Ethernet II 000A.F3D7.0616 >> 00E0.F700.45D2
   1. La dirección MAC de origen del frame no existe en la tabla MAC de Switch. Switch agrega una nueva entrada MAC a su tabla.
   2. Esta es un frame de unidifusión. Switch busca en su tabla MAC la dirección MAC de destino.

**En las CAPAS DE SALIDA**:

* **Capa 1**: Puerto(s): FastEthernet 1/1
   1. FastEthernet1/1 envía el frame.

* **Capa 2**: Encabezado Ethernet II 000A.F3D7.0616 >> 00E0.F700.45D2
   1. El puerto de salida es un puerto de acceso. El conmutador envía el frame por ese puerto.



## **Parte 2** :world_map::

###  **Pregunta 1** 

El largo del http Request del paquete HTTP es de **107 bytes**.


###  **Pregunta 2** 

Los paquetes que se usan son de tipo DNS y HTTP. 
Se utiliza paquete DNS porque es necesario este tipo de estructura y contenido para que el servidor DNS sea capaz de traducir el nombre de dominio de Disneyplus a su direcciones IP para que el web browser del Laptop de Manolito pueda cargar la página.

Por otro lado, de usa paquete HTTP ya que es necesario este tipo de estructura para poder usar el protocolo HTTP, que es el protocolo de transferencia de archivos de hiper-texto entre clientes y servidores HTTP. Entonces para poder transferir el archivo de texto (el html de la pagina web)  primero se evía desde el laptop de Manolito un paquete HTTP request, solicitando la página web, y posteriormente desde el servidor Disney, se envía paquete HTTP response, con el cual finalmente se renderiza el html en el Laptop de Manolito. 

Cada **paquete DNS** contiene la información necesaria para hacer la consulta al Servidor DNS, o la Respuesta al Cliente DNS, por lo cual se estructuran de la siguiente manera:

- Tipo de conexión
- Información IP
- Información UDP
- DNS Header
- DNS Query
- Dns Answer (si es que es una respuesta)


Cada **paquete HTTP** contiene la información necesaria para hacer la solicitud al Servidor HTTP, o la Respuesta al Cliente HTTP, por lo cual se estructuran de la siguiente manera:

- Tipo de conexión
- Información IP
- Información TCP
- HTTP Request / HTTP Response (Según corresponda)



###  **Pregunta 3** 

Primero un paquete DNS sale desde el Laptop Familia, paquete en el cual el cliente DNS envía una consulta DNS al servidor DNS. Luego este paquete pasa por el wireless router Manolito, para dirigirse al Router Giveaway Manolito. Desde aquí el paquete es transferido  hacia la red DNS, partiendo por el Router DNS, y finalmente dirigido al Server DNS, a través del Switch DNS. Es aquí donde el nombre de dominio ```www.disneyplus.com``` ingresado al browser del Laptop Familia, es traducido a la dirección IP correspondiente. Luego esta traducción, se devuelve a través del Paquete DNS por el mismo camino en que llegó: Pasa por el Switch DNS, luego por el Router DNS, para dirigirse al Router Central. Posteriormente ingresa a la Red Manolito, a través del Router Giveaway Manolito, para finalmente, a través de Wireless Router, llegar al Laptop Familia. 

Es aquí cuando el Cliente HTTP envía una solicitud HTTP al servidor Disney, a través de un paquete HTTP. El paquete pasa por Wireless Router Manolito, y por el Router Giveaway Manolito, para llegar al Router Central. Es en este lugar en donde el paquete se envía hacia la red Disney. En primer lugar ingresa al Switch Disney, para dirigirse al servidor Disney, en donde el servidor entonces recibe una solicitud HTTP, y luego llega al servidor devuelve una respuesta HTTP al cliente. El paquete se dirige ahora hacia la red Manolito, pasando por el Switch Disney hacia el Router Central. El paquete es transferido por el Router Giveaway Manolito, hacia el Wireless Router, y finalmente es recepcionado por el Laptop Familia, en donde finalmente el cliente HTTP recibe la respuesta HTTP del servidor, mostrando la página ```www.disneyplus.com``` en el navegador web.


FALTA FOTO
----------------------------------------
![Error al cargar la imagen](/flujo_paquetes.jpg "Flujo de Paquetes DNS y HTTP en la simulación")
