#include <iostream>

using namespace std;

class fig {//figure инициализировать нельзя
protected:
    float x0, y0;
    float a;
public:
    fig(float x1=0, float y1=0, float a1=0): x0(x1), y0(y1), a(a1) {}//дефолтный конструктор
    virtual float sqr() const = 0;//пустая функция как и нижняя , нужна чтобы переопределить в наследниках
    virtual fig* copyf() const = 0;//функция копии не определена
    virtual ostream& show(ostream& os) {//функция вывода
        return os << "x0 = " << x0 << ", y0 = " << y0; }
    friend ostream &operator<<(ostream &os, fig &tmp){ return tmp.show(os); }//переопределения оператора вывода
};

class tre: public fig {//triangle
    float h;
public:
    tre(float x1, float y1, float a1, float h1):
            fig(x1, y1, a1), h(h1) {} // конструктор
    fig* copyf() const { return new tre(x0, y0, a, h);}//возвращает указатель на объект tre
    float sqr() const {return a*h/2;}//возвращает площадь
    ostream& show(ostream& os) {fig::show(os);//перегрузка вывода
        return os << ", osnovanie = " << a << ", vysota = " << h << endl; }
};

class kv: public fig {//square
public:
    kv (float x1, float y1, float a1):
            fig(x1, y1, a1) {}//дефолтный конструктор
    fig* copyf() const
    { return new kv(x0, y0, a);}//возвращает указатель на объект kv
    float sqr() const {return a*a;}//возвращает площадь
    ostream& show(ostream& os) {fig::show(os);//перегрузка вывода
        return os << ", storona = " << a << endl;}
};

struct el {//звено односвязного списка
    fig* pf;//элемент который будет хранить данная функция
    el*  next;//указатель наследующий элемент
    el(): pf(0), next(0) {}//дефолтный конструктор
    el(fig* f): pf(f), next(0) {}//конструктор если передаем элемент
    ~el() { delete pf->copyf(); }//деструктор удаляет копию объекта
};

class olist {//односвязный список
    el *elf;//массив элементов
public:
    olist() : elf(0) {}
    //Virtual 1.  (продолжение)

    olist(const olist& fl):elf(0) {
        for (el* e = fl.elf; e; e = e->next) ins_end(*(e->pf->copyf())); }
    ~olist() {
        for (el* e = elf; e;) {
            el* t = e->next;
            delete e;
            e = t; }
    }
    int get_size() {//получение размера
        int i = 0;
        for (el* e = elf; e; e = e->next, i++);
        return i; }

    el* pop_beg() {//должна вернуть и удалить из списка первый элемент
        if (!elf) {
            cerr << "Ochered is empty!" << endl; return 0; }
        el* t = elf;
        elf = t->next;//??
        return t; }

    el* pop_end() {//должна вернуть и удалить из списка последний элемент
        if (!elf) {
            cerr << "Ochered is empty!"; return 0; }
        el *p = 0;
        for (el* e = elf; e->next; e = e->next) p = e;
        if(!p) elf = 0;
        else p->next = 0;
        return p;//была ошибка вместа р была е
    }
    int ins_beg(fig& f) {//вставка в начало
        el *t = new el(f.copyf());
        if (!t) { cerr << "Error memory allocation!" << endl;
            return 0; }//вылетит только если елемент не создастся
        t->next = elf;//следующий элемент временого элемента равен началу массива
        elf = t;//ссылку начального элемента передаем на временный объект
        return 1;
    }
    int ins_end(fig& f) {//вставка в конец
        el *t = new el(f.copyf());
        if (!t) { cerr << "Error memory allocation!" << endl;
            return 0; }//вылетит только если елемент не создастся
        if (!elf) elf = t;
        else {
            el* e;
            for (e = elf; e->next; e = e->next);
            e->next = t;//??ошибка вместо
        }
        return 1;}
    friend ostream& operator<<(ostream& os, olist &fs);

};
ostream& operator<<(ostream& os, olist &f) {
    os << endl << "***** Ochered of geometric objects: *****" << endl;
    int i = 0;
    for (el* e = f.elf; e; e = e->next) {
        os << "i = " << i << ", figure:" << *e->pf << endl; i++; }
    return os;

}
//
//int main(){
//
//    cout<<"Triangle test\n";
//    tre t(1.0,2.0,3.0,4);
//    cout<<"Triangle.show test "<<t;
//    cout<<"Square = "<<t.sqr()<<"\n";
//
//    cout<<"\nKvadrat test\n";
//    kv k(1.0,2.0,3.0);
//    kv k1(11.0,12.0,5.0);
//    cout<<"kv.show test "<<k;
//    cout<<"Square = "<<k.sqr()<<"\n";
//
//    cout<<"\nForward list test\n";
//    olist ls;
//    cout<<"Push forward t\n";
//    ls.ins_beg(t);
//    cout<<"Size "<<ls.get_size()<<"\n";
//    cout<<"Push forward kv\n";
//    ls.ins_beg(k);
//    ls.ins_beg(k1);
//    cout<<"Size "<<ls.get_size()<<"\n";
//    cout<<"olist.show"<<ls<<"\n";
//    cout<<"olist.pop_end test\n";
//    ls.pop_end();
//    cout<<ls<<"\n";
//    cout<<"olist.pop_beg test\n";
//    ls.pop_beg();
//    cout<<ls<<"\n";
//
//    return 0;
//}

