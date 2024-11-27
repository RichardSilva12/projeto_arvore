#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
    int height;
};

// Função para obter a altura de um nó
int height(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Função para calcular o fator de balanceamento de um nó
int balanceFactor(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Rotação à esquerda
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza a altura
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// Rotação à direita
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza a altura
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// Balanceia a árvore
struct Node* balance(struct Node* node) {
    int balance = balanceFactor(node);

    // Se o nó ficou desbalanceado, há 4 casos a considerar

    // Caso 1: Desbalanceamento à esquerda
    if (balance > 1 && balanceFactor(node->left) >= 0) {
        return rightRotate(node);
    }

    // Caso 2: Desbalanceamento à direita
    if (balance < -1 && balanceFactor(node->right) <= 0) {
        return leftRotate(node);
    }

    // Caso 3: Desbalanceamento à esquerda-direita
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Desbalanceamento à direita-esquerda
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Função para inserir um novo nó na árvore
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;  // Não permite duplicatas
    }

    // Atualiza a altura do nó ancestral
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Balanceia a árvore
    return balance(node);
}

// Função para encontrar o nó com o valor mínimo
struct Node* minNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Função para remover um nó da árvore
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Nó encontrado
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct Node* temp = minNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    return balance(root);
}

// Função para exibir a árvore em Ordem Simétrica
void inOrder(struct Node* node) {
    if (node != NULL) {
        inOrder(node->left);
        printf("%d ", node->key);
        inOrder(node->right);
    }
}

// Função para exibir a árvore em Pré-ordem
void preOrder(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->key);
        preOrder(node->left);
        preOrder(node->right);
    }
}

// Função para exibir a árvore em Pós-ordem
void postOrder(struct Node* node) {
    if (node != NULL) {
        postOrder(node->left);
        postOrder(node->right);
        printf("%d ", node->key);
    }
}

// Função para exibir a árvore em formato de Grafos (representação simples)
void printGraph(struct Node* root, int space) {
    if (root == NULL) {
        return;
    }

    space += 5;
    printGraph(root->right, space);
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);
    printGraph(root->left, space);
}

// Função para buscar um elemento na árvore
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

// Função para editar um elemento
void edit(struct Node* root, int old_key, int new_key) {
    root = deleteNode(root, old_key);
    root = insert(root, new_key);
}

// Função para balancear a árvore
struct Node* balanceTree(struct Node* root) {
    return balance(root);
}

// Função para criar uma árvore vazia
struct Node* createEmptyTree() {
    return NULL;
}

// Função para exibir o menu
void menu() {
    printf("-= Árvore AVL em C =-\n");
    printf("1. Criar árvore vazia\n");
    printf("2. Inserir elemento\n");
    printf("3. Remover elemento\n");
    printf("4. Exibir Ordem Simétrica\n");
    printf("5. Exibir Pré-ordem\n");
    printf("6. Exibir Pós-ordem\n");
    printf("7. Exibir em formato de grafos\n");
    printf("8. Buscar um elemento\n");
    printf("9. Editar um elemento\n");
    printf("10. Balancear a árvore\n");
    printf("11. Sair\n");
}

int main() {
    struct Node* root = NULL;
    int op, valor, novo_valor;

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                root = createEmptyTree();
                printf("Árvore vazia criada.\n");
                break;
            case 2:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                root = insert(root, valor);
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                root = deleteNode(root, valor);
                break;
            case 4:
                printf("Árvore em Ordem Simétrica: ");
                inOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Árvore em Pré-ordem: ");
                preOrder(root);
                printf("\n");
                break;
            case 6:
                printf("Árvore em Pós-ordem: ");
                postOrder(root);
                printf("\n");
                break;
            case 7:
                printf("Árvore em formato de grafos:\n");
                printGraph(root, 0);
                break;
            case 8:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                if (search(root, valor) != NULL) {
                    printf("Elemento %d encontrado!\n", valor);
                } else {
                    printf("Elemento %d não encontrado.\n", valor);
                }
                break;
            case 9:
                printf("Digite o valor a ser editado: ");
                scanf("%d", &valor);
                printf("Digite o novo valor: ");
                scanf("%d", &novo_valor);
                edit(root, valor, novo_valor);
                break;
            case 10:
                root = balanceTree(root);
                printf("Árvore balanceada.\n");
                break;
            case 11:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 11);

    return 0;
}
