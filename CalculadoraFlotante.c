#include <18F4620.h>
#include <stdlib.h>
#include <matematica.h>
#include <serial.c>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

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
   flagSerial=1;
   flagEcho=1;
   if(flagSerial==1)
      llenar(buffer, contador_buf, &caracter_recibido, &flagEnter);
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
         mostrar(tarea_programa,flagMostrar);
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
            else if(tarea_programa==4)
            {
               resultado=operacion(opcion_ingresada,num1,num2);
               printf("\nEl resultado es: %.4f\n",resultado);
               tarea_programa=1;
               contador_buf=0;
               flagMostrar=1;
               flagSerial=0;
               flagEnter=0;
            }
         }
   }
   
}


