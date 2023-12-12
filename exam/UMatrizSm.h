//---------------------------------------------------------------------------

#ifndef UMatrizSmH
#define UMatrizSmH

#include <iostream>
#include <string>
#include "Umem.h"
//---------------------------------------------------------------------------
using namespace std;

const string datosS = "	Fila,Col,sig";
const string ColS = "->Col";
const string FilaS = "->Fila";
const string sigS = "->sig";

struct Nodosm{
int fil ;
int col ;
int dato;
int punt;
Nodosm* sig;
};

class MatrizSm{
private:
 CSMemoria* mem;
 Nodosm* PtrMatSm ;
 CSMemoria* memo;
 int repe, df, dc, nt;
public:
	MatrizSm();              //
	MatrizSm(CSMemoria* m);  //
	void dimensionar(int df,int dc);//
	int  dimension_fila();      //
	int  dimension_col();      //
	int  elemento(int f, int c);
	int dimension_columna();    //
	int getpunt(Nodosm* a);
	int prueba();
	Nodosm* buscar(int f,int c);
	void poner(int f,int c, int valor);
	void  definir_valor_repetido(int valor);
	string to_str();
	string to_str_c();
	string get_fila(int f);
	string get_linea(int f);
	int get_max();
};


#endif


