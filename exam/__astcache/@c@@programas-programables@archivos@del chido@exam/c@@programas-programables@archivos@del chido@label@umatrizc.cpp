//---------------------------------------------------------------------------

#pragma hdrstop

#include "UMatrizC.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

MatrizC::MatrizC() {
	/* df = 0;
	 dc = 0;
	 repe = 0;
	 nt = 0; */
	df = dc = repe = nt = 0;
	vf = new int[0];
	vc = new int[0];
	vd = new char[0];
}

void MatrizC::dimensionar(int f, int c) {
	df = f;
	dc = c;
	// MAX_MV = f * c;
	// Se vacian los vectores
	/*
	 vf = new int[MAX_MV];
	 vc = new int[MAX_MV];
	 vd = new int[MAX_MV]; */
	vf = new int[df * dc];
	vc = new int[df * dc];
	vd = new char[df * dc];
}


int MatrizC::get_repe() {
	return repe;
}

int MatrizC::dimension_fila() {
	return df;
}

int MatrizC::dimension_columna() {
	return dc;
}

int MatrizC::posicion(int f, int c) {
	for (int i = 0; i < nt; i++) {
		if (vf[i] == f && vc[i] == c)
			return i;
	}
	return -1;
}

void MatrizC::poner(int f, int c, char valor) {
	if (f >= 1 && f <= df && c >= 1 && c <= dc) {
		int lugar = posicion(f, c);
		if (lugar == -1 && nt < (df * dc)) // nt < MAX_MV
		{ // insertar a lo ultimo
			if (valor != repe) {
				vd[nt] = valor;
				vf[nt] = f;
				vc[nt] = c;
				nt++;
			}
		}
		else {
			vd[lugar] = valor;
			if (valor == repe) {
				for (int i = lugar; i < nt; i++) {
					vf[i] = vf[i + 1];
					vc[i] = vc[i + 1];
					vd[i] = vd[i + 1];
				}
				nt--;
			}
		}
	}
}

char MatrizC::elemento(int f, int c) {
	if (f >= 0 && f <= df && c >= 0 && c <= dc) {
		int lugar = posicion(f, c);
		if (lugar >= 0)
			return vd[lugar];
		else
			return repe;
	}
	else
		cout << "ERROR FUERA DE RANGO\n";
}

void MatrizC::definir_valor_repetido(char valor) {
	bool hayRepe = false;
	for (int i = 0; i < nt && hayRepe == false; i++) {
		if (vd[i] == valor)
			hayRepe = true;
	}
	if (nt == 0 || hayRepe == false) {
		repe = valor;
	}
	else {
		int nRep = valor;
		int aRep = repe;
		for (int i = 1; i <= df; i++) {
			for (int j = 1; j <= dc; j++) {
				int e = elemento(i, j);
				if (e == nRep) {
					int lugar = posicion(i, j);
					for (int k = lugar; k < nt; k++) {
						vf[k] = vf[k + 1];
						vc[k] = vc[k + 1];
						vd[k] = vd[k + 1];
					}
					nt--;
				}
				else if (e == aRep) {
					vd[nt] = aRep;
					vf[nt] = i;
					vc[nt] = j;
					nt++;
				}
			}
		}
		repe = valor;
	}
}

/*
 | 3 0 5 |
 | 0 1 0 |
 | 0 0 9 | */
string MatrizC::to_str() {
	string r = "";
	for (int i = 1; i <= df; i++) {
		r += "| ";
		for (int j = 1; j <= dc; j++) {
			char e = elemento(i, j);
			r += to_string(e) + "  ";
		}
		r += "|\n";
	}
	r += "NT: " + to_string(nt) + "\n";
	/*
	 int max = df * dc;
	 r += "vf: ";
	 for (int i = 0; i < max; i++)
	 r += to_string(vf[i]) + ",";
	 r += "\nvc: ";
	 for (int i = 0; i < max; i++)
	 r += to_string(vc[i]) + ",";
	 r += "\nvd: ";
	 for (int i = 0; i < max; i++)
	 r += to_string(vd[i]) + ",";
	 */
	return r;
}
