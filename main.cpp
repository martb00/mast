#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

struct node {
        int key = NULL;
        struct node* parent = NULL;
        struct node* child = NULL;
        struct node* brother = NULL;
};

struct tree {
        struct node* root;
        struct node** node_tab;
        int tab_length = 0;
        int number_of_leaves = 0;
        int number_of_nodes = 0;
        int nodenum = 0;
        int tab_iterator = 0;
};

void create_tree(struct tree* tree);
void delete_tree(struct tree* tree);
void go_through(struct tree* tree, struct node*); // count leaves and nodes; fill the nodes with the keys
void create_node_tab_pt1(struct tree* tree, struct node*);
void create_node_tab_pt2(struct tree* tree, struct node*tmp);
int isomorphism_how_much_to_remove(struct tree* tree1, struct tree* tree2);
struct node* node_with_key(int key, struct node** tab, int length);
void generateVarWithout(int depth, int maxnumber, string& number, int** tab, int& result, int rows);
void generateVarWithout2(int depth, int maxnumber, string& number, int** tab, int& result, int rows);

int main() {

        int n;
        scanf("%i", &n);
        struct tree* tree_tab = new struct tree[n];

        for (int i = 0; i < n; i++) {
                create_tree(&tree_tab[i]);
        }

        for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                        printf("%i\n", isomorphism_how_much_to_remove(&tree_tab[i], &tree_tab[j]));
                }
        }

        for (int i = 0; i < n; i++) {
                delete_tree(&tree_tab[i]);
        }

        delete[] tree_tab;
        return 0;
}




void create_tree(struct tree* tree) {
        struct node* root = new struct node;                           
        root->key = 0;
        tree->root = root;
        struct node* tmp = tree->root;
        char sign = NULL;
        do {
                scanf("%c", &sign);
                if (sign == '(') {
                        struct node* node = new struct node;
                        node->parent = tmp;
                        tmp->child = node;
                        tmp = node;
                }
                if (sign == ',') {
                        struct node* node = new struct node;
                        node->parent = tmp->parent;
                        tmp->brother = node;
                        tmp = node;
                }
                if (sign > ('0' - 1) && sign < ('9' + 1)) {
                        int num = tmp->key * 10 + ((int)sign - '0');
                        tmp->key = num;
                }
                if (sign == ')') {
                        tmp = tmp->parent;
                }
        } while (sign != ';');

        tmp = tree->root;
        tree->number_of_nodes = 1;
        go_through(tree, tmp);
        tree->tab_length = tree->number_of_nodes + tree->number_of_leaves;
        tree->node_tab = new struct node*[tree->tab_length];
        tmp = tree->root;
        create_node_tab_pt1(tree, tmp);
        tmp = tree->root;
        tree->tab_iterator++;
        create_node_tab_pt2(tree, tmp);
        tree->node_tab[tree->number_of_leaves] = tree->root;
}


void delete_tree(struct tree* tree) {

        for (int i = 0; i < tree->tab_length; i++) {
                delete tree->node_tab[i];
        }
        delete[] tree->node_tab;
}

void go_through(struct tree* tree, struct node* tmp) { 
        if (tmp->child != NULL) {
                if (tmp->child->key == NULL) {
                        tree->nodenum--;
                        tmp->child->key = tree->nodenum;
                        tree->number_of_nodes++;
                }
                else {
                        tree->number_of_leaves++;
                }
                go_through(tree, tmp->child);
        }
        if (tmp->brother != NULL) {
                if (tmp->brother->key == NULL) {
                        tree->nodenum--;
                        tmp->brother->key = tree->nodenum;
                        tree->number_of_nodes++;
                }
                else {
                        tree->number_of_leaves++;
                }
                go_through(tree, tmp->brother);
        }
}

void create_node_tab_pt1(struct tree* tree, struct node*tmp) { 
        if (tmp->child != NULL) {
                if (tmp->child->key > 0) {
                        tree->node_tab[tree->tab_iterator] = tmp->child;
                        tree->tab_iterator++;
                }
                create_node_tab_pt1(tree, tmp->child);
        }
        if (tmp->brother != NULL) {
                if (tmp->brother->key > 0) {
                        tree->node_tab[tree->tab_iterator] = tmp->brother;
                        tree->tab_iterator++;
                }
                create_node_tab_pt1(tree, tmp->brother);
        }
}

void create_node_tab_pt2(struct tree* tree, struct node*tmp) {
        if (tmp->child != NULL) {
                if (tmp->child->key <= 0) {
                        tree->node_tab[tree->tab_iterator] = tmp->child;
                        tree->tab_iterator++;
                }
                create_node_tab_pt2(tree, tmp->child);
        }
        if (tmp->brother != NULL) {
                if (tmp->brother->key <= 0) {
                        tree->node_tab[tree->tab_iterator] = tmp->brother;
                        tree->tab_iterator++;
                }
                create_node_tab_pt2(tree, tmp->brother);
        }
}

struct node* node_with_key(int key, struct node** tab, int length) {
        node* result;
        for (int i = 0; i < length; i++) {
                if (tab[i]->key == key) {
                        result = tab[i];
                        return result;
                }
        }
        return NULL; 
}




void generateVarWithout(int depth, int maxnumber, string& number, int** tab, int& result, int rows) {
        if (depth == 0) {
                //cout << number << endl;
                int suma = 0;
                for (int r = 0; r < rows; r++) {
                        suma += tab[r][number[r] - '1'];
                }
                if (suma > result)result = suma;
                return;
        }

        for (int i = 1; i <= maxnumber; i++) {
                if (number.find(char(i + '0')) == string::npos) {
                        number += char(i + '0');
                        generateVarWithout(depth - 1, maxnumber, number, tab, result, rows);
                        number.pop_back();
                }
        }
}

void generateVarWithout2(int depth, int maxnumber, string& number, int** tab, int& result, int rows) {
        if (depth == 0) {
                int suma = 0;
                for (int r = 0; r < rows; r++) {
                        suma += tab[number[r] - '1'][r];
                }
                if (suma > result)result = suma;
                return;
        }

        for (int i = 1; i <= maxnumber; i++) {
                if (number.find(char(i + '0')) == string::npos) {
                        number += char(i + '0');
                        generateVarWithout2(depth - 1, maxnumber, number, tab, result, rows);
                        number.pop_back();
                }
        }
}



int isomorphism_how_much_to_remove(struct tree* tree1, struct tree* tree2) {

        int row = tree1->tab_length;
        int column = tree2->tab_length;
        int **tab;
        tab = (int**)malloc(row * sizeof(int *));
        for (int i = 0; i < row; i++)
        {
                tab[i] = (int*)malloc(column * sizeof(int));
                for (int j = 0; j < column; j++) tab[i][j] = 0;
        }

        int result;
        for (int i = 0; i < tree1->number_of_leaves; i++) {
                for (int j = 0; j < tree2->number_of_leaves; j++) {
                        if (tree1->node_tab[i]->key == tree2->node_tab[j]->key) result = 1;
                        else result = 0;
                        tab[i][j] = result;
                }
        }

        for (int i = tree1->tab_length - 1; i > tree1->number_of_leaves - 1; i--) { // tab dół lewy
                for (int j = 0; j < tree1->tab_length; j++) {
                        struct node* node;
                        if (j < tree2->tab_length) { node = node_with_key(tree2->node_tab[j]->key, tree1->node_tab, tree1->tab_length); }
                        else node = node_with_key(tree1->node_tab[j]->key, tree1->node_tab, tree1->tab_length);
                        if (node->parent == tree1->node_tab[i]) {
                                if (j < (tree2->tab_length) && tree2->node_tab[j]->key > 0) { 
                                        tab[i][j] = 1;
                                }
                                if ((j < tree2->tab_length && tree2->node_tab[j]->key <= 0) || j > (tree2->tab_length - 1)) { 
                                        int child_row = tree1->number_of_leaves - tree1->node_tab[j]->key;  
                                        for (int k = 0; k < tree1->number_of_leaves; k++) {
                                                if (tab[child_row][k] == 1) tab[i][k] = 1;
                                        }
                                }
                        }
                }
        }

        // tab gora prawa
        for (int i = tree2->tab_length - 1; i > tree2->number_of_leaves - 1; i--) {
                for (int j = 0; j < tree2->tab_length; j++) {
                        struct node* node;
                        if (j < tree1->tab_length) { node = node_with_key(tree1->node_tab[j]->key, tree2->node_tab, tree2->tab_length); }
                        else node = node_with_key(tree2->node_tab[j]->key, tree2->node_tab, tree2->tab_length);
                        if (node->parent == tree2->node_tab[i]) { 
                                if (j < tree1->tab_length && tree1->node_tab[j]->key > 0) { 
                                        tab[j][i] = 1;
                                }
                                if ((j < tree1->tab_length && tree1->node_tab[j]->key <= 0) || j > (tree1->tab_length - 1)) {
                                        int child_column = tree2->number_of_leaves - tree2->node_tab[j]->key;
                                        for (int k = 0; k < tree2->number_of_leaves; k++) {
                                                if (tab[k][child_column] == 1) tab[k][i] = 1;
                                        }
                                }
                        }
                }
        }

        // prawy dol tabeli 
        // wezelxwezel
        for (int i = tree1->tab_length - 1; i > tree1->number_of_leaves - 1; i--) {
                for (int j = tree2->tab_length - 1; j > tree2->number_of_leaves - 1; j--) {
                        int resultx = 0;
                        //spr wezła z tab1[i]
                        //z dziecmi wezla z tab2[j]
                        for (int n = 0; n < tree2->tab_length; n++) {
                                if ((tab[i][n] > resultx) && (tree2->node_tab[n]->parent == tree2->node_tab[j])) resultx = tab[i][n]; 
                        }

                        // to samo ale spr wezla z tab2 z dziemi wezla tab1
                        for (int n = 0; n < tree1->tab_length; n++) {
                                if ((tab[n][j] > resultx) && (tree1->node_tab[n]->parent == tree1->node_tab[i])) resultx = tab[n][j];
                        }

                        //porownanie dzieci z dziecmi
                        int childrenstree1 = 0;
                        int childrenstree2 = 0;

                        for (int h = 0; h < tree1->tab_length; h++) {
                                if (tree1->node_tab[h]->parent == tree1->node_tab[i])childrenstree1++;
                        }
                        for (int h = 0; h < tree2->tab_length; h++) {
                                if (tree2->node_tab[h]->parent == tree2->node_tab[j])childrenstree2++;
                        }

                        int** auxiliary_tab;
                        auxiliary_tab = (int**)malloc(childrenstree1 * sizeof(int *));
                        for (int r = 0; r < childrenstree1; r++)
                        {
                                auxiliary_tab[r] = (int*)malloc(childrenstree2 * sizeof(int));
                                for (int c = 0; c < childrenstree2; c++) auxiliary_tab[r][c] = 0;
                        }


                        // wypelnianie tablicy pomocniczej skrzyzowaniami dzieci
                        int ro = 0;
                        int co = 0;
                        int* rtab = (int*)malloc(childrenstree1 * sizeof(int));
                        int* ctab = (int*)malloc(childrenstree2 * sizeof(int));


                        for (int h = 0; h < tree1->tab_length; h++) {
                                if (tree1->node_tab[h]->parent == tree1->node_tab[i]) {
                                        rtab[ro] = h;
                                        ro++;
                                }
                        }
                        for (int h = 0; h < tree2->tab_length; h++) {
                                if (tree2->node_tab[h]->parent == tree2->node_tab[j]) {
                                        ctab[co] = h;
                                        co++;
                                }
                        }

                        for (int h = 0; h < childrenstree1; h++) {
                                for (int g = 0; g < childrenstree2; g++) {
                                        auxiliary_tab[h][g] = tab[rtab[h]][ctab[g]];
                                }
                        }

                        free(rtab);
                        free(ctab);

                        if (childrenstree1 <= childrenstree2) {
                                string number = "";
                                generateVarWithout(childrenstree1, childrenstree2, number, auxiliary_tab, resultx, childrenstree1);
                        }

                        if (childrenstree1 > childrenstree2) {
                                string number = "";
                                int x = childrenstree2;
                                int y = childrenstree1;
                                generateVarWithout2(x, y, number, auxiliary_tab, resultx, x);
                        }

                        tab[i][j] = resultx;

                        for (int r = 0; r < childrenstree1; r++)
                        {
                                free(auxiliary_tab[r]);
                        }
                        free(auxiliary_tab);

                }

        }

        /* wypisywanie calej tab
        for (int i = 0; i < row; i++) { // spr tabeli
                for (int j = 0; j < column; j++) {
                        printf("%i", tab[i][j]);
                }
                cout << endl;
        }*/

        int end_result = tree1->number_of_leaves - tab[tree1->number_of_leaves][tree2->number_of_leaves];


        for (int i = 0; i < row; i++)
        {
                free(tab[i]);
        }
        free(tab);
        tab = NULL;
        return end_result;
}
