This is the exam project for Real Time software development course at Università dell'Insubria.

Developed using Keil uVision 4, for device STM32F103RB.

### Tempistiche in millisecondi:
1 km/h = 5/18 m/s = 1/36 cm/ms ~ 0.0277 cm/ms

* 30 km/h ~ 0.8333 cm/ms
* 50 km/h ~ 1.3888 cm/ms
* 70 km/h ~ 1.9444 cm/ms
* 90 km/h ~ 2.5 cm/ms
* 110 km/h ~ 3.0555 cm/ms
* 130 km/h ~ 3.6111 cm/ms
* 150 km/h ~ 4.1666 cm/ms

| Task				| Periodo	| Costo		| Spostamento (50 km/h)	|
| :---------------- | --------: | --------: | --------------------: |
| Aperiodic server	| 1 ms		| 0.1 ms	| 1.39 cm				|
| Guida				| 10 ms		| 1 ms		| 13.89 cm				|
| Posizione			| 50 ms		| 15 ms		| 69.44 cm				|
| Comunicazione		| 200 ms	| 30 ms		| 277.76 cm				|

### Usando Rate Monotonic Analysis:

* t0 = A + G + P + C = 46.1 ms
* t1 = 46\*A + 4\*G + P + C = 53.6 ms 
* t2 = 53\*A + 5\*G + P + C = 55.3 ms
* t3 = 55\*A + 5\*G + P + C = 55.5 ms
* t4 = 55\*A + 5\*G + P + C = 55.5 ms <<<

#### Note per lo sviluppo:
- casi di test