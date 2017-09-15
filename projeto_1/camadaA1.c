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
#include <signal.h>
 
#define tamanho_memoria 1024 //tamanho em bytes
 

/* 

    2ª camada de A

*/

typedef struct dados{
  long tipo;
  char mensagem[100]; // Dados que serão colocados na fila
}mens;

  // Cria memória compartilhada
 char * memoria_compartilhada(){
 key_t key = ftok("calc.txt",'b');

  int id_memoria = shmget(key , tamanho_memoria, 0666 | IPC_CREAT);

  if(id_memoria == -1 ){
    printf("Erro ao criar área de memória compartilhada!!!\n");
  }
  char * id_memoria_compartilhada = shmat(id_memoria,(void*) 0, 0);

  return id_memoria_compartilhada;
}

int main() {

  char * memoria = memoria_compartilhada();

 
while(1) {
      int msqid;
      mens recebe;
       //Gera uma chave única a partir de dados de um arquivo e um caracter.
      key_t key = ftok("calc.txt",'A');
      // Cria a fila, retorna -1 para erro e em caso de sucesso retorna o identificador da fila
      msqid = msgget(key, 0666 | IPC_CREAT); // 666 (escrita e leitura) , key: chave para acesso a fila
   
      msgrcv(msqid, &recebe, sizeof(recebe), 0, 0);

      printf("===> Mensagem da fila : ");
      printf("%s\n",recebe.mensagem);
      strcpy(memoria,recebe.mensagem);

      /* 
          printf("[Pressione enter para ver proxima mensagem!!]\n");
          getchar();
          exit(0); 
      */
}
  return 0;
} 