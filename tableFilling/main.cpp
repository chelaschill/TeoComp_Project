#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n,m;
    cout <<"Ingresa el numero de estados: "<<endl;
    cin >> n;//input: n = 6
    int t_transition[n][n]; //Tabla de transicion
    vector<string> final_t_transition;
    vector<string> result;
    bool t_mark[n][n]; //Tabla de marcado
    bool fs[n]; // Estados finales
    cout <<"Ingresa el numero de simbolos: "<<endl;
    cin >> m;//input: m = 2

    cout <<"Indica si es un estado final o no: "<<endl;
    for (int i = 0; i < n; i++) {
        cin >> fs[i];
//        input:
//        0
//        0
//        1
//        1
//        1
//        0
    }

    // Ingreso los datos de la Tabla de transicion
    cout <<"Ingresa las transiciones: "<<endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> t_transition[i][j];
//            input:
//            1 2
//            0 3
//            4 5
//            4 5
//            4 5
//            5 5
        }
    }


    //STEP 1: inicializo tabla de marcado
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            t_mark[i][j] = false;
        }
    }


    //STEP 2: Marcamos todos los pares que tienen un estado final y uno inicial
    int a=1;
    for (int i = 1; i < n; i++) {
        int j=0;
        while ( j != a) {
            if((fs[i] == 0 & fs[j] == 1) || (fs[i] == 1 & fs[j] == 0)){
                t_mark[i][j] = true;
            }
            j++;
        }
        a++;
    }

    //STEP 3
    a=1;
    for (int i = 1; i < n; i++) {
        int j=0;
        while ( j != a) {
            if(!t_mark[i][j]){
                for (int k = 0; k < m; k++) {
                    int var1 = t_transition[i][k];
                    int var2 = t_transition[j][k];
                    if(t_mark[var1][var2]){
                        t_mark[i][j] = true;
                    }
                }
            }
            j++;
        }
        a++;
    }

    //STEP 4
    a=1;
    int var1=-1, var2=-1;
    string combine, final_t;
    bool merge;
    for (int i = 1; i < n; i++) {
        int j=0;
        while ( j != a) {
            merge = false;
            if(!t_mark[i][j]){
                if(var1 == i){
                    result.pop_back();
                    final_t_transition.pop_back();
                    combine = to_string(var1) + to_string(var2) + to_string(j);
                    result.push_back(combine);
                    final_t_transition.push_back(combine);
                } else if(var2 == j){
                    result.pop_back();
                    final_t_transition.pop_back();
                    combine = to_string(var1) + to_string(var2) + to_string(i);
                    result.push_back(combine);
                    final_t_transition.push_back(combine);
                } else{
                    combine = to_string(i) + to_string(j);
                    result.push_back(combine);
                    final_t_transition.push_back(combine);
                }
                var1 = i;
                var2 = j;
                merge=true;
            }
            j++;
        }
        if(!merge){
            var1 = i;
            var2 = j;
            result.push_back(to_string(i));
            final_t_transition.push_back(to_string(i));
            if(i+1==n){
                final_t_transition.push_back(to_string(i));
            }
        }
        a++;
    }

    cout << "\n AFD minimizado:\n";
    cout << "---------------------\n";
    int l=0;
    for (int i = 0; i < result.size(); ++i) {
        for(int j=0; j<m; j++){
            cout << result[i] <<"  -->"<<"(" <<j<<")  ";
            if(j == 0 ){
                cout<< final_t_transition[i]<< endl;
            } else{
                cout<< final_t_transition[i+1]<< endl;
            }
        }
    }

    return 0;
}
