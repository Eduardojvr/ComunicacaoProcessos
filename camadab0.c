#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <string.h>
#include <sys/shm.h>
#include <string.h>


/*

  1ª camada de B
  
*/
typedef struct dados{
  long tipo;
  char mensagem[50]; // Dados que serão colocados na fila
}mens;

int main(){
  	while(1){
  	int pid;
  	mens recebe_de_filho;
  	int id_fila;

    //Gera uma chave única a partir de dados de um arquivo e um caracter.
    key_t key = ftok("/Users/eduardojunio/Documents/Unb/2-2017/FSO/projeto1.c",'M');
  
    // Cria a fila, retorna -1 para erro e em caso de sucesso retorna o identificador da fila
    id_fila = msgget(key, 0666 | IPC_CREAT); // 666 (escrita e leitura) , key: chave para acesso a fila
  
    if(id_fila == -1){
      printf("Erro ao criar fila!!!\n");    
     }

    pid = fork();
    if(pid == 0){
        execve("camadaB1.c",NULL,0); // altera a imagem do nucleo de um processo
         // execl("camadaA1", "5", NULL);
    }
    msgrcv(id_fila, &recebe_de_filho, sizeof(recebe_de_filho), 0, 0);
    printf("mensagem recebida do filho (camada B1)\n");
    printf("%s\n",recebe_de_filho.mensagem);
    // exit(0);
}
  return 0;
}