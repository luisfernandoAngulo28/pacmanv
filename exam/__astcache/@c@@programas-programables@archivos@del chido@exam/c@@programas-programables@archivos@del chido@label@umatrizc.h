//---------------------------------------------------------------------------

#ifndef UMatrizCH
#define UMatrizCH
//---------------------------------------------------------------------------
#include <iostream>
#include <string>

using namespace std;

//int MAX_MV = 0;

class MatrizC {
private:
	int* vf;
	int* vc;
	char* vd;
	int df, dc;
	int repe;
	int nt;

	int posicion(int f, int c);

public:
	MatrizC();
	void dimensionar(int f, int c);
	int get_repe();
	int dimension_fila();
	int dimension_columna();
	void poner(int f, int c, char valor);
	char elemento(int f, int c);
	void definir_valor_repetido(char valor);
	string to_str();
};
#endif
