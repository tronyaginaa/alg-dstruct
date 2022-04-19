//
//  LabI_source.c
//  3-TronyaginaAlexandra-I12
//
//  Created by Alexandra Tronyagina on 14.04.2022.
//
//
#include "LabI_header.h"

node_t* root;

node_t* createNode(void){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (!newNode)
        return NULL;
    newNode->keys = (int*)malloc((2 * PARAMETR - 1) * sizeof(int));
    if (!newNode->keys){
        free(newNode);
        return NULL;
    }
    newNode->childrens = (node_t**)malloc(2 * PARAMETR * sizeof(node_t*));
    if (!newNode->childrens){
        free(newNode->keys);
        free(newNode);
        return NULL;
    }
    newNode->num = 0;
    newNode->isLeaf = TRUE;
    return newNode;
}

int findPosition(int key, int* keyArr, int n){
    int pos = 0;
    while (pos < n && key > keyArr[pos])
        pos++;
    return pos;
}

void splitChild(node_t* node, int ind){
    node_t* newNode = createNode();
    if (!newNode)
        return;
    node_t* tmp = node->childrens[ind];
    newNode->isLeaf = tmp->isLeaf;
    newNode->num = (PARAMETR - 1);
    for (int i = 0; i < (PARAMETR - 1); i++)
        newNode->keys[i] = tmp->keys[i + PARAMETR];
    if (tmp->childrens[0])
        for (int i = 0; i < PARAMETR; i++)
            newNode->childrens[i] = tmp->childrens[i + PARAMETR];
    tmp->num = (PARAMETR - 1);
    for (int i = node->num; i >= ind; i--)
        node->childrens[i + 1] = node->childrens[i];
    node->childrens[ind + 1] = newNode;
    for (int i = node->num - 1; i >= ind; i--)
        node->keys[i + 1] = node->keys[i];
    node->keys[ind] = tmp->keys[(PARAMETR - 1)];
    node->num++;
}

static void addKey(node_t* node, int key){
    int len = node->num - 1;
    if (!node->childrens[0]){
        while (len >= 0 && key < node->keys[len]){
            node->keys[len + 1] = node->keys[len];
            len--;
        }
        node->keys[len + 1] = key;
        node->num++;
    }
    else{
        while (len >= 0 && key < node->keys[len])
            len--;
        len++;
        if (node->childrens[len]->num == (2 * PARAMETR - 1)){
            splitChild(node, len);
            if (key > node->keys[len])
                len++;
        }
        addKey(node->childrens[len], key);
    }
}

status_t removeKey(node_t* node, int key){
    int pos, i, k, n;
    int* keyArr;
    status_t status;
    node_t** p;
    node_t* l;
    node_t* r;
    if (!node)
        return NOT_FOUND;
    n = node->num;
    keyArr = node->keys;
    p = node->childrens;
    pos = findPosition(key, keyArr, n);
    if (!p[0]){
        if (pos == n || key < keyArr[pos])
            return NOT_FOUND;
        for (i = pos + 1; i < n; i++){
            keyArr[i - 1] = keyArr[i];
            p[i] = p[i + 1];
        }
        int min = PARAMETR - 1;
        node->num--;
        if (node == root)
            min = 1;
        if (node->num >= min)
            return SUCCESS;
        else
            return NOT_ENOUGH_KEYS;
    }
    if (pos < n && key == keyArr[pos]){
        node_t* tmp1 = p[pos];
        node_t* tmp2;
        int nkey;
        while (1){
            nkey = tmp1->num;
            tmp2 = tmp1->childrens[nkey];
            if (!tmp2)
                break;
            tmp1 = tmp2;
        }
        keyArr[pos] = tmp1->keys[nkey - 1];
        tmp1->keys[nkey - 1] = key;
    }
    status = removeKey(p[pos], key);
    if (status != NOT_ENOUGH_KEYS)
        return status;
    if (pos > 0 && p[pos - 1]->num > (PARAMETR - 1)){
        k = pos - 1;
        l = p[k];
        r = p[pos];
        r->childrens[r->num + 1] = r->childrens[r->num];
        for (i = r->num; i > 0; i--){
            r->keys[i] = r->keys[i - 1];
            r->childrens[i] = r->childrens[i - 1];
        }
        r->num++;
        r->keys[0] = keyArr[k];
        r->childrens[0] = l->childrens[l->num];
        keyArr[k] = l->keys[--l->num];
        return SUCCESS;
    }
    if (pos < n && p[pos + 1]->num > (PARAMETR - 1)){
        k = pos;
        l = p[k];
        r = p[k + 1];
        l->keys[l->num] = keyArr[k];
        l->childrens[l->num + 1] = r->childrens[0];
        keyArr[k] = r->keys[0];
        l->num++;
        r->num--;
        for (i = 0; i < r->num; i++){
            r->keys[i] = r->keys[i + 1];
            r->childrens[i] = r->childrens[i + 1];
        }
        r->childrens[r->num] = r->childrens[r->num + 1];
        return SUCCESS;
    }
    if (pos == n)
        k = pos - 1;
    else
        k = pos;
    l = p[k];
    r = p[k + 1];
    l->keys[l->num] = keyArr[k];
    l->childrens[l->num + 1] = r->childrens[0];
    for (i = 0; i < r->num; i++){
        l->keys[l->num + 1 + i] = r->keys[i];
        l->childrens[l->num + 2 + i] = r->childrens[i + 1];
    }
    l->num = l->num + r->num + 1;
    free(r);
    for (i = pos + 1; i < n; i++){
        keyArr[i - 1] = keyArr[i];
        p[i] = p[i + 1];
    }
    int min = PARAMETR - 1;
    if (node == root)
        min = 1;
    node->num--;
    if (node->num >= min)
        return SUCCESS;
    else
        return NOT_ENOUGH_KEYS;
}

void removeElement(int key){
    node_t* oldRoot;
    status_t status = removeKey(root, key);
    if (status == NOT_ENOUGH_KEYS){
        oldRoot = root;
        root = root->childrens[0];
        free(oldRoot);
    }
}

int findElement(int key){
    node_t* tmp = root;
    int child = 0;
    while (tmp){
        for (int i = 0; i < tmp->num; i++){
            if (key == tmp->keys[i])
                return 1;
            if (key < tmp->keys[i]){
                child = i;
                break;
            }
            else
                child = i + 1;
        }
        tmp = tmp->childrens[child];
    }
    return 0;
}

void addElement(int key){
    if (findElement(key))
        return;
    if (!root){
        root = createNode();
        if (!root)
            return;
        root->keys[0] = key;
        root->num = 1;
    }
    else if (root->num == (2 * PARAMETR - 1)){
        node_t* oldRoot = root;
        node_t* newRoot = createNode();
        if (!newRoot)
            return;
        root = newRoot;
        newRoot->isLeaf = FALSE;
        newRoot->childrens[0] = oldRoot;
        splitChild(newRoot, 0);
        addKey(newRoot, key);
    }
    else
        addKey(root, key);
}

void deleteTree(node_t* node){
    if (!node)
        return;
    if (!node->isLeaf)
        for (int  i = 0; i < node->num; i++)
            deleteTree(node->childrens[i]);
    free(node);
    return;
}


