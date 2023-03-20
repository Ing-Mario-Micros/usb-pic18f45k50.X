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

#define LED_CPU LATC0         //Pin del led de CPU asociado al funcionamiento del micro
#define LED_TEST LATC2        //Pin del led de prueba asociado a tareas especificas
#define LED_FAULT LATC1       //Pin del led de Error asociado a bloqueos en el micro

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
 
 /*-------------------- Configuración de timer 0 ----------------------------*/
    T0CON=0b00000110; /*Configuración del timer0 correspondiente 
                     * a un tiempo aproximado de 0.5seg usando la ecuación
                     * (2^N)-((Tsflujo*Fbus)/PS)= Precarga
                     * la frecuencia de Bus "Fbus" es igual a la drecuencia de reloj
                     * divididad 4, en esté caso 48MHz/4 = 12MHz
                     * La precarga debe de ser menor a 2^N que es la
                     * resolución del timer 2^16 = 65536
                     * 2^16 -((0.5seg*12x10^6Hz)/128)=18661
                     * La precarga se suma al valor del registro TMR0L
                     */
    TMR0L=18661 & 255;//precarga del registro del timer0, la explicación está en
    TMR0H=18661 >> 8; //la función de interrupción del Timer 0
    TMR0ON=1;         //Encendido del Timer 0
    /** Configuración de interrupción del timer 0**/
    TMR0IF=0; //Bandera de Interrupción timer 0 en Cero
 
 while (1){
    USBDeviceTasks();//Se tiene que realizar el llamado de este metodo para que funcione correctamente
    USBTask(); // Add your application code
    if(TMR0IF==1){
        LED_CPU=LED_CPU ^ 1;
        TMR0L=18661 & 255; /* para cargar el valor de precarga se divide
                           el numero en dos registros el alto y el bajo
                           para la parte alta baja se toma la precarga y
                           se realiza una and de 255 (0b1111 1111) para 
                           que de esta manera solo se tenga el Valor bajo*/
        TMR0H=18661 >> 8;  /* Para la parte alte se realiza un corrimiento de 
                           el valor de precarga de ocho posiciones*/
        TMR0IF=0;         /*se pone la bandera de interrupción en 0 para que
                           vuelva a ocurrir*/
    }
 
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