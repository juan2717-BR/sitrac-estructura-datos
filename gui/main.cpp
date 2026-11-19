#include <QtWidgets>
#include <functional>
#define main sitrac_console_main
#include "../src/main.cpp"
#undef main

class Window : public QWidget {
    QListWidget *nav;
    QStackedWidget *stack;
    QPlainTextEdit *output;
    int module=1;
    QString transcript;
    bool active=false;
    ListaPasajeros passengers; GrafoCiudades graph; ColaSolicitudes queue;
    std::vector<std::string> history;
    int nextP=1,nextS=1;
    void execute(int m,int op,const QStringList &args={}){
        std::ostringstream out; auto *old=std::cout.rdbuf(out.rdbuf());
        auto a=[&](int i){return args.at(i).toStdString();};
        auto id=[&](){return args.at(0).toInt();};
        auto event=[&](bool ok,const std::string &s){if(ok){history.push_back(s);out<<s<<"\n";}else out<<"Operacion rechazada: datos invalidos, duplicados o inexistentes.\n";};
        if(m==1){if(op==1)event(graph.agregarCiudad(a(0)),"Ciudad registrada: "+a(0));if(op==2)graph.mostrarCiudades();if(op==3)event(graph.eliminarCiudad(a(0)),"Ciudad y conexiones eliminadas: "+a(0));}
        if(m==2){if(op==1)event(graph.agregarRuta(a(0),a(1),args.at(2).toDouble()),"Conexion bidireccional agregada");if(op==2)event(graph.eliminarRuta(a(0),a(1)),"Conexion eliminada");if(op==3)graph.mostrarRutas();if(op==4)graph.vecinos(a(0));if(op==5)out<<(graph.conectadas(a(0),a(1))?"Existe conexion directa":"No existe conexion directa");}
        if(m==3){if(op==1){if(passengers.insertar(nextP,a(0),a(1),a(2)))event(true,"Pasajero registrado con ID "+std::to_string(nextP++));else event(false,"");}if(op==2){auto *p=passengers.buscar(id());if(p)out<<p->id<<" | "<<p->nombre<<" | "<<p->documento<<" | "<<p->telefono;else out<<"Pasajero inexistente";}if(op==3)event(passengers.actualizar(id(),a(1),a(2),a(3)),"Pasajero actualizado");if(op==4)event(passengers.eliminar(id()),"Pasajero eliminado");if(op==5)passengers.listar();}
        if(m==4){if(op==1){if(passengers.buscar(id())&&graph.conectadas(a(1),a(2))){queue.encolar(nextS,id(),a(1),a(2));event(true,"Solicitud encolada #"+std::to_string(nextS++));}else event(false,"");}if(op==2){Solicitud s(0,0,"","");if(queue.atender(s))event(true,"Solicitud atendida #"+std::to_string(s.codigo));else out<<"Cola vacia";}if(op==3)queue.mostrar();}
        if(m==5||m==7){if(m==7){out<<"PASAJEROS\n";passengers.listar();out<<"\nCIUDADES Y RUTAS\n";graph.mostrarRutas();out<<"\nSOLICITUDES\n";queue.mostrar();}out<<"\nHISTORIAL\n";for(auto &h:history)out<<h<<"\n";}
        if(m==6){if(op==1){auto *p=passengers.buscar(id());if(p)out<<p->nombre<<" | "<<p->documento<<" | "<<p->telefono;else out<<"Pasajero inexistente";}if(op==2)graph.vecinos(a(0));if(op==3)out<<(graph.conectadas(a(0),a(1))?"Existe conexion directa":"No existe conexion directa");}
        if(m==8&&op==1){std::ofstream f("sitrac_datos.txt");if(f){passengers.guardar(f);graph.guardar(f);queue.guardar(f);for(auto &h:history)f<<"H|"<<h<<"\n";f.close();out<<(f?"Datos guardados":"Error al guardar");}else out<<"Error al abrir archivo";}
        if(m==8&&op==2){std::ifstream f("sitrac_datos.txt");if(!f)out<<"No existe sitrac_datos.txt";else{passengers.limpiar();graph=GrafoCiudades();queue.limpiar();history.clear();nextP=nextS=1;std::string line;while(std::getline(f,line)){std::stringstream ss(line);std::vector<std::string> v;std::string x;while(std::getline(ss,x,'|'))v.push_back(x);if(!line.empty()&&line.back()=='|')v.push_back("");try{if(v.size()>=5&&v[0]=="P"){int i=std::stoi(v[1]);if(passengers.insertar(i,v[2],v[3],v[4]))nextP=std::max(nextP,i+1);}else if(v.size()==2&&v[0]=="C")graph.agregarCiudad(v[1]);else if(v.size()==4&&v[0]=="R")graph.agregarRuta(v[1],v[2],std::stod(v[3]));else if(v.size()==5&&v[0]=="S"){int i=std::stoi(v[1]),p=std::stoi(v[2]);if(passengers.buscar(p)&&graph.conectadas(v[3],v[4])){queue.encolar(i,p,v[3],v[4]);nextS=std::max(nextS,i+1);}}else if(v.size()==2&&v[0]=="H")history.push_back(v[1]);}catch(...){}}out<<"Datos cargados";}}
        std::cout.rdbuf(old);output->setPlainText(QString::fromStdString(out.str()));
    }
    QString ask(const QString &label,bool &ok){
        auto s=QInputDialog::getText(this,"SITRAC",label,QLineEdit::Normal,{},&ok).trimmed();
        if(ok && (s.contains('|')||s.contains('\n')||s.isEmpty())){
            QMessageBox::warning(this,"Dato invalido","Complete el campo sin usar el caracter |.");ok=false;
        }
        return s;
    }
    void action(int m,int op,QStringList fields){
        QStringList args;
        for(const auto &f:fields){
            bool ok=false; QString v;
            if(f.startsWith("ID")) v=QString::number(QInputDialog::getInt(this,"SITRAC",f,1,1,2147483647,1,&ok));
            else if(f.startsWith("Distancia")) v=QString::number(QInputDialog::getDouble(this,"SITRAC",f,120,-1000000,1000000,2,&ok),'f',2);
            else v=ask(f,ok);
            if(!ok)return;
            args<<v;
        }
        execute(m,op,args);
    }
    void add(QVBoxLayout *l,QString title,int m,int op,QStringList fields={}){
        auto *b=new QPushButton(title); l->addWidget(b);
        connect(b,&QPushButton::clicked,this,[=]{action(m,op,fields);});
    }
    QVBoxLayout *page(QString name,QString description){
        auto *w=new QWidget; auto *l=new QVBoxLayout(w);
        auto *h=new QLabel(name);h->setObjectName("heading");l->addWidget(h);
        auto *d=new QLabel(description);d->setWordWrap(true);l->addWidget(d);
        stack->addWidget(w);return l;
    }
public:
    Window(){
        setWindowTitle("SITRAC | Gestion de transporte");resize(1050,700);
        auto *root=new QHBoxLayout(this);root->setContentsMargins(0,0,0,0);
        nav=new QListWidget;nav->setFixedWidth(220);
        nav->addItems({"Inicio","Ciudades","Rutas","Pasajeros","Solicitudes FIFO","Historial","Busquedas","Reportes","Guardar / cargar"});
        root->addWidget(nav);
        auto *right=new QWidget;auto *layout=new QVBoxLayout(right);layout->setContentsMargins(24,20,24,20);
        stack=new QStackedWidget;layout->addWidget(stack,1);
        output=new QPlainTextEdit;output->setReadOnly(true);output->setPlaceholderText("Los resultados de las operaciones aparecen aqui.");
        layout->addWidget(new QLabel("RESULTADOS DEL SISTEMA"));layout->addWidget(output,1);root->addWidget(right,1);
        auto *l=page("SITRAC","Sistema Inteligente de Transporte y Gestion de Rutas. Selecciona un modulo del menu lateral.");
        add(l,"Ver reporte general",7,0);l->addStretch();
        l=page("Ciudades","Administra los vertices del grafo.");
        add(l,"Registrar ciudad",1,1,{"Nombre"});add(l,"Listar ciudades",1,2);add(l,"Eliminar ciudad",1,3,{"Ciudad a eliminar"});l->addStretch();
        l=page("Rutas","Conexiones bidireccionales entre ciudades.");
        add(l,"Agregar conexion",2,1,{"Origen","Destino","Distancia en km"});add(l,"Eliminar conexion",2,2,{"Origen","Destino"});add(l,"Mostrar grafo",2,3);add(l,"Consultar vecinos",2,4,{"Ciudad"});add(l,"Consultar ruta directa",2,5,{"Origen","Destino"});l->addStretch();
        l=page("Pasajeros","Lista enlazada propia de pasajeros.");
        add(l,"Registrar pasajero",3,1,{"Nombre","Documento","Telefono"});add(l,"Buscar pasajero",3,2,{"ID"});add(l,"Actualizar pasajero",3,3,{"ID","Nuevo nombre","Nuevo documento","Nuevo telefono"});add(l,"Eliminar pasajero",3,4,{"ID"});add(l,"Listar pasajeros",3,5);l->addStretch();
        l=page("Solicitudes de viaje","Cola enlazada: primero en entrar, primero en salir.");
        add(l,"Encolar viaje",4,1,{"ID del pasajero","Origen","Destino"});add(l,"Atender siguiente",4,2);add(l,"Mostrar cola y frente",4,3);l->addStretch();
        l=page("Historial","Registro de operaciones.");add(l,"Consultar historial",5,0);l->addStretch();
        l=page("Busquedas","Consulta pasajeros y conexiones.");add(l,"Buscar pasajero",6,1,{"ID"});add(l,"Consultar vecinos",6,2,{"Ciudad"});add(l,"Buscar conexion directa",6,3,{"Origen","Destino"});l->addStretch();
        l=page("Reportes","Consulta el estado general del sistema.");add(l,"Generar reporte",7,0);l->addStretch();
        l=page("Guardar y cargar","Persistencia en sitrac_datos.txt dentro del directorio de ejecucion.");add(l,"Guardar informacion",8,1);add(l,"Cargar informacion",8,2);l->addStretch();
        connect(nav,&QListWidget::currentRowChanged,stack,&QStackedWidget::setCurrentIndex);nav->setCurrentRow(0);
        setStyleSheet("QWidget {background:#f1f5f9;color:#172b45;font-size:14px;} QListWidget {background:#142b49;color:white;border:0;padding:12px;} QListWidget::item {padding:15px;border-radius:6px;} QListWidget::item:selected {background:#2563eb;color:white;} QLabel#heading {font-size:30px;font-weight:bold;} QPushButton {background:#2563eb;color:white;border:0;border-radius:7px;padding:10px;text-align:left;} QPushButton:hover {background:#1749ba;} QPlainTextEdit,QLineEdit,QSpinBox,QDoubleSpinBox {background:white;border:1px solid #b9c9dc;border-radius:5px;padding:8px;} ");
    }
};
int main(int argc,char **argv){QApplication app(argc,argv);Window w;w.show();return app.exec();}
