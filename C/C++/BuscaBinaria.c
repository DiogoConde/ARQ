#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char**argv)
{
	FILE *arquivo;
	Endereco e;
	int quantidade;
	int contador;
	long tamanhoArquivo, posicao, inicio, fim, meio;

    if(argc!=2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

    int contador = 0; //  contador inicializado como 0
	printf("Tamanho do Registro: %ld\n\n", sizeof(Endereco));
	arquivo = fopen("cep_ordenado.dat","r"); //  abrindo o arquivo com os ceps ordenados
	fseek(arquivo,0,SEEK_END); //  vai ate o final do arquivo
	tamanhoArquivo = ftell(arquivo); //  atribui ao tamanhoArquivo o valor do ultimo byte
	fseek(f,0,SEEK_SET); //  volta ao inicio do arquivo
	printf("Tamanho do Arquivo: %ld\n", tamanhoArquivo);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", tamanhoArquivo/sizeof(Endereco));
	inicio = 0; //	inicio tem valor 0
	fim = (tamanhoArquivo/sizeof(Endereco))-1; //  fim se iguala ao numero de registros menos 1, como a primeira seria 0
	while(inicio<=fim){ // repete as comparacoes ate que nao ache o valor no ultimo restante
		contador++; // atualiza o valor do contador
		meio = (inicio+fim)/2; //  meio seria metade do valor da soma do inicial com a ultima 
        fseek(arquivo, meio * sizeof(Endereco), SEEK_SET); // move para o meio do arquivo
		fread(&e,sizeof(Endereco),1,arquivo);
		if(strncmp(argv[1],e.cep,8)==0) // if(argv[1] == e.cep)
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		}
	    else if(strncmp(argv[1],e.cep,8)>0)// caso o procurado seja maior que o corrente
		{
		  inicio=meio+1; //o novo inicio se torna o registro imediatamente superior ao meio atual
		}
		else if(strncmp(argv[1],e.cep,8)<0)// caso o procurado seja menor que o corrente 
		{
		  fim=meio-1; // o novo fim se torna o registro imediatamente anterior ao meio atual
		}
	}
	if (inicio>fim){
		printf("O cep nao esta no arquivo");
	}
	printf("Total Lido: %d\n", contador);
	fclose(arquivo);
}