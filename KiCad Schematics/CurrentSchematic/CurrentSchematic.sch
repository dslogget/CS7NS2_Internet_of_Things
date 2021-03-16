EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Group5:ESP32_DevkitC_V4 U1
U 1 1 60379BBB
P 5600 3100
F 0 "U1" H 5625 3825 50  0000 C CNN
F 1 "ESP32_DevkitC_V4" H 5625 3734 50  0000 C CNN
F 2 "" H 5600 3650 50  0001 C CNN
F 3 "" H 5600 3650 50  0001 C CNN
	1    5600 3100
	1    0    0    -1  
$EndComp
Text GLabel 5000 3100 0    50   Input ~ 0
LDR
Text GLabel 6250 3800 2    50   Output ~ 0
LED
$Comp
L power:+3V3 #PWR0101
U 1 1 60384205
P 5000 2600
F 0 "#PWR0101" H 5000 2450 50  0001 C CNN
F 1 "+3V3" V 5015 2728 50  0000 L CNN
F 2 "" H 5000 2600 50  0001 C CNN
F 3 "" H 5000 2600 50  0001 C CNN
	1    5000 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 60384B5E
P 6250 2600
F 0 "#PWR0102" H 6250 2350 50  0001 C CNN
F 1 "GND" V 6255 2472 50  0000 R CNN
F 2 "" H 6250 2600 50  0001 C CNN
F 3 "" H 6250 2600 50  0001 C CNN
	1    6250 2600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 6038D397
P 3400 2900
AR Path="/6037F47C/6038D397" Ref="R?"  Part="1" 
AR Path="/6038D397" Ref="R1"  Part="1" 
F 0 "R1" H 3470 2946 50  0000 L CNN
F 1 "100k" H 3470 2855 50  0000 L CNN
F 2 "" V 3330 2900 50  0001 C CNN
F 3 "~" H 3400 2900 50  0001 C CNN
	1    3400 2900
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Optical:LDR03 R?
U 1 1 6038D39D
P 3400 3300
AR Path="/6037F47C/6038D39D" Ref="R?"  Part="1" 
AR Path="/6038D39D" Ref="R2"  Part="1" 
F 0 "R2" H 3470 3346 50  0000 L CNN
F 1 "LDR03" H 3470 3255 50  0000 L CNN
F 2 "OptoDevice:R_LDR_10x8.5mm_P7.6mm_Vertical" V 3575 3300 50  0001 C CNN
F 3 "http://www.elektronica-componenten.nl/WebRoot/StoreNL/Shops/61422969/54F1/BA0C/C664/31B9/2173/C0A8/2AB9/2AEF/LDR03IMP.pdf" H 3400 3250 50  0001 C CNN
	1    3400 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6038D3A3
P 3400 3450
AR Path="/6037F47C/6038D3A3" Ref="#PWR?"  Part="1" 
AR Path="/6038D3A3" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 3400 3200 50  0001 C CNN
F 1 "GND" H 3405 3277 50  0000 C CNN
F 2 "" H 3400 3450 50  0001 C CNN
F 3 "" H 3400 3450 50  0001 C CNN
	1    3400 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3050 3400 3100
Wire Wire Line
	3400 3100 3800 3100
Connection ~ 3400 3100
Wire Wire Line
	3400 3100 3400 3150
Text GLabel 3800 3100 2    50   Output ~ 0
LDR
$Comp
L power:+3V3 #PWR?
U 1 1 6038D3AE
P 3400 2750
AR Path="/6037F47C/6038D3AE" Ref="#PWR?"  Part="1" 
AR Path="/6038D3AE" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 3400 2600 50  0001 C CNN
F 1 "+3V3" H 3415 2923 50  0000 C CNN
F 2 "" H 3400 2750 50  0001 C CNN
F 3 "" H 3400 2750 50  0001 C CNN
	1    3400 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 60390C0C
P 8000 2750
F 0 "R3" V 8207 2750 50  0000 C CNN
F 1 "1k" V 8116 2750 50  0000 C CNN
F 2 "" V 7930 2750 50  0001 C CNN
F 3 "~" H 8000 2750 50  0001 C CNN
	1    8000 2750
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 60391B7D
P 8400 3100
F 0 "D1" V 8439 2982 50  0000 R CNN
F 1 "LED" V 8348 2982 50  0000 R CNN
F 2 "" H 8400 3100 50  0001 C CNN
F 3 "~" H 8400 3100 50  0001 C CNN
	1    8400 3100
	0    -1   -1   0   
$EndComp
Text GLabel 7700 2750 0    50   Input ~ 0
LED
Wire Wire Line
	7700 2750 7850 2750
Wire Wire Line
	8400 3250 8400 3400
$Comp
L power:GND #PWR0105
U 1 1 603945B3
P 8400 3400
F 0 "#PWR0105" H 8400 3150 50  0001 C CNN
F 1 "GND" H 8405 3227 50  0000 C CNN
F 2 "" H 8400 3400 50  0001 C CNN
F 3 "" H 8400 3400 50  0001 C CNN
	1    8400 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2750 8400 2950
Wire Wire Line
	8150 2750 8400 2750
Wire Notes Line
	7300 2450 8850 2450
Wire Notes Line
	8850 2450 8850 3850
Wire Notes Line
	8850 3850 7300 3850
Wire Notes Line
	7300 3850 7300 2450
Wire Notes Line
	4100 2450 2900 2450
Wire Notes Line
	4100 2450 4100 3800
Wire Notes Line
	2900 2450 2900 3800
Wire Notes Line
	2900 3800 4100 3800
Text GLabel 6250 3700 2    50   Output ~ 0
SERVO
$Comp
L power:+5V #PWR?
U 1 1 603922FA
P 5000 4400
F 0 "#PWR?" H 5000 4250 50  0001 C CNN
F 1 "+5V" V 5015 4528 50  0000 L CNN
F 2 "" H 5000 4400 50  0001 C CNN
F 3 "" H 5000 4400 50  0001 C CNN
	1    5000 4400
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60393670
P 7450 4600
F 0 "#PWR?" H 7450 4450 50  0001 C CNN
F 1 "+5V" H 7465 4728 50  0000 C BNN
F 2 "" H 7450 4600 50  0001 C CNN
F 3 "" H 7450 4600 50  0001 C CNN
	1    7450 4600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 6039A676
P 8300 4700
F 0 "J?" H 8000 4800 50  0000 L CNN
F 1 "Servo Header" H 7750 4700 50  0000 L CNN
F 2 "" H 8300 4700 50  0001 C CNN
F 3 "~" H 8300 4700 50  0001 C CNN
	1    8300 4700
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6039C390
P 7450 4900
F 0 "#PWR?" H 7450 4650 50  0001 C CNN
F 1 "GND" H 7455 4772 50  0000 C TNN
F 2 "" H 7450 4900 50  0001 C CNN
F 3 "" H 7450 4900 50  0001 C CNN
	1    7450 4900
	1    0    0    -1  
$EndComp
Text GLabel 8000 4600 0    50   Input ~ 0
SERVO
Text Notes 7400 4350 0    50   ~ 0
Pin 1 has an arrow and is orange\nRed it 5V\nBrown is ground
Wire Wire Line
	7450 4700 7450 4600
Wire Wire Line
	7450 4700 8100 4700
Wire Wire Line
	7450 4800 7450 4900
Wire Wire Line
	7450 4800 8100 4800
Wire Wire Line
	8100 4600 8000 4600
Wire Notes Line
	7300 4050 8850 4050
Wire Notes Line
	8850 4050 8850 5150
Wire Notes Line
	8850 5150 7300 5150
Wire Notes Line
	7300 5150 7300 4050
$Comp
L Connector:Conn_01x04_Female J?
U 1 1 605071EB
P 3550 4250
F 0 "J?" H 3700 4200 50  0000 L CNN
F 1 "Microphone Header" H 3250 3950 50  0000 L CNN
F 2 "" H 3550 4250 50  0001 C CNN
F 3 "~" H 3550 4250 50  0001 C CNN
	1    3550 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 605071F1
P 2700 4450
F 0 "#PWR?" H 2700 4200 50  0001 C CNN
F 1 "GND" H 2705 4322 50  0000 C TNN
F 2 "" H 2700 4450 50  0001 C CNN
F 3 "" H 2700 4450 50  0001 C CNN
	1    2700 4450
	1    0    0    -1  
$EndComp
Text GLabel 3250 4450 0    50   Output ~ 0
MIC
Wire Wire Line
	2700 4250 2700 4150
Wire Wire Line
	2700 4250 3350 4250
Wire Wire Line
	2700 4350 2700 4450
Wire Wire Line
	2700 4350 3350 4350
Wire Wire Line
	3350 4450 3250 4450
Wire Notes Line
	4100 4700 2550 4700
$Comp
L power:+3V3 #PWR?
U 1 1 60507C63
P 2700 4150
AR Path="/6037F47C/60507C63" Ref="#PWR?"  Part="1" 
AR Path="/60507C63" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2700 4000 50  0001 C CNN
F 1 "+3V3" H 2715 4323 50  0000 C CNN
F 2 "" H 2700 4150 50  0001 C CNN
F 3 "" H 2700 4150 50  0001 C CNN
	1    2700 4150
	1    0    0    -1  
$EndComp
Wire Notes Line
	4100 4700 4100 3850
Wire Notes Line
	4100 3850 2550 3850
Wire Notes Line
	2550 3850 2550 4700
Text GLabel 6250 3600 2    50   Input ~ 0
MIC
Text GLabel 3550 5200 1    50   Input ~ 0
BUZZER
Wire Wire Line
	3550 5600 3550 5750
$Comp
L power:GND #PWR?
U 1 1 6051CFDC
P 3550 5750
F 0 "#PWR?" H 3550 5500 50  0001 C CNN
F 1 "GND" H 3555 5577 50  0000 C CNN
F 2 "" H 3550 5750 50  0001 C CNN
F 3 "" H 3550 5750 50  0001 C CNN
	1    3550 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 5200 3550 5400
$Comp
L Device:Buzzer BZ?
U 1 1 6051DB12
P 3650 5500
F 0 "BZ?" H 3802 5529 50  0000 L CNN
F 1 "Buzzer" H 3802 5438 50  0000 L CNN
F 2 "" V 3625 5600 50  0001 C CNN
F 3 "~" V 3625 5600 50  0001 C CNN
	1    3650 5500
	1    0    0    -1  
$EndComp
Wire Notes Line
	4100 4750 3350 4750
Wire Notes Line
	3350 4750 3350 6050
Wire Notes Line
	3350 6050 4100 6050
Wire Notes Line
	4100 4750 4100 6050
Text GLabel 6250 3500 2    50   Output ~ 0
BUZZER
Text Notes 2950 4000 0    50   ~ 0
Pin 1 is labelled P1 on PCB
$EndSCHEMATC
