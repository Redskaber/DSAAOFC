#include <iostream>
using namespace std;

typedef struct Node
{//����������ṹ
    char data;
    struct Node* lchild, * rchild;
}*BiTree, BiTNode;

void CreateBiTree(BiTree& T)
{//���򴴽�������
    char ch;
    cin >> ch;
    if (ch == '#') T = NULL;
    else {
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}
void InOrderTraverse(BiTree T)
{//�������
    if (T)
    {
        InOrderTraverse(T->lchild);
        cout << T->data;
        InOrderTraverse(T->rchild);
    }
}
void PreOrderTraverse(BiTree T)
{//�������
    if (T)
    {
        cout << T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
void PostOrderTraverse(BiTree T)
{//�������
    if (T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
}
void Copy(BiTree T, BiTree& NewT)
{//�������ĸ���
    if (T == NULL) {
        NewT = NULL;
        return;
    }
    else
    {
        NewT = new BiTNode;
        NewT->data = T->data;
        Copy(T->lchild, NewT->lchild);
        Copy(T->rchild, NewT->rchild);
    }
}
int Depth(BiTree T)
{//�������
    if (T == NULL)
        return 0;
    else
    {
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        if (m > n) return (m + 1);
        else return (n + 1);
    }
}
int NodeCount(BiTree T)
{//ͳ�ƶ������н��ĸ���
    if (T == NULL) return 0;
    else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}
int LeafCount(BiTree T)
{//ͳ�ƶ�������Ҷ�ӽ��ĸ���
    if (!T) return 0;
    if (!T->lchild && !T->rchild) {//�������������������������Ϊ��,˵���ö��������ڵ�ΪҶ�ӽڵ�,��1.
        return 1;
    }
    else {
        return LeafCount(T->lchild) + LeafCount(T->rchild);
    }
}
int Node_1_Count(BiTree T)
{//ͳ�ƶ������Ķ�Ϊ1�Ľ�����
    if (!T) return 0;
    if ((!T->lchild) && (T->rchild) || (T->lchild) && (!T->rchild))
        return 1 + Node_1_Count(T->lchild) + Node_1_Count(T->rchild);
    else
        return Node_1_Count(T->lchild) + Node_1_Count(T->rchild);
}
void PrintAllPath(BiTree T, char path[], int pathlen)
{//�������д�ÿ��Ҷ�ӽ�㵽������·��
    int i;
    if (T != NULL) {
        path[pathlen] = T->data; //����ǰ������·����
        if (T->lchild == NULL && T->rchild == NULL) {//Ҷ�ӽ��
            for (i = pathlen; i >= 0; i--)
                cout << path[i] << " ";
            cout << endl;
        }
        else {
            PrintAllPath(T->lchild, path, pathlen + 1);
            PrintAllPath(T->rchild, path, pathlen + 1);
        }
    }
}
void ExChangeTree(BiTree& T)
{//���캯����ʹ�õݹ��㷨�������ҽ��ת��
    BiTree temp;
    if (T != NULL) {//�ж�T�Ƿ�Ϊ�գ��ǿս���ת��������ת��
        temp = T->lchild;
        T->lchild = T->rchild;//ֱ�ӽ����ڵ��ַ
        T->rchild = temp;
        ExChangeTree(T->lchild);
        ExChangeTree(T->rchild);
    }
}
void DblOrderTraverse(BiTree T)
{//��������˫�����
    if (T)
    {
        cout << T->data;
        DblOrderTraverse(T->lchild);
        cout << T->data;//��������
        DblOrderTraverse(T->rchild);
    }
}
int main()
{
    BiTree T;
    //��������AB#CD##E##F#GH###
    cout << "�����������(��#����):";
    CreateBiTree(T);
    cout << "����������:";
    InOrderTraverse(T);
    cout << endl << "����������:";
    PreOrderTraverse(T);
    cout << endl << "����������:";
    PostOrderTraverse(T);
    cout << endl << "�������:" << Depth(T);
    cout << endl << "���ĸ���:" << NodeCount(T);
    cout << endl << "Ҷ���ĸ���:" << LeafCount(T);
    cout << endl << "��Ϊ1�Ľ�����:" << Node_1_Count(T);
    cout << endl << "�������д�ÿ��Ҷ�ӽ�㵽����������·����" << endl;
    char path[256];
    int pathlen = 0;
    PrintAllPath(T, path, pathlen);//
    //����������ÿ���������Ӻ��Һ���
    BiTree tem = T;//ֱ�Ӹ���һ�������ڲ��ı�ԭ����ǰ���£�����ʱ�����н�����
    ExChangeTree(tem);
    cout << "����������������Ľ��:";
    PreOrderTraverse(tem);
    cout << endl << "˫��������:";
    DblOrderTraverse(T);
    return 0;
}