# BS16_Steering_Wheel
Programul principal este:<br>
BS16_Steering_Wheel/FreeRTOS_AT90-volan - FINAL/AT90_Semph/AT90_Semph/source/main.c<br>
<br>
Acest software este scris pentru a fi folosit pe volanul monopostului de Formula Student.<br>
<br>
Sistemul de operare folosit este FREERTOS v9.0.0<br>
Microcontroller-ul folosit este AT90CAN32<br>
<br>
 + Functionalitatea consta in:<br>
- preluarea si prelucrarea datelor primite pe magistrala CAN de la ECU<br>
- afisarea datelor de la senzori:<br>
  * viteza
  * treapta de viteza
  * temperatura motorului
  * turatia motorului indicata prin leduri cat si afisata pe Display-ul LCD.
  * temperatura aerului
  * alte date de la senzorii aflati pe monopost<br>
 + Detalii de functionare:<br>
  - microcontrollerul controleaza pe interfata paralela LCD-ul
  - Ledurile de turatie cat si afisajele de tip 7 segmente sunt controlate prin intermediul unor registre de deplasare cascadate, controlate prin SPI
  - pozitia comutatoarelor rotative este citita in cod BCD

