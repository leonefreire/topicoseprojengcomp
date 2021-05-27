#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <io.h>
#include <sys/stat.h>
#include <signal.h>

int isFileExistsAccess(const char *path);

void handler(int);

int
main(void)
{
    char path[100];
	printf("Insira o diretório que deve ser monitorado: ");
    scanf("%s", path);
	
	
	// Checa se um arquivo existe ou não usando a função access() 
	int isFileExistsAccess(const char *path) {
		if (access(path, F_OK) == -1)
			return 0;

		return 1;
	}
	
	int i;
    char c;
    pid_t pid;

    // Cria o processo A (background)
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Código executado no processo A (background) (fork retornou zero)
        // Checa se o arquivo existe ou não
		if (isFileExistsAccess(path)) {
			if (signal(SIGUSR1, handler) == SIG_ERR) {
				fprintf(stderr, "Não foi possível definir um manipulador para SIGUSR1\n");
				exit(1);
			}
			
			// Aguarda a chegada do sinal
			for (;;)
			pause();
		}
		else {
			exit(0);
		}

		return 0;
    }
    else {
        // Código executado no processo B (foreground)
        printf("Ok");
        }
    }

    // Código executado nos dois processos (ex: é executado 2 vezes)
    write(1, "\n", 1);
    exit(0);
}

void
handler(int sig)
{
    // Imprime o que foi recebido
    psignal(sig, "Sinal Recebido");
}
