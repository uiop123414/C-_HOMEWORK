#include <iostream>


template<typename T>
struct Node{
    T var = NULL;
    Node * forward = nullptr;
    Node * back = nullptr;
};

template<class T>
class List{
private:
    Node<T> * Head;
    Node<T> * Tail;
public:
    List(){
        Head = nullptr;
        Tail = nullptr;
    }

    int get_SIZE(){
        if (Head == nullptr & Tail == nullptr)
            return 0;
        else if(Head == Tail)
            return 1;
        Node<T> * tmp = Tail;
        int size=0;
        while(tmp!= nullptr)
        {
            tmp = tmp->forward;
            size++;
        }
        return size;
    }
    void add_to_head(T  _var){
        Node<T> * tmp = new Node<T>;
        tmp->var = _var;
        if (Head == nullptr & Tail == nullptr){
            Head = tmp;
            Tail = tmp;

            return;
        }
        else if (Head == Tail){
            Head = tmp;
            Head->back = Tail;
            Tail->forward = Head;
            return;
        }

        tmp->back = Head;
        Head->forward = tmp;
        Head = tmp;
        Head->forward = nullptr;
    }

    void add_to_tail(T  _var){
        Node<T> * tmp = new Node<T>;
        tmp->var = _var;
        if (Head == nullptr & Tail == nullptr){
            Head = tmp;
            Tail = tmp;
            return;
        }
        else if (Head == Tail){
            Tail = tmp;
            Tail->forward = Head;
            Head->back = Tail;
            return;
        }
        tmp->forward = Tail;
        Tail->back = tmp;
        Tail = tmp;
        Tail->back = nullptr;
    }
    T pop_head(){
        if (Head == nullptr)
            return NULL;
        if(Head == Tail){
            T num_tmp = Head->var;
            Head = nullptr;
            Tail = nullptr;
            return num_tmp;
        }

        Head = Head->back;
        T tmp = Head->forward->var;
        delete Head->forward;
        Head->forward = nullptr;
        return tmp;
    }

    T pop_tail(){
        if (Tail == nullptr)
            return NULL;
        if(Head == Tail){
            T num_tmp = Head->var;
            Head = nullptr;
            Tail = nullptr;
            return num_tmp;
        }
        Tail = Tail->forward;
        T tmp = Tail->back->var;
        delete Tail->back;
        Tail->back = nullptr;
        return tmp;
    }
    void insert(const int count,T _var){
        Node<T> * tmp = new Node<T>;
        tmp->var = _var;
        Node<T> * tmp_iter = Tail;
        for(int i = 0;i<count-1;i++)
            if(tmp_iter == nullptr){
                add_to_head(_var);
                return;
            }
            else
                tmp_iter = tmp_iter->forward;
        tmp->forward = tmp_iter;
        tmp->back = tmp_iter->back;
        tmp_iter->back->forward = tmp;
        tmp_iter->back = tmp;

    }
    void replace(const int count,T _var){
        Node<T> * tmp_iter = Tail;
        for(int i = 0;i<count-1;i++)
            if(tmp_iter == nullptr){
                Head->var = _var;
                return;
            }
            else
                tmp_iter = tmp_iter->forward;
        tmp_iter->var =_var;
    }
    void print_List(const bool _reverse =false){
        if(_reverse){
            Node<T> * tmp = Head;
            int i = get_SIZE();
            while (tmp!= nullptr){
                std::cout<<"Node "<<i<<" num = "<<tmp->var<<"\n";
                i--;
                tmp = tmp->back;
            }

        }
        else{
            Node<T> * tmp = Tail;
            int i = 1;
            while (tmp!= nullptr){
                std::cout<<"Node "<<i<<" num = "<<tmp->var<<"\n";
                i++;
                tmp = tmp->forward;
            }

        }
    }
    void remove(const int count){
        Node<T> * tmp_iter = Tail;
        for(int i = 0;i<count-1;i++)
            if(tmp_iter == nullptr){
                pop_head();
                return;
            }
            else
                tmp_iter = tmp_iter->forward;
        tmp_iter->back->forward = tmp_iter->forward;
        tmp_iter->forward->back = tmp_iter->back;
        delete tmp_iter;
    }
    T operator [](int place){
        Node<T> * tmp_iter = Tail;
        if(place>=0) {
            for (int i = 0; i < place; i++)
                if (tmp_iter == nullptr) {
                    return Head->var;
                } else
                    tmp_iter = tmp_iter->forward;
            return tmp_iter->var;
        }
        else{
            tmp_iter = Head;
            for (int i = get_SIZE()+place; i !=0; i--)
                if (tmp_iter == nullptr) {
                    return Head->var;
                } else
                    tmp_iter = tmp_iter->back;
            return tmp_iter->var;
        }
    }
    ~List(){
        if(Tail == nullptr & Head == nullptr)
            return;

        if (Tail == Head)
        {
            delete Tail;
            return;
        }

        Node<T> * tmp = Tail->forward;


        while (tmp->forward!= nullptr)
        {
            delete tmp->back;
            tmp = tmp->forward;
        }
    }
};



//int main(){
//    List<int> ls;
//    ls.add_to_head(10);
//    ls.add_to_head(20);
//    ls.add_to_head(30);
//    ls.add_to_tail(50);
//    ls.add_to_tail(60);
//    ls.add_to_tail(70);
//    ls.print_List();
//    printf("********************INSERT*****************************\n");
//    ls.insert(1000,1234);
//    ls.print_List(false);
//    printf("********************INSERT_TRUE_PRINT*****************************\n");
//    ls.print_List(true);
//    printf("********************REPLACE_TRUE_PRINT*****************************\n");
//    ls.replace(3,2280);
//    ls.print_List(true);
//    printf("********************REPLACE_FALSE_PRINT*****************************\n");
//    ls.remove(3);
//    ls.print_List();
//    printf("********************GET_ITEM_FALSE_PRINT*****************************\n");
//    std::cout<<"Node i = 3 , var = "<<ls[-7];
//}