/*serial.h*/

/*Diferentes funciones a utilizar*/

/*Deacuerdo a la tarea enviada y el estado de la bandera mostrar es la tarea que mandara*/
void mostrar (int &tarea_programa, int &flagMostrar);
void llenar(char buffer, int &contador_buf, char *caracter_recibido, int *flagEnter);

/*Declarando la interrupcion para la recepcion de datos del sistema*/
//#INT_RDA

//void(isrRDA)(char buffer, int &contador_buf, char *caracter_recibido, int &flagEnter, int &flagEcho,int &flagSerial);

