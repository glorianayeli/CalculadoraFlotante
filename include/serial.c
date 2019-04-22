/*serial.c*/

/*Necesaria para utilizar la salida serial para las impresiones*/
#use delay(clock=16000000)

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif 

void mostrar (int &tarea_programa, int &flagMostrar){
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
}

/*Llena el fubber con los caracteres disponible por medio 
de la interrupcion*/
void llenar (char buffer[], int &contador_buf, char *caracter_recibido, int *flagEnter)
{
   if(contador_buf<10)
   {
      *caracter_recibido=getc();
      buffer[contador_buf]=*caracter_recibido;
      contador_buf++; 
   }
   if(*caracter_recibido==0x0D)
   {
      *flagEnter=1;
   }
   //valida backspaces  
   if(*caracter_recibido==0x08)
   {
      buffer[contador_buf-1]=0;
      buffer[contador_buf-2]=0;
      contador_buf-=2;
   }
}
/*void isrRDA (char buffer[], int &contador_buf, char *caracter_recibido, int &flagEnter, int &flagEcho,int &flagSerial)
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
}*/
