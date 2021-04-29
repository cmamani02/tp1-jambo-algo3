/* 
================================================================================
 TRABAJO PRACTICO 1 - Jambo Tubos - Algoritmos y Estructura de Datos III - FCEN
================================================================================
*/
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>
using namespace std;

const int INFINITO = INT_MAX;

// Información de la instancia a resolver.
int R;
int n;
vector<int> r; // resistencias
vector<int> w; // pesos

/***Fueza Bruta***/
// i: posicion del elemento a considerar en este nodo.
// p: suma de los pesos de los elementos seleccionados hasta este nodo.
// mr: maxima resistencia que soportan sin romperse los elementos 
//    seleccionados hasta este nodo. Inicialmente su valor sera la resistencia del tubo.
// k: cantidad de elementos seleccionados hasta este nodo.
int PJT_FB(int i, int p, int mr, int k){
    // Caso base
    if(i == n){ 
        if(mr >= 0 and p <= R) return k;
        else return -INFINITO;
    }
    // Recursion.
    int no_agrego = PJT_FB(i+1, p, mr, k); 
    int agrego = PJT_FB(i+1, p+w[i], min(mr-w[i], r[i]), k+1);
    return max(no_agrego, agrego);  
}
//PJT_FB(0,0,R,0) es la solucion al problema

/***Programacion Dinamica***/
const int UNDEFINED = -1;
vector<vector<int>> D; // Memoria de PD.

// jambo_PD(i, j): maxima cantidad de productos que se puede apilar considerando los 
// los productos {Si, ... Sn}, cuando j es la maxima resistencia que se puede utilizar 
int jambo_PD(int i, int j){
    if(j < 0) return -INFINITO;
    if(i == n && j >= 0) return 0;
        
    if(D[i][j] == UNDEFINED){
        int caso_no_agrego = jambo_PD(i+1,j); 
        int caso_agrego = jambo_PD(i+1, min(j-w[i], r[i]) ) + 1;
        int aux = max(caso_no_agrego, caso_agrego);
        D[i][j] = aux;
    }
    return D[i][j];
}
// jambo_PD(0, R) es la solucion al problema

/***Programacion Dinamica***/
// i: posicion del elemento a considerar en este nodo.
// p: suma de los pesos de los elementos seleccionados hasta este nodo.
// mr: maxima resistencia que soportan sin romperse los elementos 
//    seleccionados hasta este nodo. Inicialmente su valor sera la resistencia del tubo.
// k: cantidad de elementos seleccionados hasta este nodo.
bool poda_factibilidad; // define si la poda por factibilidad esta habilitada.
bool poda_optimalidad; // define si la poda por optimalidad esta habilitada.
int max_global = 0; // Mejor solucion hasta el momento.
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

    // Poda por optimalidad.
    int k2 = n - i; // cantidad de productos sin explorar 
    if(poda_optimalidad && k + k2 <= max_global) return -INFINITO;

    // Recursion.
    int no_agrego = PJT_BT(i+1, p, mr, k); 
    int agrego = PJT_BT(i+1, p+w[i], min(mr-w[i], r[i]), k+1);
    return max(no_agrego, agrego);  
}
// PJT_BT(0,0,R,0) es la solucion al problema



// Recibe por parámetro qué algoritmos utilizar para la ejecución separados por espacios.
// Imprime por clog la información de ejecución de los algoritmos.
// Imprime por cout el resultado de algun algoritmo ejecutado.
int main(int argc, char** argv)
{
    // Leemos el parametro que indica el algoritmo a ejecutar.
    map<string, string> algoritmos_implementados = {
        {"FB", "Fuerza Bruta"}, {"BT", "Backtracking con podas"}, {"BT-F", "Backtracking con poda por factibilidad"}, 
        {"BT-O", "Backtracking con poda por optimalidad"}, {"DP", "Programacion dinámica"}
    };

    // Verificar que el algoritmo pedido exista.
    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    // Leemos el input.
    cin >> n >> R;
    w.assign(n, 0);
    r.assign(n, 0);
    for (int i = 0; i < n; ++i) cin >> w[i] >> r[i];

    // Ejecutamos el algoritmo y obtenemos su tiempo de ejecución.
    int optimum;
    optimum = 0;
    auto start = chrono::steady_clock::now();
    if (algoritmo == "FB")
    {
        optimum = PJT_FB(0, 0,R,0);
    }
    else if (algoritmo == "BT")
    {
        poda_optimalidad = poda_factibilidad = true;
        optimum = PJT_BT(0,0,R,0);
    }
    else if (algoritmo == "BT-F")
    {
        poda_optimalidad = false;
        poda_factibilidad = true;
        optimum = PJT_BT(0,0,R,0);
    }
    else if (algoritmo == "BT-O")
    {
        poda_optimalidad = true;
        poda_factibilidad = false;
        optimum = PJT_BT(0,0,R,0);
    }
    else if (algoritmo == "DP")
    {
        // Precomputamos la solucion para los estados.
        D = vector<vector<int>>(n+1, vector<int>(R+1, UNDEFINED));
        for (int i = 0; i < n+1; ++i)
            for (int j = 0; j < R+1; ++j)
                jambo_PD(i, j);

        // Obtenemos la solucion optima.
        optimum = jambo_PD(0, R);
    }
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();

    // Imprimimos el tiempo de ejecución por stderr.
    clog << total_time << endl;

    // Imprimimos el resultado por stdout.
    cout << optimum << endl;
    return 0;
}