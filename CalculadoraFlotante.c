#include <18F4620.h>
#include <stdlib.h>
#include <include/matematica.h>
#include <include/serial.c>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

//declarion de variables de almacenamiento
char opcion_ingresada;

//banderas
int tarea_programa=1;
char bandera;
//echo

//operaciones aritmeticas
float num1=0,num2=0,resultado=0;
#bit flagSerial = bandera.0
//Recepcion de datos dentro del buffer

void main (void)
{
   set_tris_c(0x80); 
   //habilito mi interrupcion
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   printf("\nIngresar una de las siguientes opciones: \n"); 
   printf("\ns)Suma \n r)Resta \n m)Multiplicacion \n d)Division\n");
   //inicio mi ciclo while
   while(1)
   {
         if(flagEcho==1)
         {
            putc(caracter_recibido);
            flagEcho=0;
         }
         if(flagSerial == 1){
            llenar(buffer, contador_buf, &caracter_recibido, &flagEnter);
         }
         mostrar(tarea_programa,flagMostrar);
         if(flagSerial==1&&flagEnter==1)
         {
            if(tarea_programa==1)
            {
                  opcion_ingresada=buffer[0];
                  if((contador_buf==2)||(contador_buf==0x0C))
                  {
                     if((opcion_ingresada=='s')||(opcion_ingresada=='S')||(opcion_ingresada=='r')||(opcion_ingresada=='R')||(opcion_ingresada=='M')||(opcion_ingresada=='m')||(opcion_ingresada=='D')||(opcion_ingresada=='d'))
                     {
                        tarea_programa=2;
                     }
                     else 
                     {
                        tarea_programa=1;
                     }
                  }
                  contador_buf=0;        
                  flagSerial=0;
                  flagEnter=0;
                  flagMostrar=1;              
            }
            else if(tarea_programa==2)
            {
               int VecEntero = 1, VecPunto=0, VecSigno=0;
               for(int i = 0; i < 11; i++){
                  if((buffer[i]>= 65) && (buffer[i] <=122))
                  {
                     VecEntero = 0;
                     for(int j=0;j<=11;j++)
                     {
                        buffer[j]='\0';
                     }
                  } 
                  if((buffer[i]==45))
                  {
                     VecSigno++;
                  }
                  if((buffer[i]==46))
                  {
                     VecPunto++;
                  }
               }
               if(contador_buf<=11&&VecEntero==1&&VecSigno<=1&&VecPunto<=1)
               {
                  num1=conversion(buffer,11);
                  tarea_programa=3;  
               }
               else
               {
                  tarea_programa=2;
               }
               contador_buf=0;
               for(int j=0;j<=11;j++)
               {
                  buffer[j]='\0';
               }
               flagMostrar=1;
               flagSerial=0;
               flagEnter=0;
            }
            else if(tarea_programa==3)
            {
               int VecEntero = 1, VecPunto=0, VecSigno=0;
               for(int i = 0; i < 11; i++){
                  if((buffer[i]>= 65) && (buffer[i] <=122))
                  {
                     VecEntero = 0;
                     for(int j=0;j<=11;j++)
                     {
                        buffer[j]='\0';
                     }
                  } 
                  if((buffer[i]==45))
                  {
                     VecSigno++;
                  }
                  if((buffer[i]==46))
                  {
                     VecPunto++;
                  }
               }
               if(contador_buf<=11&&VecEntero==1&&VecSigno<=1&&VecPunto<=1)
               {
                  num2=conversion(buffer,11);
                  tarea_programa=4;  
               }
               else
               {
                  tarea_programa=3;
               }
               if((opcion_ingresada=='d'||opcion_ingresada=='D')&&(num2==0))
               {  
                  printf("Error");
               }
               contador_buf=0;
               for(int j=0;j<=11;j++)
               {
                  buffer[j]='\0';
               }
               flagMostrar=1;
               flagSerial=0;
               flagEnter=0;
               
            }
            else if(tarea_programa==4)
            {
               resultado=operacion(opcion_ingresada,&num1,&num2);
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


