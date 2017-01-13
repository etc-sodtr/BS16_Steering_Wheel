# BS16_Steering_Wheel
Programul principal este:
BS16_Steering_Wheel/FreeRTOS_AT90-volan - FINAL/AT90_Semph/AT90_Semph/source/main.c

Acest software este scris pentru a fi folosit pe volanul monopostului de Formula Student.

Sistemul de operare folosit este FREERTOS v9.0.0
Microcontroller-ul folosit este AT90CAN32

Functionalitatea consta in:
-preluarea si prelucrarea datelor primite pe magistrala CAN de la ECU
-afisarea datelor de la senzori:-viteza
				-treapta de viteza
				-temperatura motorului
				-turatia motorului indicata prin leduri cat si afisata pe Display-ul LCD.
				-temperatura aerului
				-alte date de la senzorii aflati pe monopost
Detalii de functionare:
-microcontrollerul controleaza pe interfata paralela LCD-ul
-Ledurile de turatie cat si afisajele de tip 7 segmente sunt controlate prin intermediul unor registre de deplasare cascadate, controlate prin SPI
-pozitia comutatoarelor rotative este citita in cod BCD

