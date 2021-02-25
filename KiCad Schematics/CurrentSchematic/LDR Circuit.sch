EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L Device:R R?
U 1 1 6037FC74
P 3700 2350
F 0 "R?" H 3770 2396 50  0000 L CNN
F 1 "100k" H 3770 2305 50  0000 L CNN
F 2 "" V 3630 2350 50  0001 C CNN
F 3 "~" H 3700 2350 50  0001 C CNN
	1    3700 2350
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Optical:LDR03 R?
U 1 1 60381036
P 3700 2750
F 0 "R?" H 3770 2796 50  0000 L CNN
F 1 "LDR03" H 3770 2705 50  0000 L CNN
F 2 "OptoDevice:R_LDR_10x8.5mm_P7.6mm_Vertical" V 3875 2750 50  0001 C CNN
F 3 "http://www.elektronica-componenten.nl/WebRoot/StoreNL/Shops/61422969/54F1/BA0C/C664/31B9/2173/C0A8/2AB9/2AEF/LDR03IMP.pdf" H 3700 2700 50  0001 C CNN
	1    3700 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60381EB8
P 3700 2900
F 0 "#PWR?" H 3700 2650 50  0001 C CNN
F 1 "GND" H 3705 2727 50  0000 C CNN
F 2 "" H 3700 2900 50  0001 C CNN
F 3 "" H 3700 2900 50  0001 C CNN
	1    3700 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2500 3700 2550
Wire Wire Line
	3700 2550 4100 2550
Connection ~ 3700 2550
Wire Wire Line
	3700 2550 3700 2600
Text GLabel 4100 2550 2    50   Output ~ 0
LDR
$Comp
L power:+3V3 #PWR?
U 1 1 60383138
P 3700 2200
F 0 "#PWR?" H 3700 2050 50  0001 C CNN
F 1 "+3V3" H 3715 2373 50  0000 C CNN
F 2 "" H 3700 2200 50  0001 C CNN
F 3 "" H 3700 2200 50  0001 C CNN
	1    3700 2200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
