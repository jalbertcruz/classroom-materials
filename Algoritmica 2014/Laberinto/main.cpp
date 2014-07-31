// Compiling using:
// g++ main.cpp -std=gnu++11 -o laberinto

#include<iostream>
#include<vector>
#include<fstream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <stdlib.h>

using namespace std;

auto TTime = std::chrono::high_resolution_clock::now();

class Solucion{

	private:

		vector< vector<int> > *matriz;
		vector< pair<int,int> > x;

		vector< pair<int,int> > mejorSolucion, primeraSolucion;

        pair<int,int> END, GAMEOVER, NULO;

	public:
        decltype(TTime) firstSolTime;

	    vector< pair<int,int> > MejorSolucion();
	    vector< pair<int,int> > PrimeraSolucion();

		Solucion(vector<vector<int> > * pv);
		int Size() const;
		void IniciaComp(int k);
		void SigValComp(int k);
		bool TodosGenerados(int k);

        int cSoluciones;

		pair<int,int> Decision(int k)const;
		void ProcesaSolucion(int k);
		bool LlegueASolucion(int pos);

		bool TodosCeros(int k)const;

		bool TodosConsecutivos(int k)const;

		bool SinRepetidos(int k)const;

		// Todos son 0, son consecutivos y
		// no se pasa dos veces por el mismo lugar
		bool Factible(int k)const;
};


		pair<int,int> Solucion::Decision(int k)const{
		    return x[k];
        }

		void Solucion::ProcesaSolucion(int k){
                if (primeraSolucion.size() == 0){// no tengo ninguna todavia
                    firstSolTime = std::chrono::high_resolution_clock::now();
                     // marco la hora de la primera solucion
                    for(int i = 0; i < k + 1; i++){
                        primeraSolucion.push_back(x[i]);
                        mejorSolucion.push_back(x[i]);
                    }
                    cSoluciones = 0;
                    cout<<"Primera solucion encontrada."<<endl;
                }
                cSoluciones++;
                cout<<"Solucion: "<<cSoluciones<<"   Tamano= "<<k+1<<endl;

                if (mejorSolucion.size() > k){
                    mejorSolucion.clear();
                    for(int i = 0; i < k + 1; i++){
                        mejorSolucion.push_back(x[i]);
                    }
                }
		}

		bool Solucion::LlegueASolucion(int pos){
            return x[pos] == GAMEOVER;
		}

		bool Solucion::TodosCeros(int k)const{
            vector< vector<int> > &m = *matriz;
            bool res = true;
            for(int i = 0; i < k+1 && res; i++){
                if (m[x[i].first][x[i].second] != 0)
                    res = false;
            }
            return res;
		}

		bool Solucion::TodosConsecutivos(int k)const{
            bool res = true;
            for(int i = 0; i < k && res; i++){
                if ( std::abs(x[i].first  - x[i+1].first)  > 1 ||
                     std::abs(x[i].second - x[i+1].second) > 1 )

                    res = false;
            }
            return res;
		}

		bool Solucion::SinRepetidos(int k)const{
            bool res = true;
            for(int i = 0; i < k && res; i++){
                for(int j = i+1; j < k + 1 && res; j++){
                        if (x[i] == x[j])
                            res = false;
                    }
            }
            return res;
		}

		// Todos son 0, son consecutivos y
		// no se pasa dos veces por el mismo lugar
		bool Solucion::Factible(int k)const{
		    return TodosCeros(k) && TodosConsecutivos(k) && SinRepetidos(k);
		}

vector< pair<int,int> > Solucion::MejorSolucion(){ return mejorSolucion; }
vector< pair<int,int> > Solucion::PrimeraSolucion(){ return primeraSolucion; }

Solucion::Solucion(vector<vector<int> > *pv){
	matriz=pv;

    END = pair<int, int>(matriz->size(), matriz->size());
    GAMEOVER = pair<int, int>(matriz->size()-1, matriz->size()-1);
    NULO = pair<int,int>(-1,-1);

	for(int i=0; i<100; i++)
		x.push_back(NULO);
    x[0] = pair<int, int>(0, 0);
}


int Solucion::Size() const{
	return x.size();
}

void Solucion::IniciaComp(int k){
	x[k] = NULO;
}

void Solucion::SigValComp(int k){

    pair<int, int> norte = pair<int, int>(x[k-1].first - 1, x[k-1].second);
    pair<int, int> este  = pair<int, int>(x[k-1].first, x[k-1].second + 1);
    pair<int, int> sur   = pair<int, int>(x[k-1].first + 1, x[k-1].second);
    pair<int, int> oeste = pair<int, int>(x[k-1].first, x[k-1].second - 1);

    if (x[k] == NULO){
        if (x[k-1].first == 0){// primera fila
            if (x[k-1].second != matriz->size() - 1){
                x[k] = este;
            }else{ // ultima columna
                x[k]= sur;
            }
        }else{
               x[k]= norte;
        }
    }else{
        if (x[k] == norte){// primera posicion, next: este o sur
            if (x[k-1].second != matriz->size() - 1){
                x[k] = este;
            }else{
                x[k] = sur;
            }
        }else if (x[k] == este){ // segunda posicion, next: sur, oeste o END
            if (x[k-1].first != matriz->size() - 1){
                x[k] = sur;
            }else{
                if (x[k-1].second != 0)
                    x[k] = oeste;
                else
                    x[k] = END;
            }
        }else if (x[k] == sur){// tercera posicion, next: oeste o END
            if (x[k-1].second != 0){
                x[k] = oeste;
            }else{
                x[k] = END;
            }
        }else if (x[k] == oeste){
            x[k] = END;
        }
    }
}

bool Solucion::TodosGenerados(int k){
    return x[k] == END;
}

void back_recursivo(Solucion &sol, int k){
    /*
    if (k > 50){
        cout<<"ERROR!!!"<<endl;
        exit(1);
    }
    */
    if (sol.LlegueASolucion(k - 1)){
        sol.ProcesaSolucion(k - 1);
    }else{
        sol.IniciaComp(k);
        sol.SigValComp(k);
        while(!sol.TodosGenerados(k)){
            if(sol.Factible(k)){
                back_recursivo(sol, k+1);
            }
            sol.SigValComp(k);
        }
    }
}


int main(int argc, char* argv[]){

    vector< vector<int> > *mat = new vector< vector<int> >();
    vector< vector<int> > &m = *mat;

    std::ifstream file(argv[1]);
    std::string str;
    int fila = 0;
    while (std::getline(file, str)){
        m.push_back(vector<int>());
        for(int i = 0; i < str.size(); i += 2){
            if (str[i]=='0'){
                m[fila].push_back(0);
            }else {
                m[fila].push_back(1);
            }
        }
        fila++;
    }


    decltype(TTime) startTime = std::chrono::high_resolution_clock::now();

    Solucion bt(mat);
    back_recursivo(bt, 1);

    decltype(TTime) allSolutionTime = std::chrono::high_resolution_clock::now();

    cout<<"Primera solucion encontrada: "<<endl;
    for(int i = 0; i < bt.PrimeraSolucion().size(); i++){
        cout<<"("<<bt.PrimeraSolucion()[i].first<<", "<<bt.PrimeraSolucion()[i].second<<") ";
    }

    cout<<"Tiempo demorado en encontrar la primera solucion: "<<std::chrono::duration_cast<std::chrono::milliseconds>(bt.firstSolTime - startTime).count()<< " ms"<<endl;

    cout<<endl;

    cout<<"Mejor solucion encontrada: "<<endl;
    for(int i = 0; i < bt.MejorSolucion().size(); i++){
        cout<<"("<<bt.MejorSolucion()[i].first<<", "<<bt.MejorSolucion()[i].second<<") ";
    }

    cout<<"Tiempo demorado en encontrar la mejor solucion: "<<std::chrono::duration_cast<std::chrono::milliseconds>(allSolutionTime - startTime).count()<< " ms"<<endl;

    delete mat;

}
