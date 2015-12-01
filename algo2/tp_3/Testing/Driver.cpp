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
    // TODO
	assert(false);
}

Nombre Driver::iesimoHippie(Nat i) const
{
    // TODO
	assert(false);
}

Nat Driver::iesimoAgente(Nat i) const
{
    // TODO
	assert(false);
}

Nat Driver::cantEstudiantes() const {
    // TODO
	assert(false);

}

Nat Driver::cantHippies() const
{    // TODO
	assert(false);
}

Nat Driver::cantAgentes() const
{
    // TODO
	assert(false);
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

