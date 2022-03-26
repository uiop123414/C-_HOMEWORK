#include <iostream>

template<class T>
struct Node{
    T num = 0;
    Node<T> * right = nullptr;
    Node<T> * left = nullptr;
};
template<class T>
class BTree{

private:
    Node<T> * root;
    void Insert(T _num,Node<T> * cur_node  ){
        if(_num == cur_node->num )
            return;
        else
        if(_num>cur_node->num)
            if(cur_node->right!= nullptr)
                Insert(_num,cur_node->right);
            else
            {
                Node<T> * tmp = new Node<T>;
                tmp->num = _num;
                cur_node->right =tmp;
            }
        else
        if(cur_node->left!= nullptr)
            Insert(_num,cur_node->left);
        else
        {
            Node<T> * tmp = new Node<T>;
            tmp->num = _num;
            cur_node->left =tmp;
        }
    }
    void PrintTree(Node<T> * node){
        if(node != NULL){
            if(node->left != NULL)
                PrintTree(node->left);

            std::cout<< node->num << ' ';

            if(node->right != NULL)
                PrintTree( node->right);
        }
    }
    void print_tree_Nice_private(Node<T> * curr,int tabs = 5)
    {
        if (!curr) return; // Проверка на ненулевой указатель

        tabs++;
        print_tree_Nice_private(curr->left,tabs);

        for(int i=0;i<tabs;i++)
            std::cout<<"  ";

        std::cout << curr->num<<std::endl;
        print_tree_Nice_private(curr->right,tabs);

        tabs--;

        return;
    }
    void Remove_Node(T _num,Node<T> * cur_node){
        if(cur_node == NULL)
            return;
        else{
            if(cur_node->left->num == _num) {
                ClearNode(cur_node->left);
                cur_node->left = nullptr;
                return;
            }
            else if(cur_node->right->num == _num){
                ClearNode(cur_node->right);
                cur_node->right = nullptr;
                return;
            }
            if (_num>cur_node->num)
            {
                Remove_Node(_num,cur_node->right);
            }
            else if(_num<cur_node->num)

                Remove_Node(_num,cur_node->left);
            else
                ClearNode(cur_node);
        }
    }

    void ClearNode(Node<T>* node){
        if(node != NULL){
            if(node->left != NULL)
                ClearNode(node->left);
            if(node->right != NULL)
                ClearNode(node->right);
            delete node;
        }

    }

public:
    BTree(){
        root = nullptr;
    }
    BTree(T _num):BTree(){
        root = new Node<T>;
        root->num = _num;
    }


    void insert_item(T _num){
        if(root == nullptr){
            root = new Node<T>;
            root->num = _num;
            return;
        }
        Insert(_num,root);
    }
    void print_tree(){
        PrintTree(root);
    }
    void remove(T _num){
        if (root->num ==_num){
            ClearNode(root);
            root = nullptr;
            return;
        }
        Remove_Node(_num,root);
    }
    void print_Tree_Nice(){
        if(root == nullptr)
            return;
        print_tree_Nice_private(root);
    }
};

int main(){
    BTree<int> tree(2);
    tree.insert_item(1);
    tree.insert_item(1);
    tree.insert_item(2);
    tree.insert_item(2);
    tree.insert_item(2);
    tree.insert_item(8);
    tree.insert_item(3);
    tree.insert_item(5);
    tree.insert_item(7);
    printf("\n");
    tree.print_Tree_Nice();
    return 0;
}