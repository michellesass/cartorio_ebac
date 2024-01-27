#include <stdio.h> //biblioteca de comunicação com o usuário
#include <stdlib.h> //biblioteca de alocação de espaço em memória (variáveis)
#include <locale.h> //biblioteca de alocações de texte por região (acentos)
#include <string.h> //biblioteca resposnsável por cuidar das strings

// Função para validar se uma string contém apenas dígitos
int validaDigitos(const char *str) {
    int i;  
    for (i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;  // Retorna 0 se encontrar algum caractere que não é dígito
        }
    }
    return 1;  // Retorna 1 se todos os caracteres forem dígitos
}

// Função para validar o CPF
int validaCPF(const char *cpf) {
    // CPF deve ter 11 dígitos
    if (strlen(cpf) != 11) {
        return 0;
    }

    // Verifica se todos os caracteres são dígitos
    if (!validaDigitos(cpf)) {
        return 0;
    }

    return 1;  // CPF válido
} 

// Função para validar se uma string contém apenas letras
int validaLetras(const char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) {
            return 0;  // Retorna 0 se encontrar algum caractere que não é letra nem espaço
        }
    }
    return 1;  // Retorna 1 se todos os caracteres forem letras ou espaços
}

void converterParaMaiuscula(char *str) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);  // Converte cada caractere para maiúsculo
    }
}


int registro(){ //Função responsável por cadastrar os usuários no sistema
	
	setlocale(LC_ALL, "Portuguese"); //Definindo a linguagem
	
	//Início da criação de variáveis(string)
	char arquivo[40];
	char cpf[40];
	char nome[40];
	char sobrenome[40];
	char cargo[40];
	//Final da criação de variáveis(string)
	
	printf("Digite o CPF a ser cadastrado: "); //Coletando informação do usuário
	scanf("%s", cpf); //%s refere-se ao armazenamento de string
	
	int x = 0;
	while (cpf[x] != '\0') {
    	if (!isdigit(cpf[x])) {
        	printf("\nCPF inválido. Por favor, insira apenas números.\n\n");
        	system("pause");
        	return 0;
    	}
    	x++;
	}
	
	
	strcpy(arquivo, cpf); //Responsável por copiar os valores das strings
	
	FILE *file; //Cria o arquivo
	file = fopen(arquivo, "w"); //Cria o arquivo e o "W" significa escrever
	fprintf(file, cpf); //Salvando os dados no arquivo, não mandando para o computador executar, ou seja, montando o banco de dados.
	fclose(file); //Fechar o arquivo
	
	file = fopen(arquivo, "a");
	fprintf(file, ",");
	fclose(file);
	
	printf("Digite o nome a ser cadastrado: ");
	scanf("%s", nome);
	
	 if (!validaLetras(nome)) {
        printf("\nNome inválido. Por favor, insira apenas letras.\n\n");
        system("pause");
        return 0;
    }
	
	converterParaMaiuscula(nome);
	
	file = fopen(arquivo, "a"); //"a" porque o dado está sendo atualizado, não é um dado novo, exclusivo, é uma atualização de um que já existia.
	fprintf(file, nome);
	fclose(file);
	
	file = fopen(arquivo, "a");
	fprintf(file, ",");
	fclose(file);
	
	printf("Digite o sobrenome a ser cadastrado: ");
	scanf("%s", sobrenome);
	
	 if (!validaLetras(sobrenome)) {
        printf("\nSobrenome inválido. Por favor, insira apenas letras.\n\n");
        system("pause");
        return 0;
    }
    
    converterParaMaiuscula(sobrenome);
	
	file = fopen(arquivo, "a");
	fprintf(file, sobrenome);
	fclose(file);
	
	file = fopen(arquivo, "a");
	fprintf(file, ",");
	fclose(file);
	
	printf("Digite o cargo a ser cadastrado: ");
	scanf("%s", cargo);
	
	if (!validaLetras(cargo)) {
        printf("\nCargo inválido. Por favor, insira apenas letras.\n\n");
        system("pause");
        return 0;
    }
    
    converterParaMaiuscula(cargo);
	
	file = fopen(arquivo, "a");
	fprintf(file, cargo);
	fclose(file);
	
	system("pause");
	
	return 1;
	
}

int consulta(){
	
    setlocale(LC_ALL, "Portuguese");

    char cpf[40];
    char conteudo[200];
    const char *rotulos[] = {"CPF", "Nome", "Sobrenome", "Cargo"};

    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);

    FILE *file;
    file = fopen(cpf, "r");
    
    if (file == NULL) {
        printf("\nNão foi possível abrir o arquivo. Arquivo não localizado.\n\n");
    } else {
        printf("\nEssas são as informações do usuário: \n");

        // Lê cada campo separado por vírgula e imprime como uma lista com rótulos
        int j = 0;
        while (fscanf(file, "%[^,],", conteudo) != EOF) {
            printf("- %s: %s\n", rotulos[j], conteudo);
            j++;
        }

        printf("\n");
        fclose(file);
    }

    system("pause");
    return 0;  
		
	
}

int deletar(){
	
	char cpf[40];
	
	printf("Digite o CPF do usuário a ser deletado: ");
	scanf("%s", cpf); 
	
	FILE *file;
	file = fopen(cpf, "r");
	
	if(file == NULL){
		printf("\nO usuário não se encontra no sistema! \n\n");
		system("pause");
	}
	
	else{
		remove(cpf);
		printf("\nUsuário deletado com sucesso! \n\n");	
		system("pause");
	}
	
}



int main(){
	
	int opcao = 0; //Definindo as variáveis
	int laco = 1;
	
	for(laco = 1; laco == 1;){ //Início do laço de repetição (sempre volta ao menu)
		
		system("cls");
		
		setlocale(LC_ALL, "Portuguese"); //Definindo a linguagem
	
		printf("### Cartório da EBAC ### \n\n"); //Início do menu
		printf("Escolha a opção desejada do menu: \n\n");
		printf("\t1- Registrar nomes \n");
		printf("\t2- Consultar nomes \n");
		printf("\t3- Deletar nomes \n\n"); 
		printf("Opção: ");//Fim do menu
	
		scanf("%d", &opcao); //Armazenando a escolha do usuário
	
		system("cls"); //Responsável por limpar a tela
		
		switch(opcao){ //Início da escolha de opções
			case 1: 
				registro(); //chamada de funções
				break;
			
			case 2:
				consulta();
				break;
			
			case 3:
				deletar();
				break;
							
			default:
				printf("Essa opção não está disponível.\n\n");
				system("pause");
				break;						
		} //Fim do switch (esolha das opções)
	
	} //Fim do laço de repetição
	
} //Fim do programa
