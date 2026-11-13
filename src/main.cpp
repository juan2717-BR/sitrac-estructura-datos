#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Pasajero {
 int id; string nombre, documento, telefono; Pasajero* sig;
 Pasajero(int i,string n,string d,string t):id(i),nombre(n),documento(d),telefono(t),sig(nullptr){}
};
class ListaPasajeros {
 Pasajero* cabeza;
public:
 ListaPasajeros():cabeza(nullptr){}
 ~ListaPasajeros(){while(cabeza){auto*p=cabeza;cabeza=cabeza->sig;delete p;}}
 bool existeDocumento(string d)const{for(auto*p=cabeza;p;p=p->sig)if(p->documento==d)return true;return false;}
 bool agregar(int id,string n,string d,string t){if(existeDocumento(d))return false;auto*p=new Pasajero(id,n,d,t);if(!cabeza)cabeza=p;else{auto*q=cabeza;while(q->sig)q=q->sig;q->sig=p;}return true;}
 Pasajero* buscar(int id)const{for(auto*p=cabeza;p;p=p->sig)if(p->id==id)return p;return nullptr;}
 bool eliminar(int id){Pasajero*p=cabeza,*ant=nullptr;while(p&&p->id!=id){ant=p;p=p->sig;}if(!p)return false;if(ant)ant->sig=p->sig;else cabeza=p->sig;delete p;return true;}
 void listar()const{if(!cabeza){cout<<"No hay pasajeros registrados.\n";return;}for(auto*p=cabeza;p;p=p->sig)cout<<p->id<<" | "<<p->nombre<<" | "<<p->documento<<" | "<<p->telefono<<"\n";}
 void guardar(ofstream&f)const{for(auto*p=cabeza;p;p=p->sig)f<<"P|"<<p->id<<"|"<<p->nombre<<"|"<<p->documento<<"|"<<p->telefono<<"\n";}
};
struct Arista{int destino;double km;};
struct Ciudad{string nombre;vector<Arista> ady;};
class Grafo {
 vector<Ciudad> ciudades;
 int indice(string n)const{for(size_t i=0;i<ciudades.size();++i)if(ciudades[i].nombre==n)return (int)i;return -1;}
public:
 bool agregarCiudad(string n){if(n.empty()||indice(n)>=0)return false;ciudades.push_back({n,{}});return true;}
 bool agregarRuta(string a,string b,double km){int x=indice(a),y=indice(b);if(x<0||y<0||x==y||km<=0)return false;for(auto&e:ciudades[x].ady)if(e.destino==y)return false;ciudades[x].ady.push_back({y,km});ciudades[y].ady.push_back({x,km});return true;}
 bool conectadas(string a,string b)const{int x=indice(a),y=indice(b);if(x<0||y<0)return false;for(auto&e:ciudades[x].ady)if(e.destino==y)return true;return false;}
 void listar()const{if(ciudades.empty()){cout<<"No hay ciudades.\n";return;}for(size_t i=0;i<ciudades.size();++i){cout<<ciudades[i].nombre<<" -> ";if(ciudades[i].ady.empty())cout<<"sin conexiones";for(auto&e:ciudades[i].ady)cout<<ciudades[e.destino].nombre<<" ("<<e.km<<" km) ";cout<<"\n";}}
 void guardar(ofstream&f)const{for(auto&c:ciudades)f<<"C|"<<c.nombre<<"\n";for(size_t i=0;i<ciudades.size();++i)for(auto&e:ciudades[i].ady)if((int)i<e.destino)f<<"R|"<<ciudades[i].nombre<<"|"<<ciudades[e.destino].nombre<<"|"<<e.km<<"\n";}
};
struct Solicitud{int codigo,pasajero;string origen,destino;Solicitud*sig;Solicitud(int c,int p,string o,string d):codigo(c),pasajero(p),origen(o),destino(d),sig(nullptr){}};
class Cola {
 Solicitud* frente; Solicitud* fin;
public:
 Cola():frente(nullptr),fin(nullptr){}
 ~Cola(){while(frente){auto*p=frente;frente=frente->sig;delete p;}}
 bool vacia()const{return frente==nullptr;}
 void encolar(int c,int p,string o,string d){auto*n=new Solicitud(c,p,o,d);if(fin)fin->sig=n;else frente=n;fin=n;}
 bool atender(Solicitud&out){if(vacia())return false;auto*p=frente;out.codigo=p->codigo;out.pasajero=p->pasajero;out.origen=p->origen;out.destino=p->destino;frente=frente->sig;if(!frente)fin=nullptr;delete p;return true;}
 void listar()const{if(vacia()){cout<<"No hay solicitudes pendientes.\n";return;}for(auto*p=frente;p;p=p->sig)cout<<"#"<<p->codigo<<" Pasajero "<<p->pasajero<<": "<<p->origen<<" -> "<<p->destino<<"\n";}
 void guardar(ofstream&f)const{for(auto*p=frente;p;p=p->sig)f<<"S|"<<p->codigo<<"|"<<p->pasajero<<"|"<<p->origen<<"|"<<p->destino<<"\n";}
};
int entero(string m){int n;cout<<m;while(!(cin>>n)){cout<<"Valor invalido. Intente: ";cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');}cin.ignore(numeric_limits<streamsize>::max(),'\n');return n;}
double decimal(string m){double n;cout<<m;while(!(cin>>n)||n<=0){cout<<"Ingrese un numero mayor que cero: ";cin.clear();cin.ignore(numeric_limits<streamsize>::max(),'\n');}cin.ignore(numeric_limits<streamsize>::max(),'\n');return n;}
string texto(string m){string s;cout<<m;getline(cin,s);return s;}

class Sistema {
 ListaPasajeros pasajeros; Grafo grafo; Cola solicitudes; vector<string> historial; int idPas=1,idSol=1;
 void pasajerosMenu(){int op;do{cout<<"\n-- PASAJEROS --\n1 Registrar\n2 Listar\n3 Buscar\n4 Eliminar\n0 Volver\n";op=entero("Opcion: ");if(op==1){string n=texto("Nombre: "),d=texto("Documento: "),t=texto("Telefono: ");if(n.empty()||d.empty())cout<<"Nombre y documento obligatorios.\n";else if(pasajeros.agregar(idPas,n,d,t))cout<<"Registrado con ID "<<idPas++<<"\n";else cout<<"Documento duplicado.\n";}else if(op==2)pasajeros.listar();else if(op==3){int id=entero("ID: ");auto*p=pasajeros.buscar(id);if(p)cout<<p->nombre<<" | "<<p->documento<<" | "<<p->telefono<<"\n";else cout<<"No encontrado.\n";}else if(op==4){int id=entero("ID a eliminar: ");cout<<(pasajeros.eliminar(id)?"Eliminado.\n":"ID inexistente.\n");}}while(op!=0);}
 void rutasMenu(){int op;do{cout<<"\n-- CIUDADES Y RUTAS --\n1 Agregar ciudad\n2 Agregar ruta\n3 Mostrar grafo\n4 Consultar conexion directa\n0 Volver\n";op=entero("Opcion: ");if(op==1){string n=texto("Ciudad: ");cout<<(grafo.agregarCiudad(n)?"Ciudad agregada.\n":"Ciudad vacia o repetida.\n");}else if(op==2){string a=texto("Origen: "),b=texto("Destino: ");double km=decimal("Distancia km: ");cout<<(grafo.agregarRuta(a,b,km)?"Ruta bidireccional creada.\n":"No se pudo crear. Verifique ciudades y duplicados.\n");}else if(op==3)grafo.listar();else if(op==4){string a=texto("Origen: "),b=texto("Destino: ");cout<<(grafo.conectadas(a,b)?"Hay conexion directa.\n":"No hay conexion directa.\n");}}while(op!=0);}
 void solicitudesMenu(){int op;do{cout<<"\n-- SOLICITUDES --\n1 Crear solicitud\n2 Ver cola\n3 Atender siguiente\n0 Volver\n";op=entero("Opcion: ");if(op==1){int p=entero("ID pasajero: ");if(!pasajeros.buscar(p)){cout<<"Pasajero no registrado.\n";continue;}string a=texto("Origen: "),b=texto("Destino: ");if(!grafo.conectadas(a,b)){cout<<"No existe ruta directa registrada.\n";continue;}solicitudes.encolar(idSol,p,a,b);historial.push_back("Solicitud "+to_string(idSol)+" creada: "+a+" a "+b);cout<<"Solicitud #"<<idSol++<<" en cola.\n";}else if(op==2)solicitudes.listar();else if(op==3){Solicitud s(0,0,"","");if(solicitudes.atender(s)){cout<<"Atendida #"<<s.codigo<<": "<<s.origen<<" a "<<s.destino<<"\n";historial.push_back("Solicitud "+to_string(s.codigo)+" atendida");}else cout<<"Cola vacia.\n";}}while(op!=0);}
 void reportes(){cout<<"\nPASAJEROS\n";pasajeros.listar();cout<<"\nRED DE RUTAS\n";grafo.listar();cout<<"\nSOLICITUDES\n";solicitudes.listar();cout<<"\nHISTORIAL\n";if(historial.empty())cout<<"Sin movimientos.\n";for(auto&h:historial)cout<<"- "<<h<<"\n";}
 void guardar(){ofstream f("sitrac_datos.txt");if(!f){cout<<"No se pudo crear el archivo.\n";return;}pasajeros.guardar(f);grafo.guardar(f);solicitudes.guardar(f);for(auto&h:historial)f<<"H|"<<h<<"\n";cout<<"Datos guardados en sitrac_datos.txt\n";}
 void cargar(){ifstream f("sitrac_datos.txt");if(!f){cout<<"No existe sitrac_datos.txt\n";return;}string l;int total=0;while(getline(f,l)){stringstream ss(l);string tipo;getline(ss,tipo,'|');if(tipo=="P"){string si,n,d,t;getline(ss,si,'|');getline(ss,n,'|');getline(ss,d,'|');getline(ss,t);try{int id=stoi(si);if(pasajeros.agregar(id,n,d,t)){idPas=max(idPas,id+1);++total;}}catch(...){}}else if(tipo=="C"){string n;getline(ss,n);if(grafo.agregarCiudad(n))++total;}else if(tipo=="R"){string a,b,k;getline(ss,a,'|');getline(ss,b,'|');getline(ss,k);try{if(grafo.agregarRuta(a,b,stod(k)))++total;}catch(...){}}else if(tipo=="S"){string c,p,a,b;getline(ss,c,'|');getline(ss,p,'|');getline(ss,a,'|');getline(ss,b);try{int ci=stoi(c),pi=stoi(p);if(pasajeros.buscar(pi)&&grafo.conectadas(a,b)){solicitudes.encolar(ci,pi,a,b);idSol=max(idSol,ci+1);++total;}}catch(...){}}else if(tipo=="H"){string h;getline(ss,h);historial.push_back(h);}}cout<<"Registros cargados: "<<total<<"\n";}
public:
 void ejecutar(){int op;do{cout<<"\n====================================\n SITRAC - TRANSPORTE Y RUTAS\n====================================\n1 Gestion de pasajeros\n2 Gestion de ciudades y rutas\n3 Solicitudes de viaje\n4 Consultas y reportes\n5 Guardar datos\n6 Cargar datos\n0 Salir\n";op=entero("Seleccione: ");switch(op){case 1:pasajerosMenu();break;case 2:rutasMenu();break;case 3:solicitudesMenu();break;case 4:reportes();break;case 5:guardar();break;case 6:cargar();break;case 0:cout<<"Hasta pronto.\n";break;default:cout<<"Opcion no valida.\n";}}while(op!=0);}
};
int main(){Sistema app;app.ejecutar();return 0;}
