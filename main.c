#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(__attribute__((unused)) int argc,
         __attribute__((unused)) char *argv[]) {
  /* int descrip; */
  pid_t var;
  int status;
  int salir = 0;
  FILE *pf;
  /* char nombre[100]; */
  printf("father pid %d \n", getpid());
  /* strncpy(nombre, "Mi nombre es juancito", 100); */
  pf = fopen("datos.txt", "w+");
  if (pf == NULL) {
    printf("error de apertura de archivo datos.txt ");
    return 1;
  }
  do {
    printf("do: ftell(pf): %ld\n", ftell(pf));

    if ((var = fork()) == 0) {
      int x;
      printf("*********************************************\n");
      printf("\tchild: fork(): %d\n", var);
      printf("\tchild: pid %d \n", getpid());
      printf("\tchild: father pid %d \n", getppid());
      printf("\tchild: ftell(pf): %ld\n", ftell(pf));
      printf("\tIntroduzca un numero:");
      scanf("%d", &x);
      fprintf(pf, "child (%d): x:%d\n", getpid(), x);
      fflush(pf);
      printf("\tchild: pf: %p\n", pf);
      printf("\tchild: ftell(pf): %ld\n", ftell(pf));
      printf("*********************************************\n");
      return x;

    } else {
      printf("---------------------------------------------\n");
      printf("father: fork():%d \n", var);
      /* printf("father: nombre:%s\n", nombre); */
      printf("father: ftell(pf): %ld\n", ftell(pf));
      printf("father: waitpid()...\n\n");
      waitpid(var, &status, 0);
      printf("father: ftell(pf): %ld\n", ftell(pf));
      printf("father: print line to file\n");
      fprintf(pf, "father: print line\n");
      fflush(pf);
      printf("father: ftell(pf): %ld\n", ftell(pf));
      /* printf("father: pf:%p\n", pf); */
      if (WIFEXITED(status)) {
        printf("father: child return:%d\n\n", WEXITSTATUS(status));
      }
      /* printf("father: nombre:%s\n", nombre); */
      /* strncpy(nombre, "Mi nombre es Maria", 100); */
      /* printf("El nuevo mensaje es: %s\n", nombre); */
      printf("---------------------------------------------\n");
      printf("father: end with 1...\n");
      scanf("%d", &salir);
      if (salir != 1) {
        salir = 0;
      }
    }

  } while (salir == 0);
  fclose(pf);
  return 0;
}
