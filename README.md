# Automatización del cambio de escala en luxometría

Proyecto académico de Electrónica Digital desarrollado por Braither Diaz Chiquillo y Edison Ortega Perenguez, del Departamento de Física de la Universidad Nacional de Colombia, en noviembre de 2023.

El objetivo fue automatizar el cambio de escala de un luxómetro mediante un motor paso a paso acoplado a su perilla. El montaje combina un Arduino UNO, un motor 28BYJ-48 con su driver ULN2003, pulsadores, un DIP switch y un integrado 74HC14 para reducir el ruido de las entradas. Las piezas de acople se diseñaron para impresión 3D.

## Contenido

- [`ProgramaProyectoED.ino`](ProgramaProyectoED.ino): firmware Arduino para controlar el motor en modo manual o automático.
- [`DiagramaProyectoFinalED.png`](DiagramaProyectoFinalED.png): diagrama de flujo del programa.
- [`ED_InformeProyectoFinal.pdf`](ED_InformeProyectoFinal.pdf): informe del proyecto, que describe el circuito, los componentes, el firmware, las dificultades y las recomendaciones.

## Funcionamiento previsto

- En modo manual, los pulsadores solicitan giros horarios o antihorarios en incrementos de 30 grados.
- En modo automático, el Arduino recibe por el puerto serial una instrucción de giro y comprueba que la posición solicitada esté entre 0 y 150 grados.
- El firmware utiliza las bibliotecas `Stepper` y `EEPROM`; el informe describe el almacenamiento de la posición para limitar el recorrido del motor.

## Estado y limitaciones

Este repositorio documenta el prototipo académico; no incluye los archivos CAD de las piezas ni una guía completa de cableado. El informe señala dificultades en el manejo de errores, el control de los límites y la precisión, además de calentamiento del motor y oportunidades de mejorar las piezas de acople.

El firmware se conserva como parte del trabajo original y no se ha validado para operar un luxómetro sin supervisión. Antes de usarlo con el dispositivo, conviene revisar la inicialización y recuperación de la posición: aunque lee un valor de EEPROM, el programa no lo asigna a `GeneralPosition` al arrancar. También se deberían probar los límites de movimiento y el comportamiento ante reinicios o entradas seriales inesperadas.
