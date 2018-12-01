This is the exam project for Real Time software development course at Università dell'Insubria.

Developed using Keil uVision 4, for device STM32F103RB.

Task				periodo		costo
Aperiodic server	1 ms		0.1 ms
Guida				10 ms		1 ms
Posizione			50 ms		15 ms
Comunicazione		200 ms		30 ms

Usando Rate Monotonic Analysis:

t0 = 1 + 15 + 30 + 0.1 = 46.1
t1 = 1*4 + 15 + 30 + 0.1 = 49.1
t2 = 1*4 + 15 + 30 + 0.1 = 49.1  <<<