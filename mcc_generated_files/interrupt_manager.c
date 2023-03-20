/**
  Generated Interrupt Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F45K50
        Driver Version    :  2.12
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above or later
        MPLAB 	          :  MPLAB X 5.45
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
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

#include "interrupt_manager.h"
#include "mcc.h"

//#define LED_CPU LATC0         //Pin del led de CPU asociado al funcionamiento del micro



void  INTERRUPT_Initialize (void)
{
    // Enable Interrupt Priority Vectors
    
    USBIE=1;
    USBIP=1;
    RCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors

    // USBI - high priority
    IPR3bits.USBIP = 1;
    
    
    PEIE=1;   //Activación de interrupción por perifericos
    IPEN=1;   //Activación de esquema de interrupciones
    GIE=1;    //Activación global de interrupciones

}

void __interrupt(high_priority) INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
    if(PIE3bits.USBIE == 1 && PIR3bits.USBIF == 1)
    {   
        //LATC2=1;  //LED de comprobación para ejecución de interrupción
        USB_USBDeviceTasks();
        USBIF=0; //Reset de la bandera de interrupción USB en cero
    }
    else
    {
        //LATC2=0;  //LED de comprobación para ejecución de interrupción
        //Unhandled Interrupt
    }
}


/**
 End of File
*/
