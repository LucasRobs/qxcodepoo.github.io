#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Pass{
    string id;
    int idade;

    Pass(string id = "", int idade = 0  ){
        this->id = id;
        this->idade = idade;
    }
    string toString(){
        stringstream ss;
        ss << this->id << ":" << this->idade;
        return ss.str();
    }
};

struct Topic{
    vector<Pass*> cadeiras;
    int qtdPref;

    Topic(int lotacao = 0, int qtdPref = 0):
        cadeiras(lotacao, nullptr), qtdPref(qtdPref)
    {
    }

    ~Topic(){
        for(Pass * pass : cadeiras)
            delete(pass);
    }

    int find(string id){
        for(int i = 0; i < (int) cadeiras.size(); i++)
            if(cadeiras[i] != nullptr && cadeiras[i]->id == id)
                return i;
        return -1;
    }

    int findPref(){
        for(int i = 0; i < qtdPref; i++)
            if(cadeiras[i] == nullptr)
                return i;
        return -1;
    }
    
    int findNormal(){
        for(int i = qtdPref; i < (int) cadeiras.size(); i++)
            if(cadeiras[i] == nullptr)
                return i;
        return -1;
    }
    

    bool reservar(string id, int idade){
        if(this->find(id) != -1){
            cout << "failure: pass ja esta na topic";
            return false;
        }
        int pref = findPref();
        int norm = findNormal();
        if(pref == -1 && norm == -1){
            cout << "failure: topic lotada";
            return false;
        }
        int pos = 0;
        if(idade >= 65)
            pos = pref != -1? pref : norm;
        else
            pos = norm != -1? norm : pref;
        cadeiras[pos] = new Pass(id, idade);
        return true;
    }

    bool cancelar(string id){
        for(int i = 0; i < (int) cadeiras.size(); i++){
            if(cadeiras[i] != nullptr && cadeiras[i]->id == id){
                delete cadeiras[i];
                cadeiras[i] = nullptr;
                return true;
            }
        }
        cout << "failure: pass nao esta na topic";
        return false;
    }

    string toString(){
        stringstream ss;
        ss << "[ ";
        for(int i = 0; i < (int) cadeiras.size(); i++){
            ss << (i < qtdPref ? "@" : "=");
            if(cadeiras[i] != nullptr)
                ss << cadeiras[i]->toString();
            ss << " ";
        }
        ss << "]";
        return ss.str();
    }
};

struct Controller{
    Topic sala;

    string shell(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
        if(op == "show"){
            out << sala.toString();
        }else if(op == "init"){
            int qtd, pref;
            in >> qtd >> pref;
            sala = Topic(qtd, pref);
            out << "success";
        }else if(op == "in"){
            string id;
            int idade;
            in >> id >> idade;
            if(sala.reservar(id, idade))
                out << "success";
        }else if(op == "out"){
            string id;
            in >> id;
            if(sala.cancelar(id))
                out << "success";
        }
        return out.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            cout << "$" << line << endl;
            if(line == "end")
                return;
            cout << shell(line) << endl;
        }
    }
};

int main(){
    Controller c;
    c.exec();
    return 0;
}