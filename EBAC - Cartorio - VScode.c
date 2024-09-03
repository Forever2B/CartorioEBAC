#include <stdio.h>  //Biblioteca de comunicação com o usuário
#include <stdlib.h> //Biblioteca de alocação de espaços em memória
#include <locale.h> //Biblioteca de alocação de textos por região
#include <string.h> //Biblioteca responsável pelas strings
#include <windows.h> //Biblioteca pra arrumar a acentuação do meu VScode

// Iniciação das subfunções
int MenuDeEscolhas(void);
int ValidacaoEscolhas(void);
int RegistrarNomes(void);
int ConsultarNomes(void);
int DeletarNomes(void);
int validarCPFNumerico(char cpf[]);
// Início do programa
int main()
{
    SetConsoleCP(1250);           // Define a página de código para entrada (input)
    SetConsoleOutputCP(1250);     // Define a página de código para saída (output)
    
    ValidacaoEscolhas(); // Chama a primeira Sub

    system("cls");
    printf("\n\n Esse Software foi desenvolvido por Bruno B. \n\n");
    system("pause"); // espera um input do usuário antes de continuar o programa, evita que termine cedo
    return 0;
};
// Fim Main

// subFunção 01: Validação de escolhas do menu ---------------------------------------------------------------------------------------------
int ValidacaoEscolhas(void)
{
    // iniciação variáveis
    int opcao_escolhida = 0;
    //

    while (opcao_escolhida == 0)
    {

        opcao_escolhida = MenuDeEscolhas(); // Chama a subfunção que pergunta e recebe resposta

        switch (opcao_escolhida)
        {       // compara resposta com escolhas possíveis
        case 1: // opção: Registrar Nomes
            system("cls");
            RegistrarNomes(); // Chamada Sub 3
            opcao_escolhida = 0;
            system("cls");
            break;
        case 2: // Opção: Consultar Nomes
            system("cls");
            ConsultarNomes(); // Chamada Sub 4
            opcao_escolhida = 0;
            system("cls");
            break;
        case 3: // Opção: Deletar Nomes
            system("cls");
            DeletarNomes(); // Chamada Sub 5
            opcao_escolhida = 0;
            system("cls");
            break;
        case 4: // Opção: Finalizar Programa
            return 0;
            break;
        default: // Retorna o valor "0" como valor padrão para repetir a pergunta
            opcao_escolhida = 0;
            system("cls");
            printf("\n- - - - - - por favor escolha dentre as 4 opções!! - - - - - -\n\n");
            break;
        };
    };
    return (0);
};
// Fim Sub 01

// subFunção 02: menu, pergunta e armazenamento da resposta --------------------------------------------------------------------------------
int MenuDeEscolhas(void)
{
    // Iniciação variáveis
    int opcao_sub = 123;
    //

    printf("### Cartório da EBAC ###\n\n"); // Menu e pergunta
    printf("Escolha a opção desejada do menu:\n\n");
    printf("\t1 - Registrar nomes\n");
    printf("\t2 - Consultar nomes\n");
    printf("\t3 - Deletar nomes \n");
    printf("\t4 - Finalizar programa \n\n");
    printf("Opção:  ");

    if (scanf("%d", &opcao_sub) != 1) // verifica se a resposta é um número (Int)
    {
        while (getchar() != '\n')
            ;     // evita um loop infinito no buffer por causa da resposta
        return 0; // retorna "0" forçando a repetição da sub se for inválido
    };
    return opcao_sub; // retorna a resposta escolhida
}
// Fim Sub 02

// SubFunção 03: Registra novos nomes na lista ---------------------------------------------------------------------------------------------
int RegistrarNomes(void)
{
    // iniciação variáveis
    char CPF[12];
    char arquivo[40];
    char nome[20];
    char sobrenome[40];
    char cargo[20];
    int SimNao = 0;
    FILE *file;
    //
    printf("\n\t[Opção 1] - REGISTRAR NOVOS NOMES\n\n");

    // Começa a receber as informações
    do
    {
        printf("Digite o CPF a ser cadastrado: ");
        scanf("%s", CPF);

        // Validação do tamanho do CPF
        if (strlen(CPF) != 11)
        {
            printf("\nPor favor, insira um CPF válido (11 dígitos)!\n");
            continue; // Volta ao início do loop se o CPF não tiver 11 dígitos
        }

        // Validação de caracteres numéricos
        if (!validarCPFNumerico(CPF))
        {
            printf("\nPor favor, insira um CPF válido (apenas números)!\n");
            continue; // Volta ao início do loop se o CPF não for numérico
        }

        // Verifica se o arquivo com o nome do CPF já existe
        file = fopen(CPF, "r");
        if (file != NULL)
        {
            fclose(file); // Fecha o arquivo se ele existir
            printf("\nEste CPF já está registrado!\n");
        }
        else
        {
            break; // CPF válido e não registrado, sai do loop
        }
    } while (1);

    printf("\n\nDigite o nome a ser cadastrado: ");
    scanf("%s", nome);

    printf("\n\nDigite o sobrenome: ");
    getchar();
    fgets(sobrenome, sizeof(sobrenome), stdin); // Remove o ('\n') pra poder usar sobrenomes com espaços ex ("Dos Santos)
    sobrenome[strcspn(sobrenome, "\n")] = '\0';

    printf("\n\nDigite o cargo: ");
    scanf("%s", cargo);
    //

    strcpy(arquivo, CPF);

    file = fopen(arquivo, "w"); // abre o arquivo e edita o nome

    fprintf(file, CPF); // salva o valor da variável CPF no arquivo
    fprintf(file, ",");
    fprintf(file, nome); // salva o valor da variável nome no arquivo
    fprintf(file, ",");
    fprintf(file, sobrenome); // salva o valor da variável sobrenome no arquivo
    fprintf(file, ",");
    fprintf(file, cargo); // salva o valor da variável cargo no arquivo
    fclose(file);         // fecha o arquivo

    printf("\n\nGostaria de registrar outro nome? (1 = SIM) ou (2 = NÃO)\n");
    while (SimNao != 1 && SimNao != 2)
    {
        scanf("%d", &SimNao);
        if (SimNao != 1)
        {
            while (getchar() != '\n')
                ; // evita um loop infinito no buffer por causa da resposta
            printf("\nPor favor responda com (1 = SIM) ou (2 = NÃO)\n");
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

// SubFunção 04: Consulta os nomes da lista ------------------------------------------------------------------------------------------------
int ConsultarNomes(void)
{
    // iniciação variáveis
    char cpf[12];
    char conteudo[200];
    int SimNao = 0;
    //

    printf("\n\t[Opção 2] - CONSULTA DE NOMES\n\n");
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);

    FILE *file;
    file = fopen(cpf, "r"); // tenta ler o file do cpf
       if (file == NULL)
    {
        printf("\n\n- - - CPF não encontrado no sistema, Confira a escrita! - - -\n");
    }
    else
    {
        while (fgets(conteudo, 200, file) != NULL)
        {
            char *token = strtok(conteudo, ","); // Divide o conteúdo usando strtok 
            printf("\nEssas são as informações do usuário:\n");

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

    printf("\n\nGostaria de tentar consultar outro nome? (1 = SIM) ou (2 = NÃO)\n");
    while (SimNao != 1 && SimNao != 2)
    {
        scanf("%d", &SimNao);
        if (SimNao != 1)
        {
            while (getchar() != '\n')
                ; // evita um loop infinito no buffer por causa da resposta
            printf("\nPor favor responda com (1 = SIM) ou (2 = NÃO)\n");
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

// SubFunção 05: Deleta nomes da lista -----------------------------------------------------------------------------------------------------
int DeletarNomes(void)
{
    // iniciação variáveis
    char cpf[12];
    int SimNao = 0;
    //

    printf("\n\t[opção 3] - DELETAR NOMES DA LISTA\n\n");
    printf("\nDigite o CPF a ser deletado: ");
    scanf("%s", cpf);

    FILE *file;
    file = fopen(cpf, "r"); // tenta ler o file do cpf pra ver se ele existe
    if (file == NULL)
    {
        printf("\n\n- - - CPF não encontrado no sistema, Confira a escrita! - - -\n");
    }
    else
{
    fclose(file);
    remove(cpf);
    printf("\n\nUsuário do CPF [%s] Deletado.\n\n", cpf);
}

printf("\n\nGostaria de tentar deletar outro nome? (1 = SIM) ou (2 = NÃO)\n");
while (SimNao != 1 && SimNao != 2)
{
    scanf("%d", &SimNao);
    if (SimNao != 1)
    {
        while (getchar() != '\n')
            ; // evita um loop infinito no buffer por causa da resposta
        printf("\nPor favor responda com (1 = SIM) ou (2 = NÃO)\n");
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

// SubFunção 06: valida se o CPF contém apenas números -------------------------------------------------------------------------------------
int validarCPFNumerico(char cpf[])
{
     size_t i;

    // Verifica se cada caractere do CPF é um dígito numérico
    for (i = 0; i < strlen(cpf); i++)
    {
        if (cpf[i] < '0' || cpf[i] > '9')
        {
            return 0; // Retorna 0 se encontrar algo que não seja número
        };
    };
    return 1; // Retorna 1 se todos os caracteres forem números
};
// Fim Sub 06
