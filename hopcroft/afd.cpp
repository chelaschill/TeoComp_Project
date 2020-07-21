#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
struct state{
typedef state<T> states;

char nombre;
bool final = false;
bool inicial = false;
bool in_set = false;
int set;
vector<pair<T,states*>> transitions;

    state(){}
    
    state(char nombre,bool acceptance, bool initiation): nombre(nombre),final(acceptance),inicial(initiation){}
    
    void set_t(T varchar, state<T>* estado){
        pair<T,states*> temp = {varchar,estado};
        this->transitions.push_back(temp);
    }

    bool get_start(){
        return inicial;
    }
    
    bool get_final(){
        return final;
    }

    state<T>* get_estado(T n){
        for(auto i = 0 ; i < transitions.size() ; ++i){
            if(transitions.at(i).first == n)
                return transitions.at(i).second;
        }
    }

    bool operator==(states* estado){
        return nombre == estado->nombre;
    }

    bool operator!=(states* estado){
        return nombre != estado->nombre;
    }

};

template<typename T>
class DFA{
    private:
    typedef state<T> states;
    vector<vector<states*>> sets;
    vector<states*> aceptacion;
    vector<states*> no_aceptacion;
    states* inicial;
    int numtrans = 0;
    int numsets = 2;
    vector<T> trans;

    void Paso1(states* head){
        
        if(!head->in_set){    
            if(head->final){
                aceptacion.push_back(head);
                head->set = 1;
            }else{
                no_aceptacion.push_back(head);
                head->set = 0;
            }

            head->in_set = true;

            if(!head->transitions.empty()){
                for(auto i = 0 ; i < head->transitions.size() ; ++i){
                    Paso1(head->transitions[i].second);
                }
            }
        }
    }

    void Equivalencia(){
        
        bool bandera = false;

        do{
            bandera = false;
            vector<states*> equivalence;
            int original = sets.size();
            for(int i = 0; i < original; i++){
                if(sets[i].size() > 1){
                    for(int j = 1; j < sets[i].size(); j++){
                        if(sets[i][0]->get_estado(0)->set != sets[i][j]->get_estado(0)->set || sets[i][0]->get_estado(1)->set != sets[i][j]->get_estado(1)->set){
                            equivalence.push_back(sets[i][j]);
                            sets[i].erase(sets[i].begin()+j);
                            j--;
                        }
                    }
                    if(equivalence.size() > 0){
                        sets.push_back(equivalence);
                        for(auto z: sets[sets.size()-1])
                            z->set = sets.size()-1;
                        bandera = true;
                    }
                }
            }
        }while(bandera);
    }
            

    public:

    DFA():inicial(nullptr){}
    
    DFA(states* head):inicial(head){
        numtrans = head->transitions.size();
        for(auto i = 0 ; i < numtrans ; ++i){
            trans.push_back(head->transitions.at(i).first);
        }
    }

    void Paso1(){
        Paso1(inicial);
        sets.push_back(no_aceptacion);
        sets.push_back(aceptacion);
        
    }

    void Paso2(){
        Equivalencia();
    }

    bool distinguibles(states* inic, vector<states*>& conjunto){

            bool banderita = false;

            vector<states*> diferentes;
            for(auto i = 1 ; i < conjunto.size() ; ++i){
                states* temp = conjunto.at(i);
                for(auto j = 0 ; j < numtrans ; ++j){
                    if(inic->get_estado(trans[j])->set != temp->get_estado(trans[j])->set){
                        diferentes.push_back(temp);
                        banderita = true;
                        break;
                    }
                    else
                        continue;
                }
            }

            if(banderita){

                
                
                for(int i = 0 ; i < conjunto.size() ; ++i){
                    for(auto j = 0 ; j < diferentes.size() ; ++j){
                        diferentes.at(j)->set=numsets;
                        if(conjunto[i] == diferentes[j]){
                            conjunto.erase(conjunto.begin()+i);
                            i--;
                            break;
                        }
                        else 
                            continue;
                    }
                }

                numsets++;

                
                if(diferentes.size() > 1){
                    if(distinguibles(diferentes.at(0),diferentes))
                        return true;                    
                    else 
                    {   
                        sets.push_back(diferentes);
                        return false;
                    }
                }else if(diferentes.size() == 1){
                    
                    sets.push_back(diferentes);
                    return false;
                }
            }
            else
                return false;            
    }
    
    void distinguibles(){
        int h = 3;
        do{
            h--;
            for(auto i = 0; i < sets.size() ; ++i)
                distinguibles(sets[i][0],sets.at(i));
        }while(h);
    }

    void Moore(){
        distinguibles();
    }

    void print(){

        for(auto i = 0 ; i < numtrans ; ++i){
            if(i == 0)
                cout<<"     | "<<(inicial->transitions).at(0).first;
            else if(i == numtrans - 1){
                cout<<"  | "<<(inicial->transitions).at(i).first<<endl;
            }else{
                cout<<" | "<<(inicial->transitions).at(i).first;
            }
            
        }

        for(auto i= 0 ; i < sets.size() ; ++i){
            states* temp;
            for(auto j = 0 ; j < sets[i].size() ; ++j){
                temp = sets[i].at(j);
                if(temp->inicial && temp->final){
                    cout<<"->*q"<<i<<"| ";
                    break;
                }else if(temp->inicial){
                    cout<<"->q"<<i<<" | ";
                    break;
                }else if(temp->final){
                    cout<<"* q"<<i<<" | ";
                    break;
                }else{
                    cout<<"  q"<<i<<" | ";
                    break;
                }

            }


            for(auto k = 0 ; k < numtrans ; ++k){
                cout<<"q"<<temp->transitions.at(k).second->set;
                if(k == numtrans-1) cout<<endl;
                else cout<<" | ";
            }
            
        }
    }

};
