#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Lectura segura: siempre consume la linea completa y recupera entradas no numericas.
string leerLinea(const string& mensaje){ cout<<mensaje; string s; getline(cin,s); return s; }
int leerOpcion(const string& mensaje){
    while(true){
        string s=leerLinea(mensaje); stringstream ss(s); int n; char extra;
        if(ss>>n && !(ss>>extra)) return n;
        cout<<"Entrada invalida. Escriba un numero entero.\n";
    }
}
double leerReal(const string& mensaje){
    while(true){
        string s=leerLinea(mensaje); stringstream ss(s); double n; char extra;
        if(ss>>n && !(ss>>extra)) return n;
        cout<<"Distancia invalida. Ingrese un numero.\n";
    }
}
bool confirmar(const string& m){string s=leerLinea(m+" (S/N): ");return s=="S"||s=="s";}

// LISTA ENLAZADA PROPIA DE PASAJEROS
struct Pasajero{int id;string nombre,documento,telefono;Pasajero*sig;Pasajero(int i,string n,string d,string t):id(i),nombre(n),documento(d),telefono(t),sig(nullptr){}};
class ListaPasajeros{
    Pasajero*cabeza;
public:
    ListaPasajeros():cabeza(nullptr){}
    ~ListaPasajeros(){limpiar();}
    void limpiar(){while(cabeza){Pasajero*p=cabeza;cabeza=cabeza->sig;delete p;}}
    bool existeId(int id)const{for(Pasajero*p=cabeza;p;p=p->sig)if(p->id==id)return true;return false;}
    bool existeDocumento(const string&d)const{for(Pasajero*p=cabeza;p;p=p->sig)if(p->documento==d)return true;return false;}
    bool insertar(int id,const string&n,const string&d,const string&t){
        if(id<=0||n.empty()||d.empty()||existeId(id)||existeDocumento(d))return false;
        Pasajero*nuevo=new Pasajero(id,n,d,t);
        if(!cabeza)cabeza=nuevo;else{Pasajero*p=cabeza;while(p->sig)p=p->sig;p->sig=nuevo;}
        return true;
    }
    Pasajero*buscar(int id)const{for(Pasajero*p=cabeza;p;p=p->sig)if(p->id==id)return p;return nullptr;}
    bool actualizar(int id,const string&n,const string&d,const string&t){
        Pasajero*p=buscar(id);if(!p||n.empty()||d.empty())return false;
        for(Pasajero*q=cabeza;q;q=q->sig)if(q!=p&&q->documento==d)return false;
        p->nombre=n;p->documento=d;p->telefono=t;return true;
    }
    bool eliminar(int id){
        Pasajero*p=cabeza,*ant=nullptr;
        while(p&&p->id!=id){ant=p;p=p->sig;}
        if(!p)return false;
        if(ant)ant->sig=p->sig;else cabeza=p->sig;
        delete p;return true;
    }
    void listar()const{
        if(!cabeza){cout<<"No hay pasajeros registrados.\n";return;}
        cout<<"\nID | NOMBRE | DOCUMENTO | TELEFONO\n";
        for(Pasajero*p=cabeza;p;p=p->sig)cout<<p->id<<" | "<<p->nombre<<" | "<<p->documento<<" | "<<p->telefono<<"\n";
    }
    void guardar(ofstream&f)const{for(Pasajero*p=cabeza;p;p=p->sig)f<<"P|"<<p->id<<"|"<<p->nombre<<"|"<<p->documento<<"|"<<p->telefono<<"\n";}
};

// GRAFO: vector de vertices y listas de adyacencia. Los indices se ajustan al borrar vertices.
struct Arista{int destino;double km;};
struct Ciudad{string nombre;vector<Arista>adyacencia;};
class GrafoCiudades{
    vector<Ciudad> ciudades;
    int indice(const string&n)const{for(size_t i=0;i<ciudades.size();++i)if(ciudades[i].nombre==n)return (int)i;return -1;}
public:
    bool existeCiudad(const string&n)const{return indice(n)>=0;}
    bool agregarCiudad(const string&n){if(n.empty()||existeCiudad(n))return false;ciudades.push_back({n,{}});return true;}
    bool agregarRuta(const string&a,const string&b,double km){
        int x=indice(a),y=indice(b);if(x<0||y<0||x==y||km<=0)return false;
        for(const Arista&e:ciudades[x].adyacencia)if(e.destino==y)return false;
        ciudades[x].adyacencia.push_back({y,km});ciudades[y].adyacencia.push_back({x,km});return true;
    }
    bool eliminarRuta(const string&a,const string&b){
        int x=indice(a),y=indice(b);if(x<0||y<0)return false;
        auto quitar=[](vector<Arista>&v,int destino){size_t antes=v.size();v.erase(remove_if(v.begin(),v.end(),[destino](const Arista&e){return e.destino==destino;}),v.end());return v.size()!=antes;};
        bool uno=quitar(ciudades[x].adyacencia,y);bool dos=quitar(ciudades[y].adyacencia,x);return uno&&dos;
    }
    bool eliminarCiudad(const string&n){
        int x=indice(n);if(x<0)return false;
        for(Ciudad&c:ciudades){
            for(Arista&e:c.adyacencia)if(e.destino>x)--e.destino;
            c.adyacencia.erase(remove_if(c.adyacencia.begin(),c.adyacencia.end(),[x](const Arista&e){return e.destino==x;}),c.adyacencia.end());
        }
        ciudades.erase(ciudades.begin()+x);return true;
    }
    bool conectadas(const string&a,const string&b)const{
        int x=indice(a),y=indice(b);if(x<0||y<0)return false;
        for(const Arista&e:ciudades[x].adyacencia)if(e.destino==y)return true;return false;
    }
    void mostrarCiudades()const{if(ciudades.empty()){cout<<"No hay ciudades.\n";return;}for(const Ciudad&c:ciudades)cout<<"- "<<c.nombre<<"\n";}
    void mostrarRutas()const{
        if(ciudades.empty()){cout<<"No hay ciudades ni rutas.\n";return;}
        for(size_t i=0;i<ciudades.size();++i){cout<<ciudades[i].nombre<<" -> ";if(ciudades[i].adyacencia.empty())cout<<"sin conexiones";for(const Arista&e:ciudades[i].adyacencia)cout<<ciudades[e.destino].nombre<<" ("<<e.km<<" km) ";cout<<"\n";}
    }
    void vecinos(const string&n)const{int x=indice(n);if(x<0){cout<<"Ciudad inexistente.\n";return;}cout<<"Vecinos de "<<n<<": ";if(ciudades[x].adyacencia.empty())cout<<"ninguno";for(const Arista&e:ciudades[x].adyacencia)cout<<ciudades[e.destino].nombre<<" ("<<e.km<<" km) ";cout<<"\n";}
    void guardar(ofstream&f)const{for(const Ciudad&c:ciudades)f<<"C|"<<c.nombre<<"\n";for(size_t i=0;i<ciudades.size();++i)for(const Arista&e:ciudades[i].adyacencia)if((int)i<e.destino)f<<"R|"<<ciudades[i].nombre<<"|"<<ciudades[e.destino].nombre<<"|"<<e.km<<"\n";}
};

// COLA ENLAZADA PROPIA FIFO DE SOLICITUDES
struct Solicitud{int codigo,pasajeroId;string origen,destino;Solicitud*sig;Solicitud(int c,int p,string o,string d):codigo(c),pasajeroId(p),origen(o),destino(d),sig(nullptr){}};
class ColaSolicitudes{
    Solicitud*frente,*final;
public:
    ColaSolicitudes():frente(nullptr),final(nullptr){}
    ~ColaSolicitudes(){limpiar();}
    void limpiar(){while(frente){Solicitud*p=frente;frente=frente->sig;delete p;}final=nullptr;}
    bool vacia()const{return frente==nullptr;}
    void encolar(int c,int p,const string&o,const string&d){Solicitud*n=new Solicitud(c,p,o,d);if(final)final->sig=n;else frente=n;final=n;}
    bool atender(Solicitud&salida){if(vacia())return false;Solicitud*p=frente;salida.codigo=p->codigo;salida.pasajeroId=p->pasajeroId;salida.origen=p->origen;salida.destino=p->destino;frente=frente->sig;if(!frente)final=nullptr;delete p;return true;}
    void mostrar()const{if(vacia()){cout<<"Cola vacia.\n";return;}cout<<"Frente: solicitud #"<<frente->codigo<<" (pasajero "<<frente->pasajeroId<<")\n";for(Solicitud*p=frente;p;p=p->sig)cout<<"#"<<p->codigo<<" | "<<p->origen<<" -> "<<p->destino<<"\n";}
    void guardar(ofstream&f)const{for(Solicitud*p=frente;p;p=p->sig)f<<"S|"<<p->codigo<<"|"<<p->pasajeroId<<"|"<<p->origen<<"|"<<p->destino<<"\n";}
};

class SITRAC{
    ListaPasajeros pasajeros;GrafoCiudades grafo;ColaSolicitudes cola;
    vector<string>historial;int siguientePasajero=1,siguienteSolicitud=1;
    void registrarEvento(const string&e){historial.push_back(e);}
    void menuCiudades(){
        int op;do{cout<<"\n--- CIUDADES ---\n1. Registrar ciudad\n2. Listar ciudades\n3. Eliminar ciudad\n0. Volver\n";op=leerOpcion("Opcion: ");
            if(op==1){string n=leerLinea("Nombre: ");if(grafo.agregarCiudad(n)){cout<<"Ciudad registrada.\n";registrarEvento("Ciudad agregada: "+n);}else cout<<"Ciudad vacia o duplicada; no se agrego.\n";}
            else if(op==2)grafo.mostrarCiudades();
            else if(op==3){string n=leerLinea("Ciudad a eliminar: ");if(grafo.eliminarCiudad(n)){cout<<"Ciudad y conexiones eliminadas sin referencias colgantes.\n";registrarEvento("Ciudad eliminada: "+n);}else cout<<"Ciudad inexistente.\n";}
            else if(op!=0)cout<<"Opcion no valida.\n";
        }while(op!=0);
    }
    void menuRutas(){
        int op;do{cout<<"\n--- RUTAS ---\n1. Agregar conexion\n2. Eliminar conexion\n3. Mostrar grafo\n4. Consultar vecinos\n5. Consultar ruta directa\n0. Volver\n";op=leerOpcion("Opcion: ");
            if(op==1){string a=leerLinea("Origen: "),b=leerLinea("Destino: ");double km=leerReal("Distancia en km: ");if(km<=0){cout<<"Distancia invalida: debe ser mayor que cero.\n";continue;}if(grafo.agregarRuta(a,b,km)){cout<<"Conexion bidireccional agregada.\n";registrarEvento("Ruta agregada: "+a+" - "+b);}else cout<<"No se pudo agregar. Verifique ciudades, duplicados y origen/destino.\n";}
            else if(op==2){string a=leerLinea("Origen: "),b=leerLinea("Destino: ");if(grafo.eliminarRuta(a,b)){cout<<"Conexion eliminada.\n";registrarEvento("Ruta eliminada: "+a+" - "+b);}else cout<<"Ruta inexistente.\n";}
            else if(op==3)grafo.mostrarRutas();
            else if(op==4){string n=leerLinea("Ciudad: ");grafo.vecinos(n);}
            else if(op==5){string a=leerLinea("Origen: "),b=leerLinea("Destino: ");cout<<(grafo.conectadas(a,b)?"Existe conexion directa.\n":"No existe conexion directa.\n");}
            else if(op!=0)cout<<"Opcion no valida.\n";
        }while(op!=0);
    }
    void menuPasajeros(){
        int op;do{cout<<"\n--- PASAJEROS ---\n1. Insertar\n2. Buscar\n3. Actualizar\n4. Eliminar\n5. Listar\n0. Volver\n";op=leerOpcion("Opcion: ");
            if(op==1){string n=leerLinea("Nombre: "),d=leerLinea("Documento: "),t=leerLinea("Telefono: ");if(pasajeros.insertar(siguientePasajero,n,d,t)){cout<<"Pasajero registrado con ID "<<siguientePasajero<<".\n";registrarEvento("Pasajero registrado: "+to_string(siguientePasajero));++siguientePasajero;}else cout<<"Datos invalidos o documento duplicado.\n";}
            else if(op==2){int id=leerOpcion("ID: ");Pasajero*p=pasajeros.buscar(id);if(p)cout<<p->id<<" | "<<p->nombre<<" | "<<p->documento<<" | "<<p->telefono<<"\n";else cout<<"Pasajero inexistente.\n";}
            else if(op==3){int id=leerOpcion("ID a actualizar: ");string n=leerLinea("Nuevo nombre: "),d=leerLinea("Nuevo documento: "),t=leerLinea("Nuevo telefono: ");if(pasajeros.actualizar(id,n,d,t)){cout<<"Pasajero actualizado.\n";registrarEvento("Pasajero actualizado: "+to_string(id));}else cout<<"No se pudo actualizar: ID inexistente o documento duplicado.\n";}
            else if(op==4){int id=leerOpcion("ID a eliminar: ");if(pasajeros.eliminar(id)){cout<<"Pasajero eliminado.\n";registrarEvento("Pasajero eliminado: "+to_string(id));}else cout<<"No existe pasajero con ese ID.\n";}
            else if(op==5)pasajeros.listar();
            else if(op!=0)cout<<"Opcion no valida.\n";
        }while(op!=0);
    }
    void menuCola(){
        int op;do{cout<<"\n--- COLA DE SOLICITUDES ---\n1. Encolar viaje\n2. Atender siguiente\n3. Mostrar cola y frente\n0. Volver\n";op=leerOpcion("Opcion: ");
            if(op==1){int id=leerOpcion("ID del pasajero: ");if(!pasajeros.buscar(id)){cout<<"Pasajero inexistente.\n";continue;}string a=leerLinea("Origen: "),b=leerLinea("Destino: ");if(!grafo.conectadas(a,b)){cout<<"Ruta inexistente; solicitud no creada.\n";continue;}cola.encolar(siguienteSolicitud,id,a,b);cout<<"Solicitud #"<<siguienteSolicitud<<" agregada.\n";registrarEvento("Solicitud encolada: "+to_string(siguienteSolicitud));++siguienteSolicitud;}
            else if(op==2){Solicitud s(0,0,"","");if(cola.atender(s)){cout<<"Atendida solicitud #"<<s.codigo<<": "<<s.origen<<" -> "<<s.destino<<"\n";registrarEvento("Solicitud atendida: "+to_string(s.codigo));}else cout<<"Cola vacia: no hay elementos para atender.\n";}
            else if(op==3)cola.mostrar();
            else if(op!=0)cout<<"Opcion no valida.\n";
        }while(op!=0);
    }
    void menuHistorial(){if(historial.empty()){cout<<"Historial vacio.\n";return;}cout<<"\n--- HISTORIAL ---\n";for(size_t i=0;i<historial.size();++i)cout<<i+1<<". "<<historial[i]<<"\n";}
    void menuBusquedas(){
        int op;do{cout<<"\n--- BUSQUEDAS ---\n1. Buscar pasajero por ID\n2. Buscar ciudad y consultar vecinos\n3. Consultar conexion entre ciudades\n0. Volver\n";op=leerOpcion("Opcion: ");
            if(op==1){int id=leerOpcion("ID: ");Pasajero*p=pasajeros.buscar(id);if(p)cout<<p->nombre<<" | "<<p->documento<<" | "<<p->telefono<<"\n";else cout<<"Pasajero no encontrado.\n";}
            else if(op==2){string n=leerLinea("Ciudad: ");grafo.vecinos(n);}
            else if(op==3){string a=leerLinea("Origen: "),b=leerLinea("Destino: ");cout<<(grafo.conectadas(a,b)?"Conexion directa encontrada.\n":"No se encontro conexion directa.\n");}
            else if(op!=0)cout<<"Opcion no valida.\n";
        }while(op!=0);
    }
    void menuReportes(){cout<<"\n--- REPORTE GENERAL ---\nPASAJEROS\n";pasajeros.listar();cout<<"\nCIUDADES Y RUTAS\n";grafo.mostrarRutas();cout<<"\nSOLICITUDES\n";cola.mostrar();cout<<"\nHISTORIAL\n";menuHistorial();}
    void guardar(){
        ofstream f("sitrac_datos.txt");if(!f){cout<<"Error al abrir archivo.\n";return;}
        pasajeros.guardar(f);grafo.guardar(f);cola.guardar(f);for(const string&h:historial)f<<"H|"<<h<<"\n";
        f.close();cout<<"Informacion guardada en sitrac_datos.txt.\n";
    }
    void cargar(){
        ifstream f("sitrac_datos.txt");if(!f){cout<<"No existe sitrac_datos.txt.\n";return;}
        // Evita duplicar datos si el usuario intenta cargar mas de una vez.
        pasajeros.limpiar();grafo=GrafoCiudades();cola.limpiar();historial.clear();siguientePasajero=1;siguienteSolicitud=1;
        string linea;int total=0;
        while(getline(f,linea)){stringstream ss(linea);string tipo;getline(ss,tipo,'|');
            if(tipo=="P"){string si,n,d,t;getline(ss,si,'|');getline(ss,n,'|');getline(ss,d,'|');getline(ss,t);try{int id=stoi(si);if(pasajeros.insertar(id,n,d,t)){siguientePasajero=max(siguientePasajero,id+1);++total;}}catch(...){}}
            else if(tipo=="C"){string n;getline(ss,n);if(grafo.agregarCiudad(n))++total;}
            else if(tipo=="R"){string a,b,k;getline(ss,a,'|');getline(ss,b,'|');getline(ss,k);try{if(grafo.agregarRuta(a,b,stod(k)))++total;}catch(...){}}
            else if(tipo=="S"){string c,p,a,b;getline(ss,c,'|');getline(ss,p,'|');getline(ss,a,'|');getline(ss,b);try{int ci=stoi(c),pi=stoi(p);if(pasajeros.buscar(pi)&&grafo.conectadas(a,b)){cola.encolar(ci,pi,a,b);siguienteSolicitud=max(siguienteSolicitud,ci+1);++total;}}catch(...){}}
            else if(tipo=="H"){string h;getline(ss,h);historial.push_back(h);}
        }
        cout<<"Registros cargados: "<<total<<".\n";
    }
public:
    void ejecutar(){
        int op;do{cout<<"\n========== SITRAC ==========\n1. Ciudades\n2. Rutas\n3. Pasajeros\n4. Cola\n5. Historial\n6. Busquedas\n7. Reportes\n8. Guardar/cargar\n0. Salir\n";
            op=leerOpcion("Seleccione: ");
            switch(op){
                case 1:menuCiudades();break;case 2:menuRutas();break;case 3:menuPasajeros();break;case 4:menuCola();break;
                case 5:menuHistorial();break;case 6:menuBusquedas();break;case 7:menuReportes();break;
                case 8:{int a;do{cout<<"\n--- ARCHIVOS ---\n1. Guardar\n2. Cargar\n0. Volver\n";a=leerOpcion("Opcion: ");if(a==1)guardar();else if(a==2)cargar();else if(a!=0)cout<<"Opcion no valida.\n";}while(a!=0);break;}
                case 0:cout<<"SITRAC finalizado.\n";break;default:cout<<"Opcion fuera de rango.\n";
            }
        }while(op!=0);
    }
};
int main(){SITRAC sistema;sistema.ejecutar();return 0;}
