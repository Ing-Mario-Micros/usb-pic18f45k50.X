/**
 Generated Main Source File
 Company:
 Microchip Technology Inc.
 File Name:
 main.c
 Summary:
 This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 Description:
 This header file provides implementations for driver APIs for all modules selected in the GUI.
 Generation Information :
 Product Revision : PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
 Device : PIC18F45K50
 Driver Version : 2.00
*/
/*
 (c) 2018 Microchip Technology Inc. and its subsidiaries. 
 
 Subject to your compliance with these terms, you may use Microchip software and any 
 derivatives exclusively with Microchip products. It is your responsibility to comply with third 
party 
 license terms applicable to your use of third party software (including open source software) that 
 may accompany Microchip software.
 
 THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
 EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
 IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
 FOR A PARTICULAR PURPOSE.
 
 IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
 HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
 THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
 CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
 OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
 SOFTWARE.
*/
#include <pic18f45k50.h>
#include<stdio.h>
#include<string.h>
#include "mcc_generated_files/mcc.h"

#define LED_CPU LATC1         //Pin del led de CPU asociado al funcionamiento del micro
#define LED_TEST LATC2        //Pin del led de prueba asociado a tareas especificas
#define LED_FAULT LATC0       //Pin del led de Error asociado a bloqueos en el micro

/*
 Main application
*/
char USB_Out_Buffer[64];
char buffer[64];
int cont=0;
void USBTask(void);
void main(void)
{
 // INTERRUPT_GlobalInterruptEnable();//activar interrupciones
 //INTERRUPT_PeripheralInterruptEnable();//activar interrupcion perifericos
 
 SYSTEM_Initialize();//inicializacion de todo el sistema
 // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
 // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
 // Use the following macros to:
 
 // Enable the Global Interrupts
 //INTERRUPT_GlobalInterruptEnable();
 // Disable the Global Interrupts
 //INTERRUPT_GlobalInterruptDisable();
 // Enable the Peripheral Interrupts
 //INTERRUPT_PeripheralInterruptEnable();
 // Disable the Peripheral Interrupts
 //INTERRUPT_PeripheralInterruptDisable();
 while (1)
 {
 USBDeviceTasks();
 USBTask(); // Add your application code
 
 }
}
void USBTask(void){
 if(USBGetDeviceState() < CONFIGURED_STATE || (USBIsDeviceSuspended() == true)) 
return;//comprobar la conexión
 uint8_t READ = getsUSBUSART(USB_Out_Buffer,64);
 if(USBUSARTIsTxTrfReady()) //Si el Buffer de salida esta libre
 {
 if(READ != 0){
    sprintf(buffer,"t%c h%c \n",22,48);
    putrsUSBUSART(buffer); //escribir 
 }
 __delay_ms(20);
 
 }
 CDCTxService(); //Procesa servicio USB
}
/**
End of File
*/