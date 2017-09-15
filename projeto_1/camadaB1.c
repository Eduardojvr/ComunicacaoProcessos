#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <string.h>
#include <string.h>

#define tamanho_memoria 1024 //tamanho em bytes

/*

	2ª camada de B

*/
typedef struct dados{
  long tipo;
  char mensagem[100]; // Dados que serão colocados na fila

}mens;

int main(){

 // Memória compartilhada

  key_t key = ftok("calc.txt",'b');

  int id_memoria = shmget(key , tamanho_memoria, 0666 | IPC_CREAT);

  if(id_memoria == -1 ){
    printf("Erro ao criar área de memória compartilhada!!!\n");
  }
while(1){
  char * id_memoria_compartilhada = shmat(id_memoria,(void*) 0, 0); // lê da memória compartilhada

  printf("%s\n",id_memoria_compartilhada);
  
  // getchar();

  // Fila de mensagens
  	mens mens_recebida;
    int id_fila;
    mens_recebida.tipo = 2;

    strcpy(mens_recebida.mensagem,id_memoria_compartilhada);

    //Gera uma chave única a partir de dados de um arquivo e um caracter.
    key_t key2 = ftok("calc.txt",'M');
  
    // Cria a fila, retorna -1 para erro e em caso de sucesso retorna o identificador da fila
    id_fila = msgget(key2, 0666 | IPC_CREAT); // 666 (escrita e leitura) , key: chave para acesso a fila
  
    if(id_fila == -1){
      printf("Erro ao criar fila!!!\n");    
     }

    printf("Enviando para camada [B0], fila de mensagem!!\n");
    // printf("%s\n",msg.mensagem);
    msgsnd(id_fila, &mens_recebida, sizeof(mens_recebida), 0);// Identificador da fila, dados a ser colocado na fila, tamanho em bytes do dado

    printf("[Pressione enter para ver proxima mensagem!!]\n");
  	getchar();
  
}
	return 0;
}