#include <bits/stdc++.h>
#include <limits>

using namespace std;

// fuerza bruta:
int resistencia_tubo; // es R
int n;
int R;
const int INFINITO = INT_MAX;
vector<int> r; // resistencias
vector<int> w; // pesos

vector<int> sol_parcial; // inicialmente en cero

int max_global = 0; // Mejor solucion hasta el momento.

// verifica si algun producto de la solucion parcial se aplasto.
// devuelve true si ningun producto se aplasto
// 					false en caso contrario
bool resistencia_valida(){
  bool ans = true;
  
  int resis_actual = 0;
  int max_resis = 0;
  
  // indice del primer elemento agregado
  int index_i = n;
  for(int i=0; i < n; i++){
  	if(sol_parcial[i] == 1){
    	index_i = i;
      break;
    } 
  }
  
  if(index_i < n) {
  	max_resis = R[index_i];
  }
  
  for(int i=index_i; i < n; i++){
    if(sol_parcial[i] == 1){
      if(W[i] > max_resis){
      	ans = false;
      	break;
      }
      resis_actual = R[i];
      max_resis = min(max_resis-W[i],resis_actual);
    }
  }
  return ans;
}

// recorre todos los posibles subconjuntos
//agregar que devuelva int

void jambo_fuerza_bruta(int cardinal, int peso_actual, int i){ // {e_i, ..., e_n}
	if(i == n){ // recorrio todo
  		if(resistencia_valida() and peso_actual <= resistencia_tubo
      	 and cardinal > max_global){
    		max_global = cardinal;
    	}
    	return;
  	}
  
  sol_parcial[i] = 1;
  jambo_fuerza_bruta(cardinal+1,peso_actual+W[i],i+1);
  sol_parcial[i] = 0;
  jambo_fuerza_bruta(cardinal,peso_actual,i+1); 
}

//#define INT_MAX 2147483647
// poda factibilidad
const int max_resistencia = INT_MAX; // 1e9+7 inicializar en INFINITO
//int ans = jambo_backtrakingPF(.. ,max_resistencia);

void jambo_backtrakingPF(int cardinal, int peso_actual, int max_resistencia, int i){
  if(max_resistencia < 0 || peso_actual > resistencia_tubo){return;} //poda por factibilidad
  
	if(i == n){ // recorrio todo
  	if(cardinal > max_global){
    		max_global = cardinal;
  	}
    return;
  }
  
  sol_parcial[i] = 1;
  int max_resistencia_actual = min(max_resistencia-W[i],R[i]); // valor auxiliar
  jambo_backtrakingPF(cardinal+1,peso_actual+W[i],max_resistencia_actual,i+1);
  
  sol_parcial[i] = 0;
  jambo_backtrakingPF(cardinal,peso_actual,max_resistencia, i+1); 
}
// Se juntan los 2 algoritmos de backtracking
// i: posicion del elemento a considerar en este nodo.
// p: suma de los pesos de los elementos seleccionados hasta este nodo.
// mr: maxima resistencia que soportan sin romperse los elementos 
//    seleccionados hasta este nodo. Inicialmente su valor sera la resistencia del tubo.
// k: cantidad de elementos seleccionados hasta este nodo.
bool poda_factibilidad = true; // define si la poda por factibilidad esta habilitada.
bool poda_optimalidad = true; // define si la poda por optimalidad esta habilitada.
int PJT_BT(int i, int p, int mr, int k)
{
	// Caso base
	if(i == n){ 
  		if(mr >= 0 and p <= R){
			max_global = max(max_global, k);	  
        	return k;
    	}
    	else{
        	return -INFINITO;
  	 	}
  	}
  
	// Poda por factibilidad.
    if(poda_factibilidad && (mr < 0 || p > R)) return -INFINITO;

	// Poda por optimalidad. (vale que 0<= i < n)
	int k2 = n - i; // cantidad de productos sin explorar 
    if (poda_optimalidad && k + k2 <= max_global) return -INFINITO;

	// Recursion.
	int agrego = PJT_BT(i+1, p+w[i], min(mr-w[i], r[i]), k+1);
	int no_agrego = PJT_BT(i+1, p, mr, k); 
	return max(agrego, no_agrego);  
}
// PJT_BT(0,0,R,0) es la solucion al problema

int max_resistencia; // inicializar el INFINITO, consultar con docente
int cant_sin_explorar; // se inicializa en el valor n.
void jambo_backtrakingPO(int cardinal, int peso_actual, int max_resistencia, int cantidad_sin_explorar, int i){
  if(max_resistencia < 0 || peso_actual > resistencia_tubo) return; //poda por factibilidad
  
  if(cantidad_sin_explorar + cardinal <= max_global) return; // poda por optimalidad
  
	if(i == n){ // recorrio todo
  	if(cardinal > max_global){
    		max_global = cardinal;
  	}
    return;
  }
  
  sol_parcial[i] = 1;
  int max_resistencia_actual = min(max_resistencia-W[i],R[i]);
  // por que no agrege el 
  jambo_backtrakingPO(cardinal+1,peso_actual+W[i],max_resistencia_actual,cant_sin_explorar-1,i+1);
  
  //no agrega el elemento, y el conjunto restante 
  sol_parcial[i] = 0;
  jambo_backtrakingPO(cardinal,peso_actual,max_resistencia,cant_sin_explorar-1,i+1); 
}

//programacion dinamica

// arranca en n y reduce
// solucion = func(n,R)

//func(i, j) = 
//*  0                                        si i = 0

//* func(i-1, j)                              si j - w[i] < 0 // vale i < n

//* max{ func(i-1, j),                        caso contrario// podes agregar el i-esimo
//			 func(i-1, min(j-w[i], r[i]) ) + 1 }
       
       
vector<vector<int>> D; // diccionario
#define BOTTOM -1

int jambo_PD(int i, int j){
	if(i == 0){return 0;}
  	
  	if(D[i][j] == BOTTOM){
  		if(j - w[i] < 0){
    		int aux = jambo_PD(i-1,j);
      		D[i][j] = aux;
      	}
    }
    else{
    	int caso_agrego = jambo_PD(i-1, min(j-w[i], r[i]) ) + 1;
    	int caso_no_agrego = jambo_PD(i-1,j); 
      	int aux = max(caso_no_agrego, caso_agrego);
    	D[i][j] = aux; //calculo(i,j);
  }
  return D[i][j];
}


// nueva fuerza bruta

// i: posicion del elemento a considerar en este nodo.
// p: suma de los pesos de los elementos seleccionados hasta este nodo.
// mr: maxima resistencia que soportan sin romperse los elementos 
//    seleccionados hasta este nodo. Inicialmente su valor sera la resistencia del tubo.
// k: cantidad de elementos seleccionados hasta este nodo.
int PJT_FB(int i, int p, int mr, int k)
{
	// Caso base
	if(i == n){ 
  		if(mr >= 0 and p <= R){
        	return k;
    	}
    	else{
        	return -INFINITO;
  	 	}
  	}
  
	// Recursion.
	int agrego = PJT_FB(i+1, p+w[i], min(mr-w[i], r[i]), k+1);
	//OJO: puede ser que r[0]< mr-w[0], pero esta bien, pues si el primer producto
	// tiene muy poca resistencia, no me va a importar que el tubo tenga R = 500
	int no_agrego = PJT_FB(i+1, p, mr, k); 
	return max(agrego, no_agrego);  
}
//PJT_FB(0,0,R,0) es la solucion al problema

int main(){
    cin >> n;
    sudoku.resize(n,vector<int>(n,0));

       
    return 0;
}
