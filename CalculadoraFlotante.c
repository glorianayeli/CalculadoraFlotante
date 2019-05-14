#include <18F4620.h>
#include <stdlib.h>
#include <matematica.h>
#include <serial.c>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

//declarion de variables de almacenamiento
char OpcionIngresada;

//banderas
int TareaPrograma=1;
char Bandera;
//echo


//operaciones aritmeticas
float num1,num2,resultado;
#bit FlagSerial = Bandera.0
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
         if(FlagEcho==1)
         {
            putc(CaracterRecibido);
            FlagEcho=0;
         }
         if(FlagSerial == 1){
            llenar(Buffer, ContadorBuf, &CaracterRecibido, &FlagEnter);
         }
         mostrar(TareaPrograma,FlagMostrar);
         if(FlagSerial==1&&FlagEnter==1)
         {
            if(TareaPrograma==1)
            {
               OpcionIngresada=Buffer[0];
               if(OpcionIngresada==('s'||'S')||OpcionIngresada==('r'||'R')||OpcionIngresada==('d'||'D')||OpcionIngresada==('m'||'M'))
               {
                  TareaPrograma=2;
               }
               else 
               {
                  TareaPrograma=1;
               }
               ContadorBuf=0;
               FlagSerial=0;
               FlagEnter=0;
               FlagMostrar=1;              
            }
            else if(TareaPrograma==2)
            {
            if(ContadorBuf>9)
            {
            
                TareaPrograma=2;
            }
            else
            {
                for(int i=0; i<=9; i++)
                {
                    if(Buffer[i]>=65 && Buffer[i]<=122)
                    {
                        printf("ERROR");
                    }
                }
              }
               num1=Conversion(Buffer,9);
               TareaPrograma=3;
            }
               ContadorBuf=0;
               FlagSerial=0;
               FlagEnter=0;
               FlagMostrar=1;           
            }
            else if(TareaPrograma==3)
            {
            if(ContadorBuf>9)
            {
                TareaPrograma=3;
            }
            else
            {
               num2=Conversion(Buffer,9);
               TareaPrograma=4;
            }
               if((OpcionIngresada=='d'||OpcionIngresada=='D')&&(num2==0))
               {  
                  printf("ERROR");
               }
               ContadorBuf=0;
               FlagMostrar=1;
               FlagSerial=0;
               FlagEnter=0;
               
            }
            else if(TareaPrograma==4)
            {
               resultado=operacion(OpcionIngresada,num1,num2);
               printf("\nEl resultado es: %.4f\n",resultado);
               TareaPrograma=1;
               ContadorBuf=0;
               FlagMostrar=1;
               FlagSerial=0;
               FlagEnter=0;
            }
         }
   }
   
