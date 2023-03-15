#include "minishell.h"

t_token *create_token(char *token) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token) {
        ft_putstr_fd("Memory allocation failed\n", 2);
        exit(1);
    }
    new_token->value = ft_strdup(token);
    new_token->left = NULL;
    new_token->right = NULL;
    return new_token;
}

t_token *build_token_tree(char **tokens, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int i = start;
    int parens = 0;
    int lowest_precedence_index = -1;
    int lowest_precedence = INT_MAX;

    while (i <= end) {
        if (is_left_paren(tokens[i])) {
            parens++;
        } else if (is_right_paren(tokens[i])) {
            parens--;
        } else if (parens == 0 && is_operator(tokens[i])) {
            int precedence = (ft_strcmp(tokens[i], "&&") == 0) ? 1 : 0;
            if (precedence <= lowest_precedence) {
                lowest_precedence_index = i;
                lowest_precedence = precedence;
            }
        }
        i++;
    }

    if (lowest_precedence_index != -1) {
        t_token *new_token = create_token(tokens[lowest_precedence_index]);

        new_token->left = build_token_tree(tokens, start, lowest_precedence_index - 1);
        new_token->right = build_token_tree(tokens, lowest_precedence_index + 1, end);

        return new_token;
    } else if (is_left_paren(tokens[start]) && is_right_paren(tokens[end])) {
        return build_token_tree(tokens, start + 1, end - 1);
    } else {
        return create_token(tokens[start]);
    }
}

t_token *tokenize_input(char *input) {
    char **tokens;
	t_token *root;

	// NEXT: Create format_input function (ft_split is just for testing)
	tokens = ft_split(input, ' ');
    int i = 0;
	while (tokens[i] != 0)
		i++;
    root = build_token_tree(tokens, 0, i - 1);
    free_doublearray(tokens);
    return (root);
}