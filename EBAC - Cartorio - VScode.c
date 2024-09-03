#include <stdio.h>  //Biblioteca de comunica��o com o usu�rio
#include <stdlib.h> //Biblioteca de aloca��o de espa�os em mem�ria
#include <locale.h> //Biblioteca de aloca��o de textos por regi�o
#include <string.h> //Biblioteca respons�vel pelas strings
#include <windows.h> //Biblioteca pra arrumar a acentua��o do meu VScode

// Inicia��o das subfun��es
int MenuDeEscolhas(void);
int ValidacaoEscolhas(void);
int RegistrarNomes(void);
int ConsultarNomes(void);
int DeletarNomes(void);
int validarCPFNumerico(char cpf[]);
// In�cio do programa
int main()
{
    SetConsoleCP(1250);           // Define a p�gina de c�digo para entrada (input)
    SetConsoleOutputCP(1250);     // Define a p�gina de c�digo para sa�da (output)
    
    ValidacaoEscolhas(); // Chama a primeira Sub

    system("cls");
    printf("\n\n Esse Software foi desenvolvido por Bruno B. \n\n");
    system("pause"); // espera um input do usu�rio antes de continuar o programa, evita que termine cedo
    return 0;
};
// Fim Main

// subFun��o 01: Valida��o de escolhas do menu ---------------------------------------------------------------------------------------------
int ValidacaoEscolhas(void)
{
    // inicia��o vari�veis
    int opcao_escolhida = 0;
    //

    while (opcao_escolhida == 0)
    {

        opcao_escolhida = MenuDeEscolhas(); // Chama a subfun��o que pergunta e recebe resposta

        switch (opcao_escolhida)
        {       // compara resposta com escolhas poss�veis
        case 1: // op��o: Registrar Nomes
            system("cls");
            RegistrarNomes(); // Chamada Sub 3
            opcao_escolhida = 0;
            system("cls");
            break;
        case 2: // Op��o: Consultar Nomes
            system("cls");
            ConsultarNomes(); // Chamada Sub 4
            opcao_escolhida = 0;
            system("cls");
            break;
        case 3: // Op��o: Deletar Nomes
            system("cls");
            DeletarNomes(); // Chamada Sub 5
            opcao_escolhida = 0;
            system("cls");
            break;
        case 4: // Op��o: Finalizar Programa
            return 0;
            break;
        default: // Retorna o valor "0" como valor padr�o para repetir a pergunta
            opcao_escolhida = 0;
            system("cls");
            printf("\n- - - - - - por favor escolha dentre as 4 op��es!! - - - - - -\n\n");
            break;
        };
    };
    return (0);
};
// Fim Sub 01

// subFun��o 02: menu, pergunta e armazenamento da resposta --------------------------------------------------------------------------------
int MenuDeEscolhas(void)
{
    // Inicia��o vari�veis
    int opcao_sub = 123;
    //

    printf("### Cart�rio da EBAC ###\n\n"); // Menu e pergunta
    printf("Escolha a op��o desejada do menu:\n\n");
    printf("\t1 - Registrar nomes\n");
    printf("\t2 - Consultar nomes\n");
    printf("\t3 - Deletar nomes \n");
    printf("\t4 - Finalizar programa \n\n");
    printf("Op��o:  ");

    if (scanf("%d", &opcao_sub) != 1) // verifica se a resposta � um n�mero (Int)
    {
        while (getchar() != '\n')
            ;     // evita um loop infinito no buffer por causa da resposta
        return 0; // retorna "0" for�ando a repeti��o da sub se for inv�lido
    };
    return opcao_sub; // retorna a resposta escolhida
}
// Fim Sub 02

// SubFun��o 03: Registra novos nomes na lista ---------------------------------------------------------------------------------------------
int RegistrarNomes(void)
{
    // inicia��o vari�veis
    char CPF[12];
    char arquivo[40];
    char nome[20];
    char sobrenome[40];
    char cargo[20];
    int SimNao = 0;
    FILE *file;
    //
    printf("\n\t[Op��o 1] - REGISTRAR NOVOS NOMES\n\n");

    // Come�a a receber as informa��es
    do
    {
        printf("Digite o CPF a ser cadastrado: ");
        scanf("%s", CPF);

        // Valida��o do tamanho do CPF
        if (strlen(CPF) != 11)
        {
            printf("\nPor favor, insira um CPF v�lido (11 d�gitos)!\n");
            continue; // Volta ao in�cio do loop se o CPF n�o tiver 11 d�gitos
        }

        // Valida��o de caracteres num�ricos
        if (!validarCPFNumerico(CPF))
        {
            printf("\nPor favor, insira um CPF v�lido (apenas n�meros)!\n");
            continue; // Volta ao in�cio do loop se o CPF n�o for num�rico
        }

        // Verifica se o arquivo com o nome do CPF j� existe
        file = fopen(CPF, "r");
        if (file != NULL)
        {
            fclose(file); // Fecha o arquivo se ele existir
            printf("\nEste CPF j� est� registrado!\n");
        }
        else
        {
            break; // CPF v�lido e n�o registrado, sai do loop
        }
    } while (1);

    printf("\n\nDigite o nome a ser cadastrado: ");
    scanf("%s", nome);

    printf("\n\nDigite o sobrenome: ");
    getchar();
    fgets(sobrenome, sizeof(sobrenome), stdin); // Remove o ('\n') pra poder usar sobrenomes com espa�os ex ("Dos Santos)
    sobrenome[strcspn(sobrenome, "\n")] = '\0';

    printf("\n\nDigite o cargo: ");
    scanf("%s", cargo);
    //

    strcpy(arquivo, CPF);

    file = fopen(arquivo, "w"); // abre o arquivo e edita o nome

    fprintf(file, CPF); // salva o valor da vari�vel CPF no arquivo
    fprintf(file, ",");
    fprintf(file, nome); // salva o valor da vari�vel nome no arquivo
    fprintf(file, ",");
    fprintf(file, sobrenome); // salva o valor da vari�vel sobrenome no arquivo
    fprintf(file, ",");
    fprintf(file, cargo); // salva o valor da vari�vel cargo no arquivo
    fclose(file);         // fecha o arquivo

    printf("\n\nGostaria de registrar outro nome? (1 = SIM) ou (2 = N�O)\n");
    while (SimNao != 1 && SimNao != 2)
    {
        scanf("%d", &SimNao);
        if (SimNao != 1)
        {
            while (getchar() != '\n')
                ; // evita um loop infinito no buffer por causa da resposta
            printf("\nPor favor responda com (1 = SIM) ou (2 = N�O)\n");
        };
    };

    if (SimNao == 1)
    {
        system("cls");
        RegistrarNomes();
    };
    return (0);
}
// Fim Sub 03

// SubFun��o 04: Consulta os nomes da lista ------------------------------------------------------------------------------------------------
int ConsultarNomes(void)
{
    // inicia��o vari�veis
    char cpf[12];
    char conteudo[200];
    int SimNao = 0;
    //

    printf("\n\t[Op��o 2] - CONSULTA DE NOMES\n\n");
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);

    FILE *file;
    file = fopen(cpf, "r"); // tenta ler o file do cpf
       if (file == NULL)
    {
        printf("\n\n- - - CPF n�o encontrado no sistema, Confira a escrita! - - -\n");
    }
    else
    {
        while (fgets(conteudo, 200, file) != NULL)
        {
            char *token = strtok(conteudo, ","); // Divide o conte�do usando strtok 
            printf("\nEssas s�o as informa��es do usu�rio:\n");

            if (token != NULL)
            {
                printf("\nCPF: %s\n", token); // Exibe o CPF
                token = strtok(NULL, ",");
            }
            if (token != NULL)
            {
                printf("Nome: %s\n", token); // Exibe o Nome
                token = strtok(NULL, ",");
            }
            if (token != NULL)
            {
                printf("Sobrenome: %s\n", token); // Exibe o Sobrenome
                token = strtok(NULL, ",");
            }
            if (token != NULL)
            {
                printf("Cargo: %s\n", token); // Exibe o Cargo
            }
            printf("\n");
        }
        fclose(file);
    }

    printf("\n\nGostaria de tentar consultar outro nome? (1 = SIM) ou (2 = N�O)\n");
    while (SimNao != 1 && SimNao != 2)
    {
        scanf("%d", &SimNao);
        if (SimNao != 1)
        {
            while (getchar() != '\n')
                ; // evita um loop infinito no buffer por causa da resposta
            printf("\nPor favor responda com (1 = SIM) ou (2 = N�O)\n");
        };
    };

    if (SimNao == 1)
    {
        system("cls");
        ConsultarNomes();
    };
    return (0);
};
// Fim Sub 04

// SubFun��o 05: Deleta nomes da lista -----------------------------------------------------------------------------------------------------
int DeletarNomes(void)
{
    // inicia��o vari�veis
    char cpf[12];
    int SimNao = 0;
    //

    printf("\n\t[op��o 3] - DELETAR NOMES DA LISTA\n\n");
    printf("\nDigite o CPF a ser deletado: ");
    scanf("%s", cpf);

    FILE *file;
    file = fopen(cpf, "r"); // tenta ler o file do cpf pra ver se ele existe
    if (file == NULL)
    {
        printf("\n\n- - - CPF n�o encontrado no sistema, Confira a escrita! - - -\n");
    }
    else
{
    fclose(file);
    remove(cpf);
    printf("\n\nUsu�rio do CPF [%s] Deletado.\n\n", cpf);
}

printf("\n\nGostaria de tentar deletar outro nome? (1 = SIM) ou (2 = N�O)\n");
while (SimNao != 1 && SimNao != 2)
{
    scanf("%d", &SimNao);
    if (SimNao != 1)
    {
        while (getchar() != '\n')
            ; // evita um loop infinito no buffer por causa da resposta
        printf("\nPor favor responda com (1 = SIM) ou (2 = N�O)\n");
    };
};

if (SimNao == 1)
{
    system("cls");
    DeletarNomes();
};
return (0);
};
// Fim Sub 05

// SubFun��o 06: valida se o CPF cont�m apenas n�meros -------------------------------------------------------------------------------------
int validarCPFNumerico(char cpf[])
{
     size_t i;

    // Verifica se cada caractere do CPF � um d�gito num�rico
    for (i = 0; i < strlen(cpf); i++)
    {
        if (cpf[i] < '0' || cpf[i] > '9')
        {
            return 0; // Retorna 0 se encontrar algo que n�o seja n�mero
        };
    };
    return 1; // Retorna 1 se todos os caracteres forem n�meros
};
// Fim Sub 06
