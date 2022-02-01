# robot_arm

Buy Mechanical parts online from [Amazon](https://www.amazon.in/Ayasa-Electronics-Robotic-Included-Included/dp/B077YMCBWW)
Additional components : 
 * [Servo motors](https://www.electronicscomp.com/towerpro-sg90-9gm-micro-servo-motor?gclid=Cj0KCQiArt6PBhCoARIsAMF5waik_1FMM43HpRoCGQUPF4ZgkJ8TkyaV87QartmpxVm-6I5wElCPrwwaAvWuEALw_wcB) X 4
 * [24V SMPS](https://www.electronicscomp.com/24v-5amp-smps-dc-metal-power-supply-nwp-india?gclid=Cj0KCQiArt6PBhCoARIsAMF5wajOp_xQSTgm2NliWdLdgBOR3zY22qq_P-vnZuMcij22NBr67QIwrgYaAsfPEALw_wcB) external power is required for current demand of motors
 * [LM2596 module](https://robu.in/product/lm2596s-dc-dc-buck-converter-power-supply/) to step down 24V to 5V to provide the arduino and circuit

Assembly is shown in [this video](https://youtu.be/wQRFiqFBimE)

The basic Robot arm project:
 * It takes 4 inputs from 4 Potentiometers and moves 4 servo motors accordingly
 * It works in 3 modes : AUTO, MANUAL and PROGRAM
 * Modes are changed using 3 push buttons, and indicated by LEDs
 * In MANUAL mode servos move wrt potentiometer
 * PROGRAM mode is activated by long press of program button in Manual mode
 * In PROGRAM mode, program is saved using Enter button
 * In AUTO mode, the saved program is run in a loop with some delay.

Connections:
 * MANUAL_LED = 10, AUTO_LED = 11, PROGRAM_LED = 12
 * GRIP_SERVO = 6, ELBOW_SERVO = 7, SHOULDER_SERVO = 8, BASE_SERVO = 9
 * MANUAL_BUTTON = 2, ENTER_BUTTON = 3, AUTO_BUTTON = 4, PROGRAM_BUTTON = 5
 * BASE_ADC = 0, SHOULDER_ADC = 1, ELBOW_ADC = 2, GRIP_ADC = 3, DELAY_ADC = 4;
 * LM2596 module output connected to 5V and "NOT TO VIN" and CONNECT ALL THE GROUNDs together