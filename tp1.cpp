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
  
       
vector<vector<int>> D; // diccionario de memoizacion
#define BOTTOM -1
// jambo_PD(i, j): maxima cantidad de productos que se puede apilar considerando los 
// los productos {Si, ... Sn}, cuando j es la maxima resistencia que se puede utilizar 

// BORRAR: Esta maxima resistencia combina la informacion del tubo, y esta actualizada según los pasos previos.
// configuracion nueva de los subproblemas
int PJT_PD(int i, int j){
	if(j < 0) return -INFINITO;
	if(i == n && j >= 0) return 0; // ya no se pueden agregar elementos
  	
  	if(D[i][j] == BOTTOM){
    	int no_agrego = PJT_PD(i+1,j); 
    	int agrego = PJT_PD(i+1, min(j-w[i], r[i]) ) + 1;
    	D[i][j] = max(no_agrego, agrego);
  	}
  	return D[i][j];
}
// jambo_PD(0, R) es la solucion al problema


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
	int no_agrego = PJT_FB(i+1, p, mr, k);
	int agrego = PJT_FB(i+1, p+w[i], min(mr-w[i], r[i]), k+1);
	//OJO: puede ser que r[0]< mr-w[0], pero esta bien, pues si el primer producto
	// tiene muy poca resistencia, no me va a importar que el tubo tenga R = 500
	return max(no_agrego, agrego);  
}
//PJT_FB(0,0,R,0) es la solucion al problema

int main(){
    cin >> n;
    sudoku.resize(n,vector<int>(n,0));

       
    return 0;
}
