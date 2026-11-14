#include "Sistema.h"
#include "Estacion.h"
#include "Estructuras.h"
#include "Ciclovias.h"
#include "Bicicleta.h"
#include "Viaje.h"
#include <iostream>
#include <fstream>

using namespace std;



bool Sistema::cargarDatos(string carpeta){
    cout << "Cargando datos desde archivos..." << endl;
     if(cargado) {
        cout << "Datos cargados. Reinicie para restaurar" << endl;
        return false;
    }

    ifstream levantarEstaciones(carpeta + "/estaciones.txt");
    ifstream levantarBicicletas(carpeta + "/bicicletas.txt");
    ifstream levantarViajes(carpeta + "/viajes.txt");
    ifstream levantarCiclovias(carpeta + "/ciclovias.txt");

    if(!levantarEstaciones || !levantarBicicletas || !levantarViajes || !levantarCiclovias) {
        cout << "No se pudieron abrir los archivos" << endl;
        return false;
    }

    // se asumen q los archivos estan bien formados
    string codigo, barrio, nombre;
    int disponible, capacidad;


    
    
    while(levantarEstaciones >> codigo >> nombre >> barrio >> capacidad >> disponible )
         agregarEstacion(codigo, nombre, barrio, capacidad, disponible);

    string codigoEstacion, tipo, estado;
    int biciId, kilometros;

     while(levantarBicicletas >> biciId >> codigoEstacion >> tipo >> estado >> kilometros )
         agregarBicicleta(biciId, codigoEstacion, tipo, estado, kilometros);
 
    string estacionOrigen, estacionDestino, fecha;
    int viajeId, dniUsuario,  duracionMin;
    
    while(levantarViajes >> viajeId >> biciId >> dniUsuario >> estacionOrigen >> estacionDestino >> fecha >> duracionMin)
             agregarViajes(viajeId, biciId, dniUsuario, estacionOrigen, estacionDestino, fecha, duracionMin);

      
    string estacionA, estacionB;
     while(levantarCiclovias >> estacionA >> estacionB )
          agregarCiclovias(estacionA ,estacionB);

    cargado = true;
    
    cout << "Datos cargados correctamente" << endl;
    
    return true;
}

void Sistema::resumen() const {
  cout << " | Resumen" << endl
     << " |-----------------" << endl
     << " | Estaciones: " << estaciones.cantidad()  << endl
     << " | Bicicletas: " << bicicletas.cantidadBicicletas() << endl
     << " | Viajes: " << viajes.cantidad() << endl
     << " | Taller: " << taller.cantidad() << endl
     << " |-----------------" << endl
     << " | Colisiones: " << estaciones.totalColisiones() << endl
     << " | Factor de carga: " << estaciones.factorCarga() << endl;
}


void Sistema::listarEstaciones(bool capacidad) const {
 Array<Estacion*> ordenados;
 

 estaciones.recorrer([&](Estacion& e) {
  ordenados.agregar(&e);});

  // metodo utilizado es insercion 
  //Insercion directa sobre  una copia de punteros, para no desarmar la tabla hash
  for(int i=1; i<ordenados.cantidad(); i++){
    Estacion* actual = ordenados[i];
    int ant = i-1;
    int clave = capacidad ? actual->getCapacidad() : actual->getDisponible();
  

    while(ant >= 0){
      int tmpAnterior = capacidad ? ordenados[ant]->getCapacidad() : ordenados[ant]->getDisponible();
      if(tmpAnterior < clave || (tmpAnterior == clave && ordenados[ant]->getCodigo() > actual->getCodigo())){
        break;
      }
      ordenados[ant+1] = ordenados[ant];
      --ant;
     
    }
    ordenados[ant+1] = actual;
  }
  cout << " | Listado" << endl
       << " |--------------------------" << endl;
  for(int i=0; i<ordenados.cantidad(); i++){
   
   
    
    ordenados[i]->mostrarEstacion();
    cout << " |--------------------------" << endl;
  }

}

void Sistema::listarOcupacion() const {
  int total = 0;
  cout << " | Listado" << endl
  << " |--------------------------" << endl;
  estaciones.recorrer([&](const Estacion& e) {
    //quinta parte de la capacidad
    if(5*e.getDisponible() < e.getCapacidad()){
      e.mostrarEstacion();
      cout << " |--------------------------" << endl;
      ++total;
    }
  });
      if(!total){
      cout << " | No hay estaciones con ocupacion menor al 20%" << endl << endl;
     }
}

bool Sistema::agregarEstacion(string codigo, string nombre, string barrio, int capacidad, int disponible) {
    if(!estaciones.agregar(codigo, nombre, barrio, capacidad, disponible))
        return false;

    ciclovias.agregarVertice(codigo);
    return true;
}

bool Sistema::eliminarEstacion(string codigo) {
    if(!estaciones.buscarEstacion(codigo))
        return false;

    ciclovias.eliminarEstacion(codigo);
    return estaciones.eliminar(codigo);
}



bool Sistema::agregarBicicleta(int biciId, string codigoEstacion, string tipo, string estado, int kilometros) {
    if (biciId <= 0 || kilometros < 0 || !estaciones.buscarEstacion(codigoEstacion)
        || (tipo != "Mecanica" && tipo != "Electrica")
        || (estado != "OK" && estado != "Averiada"))
        return false;

    Bicicleta bici(biciId, codigoEstacion, tipo, estado, kilometros);
    return bicicletas.insertar(bici);
}

bool Sistema::eliminarBicicleta(int id) {
    // Una bici en el taller no se borra: el heap quedaria con un ID inexistente.
    if (taller.contiene(id)) return false;
    return bicicletas.eliminar(id);
}

 void Sistema::agregarViajes(int viajeId, int biciId, int dniUsuario, string estacionOrigen , string estacionDestino, string fecha, int duracionMin){
     Viaje viaje;
     viaje.setViajeId(viajeId);
     viaje.setBiciId(biciId);
     viaje.setDniUsuario(dniUsuario);
     viaje.setEstacionOrigen(estacionOrigen);
     viaje.setEstacionDestino(estacionDestino);
     viaje.setFecha(fecha);
     viaje.setDuracionMin(duracionMin);
     viajes.agregar(viaje);
 }

 int Sistema:: contarViajes(string codigo, string desde, string hasta) const {
        if(desde > hasta){
          throw invalid_argument("La fecha de inicio no puede ser mayor a la fecha de fin");
        }
        int cantidad = 0;
        for(int i = 0; i < viajes.cantidad(); i++){
          Viaje v = viajes[i];
          if(v.getEstacionOrigen() == codigo && v.getFecha() >= desde && v.getFecha() <= hasta){
            ++cantidad;
          }
        }
        return cantidad;
 }

 long  Sistema:: viajesUsuario(int dni) const {
  long minutos = 0;
  long cantidad = 0;

  for(int i = 0; i < viajes.cantidad(); i++){
    if(viajes[i].getDniUsuario() == dni){
      viajes[i].mostrarViaje();
      minutos += viajes[i].getDuracionMin();
      ++cantidad;
    }
  }
  cout << " | Viajes: " << cantidad << endl
         << " | Total de minutos: " << minutos << endl
         << " |--------------------------" << endl;

    return minutos;

 }


 void Sistema:: revisionBicicletas(int km) const {
  int total = 0;
  bicicletas.recorrer([&](const Bicicleta& bici){
    if(bici.getKilometros() > km){
      bici.mostrarBicicleta();
      ++total;
    }
  });
  if(!total){
    cout << " | No hay bicicletas con mas de " << km << " km" << endl << endl;
  }
}


bool Sistema:: retirarBicicleta(string cod, int dni) {
Estacion* e = estaciones.buscarEstacion(cod);
if(!e || dni <=0 ){
  cout << " | Error: Estacion o DNI no valido" << endl << endl;
  return false;
}
if(e->getDisponible() > 0){
  e->restarDisponible();
  cout << " Bicicleta asignada al dni: " << dni << endl << endl;
} else {
  e->espera.encolar(dni);
  cout << "Encolado: " << dni << endl << endl;
}
return true;
}

bool Sistema::devolverBicicleta(string cod) {
  Estacion* e = estaciones.buscarEstacion(cod);
  if (!e) {
    cout << " | Error: Estacion no valida" << endl << endl;
    return false;
  }
  // Si hay espera, la bici pasa directo al primero y no cambian las disponibles.
  if (!e->espera.vacia()) {
    int dni = e->espera.desencolar();
    cout << " Bicicleta asignada al dni en espera: " << dni << endl << endl;
    return true;
  }
  if (!e->sumarDisponible()) {
    cout << " | Error: Estacion llena, no hay anclajes libres" << endl << endl;
    return false;
  }
  cout << " Bicicleta devuelta a " << cod << ". Disponibles: " << e->getDisponible() << endl << endl;
  return true;
}

bool Sistema::mostrarEspera(string cod) const {
  const Estacion* e = estaciones.buscarEstacion(cod);
  if (!e) {
    cout << " | Error: Estacion no valida" << endl << endl;
    return false;
  }
  cout << " | Espera en " << cod << " (" << e->espera.cantidad() << "): ";
  if (e->espera.vacia()) {
    cout << "sin usuarios" << endl << endl;
    return true;
  }
  bool primero = true;
  e->espera.recorrer([&](int dni) {
    if (!primero) cout << " -> ";
    cout << dni;
    primero = false;
  });
  cout << " (primero -> ultimo)" << endl << endl;
  return true;
}

bool Sistema::ingresarTaller(int idBici, int prioridad) {
  Bicicleta* b = bicicletas.buscar(idBici);
  if (!b || b->getEstado() != "Averiada" || prioridad < 1 || prioridad > 3 || taller.contiene(idBici)) {
    cout << " | Ingreso rechazado: ID, estado, prioridad o bici ya en el taller" << endl << endl;
    return false;
  }
  int efectiva = b->getTipo() == "Electrica" ? 1 : prioridad;
  taller.insertar(idBici, efectiva);
  cout << " Bici " << idBici << " ingresada con prioridad " << efectiva << endl << endl;
  return true;
}

bool Sistema::retirarTaller() {
  Reparacion r;
  if (!taller.extraer(r)) {
    cout << " | Taller vacio" << endl << endl;
    return false;
  }
  cout << " Atender bici " << r.biciId << " con prioridad " << r.prioridad << endl << endl;
  return true;
}


 void Sistema::agregarCiclovias(string estacionA, string estacionB) {
  ciclovias.agregarVertice(estacionA);
  ciclovias.agregarVertice(estacionB);
  ciclovias.conectar(estacionA, estacionB);
}

