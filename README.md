This is the exam project for Real Time software development course at Università dell'Insubria.

Developed using Keil uVision 4, for device STM32F103RB.

Task				periodo		costo
Aperiodic server	1 ms		0.1 ms
Guida				10 ms		1 ms
Posizione			50 ms		15 ms
Comunicazione		200 ms		30 ms

Usando Rate Monotonic Analysis:

t0 = A + G + P + C = 46.1 ms
t1 = 46\*A + 4\*G + P + C = 53.6 ms 
t2 = 53\*A + 5\*G + P + C = 55.3 ms
t3 = 55\*A + 5\*G + P + C = 55.5 ms
t4 = 55\*A + 5\*G + P + C = 55.5 ms <<<


Note per lo sviluppo:
-creare task per emergenze;
-implementare task comunicazione;