#include "Driver.h"

namespace aed2 {

Driver::Driver() 
{
    // TODO
	assert(false);
}

Driver::~Driver()
{
    // TODO
	assert(false);
}


/// Generadores del Campus

void Driver::crearCampus(Nat ancho, Nat alto)
{
	_c = Campus(ancho, alto);
}

void Driver::agregarObstaculo(Posicion p)
{
    _c.AgregarObstaculo(p);
}


/// Observadores del Campus\

Nat Driver::filas() const
{
	return _c.Filas();
}

Nat Driver::columnas() const
{
	return _c.Columnas();
}

bool Driver::ocupada(Posicion p) const
{
	return _c.Ocupada(p);
}


/// Generadores de CampusSeguro
void  Driver::comenzarRastrillaje(const Dicc<Agente,Posicion>& d) {
    _cs = CampusSeguro(_c, d);
}

void Driver::ingresarEstudiante(Nombre n, Posicion p)
{
    _cs.IngresarEstudiante(n, p);
}

void Driver::ingresarHippie(Nombre n, Posicion p)
{
	_cs.IngresarHippie(n, p);
}

void Driver::moverEstudiante(Nombre n, Direccion d)
{
	_cs.MoverEstudiante(n, d);
}

void Driver::moverHippie(Nombre n)
{
	_cs.MoverHippie(n);
}

void Driver::moverAgente(Agente pl)
{
	_cs.MoverAgente(pl);
}


/// Observadores de CampusSeguro

Nombre Driver::iesimoEstudiante(Nat i) const
{
	Conj<String>::Iterador tmp = _cs.Estudiantes();

	for (int j = 0; j < i; ++j) {
		tmp.Avanzar();
	}

	return tmp.Siguiente();
}

Nombre Driver::iesimoHippie(Nat i) const
{
	Conj<String>::Iterador tmp = _cs.Hippies();

	for (int j = 0; j < i; ++j) {
		tmp.Avanzar();
	}

	return tmp.Siguiente();
}

Nat Driver::iesimoAgente(Nat i) const
{
	Conj<Nat>::Iterador tmp = _cs.dameAgentes();

	for (int j = 0; j < i; ++j) {
		tmp.Avanzar();
	}

	return tmp.Siguiente();
}

Nat Driver::cantEstudiantes() const {
	Conj<String>::Iterador tmp = _cs.Estudiantes();
	Nat i = 0;

	while (tmp.HaySiguiente()) {
		i++;
		tmp.Avanzar();
	}

	return i;
}

Nat Driver::cantHippies() const
{
	Conj<String>::Iterador tmp = _cs.Hippies();
	Nat i = 0;

	while (tmp.HaySiguiente()) {
		i++;
		tmp.Avanzar();
	}

	return i;
}

Nat Driver::cantAgentes() const
{
	Conj<Nat>::Iterador tmp = _cs.dameAgentes();
	Nat i = 0;

	while (tmp.HaySiguiente()) {
		i++;
		tmp.Avanzar();
	}

	return i;
}

Posicion Driver::posEstudianteYHippie(Nombre n) const
{
    _cs.PosHippieYEstudiante(n);
}

Posicion Driver::posAgente(Agente pl) const
{
    _cs.PosAgente(pl);
}

Nat Driver::cantSanciones(Agente pl) const
{
    _cs.CantSanciones(pl);
}

Nat Driver::cantHippiesAtrapados(Agente pl) const
{
    _cs.CantHippiesAtrapados(pl);
}


/// Otras operaciones de CampusSeguro

Agente Driver::másVigilante() const
{
    _cs.MasVigilante();
}

const Conj<Agente> Driver::conMismasSanciones(Agente a) const
{
	return _cs.ConMismasSanciones();
}

const Conj<Agente> Driver::conKSanciones(Nat k)
{
    return _cs.ConKSanciones(k);
}


} // namespace aed2

