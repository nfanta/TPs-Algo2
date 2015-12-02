#include "Driver.h"

namespace aed2 {

Driver::Driver()
{
    _cs = new CampusSeguro();
	_c = new Campus(0,0);
}

Driver::~Driver()
{
    delete _cs;
	delete _c;
}


/// Generadores del Campus

void Driver::crearCampus(Nat ancho, Nat alto)
{
	delete _c;
	_c = new Campus(ancho, alto);
}

void Driver::agregarObstaculo(Posicion p)
{
	Posicion tmp = {p.y, p.x};
    _c->AgregarObstaculo(tmp);
}


/// Observadores del Campus\

Nat Driver::filas() const
{
	return _c->Filas();
}

Nat Driver::columnas() const
{
	return _c->Columnas();
}

bool Driver::ocupada(Posicion p) const
{
	Posicion tmp = {p.y, p.x};
	return _c->Ocupada(tmp);
}


/// Generadores de CampusSeguro
void  Driver::comenzarRastrillaje(const Dicc<Agente,Posicion>& d) {
	Dicc<Agente, Posicion>::Iterador ittr = d.CrearIt();
		Dicc<Agente, Posicion> dicc;

		while (ittr.HaySiguiente()) {
			dicc.Definir(ittr.Siguiente().clave, {ittr.Siguiente().significado.y, ittr.Siguiente().significado.x});
			ittr.Avanzar();
		}

		delete _cs;
    _cs = new CampusSeguro(*_c, dicc);

}

void Driver::ingresarEstudiante(Nombre n, Posicion p)
{
	Posicion tmp = {p.y, p.x};
    _cs->IngresarEstudiante(n, tmp);
}

void Driver::ingresarHippie(Nombre n, Posicion p)
{
	Posicion tmp = {p.y, p.x};
	_cs->IngresarHippie(n, tmp);
}

void Driver::moverEstudiante(Nombre n, Direccion d)
{
	_cs->MoverEstudiante(n, d);
}

void Driver::moverHippie(Nombre n)
{
	_cs->MoverHippie(n);
}

void Driver::moverAgente(Agente pl)
{
	_cs->MoverAgente(pl);
}


/// Observadores de CampusSeguro

Nombre Driver::iesimoEstudiante(Nat i) const
{
	Conj<String>::const_Iterador tmp = _cs->Estudiantes();

	for (int j = 0; j < i; ++j) {
		tmp.Avanzar();
	}

	return tmp.Siguiente();
}

Nombre Driver::iesimoHippie(Nat i) const
{
	Conj<String>::const_Iterador tmp = _cs->Hippies();

	for (int j = 0; j < i; ++j) {
		tmp.Avanzar();
	}

	return tmp.Siguiente();
}

Nat Driver::iesimoAgente(Nat i) const
{
	Conj<Nat>::const_Iterador tmp = _cs->dameAgentes();

	for (int j = 0; j < i; ++j) {
		tmp.Avanzar();
	}

	return tmp.Siguiente();
}

Nat Driver::cantEstudiantes() const {
	Conj<String>::const_Iterador tmp = _cs->Estudiantes();
	Nat i = 0;

	while (tmp.HaySiguiente()) {
		i++;
		tmp.Avanzar();
	}

	return i;
}

Nat Driver::cantHippies() const
{
	Conj<String>::const_Iterador tmp = _cs->Hippies();
	Nat i = 0;

	while (tmp.HaySiguiente()) {
		i++;
		tmp.Avanzar();
	}

	return i;
}

Nat Driver::cantAgentes() const
{
	Conj<Nat>::const_Iterador tmp = _cs->dameAgentes();
	Nat i = 0;

	while (tmp.HaySiguiente()) {
		i++;
		tmp.Avanzar();
	}

	return i;
}

Posicion Driver::posEstudianteYHippie(Nombre n) const
{
	return {_cs->PosHippieYEstudiante(n).y, _cs->PosHippieYEstudiante(n).x};
}

Posicion Driver::posAgente(Agente pl) const
{
	return {_cs->PosAgente(pl).y, _cs->PosAgente(pl).x};
}

Nat Driver::cantSanciones(Agente pl) const
{
	return _cs->CantSanciones(pl);
}

Nat Driver::cantHippiesAtrapados(Agente pl) const
{
    return _cs->CantHippiesAtrapados(pl);
}


/// Otras operaciones de CampusSeguro

Agente Driver::masVigilante() const
{
    return _cs->MasVigilante();
}

const Conj<Agente> Driver::conMismasSanciones(Agente a) const
{
	return _cs->ConMismasSanciones(a);
}

const Conj<Agente> Driver::conKSanciones(Nat k)
{
    return _cs->ConKSanciones(k);
}


} // namespace aed2

