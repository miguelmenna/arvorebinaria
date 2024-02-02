#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um jogador
typedef struct Player {
    int pontos;
    int rebotes;
    int assist;
    // Outras estatísticas podem ser adicionadas aqui
    struct Player *left;
    struct Player *right;
} Player;

// Função para criar um novo jogador
Player *createPlayer(int pontos, int rebotes, int assist) {
    Player *newPlayer = (Player *)malloc(sizeof(Player));
    if (newPlayer == NULL) {
        printf("Erro ao alocar memória para o jogador.\n");
        exit(EXIT_FAILURE);
    }
    newPlayer->pontos = pontos;
    newPlayer->rebotes = rebotes;
    newPlayer->assist = assist;
    newPlayer->left = NULL;
    newPlayer->right = NULL;
    return newPlayer;
}

// Função para inserir um jogador na árvore
Player *insertPlayer(Player *root, int pontos, int rebotes, int assist) {
    if (root == NULL) {
        return createPlayer(pontos, rebotes, assist);
    }
    if (pontos < root->pontos) {
        root->left = insertPlayer(root->left, pontos, rebotes, assist);
    } else if (pontos > root->pontos) {
        root->right = insertPlayer(root->right, pontos, rebotes, assist);
    }
    return root;
}

// Função para buscar um jogador com uma quantidade específica de pontos
Player *searchPlayer(Player *root, int pontos) {
    if (root == NULL || root->pontos == pontos) {
        return root;
    }
    if (pontos < root->pontos) {
        return searchPlayer(root->left, pontos);
    }
    return searchPlayer(root->right, pontos);
}

// Função para encontrar o nó mais à esquerda (menor) na subárvore direita
Player *findMin(Player *node) {
    Player *current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Função para remover um jogador da árvore
Player *removePlayer(Player *root, int pontos) {
    if (root == NULL) {
        return root;
    }
    if (pontos < root->pontos) {
        root->left = removePlayer(root->left, pontos);
    } else if (pontos > root->pontos) {
        root->right = removePlayer(root->right, pontos);
    } else {
        if (root->left == NULL) {
            Player *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Player *temp = root->left;
            free(root);
            return temp;
        }
        Player *temp = findMin(root->right);
        root->pontos = temp->pontos;
        root->right = removePlayer(root->right, temp->pontos);
    }
    return root;
}

// Função para listar os jogadores em ordem de pontos
void inorderTraversal(Player *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Pontos: %d\n", root->pontos);
        inorderTraversal(root->right);
    }
}

int main() {
    Player *root = NULL;

    // Exemplo de inserção de jogadores
    root = insertPlayer(root, 20,1,1);
    insertPlayer(root, 10,4,4);
    insertPlayer(root, 30,8,7);
    insertPlayer(root, 5,2,2);
    insertPlayer(root, 15,6,9);
    insertPlayer(root, 35,1,6);

    // Exemplo de busca de um jogador com uma quantidade específica de pontos
    Player *playerFound;
    playerFound = searchPlayer(root, 30);
    if (playerFound != NULL) {
        printf("Jogador encontrado com %d pontos, %d rebotes, %d assist.\n", playerFound->pontos,playerFound->rebotes,playerFound->assist);
    } else {
        printf("Jogador não encontrado.\n");
    }

    // Exemplo de remoção de um jogador
    root = removePlayer(root, 30);
    root = removePlayer(root, 35);

    // Exemplo de listagem dos jogadores em ordem de pontos
    printf("Lista de jogadores em ordem de pontos:\n");
    inorderTraversal(root);

    return 0;
}