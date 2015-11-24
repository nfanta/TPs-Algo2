#ifndef AED2_TIPOS_H_
#define AED2_TIPOS_H_

#include "aed2/TiposBasicos.h"

namespace aed2{

	typedef struct {Nat x,y;} Posicion;
	typedef enum {izq,der,arriba,abajo} Direccion;
	typedef Nat Agente;
	typedef String Nombre;

	bool operator!=(const Posicion p1, const Posicion p2) {
		return (p1.x != p2.x) || (p1.y != p2.y);
	}
	bool operator==(const Posicion p1, const Posicion p2) {
		return (p1.x == p2.x) && (p1.y == p2.y);
	}
} // namespace aed2

#endif // AED2_TIPOS_H_
