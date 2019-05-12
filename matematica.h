//Realiza la operación de dos numeros
float operacion (char opcion, float num1, float num2)
{  
   float resultado=0;
   switch(opcion)
   {
      case 's':
      case'S':
      resultado=num1+num2;
      break;
      case 'r':
      case 'R':
      resultado=num1-num2;
      break;
      case 'm':
      case 'M':
      resultado=num1*num2;
      break;
      case 'd':
      case 'D':
      resultado=num1/num2;
      break;
   }
   return resultado;
}
//Convierte una cadena en un valor entero y lo regresa
float Conversion (char vector[], int tamano)
{
   float entero;
   for(int i=0;i<=tamano;i++)
   {
      if(vector[i]==0x0D)
      {
         vector[i]=0x00;
      }
   }
   entero=atof(vector);
   return entero;
}
