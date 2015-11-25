#ifndef TP_3_CAMPUSSEGURO_H
#define TP_3_CAMPUSSEGURO_H

#include "campus.h"
#include "Agentes.h"
#include "HippiesYEstudiantes.h"

namespace aed2{
    class CampusSeguro{
    public:
        CampusSeguro(const Campus& c, const Dicc<Nat,Posicion>& dA);

        void IngresarEstudiante(String nombre, Posicion p);
        void IngresarHippie(String nombre, Posicion p);

        void MoverEstudiante(String nombre, Direccion dir);
        void MoverHippie(String nombre);
        void MoverAgente(Nat placa);

        const Campus& dameCampus();

        const Conj<String>& Estudiantes();
        const Conj<String>& Hippies();
        const Conj<Nat>& dameAgentes();

        const Posicion& PosHippieYEstudiante(String nombre);
        const Posicion& PosAgente(Nat placa);

        const Nat& CantSanciones(Nat placa);
        const Nat& CantHippiesAtrapados(Nat placa);

        Nat CantHippies();
        Nat CantEstudiantes();

        const Nat& MasVigilante();
        const Conj<Nat>& ConMismasSanciones(Nat placa);
        const Conj<Nat>& ConKSanciones(Nat k);

    private:

        struct aOrdenadoItem {
            Nat _placa;
            Agentes::Iterador _itAgente;
        };

        Campus _campus;
        HippiesYEstudiantes _HipYEst;
        Agentes _agentes;
        Matriz<String> _posOcupadasHippies;
        Matriz<String> _posOcupadasEstudiantes;
        Matriz<Agentes::Iterador> _posOcupadasAgentes;

        Arreglo<aOrdenadoItem> _agentesOrdenados;

        bool hippieRodeadoEst(const Posicion& p) const{
        	Conj<Posicion> cjtoVec = _campus.Vecinos(p);
        	Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
        	Nat cantEst = 0;
        	while(itvecinos.HaySiguiente()){
        		if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
        			cantEst = cantEst + 1 ;
        		}
        		itvecinos.Avanzar();
        	}
        	return cantEst == cjtoVec.Cardinal();
        }

        bool bloqueado(const Posicion& p) const{
         	Conj<Posicion> cjtoVec = _campus.Vecinos(p);
            Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
            Nat cosasBloqueando = 0;
            while(itvecinos.HaySiguiente()){
            	if(_posOcupadasAgentes.Def(itvecinos.Siguiente()) || _posOcupadasHippies.Def(itvecinos.Siguiente()) || _posOcupadasEstudiantes.Def(itvecinos.Siguiente()) || _campus.Ocupada(itvecinos.Siguiente()) ){
            		cosasBloqueando = cosasBloqueando +1;
            	}
            	itvecinos.Avanzar();
            }
            return cosasBloqueando == cjtoVec.Cardinal();
        }

        bool hippieCapturado(const Posicion& p) const{
        	Conj<Posicion> cjtoVec = _campus.Vecinos(p);
        	Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
        	bool alMenos1Ag = false;
        	while(itvecinos.HaySiguiente()){
        		if(_posOcupadasAgentes.Def(itvecinos.Siguiente())){
        			alMenos1Ag = true;
        		}
        		itvecinos.Avanzar();
        	}
        	return alMenos1Ag && bloqueado(p);
        }

        bool estudianteHippificado(const Posicion& p) const{
        	Conj<Posicion> cjtoVec = _campus.Vecinos(p);
        	Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
        	Nat CantHip = 0;
        	while(itvecinos.HaySiguiente()){
        		if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
        			CantHip = CantHip + 1 ;
        	    }
        	 	itvecinos.Avanzar();
          	}
        	return CantHip >= 2;
        }

       bool estudianteSancionar(const Posicion& p) const{
        Conj<Posicion> cjtoVec = _campus.Vecinos(p);
		Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
		bool alMenos1Ag = false;
		while(itvecinos.HaySiguiente()){
				if(_posOcupadasAgentes.Def(itvecinos.Siguiente())){
					alMenos1Ag = true;
				}
				itvecinos.Avanzar();
			}
			return alMenos1Ag && bloqueado(p);
       }

       void hippificar(const Posicion& p){
    	   _HipYEst.DefinirHippie(_posOcupadasEstudiantes.Obtener(p),p);
    	   _posOcupadasHippies.Definir(p,_posOcupadasEstudiantes.Obtener(p));
    	   _HipYEst.Borrar(_posOcupadasEstudiantes.Obtener(p));
    	   _posOcupadasEstudiantes.Eliminar(p);
       }

       void sancionar(const Posicion& p){
           Conj<Posicion> cjtoVec = _campus.Vecinos(p);
           Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
           while(itvecinos.HaySiguiente()){
        	   if(_posOcupadasAgentes.Def(itvecinos.Siguiente())){
        		   _agentes.AgregarSancion(_posOcupadasAgentes.Obtener(itvecinos.Siguiente()));
        	   }
        	   itvecinos.Avanzar();
           }
       }
       void transformarHippie(const Posicion& p){
    	   _HipYEst.DefinirEstudiante(_posOcupadasHippies.Obtener(p),p);
    	   _posOcupadasEstudiantes.Definir(p,_posOcupadasHippies.Obtener(p));
    	   _HipYEst.Borrar(_posOcupadasHippies.Obtener(p));
    	   _posOcupadasHippies.Eliminar(p);
       }

       void sumarCapturas(const Posicion& p){
    	   Conj<Posicion> cjtoVec = _campus.Vecinos(p);
    	   Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
    	   while(itvecinos.HaySiguiente()){
    		   if(_posOcupadasAgentes.Def(itvecinos.Siguiente())){
    	          _agentes.AgregarCaptura(_posOcupadasAgentes.Obtener(itvecinos.Siguiente()));
    	       }
    	    itvecinos.Avanzar();
    	   }
       }

       void eliminarHippie(const Posicion& p){
    	   sumarCapturas(p);
    	   _HipYEst.Borrar(_posOcupadasHippies.Obtener(p));
    	   _posOcupadasHippies.Eliminar(p);
       }

    };
}
#endif //TP_3_CAMPUSSEGURO_H
