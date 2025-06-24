#include "minishell.h"


// Asigna índices a los tokens
void assign_token_indexes(t_dlist *tokens)
{
    int i = 0;
    while (tokens)
    {
        tokens->index = i++;
        tokens = tokens->next;
    }
}

// Imprime los tokens para depuración
void print_tokens(t_data *data)
{
    t_dlist *tmp = data->tokens;
    while (tmp)
    {
        printf("Token: %-15s | Type: %d | Index: %d\n", tmp->str, tmp->token, tmp->index);
        tmp = tmp->next;
    }
}

int main(void)
{
    char *input;
    t_data data;

    while (1)
    {
        data.tokens = NULL;
        input = readline("[shellmi] ");
        if (!input)
            break;
        if (*input)
            add_history(input);

        // Fase de tokenización y análisis
        tokenize_input_string(input, &data);
        assign_token_indexes(data.tokens);
        strip_all_token_quotes(&data); // eliminar comillas después de tokenizar

        if (validate_token_syntax(&data) == 0)
            print_tokens(&data); // muestra tokens solo si no hay error

        free_all(&data);
        free(input);
    }
    return 0;
}
