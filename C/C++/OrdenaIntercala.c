#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)

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

int comparar(const void *a, const void *b)// função que recebe como parâmetros dois endereços
{
    return strncmp(((Endereco*)a)->cep,((Endereco*)b)->cep,8); // usa strncmp para comparar dígito a dígito os ceps presentes nos endereços selecionados
}

int main(int argc, char**argv)
{
    int i=1; // variável i é inicializada como 1
    long quantidade, fracaoArquivo, tamanhoArquivo; 
    FILE *f,*a, *output;
    Endereco *w, u, h;
    f = fopen("cep.dat","r"); // abrindo o arquivo com os dados de endereços para leitura
    fseek(f,0,SEEK_END); // vai até o fim do arquivo
    tamanhoArquivo = ftell(f); // atribui ao tamanho do arquivo em bytes a última posição no arquivo
    quantidade = tamanhoArquivo/sizeof(Endereco); // calcula a quantidade de endereços dividindo o tamanho do arquivo em bytes pelo tamanho de cada endereço
    fracaoArquivo = quantidade/16; // divide o arquivo em 16 partes iguais e atribui à variável fracaoArquivo
    char file1[20],file2[20],file3[20]; 
    fseek(f,0,SEEK_SET); // volta para o início do arquivo


    while(i<=16) // repete até executar 16 vezes
    { 

        w = (Endereco*) malloc(fracaoArquivo*sizeof(Endereco));// armazena na variável w o lugar onde foi alocado espaço do tamanho da fração do arquivo 
        if(fread(w,sizeof(Endereco),fracaoArquivo,f) == fracaoArquivo) // verifica se o endereço descrito em "e" foi lido
        {
              printf("O %d arquivo foi lido\n", i);// informa a leitura de uma fração do arquivo
  
        }
        qsort(w,fracaoArquivo,sizeof(Endereco),comparar); // ordena os endereços presentes na fração do arquivo
        printf("O %do arquivo já está ordenado\n", i); // informa o arquivo recentemente ordenado
        sprintf(file1,"cep%d.dat",i); // armazena o arquivo ordenado com nome Cep.dat na ordem de criação dos arquivos ordenados
        output = fopen(file1,"w"); // abre um arquivo vazio onde serão escritos os ceps ordenados
        fwrite(w,sizeof(Endereco),fracaoArquivo,output); // escreve no novo arquivo as informações dos ceps ordenados
        fclose(output); // fecha o arquivo onde foi realizada a escrita
        printf("Foi escrito no %do arquivo\n", i); // informa o arquivo onde foi escrito 
        i++; // soma 1 ao valor de i

    }
    fclose(f); // fecha o arquivo

    int n=2,m=17;

    i=1; // reseta a variável i com valor 1

    while(m<=31) // executa os comandos 16 vezes
    { 
         sprintf(file1,"cep%d.dat",i); // guarda os arquivos com numeração ímpar
         sprintf(file2,"cep%d.dat",n); // guarda os arquivos com numeração par
         sprintf(file3,"cep%d.dat",m); // guarda os nomes dos novos ceps
         f=fopen(file1,"r"); // f é definido como abrir o arquivo file1 somente para leitura
         a=fopen(file2,"r"); // g é definido como abrir o arquivo file2 somente para leitura
         output=fopen(file3,"w"); // output é definido como abrir o arquivo vazio file3 para escrita
         fread(&u,sizeof(Endereco),1,f); //lê todo o arquivo file1
         fread(&h,sizeof(Endereco),1,a); //lê todo o arquivo file2
    
             while(!feof(f)&&!feof(a)) // repete até que seja ultrapassado o fim de algum dos arquivos
            {
                  if(comparar(&u,&h)<0) // caso o valor do primeiro cep seja menor que do segundo
                  {
                     fwrite(&u,sizeof(Endereco),1,output); // escreve o menor cep no arquivo dos ceps ordenados
                     fread(&u,sizeof(Endereco),1,f); 
                  }
                else
                 {
                      fwrite(&h,sizeof(Endereco),1,output); // escreve o menor cep no arquivo dos ceps ordenados
                      fread(&h,sizeof(Endereco),1,a);
                 }
             }

        while(!feof(f)) // repete até chegar ao fim do arquivo
        {
             fwrite(&u,sizeof(Endereco),1,output);
             fread(&u,sizeof(Endereco),1,f);
        }
        while(!feof(a)) // repete até chegar ao fim do arquivo
        {
             fwrite(&h,sizeof(Endereco),1,output);
             fread(&h,sizeof(Endereco),1,a);

        } // os 2 arquivos selecionados estão combinados

        i+=2; // são somadas duas unidades ao valor de i para que lide com os arquivos ímpares
        n+=2; // são somadas duas unidades ao valor de i para que lide com os arquivos pares
        m++; // é somado 1 ao valor de m
        if(m==24)// depois de criados 8 ceps é aumentado o valor de i e n para intercalar 8 ceps em 4, 4 ceps em 2, e 2 em 1
        {
    	i=16;
    	n=17;
        }
        fclose(a);
        fclose(f); // são fechados os arquivos f, a e output
        fclose(output);

    }
    i=1; // i é resetado com valor 1
    sprintf(file1,"cep%d.dat",i); // guarda todos os arquivos gerados
}