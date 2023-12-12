//---------------------------------------------------------------------------

#pragma hdrstop

#include "UMatrizSm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
 MatrizSm ::MatrizSm () {
	PtrMatSm  = NULL;
	df = dc = repe = 0;
	nt = 0;
	memo = new CSMemoria();
}

MatrizSm ::MatrizSm (CSMemoria* m) {
	PtrMatSm  = NULL;
	df = dc = repe = 0;
	nt = 0;
	memo=m;
}

void MatrizSm ::dimensionar(int f, int c) {
	df = f;
	dc = c;
}

int MatrizSm ::dimension_fila() {
	return df;
}

int MatrizSm ::dimension_col() {
	return dc;
}

int MatrizSm ::getpunt(Nodosm* a) {
	int xd=1;
	Nodosm * aux= PtrMatSm;
	while (aux!=a){
	aux=aux->sig;
	xd=xd+1;
	}


	return xd-1;





}

int MatrizSm ::prueba() {
	return getpunt(PtrMatSm);
}

int MatrizSm ::dimension_columna() {
	return dc;
}

Nodosm * MatrizSm ::buscar(int f, int c) {

	Nodosm * aux = PtrMatSm ;
	while (aux != NULL) {
		if (aux->fil == f && aux->col == c)
			return aux;
		aux = aux->sig;
	}
	return NULL;
}

void MatrizSm ::poner(int f, int c, int valor) {
int punt=2;
	if (f >= 1 && f <= df && c >= 1 && c <= dc) {
		Nodosm * dir = buscar(f, c);
		if (dir == NULL && valor != repe) { // Dato nuevo
			Nodosm * x = new Nodosm ;
			int aux = memo->new_espacio("fila,columna,dato,sig");
			if (x != NULL) {
				memo->poner_dato(aux,"->fila", f); // aux->coef = coef;
				memo->poner_dato(aux,"->columna", c); // aux->exp = exp;
				memo->poner_dato(aux,"->dato", valor); // aux->sig = ptr_poli;
				x->fil = f;
				x->col = c;
				x->dato = valor;
				x->sig = PtrMatSm ;
				PtrMatSm  = x;
				nt++;
				   Nodosm * auxiliar =PtrMatSm;
				   int i=1;
				   while (auxiliar!=NULL){
				   auxiliar->punt=i;
				   i++;
				   auxiliar=auxiliar->sig;
				   }

			}
			else
				cout << "ERROR NO EXISTE ESPACIO DE MEMORIA\n";
		}
		else {
			dir->dato = valor;
			 memo->poner_dato(((nt*4)-2)-(getpunt(dir)*4),"->dato", valor);
			if (valor == repe) {
				// Codigo de suprimir
				if (dir == PtrMatSm )
					PtrMatSm  = PtrMatSm ->sig;
				else {
					Nodosm * ant;
					// Codido de anterior
					Nodosm * x = PtrMatSm ;
					ant = NULL;

					while (x != NULL) {
						if (x == dir)
							break;
						ant = x;
						x = x->sig;
						punt=punt+4;
					}
					//

					ant->sig = dir->sig;
					memo->poner_dato(punt,"->dato", valor);
				}
				delete(dir);
				nt--;
				//
			}
		}
	}
}

int MatrizSm ::elemento(int f, int c) {
	if (f >= 1 && f <= df && c >= 1 && c <= dc) {
		Nodosm * dir = buscar(f, c);
		if (dir != NULL)
			return dir->dato;
		else
			return repe;
	}
}

void MatrizSm ::definir_valor_repetido(int valor) {
	bool hayRepe = false;
	Nodosm * aux = PtrMatSm ;
	while (aux != NULL && hayRepe == false) {
		if (aux->dato == valor)
			hayRepe = true;
		aux = aux->sig;
	}
	if (PtrMatSm  == NULL || hayRepe == false) {
		repe = valor;
	}
	else {
		int nRep = valor;
		int aRep = repe;
		for (int i = 1; i <= df; i++) {
			for (int j = 1; j <= dc; j++) {
				int e = elemento(i, j);
				if (e == nRep) {
					Nodosm * dir = buscar(i, j);
					// Codigo de suprimir
					if (dir == PtrMatSm )
						PtrMatSm  = PtrMatSm ->sig;
					else {
						Nodosm * ant;
						// Codido de anterior
						Nodosm * x = PtrMatSm ;
						ant = NULL;
						while (x != NULL) {
							if (x == dir)
								break;
							ant = x;
							x = x->sig;
						}
						//
						ant->sig = dir->sig;
					}
					delete(dir);
					nt--;
					//
				}
				else if (e == aRep) {
					Nodosm * x = new Nodosm ;
					if (x != NULL) {
						x->fil = i;
						x->col = j;
						x->dato = aRep;
						x->sig = PtrMatSm ;
						PtrMatSm  = x;
						nt++;
					}
					else
						cout << "ERROR NO EXISTE ESPACIO DE MEMORIA\n";
				}
			}
		}
		repe = valor;
	}
}

string MatrizSm ::to_str() {
	string r = "";
	for (int i = 1; i <= df; i++) {
		r += "| ";
		for (int j = 1; j <= dc; j++) {
			int e = elemento(i, j);
			r += to_string(e) + "  ";
		}
		r += "|\n";
	}
	r += "NT: " + to_string(nt) + "\n";
	cout<<repe<<endl;
	return r;

}

string MatrizSm ::to_str_c() {
	string r = "";
	for (int i = 1; i <= df; i++) {
		r += "| ";
		for (int j = 1; j <= dc; j++) {
			int e = elemento(i, j);
			r += to_string(e) + "  ";
		}
		r += "|,";
	}
   //	r += "NT: " + to_string(nt) + ",\n";
	//cout<<repe<<endl;
	return r;

}

string MatrizSm :: get_fila (int f) {
	int i=0;
	int j=0;
	string fila = "";
	string pal = to_str_c();
	int c =pal.length();

	while (i < pal.length() && j < f){   //  && fila<f


	  if (pal[i] == ',') {
	  j++;
		if (j<f) {
		fila="";
		i++;
		}
	  }

	  if (pal[i] != ',') {
	  fila =fila+pal[i];
	  i++;
	  }


	}


	return fila;

}

string MatrizSm :: get_linea (int f) {
	string fila = "";
	fila=  memo->get_linea(f);

	return fila;

}

int MatrizSm :: get_max() {
	return memo->get_MAX() ;
}
