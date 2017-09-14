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

#define tamanho_memoria 1024 //tamanho em bytes

int main(){


  key_t key = ftok("/Users/eduardojunio/Documents/Unb/2-2017/FSO/projeto1.c",'b');

  int id_memoria = shmget(key , tamanho_memoria, 0666 | IPC_CREAT);

  if(id_memoria == -1 ){
    printf("Erro ao criar área de memória compartilhada!!!\n");
  }
while(1){
  char * id_memoria_compartilhada = shmat(id_memoria,(void*) 0, 0); // lê da memória compartilhada

  printf("%s\n",id_memoria_compartilhada);
  printf("[Pressione enter para ver proxima mensagem!!]\n");
  getchar();
  
}
	return 0;
}