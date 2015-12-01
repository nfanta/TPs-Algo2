//
// Created by Matias on 25/11/2015.
//

#include "CampusSeguro.h"

namespace aed2 {

    CampusSeguro::CampusSeguro(const Campus& c, const Dicc<Nat, Posicion>& dA) : _campus(c.Filas(), c.Columnas()), _agentes(dA), _HipYEst(), _posOcupadasAgentes(c.Filas(), c.Columnas()), _posOcupadasEstudiantes(c.Filas(), c.Columnas()), _posOcupadasHippies(c.Filas(), c.Columnas()), _agentesOrdenados(dA.CantClaves()) {
        Agentes::Iterador itAgentes = _agentes.CrearIt();
        Nat i = 0;
        while(itAgentes.HaySiguiente()) {
            _posOcupadasAgentes.Definir(itAgentes.SiguienteDatos()._posicion, itAgentes);
            _agentesOrdenados.Definir(i, {itAgentes.SiguientePlaca(), itAgentes});
            i++;
            itAgentes.Avanzar();
        }

        Ordenar(_agentesOrdenados); //HACCER ALGUN SORT, NO IMPORTA LA COMPLEJIDAD
        //Los algoritmos no cambian, excepto moverAgente, que tiene que buscar el iterador del agente en _agentesOrdenados (busqueda binaria) en vez de en la matriz _posOcupadasAgentes
    }

    void CampusSeguro::IngresarEstudiante(String nombre, Posicion p){
    	if(estudianteHippificado(p)){
    		_HipYEst.DefinirHippie(nombre,p);
    		_posOcupadasHippies.Definir(p,nombre);
    		Conj<Posicion> cjtoVec = _campus.Vecinos(p);
    		Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
    		while(itvecinos.HaySiguiente()){
    			if(_posOcupadasHippies.Def(itvecinos.Siguiente())){
    				if(hippieCapturado(itvecinos.Siguiente())){
    					_HipYEst.Borrar(_posOcupadasHippies.Obtener(itvecinos.Siguiente()));
    				}
    			}
    			if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
    				if(estudianteHippificado(itvecinos.Siguiente())){
    					hippificar(itvecinos.Siguiente());
    				}
    				if(estudianteSancionar(itvecinos.Siguiente())){
    					sancionar(itvecinos.Siguiente());
    				}
    			}
    			itvecinos.Avanzar();
    		}
    	}else{
    		_HipYEst.DefinirEstudiante(nombre,p);
			_posOcupadasEstudiantes.Definir(p,nombre);
			Conj<Posicion> cjtoVec = _campus.Vecinos(p);
			Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
			while(itvecinos.HaySiguiente()){
				if(_posOcupadasHippies.Def(itvecinos.Siguiente())){
					if(hippieRodeadoEst(itvecinos.Siguiente())){
						transformarHippie(itvecinos.Siguiente());
					}
					if(hippieCapturado(itvecinos.Siguiente())){
						eliminarHippie(itvecinos.Siguiente());
					}
				}
				if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
					if(estudianteSancionar(itvecinos.Siguiente())){
						sancionar(itvecinos.Siguiente());
					}
				}
				itvecinos.Avanzar();
			}

    	}
    	if(estudianteSancionar(p)){
    		Conj<Posicion> cjtoVec = _campus.Vecinos(p);
    		Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
    		while(itvecinos.HaySiguiente()){
    			if(_posOcupadasAgentes.Def(itvecinos.Siguiente())){
    				_agentes.AgregarSancion(_posOcupadasAgentes.Obtener(itvecinos.Siguiente()));
    			}
    			itvecinos.Avanzar();
    		}
		}
    }

    void CampusSeguro::IngresarHippie(String nombre, Posicion p){
        if(hippieCapturado(p)){
            sumarCapturas(p);
        }
        if(hippieRodeadoEst(p)){
            _HipYEst.DefinirEstudiante(nombre,p);
            _posOcupadasEstudiantes.Definir(p,nombre);
            Conj<Posicion> cjtoVec = _campus.Vecinos(p);
            Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
            while(itvecinos.HaySiguiente()){
                if(estudianteSancionar(itvecinos.Siguiente())){
                    sancionar(itvecinos.Siguiente());

                }
                itvecinos.Avanzar();
            }

        }else{
            _HipYEst.DefinirHippie(nombre,p);
            _posOcupadasHippies.Definir(p,nombre);
            Conj<Posicion> cjtoVec = _campus.Vecinos(p);
            Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
            while(itvecinos.HaySiguiente()){
                if(_posOcupadasHippies.Def(itvecinos.Siguiente())){
                    if(hippieCapturado(itvecinos.Siguiente())){
                        eliminarHippie(itvecinos.Siguiente());
                    }
                }
                if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
                    if(estudianteHippificado(itvecinos.Siguiente()) && hippieCapturado(itvecinos.Siguiente())){
                        sumarCapturas(itvecinos.Siguiente());
                        _HipYEst.Borrar(_posOcupadasEstudiantes.Obtener(itvecinos.Siguiente()));
                        _posOcupadasEstudiantes.Eliminar(itvecinos.Siguiente());

                    }
                    if(estudianteHippificado(itvecinos.Siguiente())){
                        hippificar(itvecinos.Siguiente());
                    }
                    if(estudianteSancionar(itvecinos.Siguiente())){
                        sancionar(itvecinos.Siguiente());
                    }
                }
                itvecinos.Avanzar();
            }

        }

    }

    void CampusSeguro::MoverEstudiante(String nombre, Direccion dir){
        Posicion posVieja = _HipYEst.PosHippieYEstudiante(nombre);
        Posicion proxPosicion = _campus.ProxPosicion(posVieja,dir);
        if(meVoy(posVieja,dir)){
            _HipYEst.Borrar(nombre);
            _posOcupadasEstudiantes.Eliminar(posVieja);
        } else if (!_posOcupadasAgentes.Def(proxPosicion)) {
            muevoEstudiante(nombre,posVieja,dir);
            Posicion posNueva = _HipYEst.PosHippieYEstudiante(nombre);
            if(estudianteHippificado(posNueva)){
                hippificar(posNueva);
                Conj<Posicion> cjtoVec = _campus.Vecinos(posNueva);
                Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
                while(itvecinos.HaySiguiente()){
                    if(_posOcupadasHippies.Def(itvecinos.Siguiente())){
                        if(hippieCapturado(itvecinos.Siguiente())){
                            eliminarHippie(itvecinos.Siguiente());
                        }
                    }
                    if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
                        if(estudianteHippificado(itvecinos.Siguiente()) && hippieCapturado(itvecinos.Siguiente())){
                            sumarCapturas(itvecinos.Siguiente());
                            _HipYEst.Borrar(_posOcupadasEstudiantes.Obtener(itvecinos.Siguiente()));
                            _posOcupadasEstudiantes.Eliminar(itvecinos.Siguiente());
                        }
                        if(estudianteSancionar(itvecinos.Siguiente())){
                            sancionar(itvecinos.Siguiente());
                        }
                    }
                    itvecinos.Avanzar();
                }

            }else{
                Conj<Posicion> cjtoVec = _campus.Vecinos(posNueva);
                Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
                while(itvecinos.HaySiguiente()){
                    if(_posOcupadasHippies.Def(itvecinos.Siguiente())){
                        if(hippieRodeadoEst(itvecinos.Siguiente())){
                            transformarHippie(itvecinos.Siguiente());
                        }
                        if(hippieCapturado(itvecinos.Siguiente())){
                            eliminarHippie(itvecinos.Siguiente());
                        }
                    }
                    if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
                        if(estudianteSancionar(itvecinos.Siguiente())){
                            sancionar(itvecinos.Siguiente());
                        }
                    }
                    itvecinos.Avanzar();
                }
            }
        }
    }

    void CampusSeguro::MoverHippie(String nombre){
        Posicion posVieja = _HipYEst.PosHippieYEstudiante(nombre);
        Posicion proxPosicion = estMasCercano(posVieja);
        muevoHippie(posVieja,proxPosicion);
        Posicion posNueva = _HipYEst.PosHippieYEstudiante(nombre);
        Conj<Posicion> cjtoVec = _campus.Vecinos(posNueva);
        Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
        while(itvecinos.HaySiguiente()){
            if(_posOcupadasHippies.Def(itvecinos.Siguiente())){
                if(hippieCapturado(itvecinos.Siguiente())){
                    eliminarHippie(itvecinos.Siguiente());
                }
            }
            if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
                if(estudianteHippificado(itvecinos.Siguiente()) && hippieCapturado(itvecinos.Siguiente())){
                    sumarCapturas(itvecinos.Siguiente());
                    _HipYEst.Borrar(_posOcupadasEstudiantes.Obtener(itvecinos.Siguiente()));
                    _posOcupadasEstudiantes.Eliminar(itvecinos.Siguiente());
                }
                if(estudianteSancionar(itvecinos.Siguiente())){
                    sancionar(itvecinos.Siguiente());
                }
            }
            itvecinos.Avanzar();
        }
    }



    void CampusSeguro::MoverAgente(Nat placa){

        aOrdenadoItem agenteBuscado = busquedaBinaria(placa,_agentesOrdenados);
        Agentes::Iterador itAgente = agenteBuscado._itAgente;
        Posicion posVieja = itAgente.SiguienteDatos()._posicion;
        Posicion posDestino = hipMasCercano(posVieja);
        muevoAgente(posVieja,posDestino,itAgente);
        Posicion posNueva = itAgente.SiguienteDatos()._posicion;
        Conj<Posicion> cjtoVec = _campus.Vecinos(posNueva);
        Conj<Posicion>::Iterador itvecinos = cjtoVec.CrearIt();
        while(itvecinos.HaySiguiente()){
            if(_posOcupadasHippies.Def(itvecinos.Siguiente())){
                if(hippieCapturado(itvecinos.Siguiente())){
                    eliminarHippie(itvecinos.Siguiente());
                }
            }
            if(_posOcupadasEstudiantes.Def(itvecinos.Siguiente())){
                if(estudianteSancionar(itvecinos.Siguiente())){
                    sancionar(itvecinos.Siguiente());
                }
            }
            itvecinos.Avanzar();
        }
    }

    const Campus& CampusSeguro::dameCampus(){
        return _campus;
    }
//TODO REVISAR QUE ONDA LO QUE DEVUELVEN ESTAS FUNCIONES XQ ENE L DISE�O DICEN QUE DEVUELVEN UN ITERADOR NO AL CONJUNTO
     Conj<String>::const_Iterador& CampusSeguro::Estudiantes(){
        Conj<String>::const_Iterador itRes =  _HipYEst.Estudiantes().CrearIt();
        //return _HipYEst.Estudiantes().CrearIt();
        return itRes;
    }

     Conj<String>::const_Iterador& CampusSeguro::Hippies(){
         Conj<String>::const_Iterador itRes = _HipYEst.Hippies().CrearIt();
         return itRes;
    }

     Conj<Nat>::const_Iterador& CampusSeguro::dameAgentes(){
         Conj<Nat>::const_Iterador itRes = _agentes.dameAgentes().CrearIt();
         return itRes;
    }

    const Posicion& CampusSeguro::PosHippieYEstudiante(String nombre){
        return _HipYEst.PosHippieYEstudiante(nombre);
    }

    const Posicion& CampusSeguro::PosAgente(Nat placa){
        return _agentes.PosAgente(placa);
    }

    const Nat& CampusSeguro::CantSanciones(Nat placa){
        return _agentes.SancionesAgente(placa);
    }

    const Nat& CampusSeguro::CantHippiesAtrapados(Nat placa){
        return _agentes.CapturasAgente(placa);
    }

    Nat CampusSeguro::CantHippies(){
        return _HipYEst.Hippies().Cardinal();
    }

    Nat CampusSeguro::CantEstudiantes(){
        return _HipYEst.Estudiantes().Cardinal();
    }

    const Nat& CampusSeguro::MasVigilante(){
        return  _agentes.MasVigilante();
    }

    const Conj<Nat>& CampusSeguro::ConMismasSanciones(Nat placa){
        return _agentes.ConMismasSanciones(placa);
    }

    const Conj<Nat>& CampusSeguro::ConKSanciones(Nat k){
        return _agentes.ConKSanciones(k);
    }

}
