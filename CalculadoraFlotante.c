#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1)
   #use fast_io(c)
#endif 

   char caracterRecibido;
   char banderas=0;
   #bit flagSerial = banderas.0
   
   #INT_RDA
   void isrRDA (void){
      caracterRecibido = getc();
      flagSerial=1;
   }

void main (void){
   setup_oscillator(OSC_16MHZ);
   set_tris_c(0x80); 
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
#ifdef __DEBUG_SERIAL__ //Deberiamos de proteger nuestras depuraciones de esta forma o usar una macro ya protegida.
   printf("Hola Mundo\n");//Puedes usar putc o printf. Revisa la documentación de CCS para ver que mas puedes hacer.
#endif
/*char caracter='a';*/
   while(1){
      if(flagSerial==1){
         flagSerial=0;
         putc(caracterRecibido);
      }
      /*putc(caracter);
      delay_ms(500);
      caracter++;*/
   }
}   
