#include <bits/stdc++.h>
#include <limits>

using namespace std;

const int INFINITO = INT_MAX;

int n, R;
vector<int> r; // resistencias
vector<int> w; // pesos

int max_global = 0; // Mejor solucion hasta el momento.

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
    if(poda_optimalidad && k + k2 <= max_global) return -INFINITO;

	// Recursion.
	int no_agrego = PJT_BT(i+1, p, mr, k); 
	int agrego = PJT_BT(i+1, p+w[i], min(mr-w[i], r[i]), k+1);
	return max(no_agrego, agrego);  
}
// PJT_BT(0,0,R,0) es la solucion al problema
  
       
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
