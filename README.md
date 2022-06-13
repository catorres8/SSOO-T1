# **Entrega 2: DDCacería en San Joaquín: API :jack_o_lantern:**
* * *
*Grupo:* Grupo Senial

*Nombres:* Nicole Marín, Alonso Vargas

*Curso:* IIC2513

*Sección:* 2
* * *

## **Reglas del juego** :closed_book::

###  **Cambios en las reglas** :building_construction::

La versión completa de las reglas se encuentra en la pestaña ```reglas``` de la página web. A continuación, se presenta un breve resumen de los cambios realizados:

* Se eliminó la implementación de múltiples pisos.
* Se eliminó la capacidad de intercambiar cartas de items y maldiciones con otros jugadores, además de la capacidad de soltar items y maldiciones en habitaciones.
* Se simplificaron las condiciones de victorias: victorias por eliminar al equipo enemigo, y victorias por tokens. Una cacería puede tener una o ambas condiciones de victoria.

## **Modelos de la API** :world_map::

La API cuenta con los siguientes modelos, divididos informalmente en ``modelos modificables`` y ``modelos no modificables``. Los modelos modificables son los cuales interactuarán más directamente con el flujo de las partidas, y almacenarán los eventos que ocurran en una partida. Mientras que los modelos no modificables contienen información no modificable que los modelos modificables utilizarán:

### Modelos modificables:
* **users**: username => string, email => string, password => string, games\_played => integer, games\_won => integer, games\_lost => integer.
* **games**: id\_haunt => integer, omen\_counter => integer, current\_player => integer, winner => integer.
* **characters**: user\_id => integer, base\_character\_id => integer, game\_id => integer, x\_coord => integer, y\_coord => integer, velocity => integer, strength => integer, knowledge => integer, sanity => integer, is\_alive => boolean.
* **room_tiles**: id\_event => integer, room\_card\_id => integer, game\_id => integer, x\_coord => integer, y\_coord => integer, is_flipped => boolean.
* **has_item**: item\_id => integer, character\_id => integer.
* **has_omen**: omen\_id => integer, character\_id => integer.
* **has_event**: event\_id => integer, character\_id => integer.
* **request**: lobby\_id => integer, user\_id => integer.
* **lobby**: name => string, owner_id => integer, capacity => integer.
* **monsters**: base\_monster\_id => integer, x\_coord => integer, y\_coord => integer, velocity => integer, strength => integer, knowledge => integer, sanity => integer, is_stunned => boolean.
* **has_token**: room\_tile\_id => integer, token\_id => integer, amount => integer.

###  Modelos no modificables:
* **base_characters**: name => string, image\_url => string, min\_velocity => integer, base\_velocity => integer, min\_strength => integer, base\_strength => integer, min\_knowledge => integer, base\_knowledge => integer, min\_sanity => integer, base\_sanity => integer, color => string.
*  **haunts**: name => string, description => string, text\_good\_now => string, text\_evil\_now => string, text\_good\_about => string, text\_evil\_about => string, text\_good\_how\_to => string, text\_evil\_how\_to => string, text\_good\_victory => string, text\_evil\_victory => string, can\_good\_killwin => boolean, can\_evil\_killwin => boolean, can\_good\_tokenwin => boolean, can\_evil\_tokenwin => string, good\_token\_id => integer, evil\_token\_id => integer, good\_tokenroom\_id => integer, evil\_tokenroom\_id => integer, good\_token\_amount => integer, evil\_token\_amount => integer, summons\_monster => boolean, monster\_type\_id => integer, monster\_amount => integer.
*  **room_cards**: name => string, image\_url => string, has\_item => boolean, has\_omen => boolean, has\_event => boolean, on\_landing => string, on\_leaving => string, on_staying => string.
*  **item_cards**: name => string, description => string, icon\_url => string, on\_picking => string, on\_turn => string, allow\_special => boolean, on\_attack => string, text\_effects => string.
*  **omen_cards**: name => string, description => string, icon\_url => string, on\_picking => string, on\_turn => string, allow\_special => boolean, on\_attack => string, text\_effects => string.
*  **event_cards**: name => string, description => string, on\_picking => string, does\_rolling => boolean, is\_fixed => boolean, die\_amount => boolean, attribute => string, ranges => string, results => string, text\_results => string, can\_spawn => boolean.
*  **base_monster**: name => string, image\_url => string, base\_velocity => integer, base\_strength => integer, base\_knowledge => integer, base\_sanity => integer.
*  **tokens**: name => string.

## **Consideraciones adicionales** :warning::

* La API se encuentra en la dirección https://dccaceria-api.herokuapp.com/.
* Por temas de tiempo, la colección en Postman se encuentra bajo la dirección localhost:3000. Por favor, reemplazar por la dirección de la aplicación de no ser una posibilidad correr localmente la API.
