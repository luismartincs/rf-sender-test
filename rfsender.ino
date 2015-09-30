/*
EMISOR
 
Envia los mensajes "Apagar" y "Encender" en intervalos de un segundo
 
Escrito por Nano en beneficio de los seres humanos
www.robologs.net
*/
 
#include <VirtualWire.h>
#include <string.h>

char ID = '0';
String cmd;
 
byte comando[VW_MAX_MESSAGE_LEN];
byte comandoLenght = VW_MAX_MESSAGE_LEN;
char cmdchar[VW_MAX_MESSAGE_LEN];
 
void setup()
{
  //Iniciamos el Serial y la comunicacion por radio
  Serial.begin(9600);
  Serial.write("Sistema encendido\n");
  //vw_set_tx_pin(4);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_rx_start();
}
void loop()
{
  
  
  if (Serial.available()>0) {             
   // cmd = Serial.readStringUntil('\n');
    //Serial.println(cmd);
    Serial.readBytes(cmdchar,VW_MAX_MESSAGE_LEN);
    Serial.println(cmdchar);
    enviarPosicion();
  }
    
    /* if (vw_get_message(comando, &comandoLenght))
      {
        Serial.println("Se recibio un mensaje");
        char tipoMensaje = (char)comando[0];
        Serial.println(tipoMensaje);
       
         if(tipoMensaje == 'U'){
          if(comando[2] == ID){
            Serial.println("Instruccion para mi");
            delay(500);
            enviarPosicion();
          }
        }
                
      }*/
      
      //enviarPosicion();
      delay(1000);
      
}

void enviarPosicion(){

  char *command= "U0V11110111N00";

  Serial.println("Enviado"); 
  Serial.println(cmdchar);
  vw_send((uint8_t *)cmdchar, strlen(cmdchar));
  vw_wait_tx();
}

void send(char id,char i1){

  char command[13];
  memset(command,0, sizeof(command));
  
  int i;
  
  for(i=0; i < 12; i++){
    command[i] = '0';
  }
  
  command[0] = 'S';
  command[1] = id;
  command[2] = 'S';
  
  command[3] = i1;
  
  vw_send((uint8_t *)command, strlen(command));
  vw_wait_tx();
  
  Serial.println(command);
}
 
void send_togroup(char gid,char i1){
  
  char command[13];
  memset(command,0, sizeof(command));
  
  int i;
  
  for(i=0; i < 12; i++){
    command[i] = '0';
  }
  
  command[0] = 'G';
  command[1] = gid;
  command[2] = 'S';
  
  command[3] = i1;
  
  vw_send((uint8_t *)command, strlen(command));
  vw_wait_tx();
  
  Serial.println(command);
  
}

void send_toall(char i1){
  char command[13];
  memset(command,0, sizeof(command));
  
  int i;
  
  for(i=0; i < 12; i++){
    command[i] = '0';
  }
  
  command[0] = 'B';
  command[1] = '0';
  command[2] = 'S';
  
  command[3] = i1;
  
  vw_send((uint8_t *)command, strlen(command));
  vw_wait_tx();
  
  Serial.println(command);
}
 /*
void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message)); //Envia el mensaje
  vw_wait_tx(); //Espera hasta que se haya acabado de transmitir todo
  
  Serial.println(message); //Muestra el mensaje por Serial
} */
