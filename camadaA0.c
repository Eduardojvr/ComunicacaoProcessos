#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>   
#include <sys/ipc.h>   
#include <string.h>   
#include <signal.h> 
#include <unistd.h>   

 /* 

    1ª camada de A

*/
typedef struct dados{
  long tipo;
  char mensagem[50]; // Dados que serão colocados na fila
}mens;

int main() {
  char aux[50];
  int ax = 0;
while(1){
    mens msg;
    // printf("Digite uma mensagem:\n");
    scanf("%s",aux);
    strcpy(msg.mensagem,aux);
    msg.tipo = 2;
    int pid;

    int id_fila;

    //Gera uma chave única a partir de dados de um arquivo e um caracter.
    key_t key = ftok("/Users/eduardojunio/Documents/Unb/2-2017/FSO/projeto1.c",'A');
  
    // Cria a fila, retorna -1 para erro e em caso de sucesso retorna o identificador da fila
    id_fila = msgget(key, 0666 | IPC_CREAT); // 666 (escrita e leitura) , key: chave para acesso a fila
  
    if(id_fila == -1){
      printf("Erro ao criar fila!!!\n");    
     }

    printf("Enviando para camada [A1], fila de mensagem!!\n");
    // printf("%s\n",msg.mensagem);
    msgsnd(id_fila, &msg, sizeof(msg), 0);// Identificador da fila, dados a ser colocado na fila, tamanho em bytes do dado

    pid = fork();
    if(pid == 0){
        execve("camadaA1.c",NULL,0); // altera a imagem do nucleo de um processo
         // execl("camadaA1", "5", NULL);
    }
  }
   return 0;
 }