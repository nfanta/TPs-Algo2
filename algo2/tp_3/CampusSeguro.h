#ifndef TP_3_CAMPUSSEGURO_H
#define TP_3_CAMPUSSEGURO_H

#include "campus.h"
#include "Agentes.h"
#include "HippiesYEstudiantes.h"
#include "Matriz.h"

namespace aed2{
    class CampusSeguro{
    public:
		CampusSeguro();
        CampusSeguro(const Campus& c, const Dicc<Nat,Posicion>& dA);

        void IngresarEstudiante(String nombre, Posicion p);
        void IngresarHippie(String nombre, Posicion p);

        void MoverEstudiante(String nombre, Direccion dir);
        void MoverHippie(String nombre);
        void MoverAgente(Nat placa);

        const Campus& dameCampus();

         Conj<String>::const_Iterador Estudiantes() const;
         Conj<String>::const_Iterador Hippies() const;
         Conj<Nat>::const_Iterador dameAgentes() const;

        const Posicion& PosHippieYEstudiante(String nombre) const;
        const Posicion& PosAgente(Nat placa) const;

        const Nat& CantSanciones(Nat placa) const;
        const Nat& CantHippiesAtrapados(Nat placa) const;

        Nat CantHippies();
        Nat CantEstudiantes();

        const Nat& MasVigilante() const;
        const Conj<Nat>& ConMismasSanciones(Nat placa) const;
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
//        	Conj<Posicion> cjtoVec = _campus.Vecinos(p);
        	Conj<Posicion> cjtoVec = Conj<Posicion>();
		   _campus.Vecinos(p, cjtoVec);
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
//         	Conj<Posicion> cjtoVec = _campus.Vecinos(p);
        	Conj<Posicion> cjtoVec = Conj<Posicion>();
		   _campus.Vecinos(p, cjtoVec);
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
//        	Conj<Posicion> cjtoVec = _campus.Vecinos(p);
        	Conj<Posicion> cjtoVec = Conj<Posicion>();
		   _campus.Vecinos(p, cjtoVec);
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
//        	Conj<Posicion> cjtoVec = _campus.Vecinos(p);
        	Conj<Posicion> cjtoVec = Conj<Posicion>();
		   _campus.Vecinos(p, cjtoVec);
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
//        Conj<Posicion> cjtoVec = _campus.Vecinos(p);
		   Conj<Posicion> cjtoVec = Conj<Posicion>();
		   _campus.Vecinos(p, cjtoVec);
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
//           Conj<Posicion> cjtoVec = _campus.Vecinos(p);
    	   Conj<Posicion> cjtoVec = Conj<Posicion>();
		   _campus.Vecinos(p, cjtoVec);
           Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
           while(itvecinos.HaySiguiente()){
        	   if(_posOcupadasAgentes.Def(itvecinos.Siguiente())){
        		   _agentes.AgregarSancion(_posOcupadasAgentes.Obtener(itvecinos.Siguiente()));
        	   }
        	   itvecinos.Avanzar();
           }
       }
       void transformarHippie(const Posicion& p){
    	   _HipYEst.Borrar(_posOcupadasHippies.Obtener(p));
    	   _HipYEst.DefinirEstudiante(_posOcupadasHippies.Obtener(p),p);
    	   _posOcupadasEstudiantes.Definir(p,_posOcupadasHippies.Obtener(p));
    	   _posOcupadasHippies.Eliminar(p);
       }

       void sumarCapturas(const Posicion& p){
//    	   Conj<Posicion> cjtoVec = _campus.Vecinos(p);
    	   Conj<Posicion> cjtoVec = Conj<Posicion>();
    	   _campus.Vecinos(p, cjtoVec);
    	   Conj<Posicion>::const_Iterador itvecinos = cjtoVec.CrearIt();
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

		Posicion damePosLibre(Posicion p){
			Posicion res;
//			Conj<Posicion> cjtoVec = _campus.Vecinos(p);
			Conj<Posicion> cjtoVec = Conj<Posicion>();
		   _campus.Vecinos(p, cjtoVec);
			Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
			while(itvecinos.HaySiguiente()){
				if(!estaOcupado(itvecinos.Siguiente())){
					res = itvecinos.Siguiente();
				}
				itvecinos.Avanzar();
			}
			return res;
		}
		Nat modulo(Nat a1,Nat a2){
			if(a1 >= a2){
				return a1-a2;
			}else{
				return a2-a1;
			}
		}

		Direccion dameDireccion(Posicion p1, Posicion p2){
			Direccion dirFinal;
			if(modulo(p1.x,p2.x) >= modulo(p1.y,p2.y)){
				if(p1.x >= p2.x){
//					dirFinal = izq;
					dirFinal = arriba;
				}else{
//					dirFinal = der;
					dirFinal = abajo;
				}
			}else{
				if(p1.y >= p2.y){
//					dirFinal = abajo;
					dirFinal = izq;
				}else{
//					dirFinal = arriba;
					dirFinal = der;
				}
			}
			return dirFinal;
		}

		void muevoEstudiante(String nombre,Posicion posVieja,Direccion dir){
			Posicion posNueva = _campus.ProxPosicion(posVieja,dir);
			_HipYEst.DefinirEstudiante(nombre,posNueva);
			Posicion temp = _HipYEst.PosHippieYEstudiante(nombre);
			_posOcupadasEstudiantes.Definir(posNueva,nombre);
			_posOcupadasEstudiantes.Eliminar(posVieja);
		}

		bool meVoy(Posicion p, Direccion dir){
			return ((_campus.ingresoSuperior(p) && dir == arriba) || (_campus.ingresoInferior(p) && dir == abajo));
		}

		const Posicion& estMasCercano(Posicion p){
			Posicion res;
			if(CantEstudiantes() != 0){
				Conj<Posicion> cjtoPosEst = _posOcupadasEstudiantes.Claves();
				Conj<Posicion>::Iterador itPosiciones = cjtoPosEst.CrearIt();
				Posicion posMasCercana = itPosiciones.Siguiente();
				while(itPosiciones.HaySiguiente()){
					if(_campus.Distancia(p,posMasCercana)>= _campus.Distancia(p,itPosiciones.Siguiente())){
						posMasCercana = itPosiciones.Siguiente();
					}
					itPosiciones.Avanzar();
				}
				 res = posMasCercana;

			}else{
				res = _campus.IngresoMasCercano(p); //.CrearIt().Siguiente();
			}
			return res;
		}

		const Posicion& hipMasCercano(Posicion p){
			Posicion res;
			if(CantHippies() != 0){
				Conj<Posicion> cjtoPosHip = _posOcupadasHippies.Claves();
				Conj<Posicion>::Iterador itPosiciones = cjtoPosHip.CrearIt();
				Posicion posMasCercana = itPosiciones.Siguiente();
				while(itPosiciones.HaySiguiente()){
					if(_campus.Distancia(p,posMasCercana)>= _campus.Distancia(p,itPosiciones.Siguiente())){
						posMasCercana = itPosiciones.Siguiente();
					}
					itPosiciones.Avanzar();
				}
				res = posMasCercana;

			}else{
				res = _campus.IngresoMasCercano(p); //.CrearIt().Siguiente();
			}
			return res;
		}

		bool estaOcupado(Posicion p){
			return (_posOcupadasAgentes.Def(p) || _posOcupadasHippies.Def(p) || _posOcupadasEstudiantes.Def(p) || _campus.Ocupada(p) );
		}

		void muevoHippie(Posicion posVieja, Posicion posDestino){
			String nombrehip = _posOcupadasHippies.Obtener(posVieja);
//			if(CantEstudiantes() != 0){
				if(estaOcupado(_campus.ProxPosicion(posVieja,dameDireccion(posVieja,posDestino)))){
					_HipYEst.DefinirHippie(nombrehip,damePosLibre(posVieja));
					_posOcupadasHippies.Definir(damePosLibre(posVieja),nombrehip);
//					_posOcupadasHippies.Eliminar(damePosLibre(posVieja));
					_posOcupadasHippies.Eliminar(posVieja);
				}else{
					_HipYEst.DefinirHippie(nombrehip,_campus.ProxPosicion(posVieja,dameDireccion(posVieja,posDestino)));
					_posOcupadasHippies.Definir(_campus.ProxPosicion(posVieja,dameDireccion(posVieja,posDestino)),nombrehip);
					_posOcupadasHippies.Eliminar(posVieja);//TODO revisar si esta bien xq me parece que en el dise�o definia la poss y dsp la borraba

				}
//			}

		}
		void Ordenar(Arreglo<aOrdenadoItem>& arre){
			Nat iterador = 0;
			Nat itero = 0;
			while(iterador  < arre.Tamanho()){
				itero = iterador;
				while(itero < arre.Tamanho()){
					if(arre[iterador]._placa >= arre[itero]._placa){
						arre.Swap(iterador,itero);
					}
					itero++;
				}

				iterador++;
			}
		}

		aOrdenadoItem busquedaBinaria(Nat k, Arreglo<aOrdenadoItem>& arreglo) const {
			Nat iMin, iMax, iMed;
			iMin = 0;
			iMax = arreglo.Tamanho() - 1;
			bool res = false;

			while(iMin <= iMax){
				iMed = (iMin+iMax)/2;
				if(arreglo[iMed]._placa == k){

					res = true;
					iMin = iMax + 1;
				} else {
					if(arreglo[iMed]._placa < k) {
						iMin = iMed + 1;
					} else{
						iMax = iMed - 1;
					}
				}
			}
			return arreglo[iMed];
		}

		void muevoAgente(Posicion p,Posicion pD, Agentes::Iterador itagente){
			Nat nombreAg = itagente.SiguientePlaca();
//			if(CantEstudiantes() != 0){
				if(estaOcupado(_campus.ProxPosicion(p,dameDireccion(p,pD)))){
					_agentes.CambiarPosicion(itagente,damePosLibre(p));
					_posOcupadasAgentes.Eliminar(p);
					_posOcupadasAgentes.Definir(damePosLibre(p),itagente);
				}else{
					_agentes.CambiarPosicion(itagente,_campus.ProxPosicion(p,dameDireccion(p,pD)));
					_posOcupadasAgentes.Eliminar(p);
					_posOcupadasAgentes.Definir(_campus.ProxPosicion(p,dameDireccion(p,pD)),itagente);
				}
//			}
		}

    };
}
#endif //TP_3_CAMPUSSEGURO_H
