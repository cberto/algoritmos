#include <iostream>
#include <fstream>
#include "Estacion.h"
#include "Sistema.h"


using namespace std;


bool Sistema::CargarDatos(string carpeta , ostream& cout){
    cout << "Cargando datos desde archivos..." << endl;
     if(cargado ){
        cout << "Datos cargados. Reinicie para restaurar" << endl;
        return false;
     }
  

    ifstream levantarEstaciones(carpeta + "/estaciones.txt");
    ifstream levantarBicicletas(carpeta + "/bicicletas.txt");
    ifstream levantarViajes(carpeta + "/viajes.txt");
    ifstream levantarCiclovias(carpeta + "/ciclovias.txt");

       if(!levantarEstaciones || !levantarBicicletas || !levantarViajes || !levantarCiclovias){
        cout << "No se pudieron abrir los archivos" << endl;
        return false;
       }
       // se asumen q los archivos estan bien formados

       string codigo, barrio, nombre;
       int disponible, capacidad;

       while(levantarEstaciones >> codigo >> nombre >> barrio >> capacidad >> disponible ){
         AgregarEstacion(codigo, nombre, barrio, capacidad, disponible);
        
       }
/*
        while(levantarBicicletas >> bici_id >> codigo_estacion >> tipo >> estado >> kilometros ){
         AgregarBicicletas(bici_id, codigo_estacion, tipo, estado, kilometros);
       }
        while(levantarViajes >> viaje_id >> bici_id >> dni_usuario >> estacion_origen >> estacion_destino >> fecha >> duracion_min ){
         AgregarBicicletas(viaje_id bici_id dni_usuario estacion_origen estacion_destino fecha duracion_min);
       }
        while(levantarCiclovias >> estacion_a >> estacion_b ){
         AgregarCiclovias(estacion_a ,estacion_b);
       }
         */
       cargado = true;
       cout << "Datos cargados correctamente" << endl;
       return true;
}


bool Sistema::AgregarEstacion(string codigo, string nombre, string barrio, int capacidad, int disponible){
    return estaciones.Agregar(codigo, nombre, barrio, capacidad, disponible);
  }

  bool Sistema::EliminarEstacion(string codigo ){
  if(!estaciones.BuscarEstacion(codigo)){
    return false;
  }
 // ciclovias.Eliminar(codigo);
   return estaciones.Eliminar(codigo);
  }






/*
void Sistema::AgregarBicicletas(int bici_id int codigo_estacion, string tipo, string estado, int kilometros){
    bicicleta.Agregar(bici_id,codigo_estacion,tipo,estado,kilometros);
}

void Sistema::AgregarViajes(int viaje_id, int bici_id, int dni_usuario, string estacion_origen , string estacion_destino, string fecha, int duracion_min){
    viajes.Agregar(viaje_id, bici_id, dni_usuario, estacion_origen, estacion_destino, fecha, duracion_min);
}

void Sistema::AgregarCiclovias(string estacion_a , string estacion_b){
    ciclovias.Agregar(estacion_a , estacion_b);
}
*/


