#include "minishell.h"

void assign_token_indexes(t_dlist *tokens)
{
    int i = 0;
    while (tokens)
    {
        tokens->index = i++;
        tokens = tokens->next;
    }
}

const char *token_type_to_str(enum e_type type)
{
    switch (type)
    {
        case CMD: return "CMD";
        case PARAM: return "PARAM";
        case PIPE: return "PIPE";
        case FILENAME: return "FILENAME";
        case INF: return "INF";
        case OUTF: return "OUTF";
        case OUTF_APD: return "OUTF_APD";
        case HERE_DOC: return "HERE_DOC";
        case LIMITER: return "LIMITER";
        case UNKNOWN: return "UNKNOWN";
        default: return "NA";
    }
}

void debug_print_tokens(t_dlist *tokens, const char *title)
{
    t_dlist *tmp = tokens;
    printf(CYAN "\n🔍 %s\n" RESET, title);
    while (tmp)
    {
        printf("📦 Token[%d]: %-20s | Tipo: %-10s | Prev: %-10s | Next: %-10s\n",
               tmp->index,
               tmp->str ? tmp->str : "(null)",
               token_type_to_str(tmp->token),
               tmp->prev ? tmp->prev->str : "NULL",
               tmp->next ? tmp->next->str : "NULL");
        tmp = tmp->next;
    }
}

void load_env(char **envp, t_data *data)
{
    int i = 0;
    t_dlist *node;

    while (envp[i])
    {
        node = newnode(ft_strdup(envp[i]));
        if (!node)
            check_memory_failure(data, node, NULL, 1);
        node_addback(&data->env, node);
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
    char *line;

    (void)argc;
    (void)argv;
    ft_bzero(&data, sizeof(t_data));
    load_env(envp, &data);

    while (1)
    {
        data.tokens = NULL;
        line = readline(SHELLPRMPT);
        if (!line)
            break;
        if (check_empty_input(line))
        {
            free(line);
            continue;
        }
        if (check_quotes(line))
        {
            printf(RED "Syntax error: unclosed quote\n" RESET);
            free(line);
            continue;
        }

        data.input = fix_input(line, &data);
        printf(YELLOW "\n🧾 Entrada procesada: \"%s\"\n" RESET, data.input);

        tokenize_input_string(data.input, &data);
        assign_token_indexes(data.tokens);
        debug_print_tokens(data.tokens, "Después de tokenización");

        expand_all_tokens(&data);
        debug_print_tokens(data.tokens, "Después de expansión de variables");

        strip_all_token_quotes(&data);
        debug_print_tokens(data.tokens, "Después de eliminar comillas");

        if (!validate_token_syntax(&data))
        {
            printf(GREEN "\n✅ Sintaxis válida. Estructura lista para ejecución.\n" RESET);
        }
        else
        {
            printf(RED "\n❌ Error de sintaxis.\n" RESET);
            data.exit_status = 258;
        }

        free_all(&data);
    }

    printf("\nBye!\n");
    return (data.exit_status);
}
