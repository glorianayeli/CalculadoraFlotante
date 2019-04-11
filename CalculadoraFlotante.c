#include <18F4620.h>
#include <stdlib.h>
#include <matematica.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif 

//declaracion de vectores
char buffer[9]={""};
//declarion de variables de almacenamiento
char opcion_ingresada;
//variables de interrupcion
int flagSerial=0, contador_buf=0, flagMostrar=1, flagEnter=0, flagEcho=0;
//banderas
int tarea_programa=1;
char bandera;
//echo
char caracter_recibido;

//operaciones aritmeticas
float num1,num2,resultado;
#bit flagSerial = bandera.0
//Recepcion de datos dentro del buffer
#INT_RDA
void isrRDA (void)
{
   if(contador_buf<10)
   {
      caracter_recibido=getc();
      buffer[contador_buf]=caracter_recibido;
      contador_buf++;
   }
   if(caracter_recibido==0x0D)
   {
      flagEnter=1;     
   }
   //valida backspaces
   if(caracter_recibido==0x08)
   {
      buffer[contador_buf-1]=0;
      buffer[contador_buf-2]=0;
      contador_buf-=2;
   }
   flagSerial=1;
   flagEcho=1;
}

void main (void){
   set_tris_c(0x80); 
   //habilito mi interrupcion
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   printf("\nIngresar una de las siguientes opciones: \n"); 
   printf("\ns)Suma \n r)Resta \n m)Multiplicacion \n d)Division\n");
   //inicio mi ciclo while
   while(1){
         if(flagEcho==1)
         {
            putc(caracter_recibido);
            flagEcho=0;
         }
         if(tarea_programa==1&&flagMostrar==1)
         {
            printf("\nIngresa Opción: \t\n");
            flagMostrar=0;
         }
         else if(tarea_programa==2&&flagMostrar==1)
         {
            printf("\nIngresa Numero1: \t\n");
            flagMostrar=0;
         }
         else if(tarea_programa==3&&flagMostrar==1)
         {
            printf("\nIngresa Numero2: \t\n");
            flagMostrar=0;
         }

        
         if(flagSerial==1&&flagEnter==1)
         {
            if(tarea_programa==1)
            {
               opcion_ingresada=buffer[0];
               contador_buf=0;
               flagSerial=0;
               flagEnter=0;
               flagMostrar=1;
               tarea_programa=2;
            }
            else if(tarea_programa==2)
            {
               num1=conversion(buffer,9);
               contador_buf=0;
               flagSerial=0;
               flagEnter=0;
               flagMostrar=1;
               tarea_programa=3;
            }
            else if(tarea_programa==3)
            {
               num2=conversion(buffer,9);
               tarea_programa=4;
               contador_buf=0;
               flagMostrar=1;
               flagSerial=0;
               flagEnter=0;
               
            }
         }
         if(tarea_programa==4)
         {
            resultado=operacion(opcion_ingresada,num1,num2);
            printf("\nEl resultado es: %.4f\n",resultado);
            flagSerial=0;
            tarea_programa=1;    
         }
   }
   
}


