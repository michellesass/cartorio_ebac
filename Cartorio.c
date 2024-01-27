#include <stdio.h> //biblioteca de comunica��o com o usu�rio
#include <stdlib.h> //biblioteca de aloca��o de espa�o em mem�ria (vari�veis)
#include <locale.h> //biblioteca de aloca��es de texte por regi�o (acentos)
#include <string.h> //biblioteca resposns�vel por cuidar das strings

// Fun��o para validar se uma string cont�m apenas d�gitos
int validaDigitos(const char *str) {
    int i;  
    for (i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;  // Retorna 0 se encontrar algum caractere que n�o � d�gito
        }
    }
    return 1;  // Retorna 1 se todos os caracteres forem d�gitos
}

// Fun��o para validar o CPF
int validaCPF(const char *cpf) {
    // CPF deve ter 11 d�gitos
    if (strlen(cpf) != 11) {
        return 0;
    }

    // Verifica se todos os caracteres s�o d�gitos
    if (!validaDigitos(cpf)) {
        return 0;
    }

    return 1;  // CPF v�lido
} 

// Fun��o para validar se uma string cont�m apenas letras
int validaLetras(const char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) {
            return 0;  // Retorna 0 se encontrar algum caractere que n�o � letra nem espa�o
        }
    }
    return 1;  // Retorna 1 se todos os caracteres forem letras ou espa�os
}

void converterParaMaiuscula(char *str) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);  // Converte cada caractere para mai�sculo
    }
}


int registro(){ //Fun��o respons�vel por cadastrar os usu�rios no sistema
	
	setlocale(LC_ALL, "Portuguese"); //Definindo a linguagem
	
	//In�cio da cria��o de vari�veis(string)
	char arquivo[40];
	char cpf[40];
	char nome[40];
	char sobrenome[40];
	char cargo[40];
	//Final da cria��o de vari�veis(string)
	
	printf("Digite o CPF a ser cadastrado: "); //Coletando informa��o do usu�rio
	scanf("%s", cpf); //%s refere-se ao armazenamento de string
	
	int x = 0;
	while (cpf[x] != '\0') {
    	if (!isdigit(cpf[x])) {
        	printf("\nCPF inv�lido. Por favor, insira apenas n�meros.\n\n");
        	system("pause");
        	return 0;
    	}
    	x++;
	}
	
	
	strcpy(arquivo, cpf); //Respons�vel por copiar os valores das strings
	
	FILE *file; //Cria o arquivo
	file = fopen(arquivo, "w"); //Cria o arquivo e o "W" significa escrever
	fprintf(file, cpf); //Salvando os dados no arquivo, n�o mandando para o computador executar, ou seja, montando o banco de dados.
	fclose(file); //Fechar o arquivo
	
	file = fopen(arquivo, "a");
	fprintf(file, ",");
	fclose(file);
	
	printf("Digite o nome a ser cadastrado: ");
	scanf("%s", nome);
	
	 if (!validaLetras(nome)) {
        printf("\nNome inv�lido. Por favor, insira apenas letras.\n\n");
        system("pause");
        return 0;
    }
	
	converterParaMaiuscula(nome);
	
	file = fopen(arquivo, "a"); //"a" porque o dado est� sendo atualizado, n�o � um dado novo, exclusivo, � uma atualiza��o de um que j� existia.
	fprintf(file, nome);
	fclose(file);
	
	file = fopen(arquivo, "a");
	fprintf(file, ",");
	fclose(file);
	
	printf("Digite o sobrenome a ser cadastrado: ");
	scanf("%s", sobrenome);
	
	 if (!validaLetras(sobrenome)) {
        printf("\nSobrenome inv�lido. Por favor, insira apenas letras.\n\n");
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
        printf("\nCargo inv�lido. Por favor, insira apenas letras.\n\n");
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
        printf("\nN�o foi poss�vel abrir o arquivo. Arquivo n�o localizado.\n\n");
    } else {
        printf("\nEssas s�o as informa��es do usu�rio: \n");

        // L� cada campo separado por v�rgula e imprime como uma lista com r�tulos
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
	
	printf("Digite o CPF do usu�rio a ser deletado: ");
	scanf("%s", cpf); 
	
	FILE *file;
	file = fopen(cpf, "r");
	
	if(file == NULL){
		printf("\nO usu�rio n�o se encontra no sistema! \n\n");
		system("pause");
	}
	
	else{
		remove(cpf);
		printf("\nUsu�rio deletado com sucesso! \n\n");	
		system("pause");
	}
	
}



int main(){
	
	int opcao = 0; //Definindo as vari�veis
	int laco = 1;
	
	for(laco = 1; laco == 1;){ //In�cio do la�o de repeti��o (sempre volta ao menu)
		
		system("cls");
		
		setlocale(LC_ALL, "Portuguese"); //Definindo a linguagem
	
		printf("### Cart�rio da EBAC ### \n\n"); //In�cio do menu
		printf("Escolha a op��o desejada do menu: \n\n");
		printf("\t1- Registrar nomes \n");
		printf("\t2- Consultar nomes \n");
		printf("\t3- Deletar nomes \n\n"); 
		printf("Op��o: ");//Fim do menu
	
		scanf("%d", &opcao); //Armazenando a escolha do usu�rio
	
		system("cls"); //Respons�vel por limpar a tela
		
		switch(opcao){ //In�cio da escolha de op��es
			case 1: 
				registro(); //chamada de fun��es
				break;
			
			case 2:
				consulta();
				break;
			
			case 3:
				deletar();
				break;
							
			default:
				printf("Essa op��o n�o est� dispon�vel.\n\n");
				system("pause");
				break;						
		} //Fim do switch (esolha das op��es)
	
	} //Fim do la�o de repeti��o
	
} //Fim do programa
