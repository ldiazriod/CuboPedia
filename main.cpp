#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Usuario{                                  //Me he creado una clase Usuario, solo tiene la función Welcome.
public:
    Usuario(string _nombre): nombre{_nombre}{}

    void welcome();                            //La función welcome te da la bienvenida si ya has entrado antes. Si no has entrado antes te pide tu nombre.
    //Una vez metes el nombre, te crea dos ficheros, uno en el que se guarda tú nombre, y otro que se queda vacio.
    string getNombre() const;                  //El fichero vacio se útiliza para guardar todos los nombres de los ficheros con los cubos que tienes en la base de datos.
    void setNombre(const string &value);

private:
    string nombre;
};

//He implementado todo con menús. Tenemos una función menú principal en la que estan las opciones de crear, buscar o eliminar un cubo.
void mainMenu();

//Estas dos funciones se encargan de guardar en un fichero toda la información de tus cubos.
void guardarFicheroMod(string nomMod, string dim, vector<vector<string>> color, vector<vector<string>> nota, vector<vector<string>> algorit);
void guardarFicheroNoMod(string dim, vector<vector<string>> color, vector<vector<string>> nota, vector<vector<string>> algorit);

//Esta función es el menú en el que te piden todos los datos del cubo.
void newCubeMenu();

//Esta función es para guardar todos los nombres de los ficheros de tus cubos.
void documentosPush_Back(string nombreFichero);

//Esta función es para imprimir los nombres de los ficheros de tus cubos.
void printFicheros();

//Esta función simplemente te busca e imprime el contenido del cubo que quieras ver.
void searchFicheros();

//Estas dos funciones son para eliminar cubos. La primera función está el menú para eliminar y además te elimina el fichero como tal.
//La segunda te elimina el nombre del fichero del fichero con todos los nombres de los cubos.
void eliminarMenu();
void eliminardeLista(string nombre);

//Esta funcion elimina todos los ficheros del programa.
void eliminarUsuario();


int main()
{
    try {
        //Variables clase Usuario
        string nombre;
        Usuario miUsuario(nombre); //Nombre no lo útilizo en realidad.
        miUsuario.welcome();       //LLamamos a la función welcome.
        mainMenu();               //Después simplemente llamamos al menú principal, desde ahí el programa ya se ejecuta internamente.
    } catch (string e) {
        cout << e << endl;
    }
    return 0;
}

//CLASE USUARIO
void Usuario::welcome(){
    ifstream miUsuario("Usuario.txt");    //abrimos el fichero en el que está guardado el nombre del usuario.
    string nombre, nombreUsuario;

    if(!miUsuario.is_open()){                  //Si no se ha podido abrir, significa que no existe, así que le creamos los ficheros necesarios.
        ofstream nuevoUsuario ("Usuario.txt");
        ofstream nuevoFicheroDeFicheros ("todosMisDatos.txt");
        ofstream nuevoFicheroTiempos("mejoresTiempos.txt");
        cout << "Bienvenido, vemos que es la primera vez que te metes, podrias meter tu nombre?: ";   //le pedimos que meta su nombre.
        cin >> nombre;

        nuevoUsuario << nombre;          //Lo guardamos en el fichero llamado "Usuario.txt"
        nuevoUsuario.close();            //Cerramos los dos ficheros.
        nuevoFicheroDeFicheros.close();
        nuevoFicheroTiempos.close();

        //El fichero de "todosMisDatos.txt" lo dejamos vacio.
    }

    if(!miUsuario.eof()){                  //Si el fichero se abre, pues existe así que lo pasamos a un string y lo imprimimos.
        miUsuario >> nombreUsuario;

        cout << "Bienvenido a tu base de datos " << nombreUsuario << endl;

        miUsuario.close();
    }
}

//Otros
void mainMenu(){

    int decision;

    cout << "Que quieres hacer?: " << endl;
    cout << "1. Nuevo Cubo" << endl;      //Si es un nuevo cubo, te lleva al menú de nuevo cubo.
    cout << "2. Buscar Cubo" << endl;     //Si es buscar cubo, te lleva al menú de buscar.
    cout << "3. Eliminar Cubo" << endl;   //Si es eliminar cubo, te lleva al menú de eliminar.
    cout << "4. Borrar usuario" << endl;
    cout << "5. Salir" << endl;           //Esto simplemente hace que acabe el programa.

    cin >> decision;

    if(decision < 1 || decision > 4 ){              //Si no es una valida.
        throw string {"No es una opcion valida"};
    }else{                                         //Si lo es, te lleva a cada función correspondiente.
        switch(decision){

        case 1:{
            newCubeMenu();
            break;
        }
        case 2:{
            cout << endl;
            searchFicheros();
            break;
        }
        case 3:{
            cout << endl;
            eliminarMenu();
            break;
        }
        case 4:{
            cout << endl;
            eliminarUsuario();
            break;
        }

        case 5: {  //Al salir
            ifstream miUsuario ("Usuario.txt"); //Abrimos el fichero que almacena el nombre del usuario.
            string nombreUsuario;
            if(!miUsuario.eof()){               //Pasamos su contenido a un string.
                miUsuario >> nombreUsuario;
                cout << "Adios " << nombreUsuario << endl;   //Le despedimos mostrando además su nombre.
                miUsuario.close();
            }
            break;
        }

        }
    }
}

void newCubeMenu(){

    //Se que no hace falta útilizar vectores 2D para hacer esto, pero quería practicarlos un poco.

    string nomMod, dim;
    int decision;
    int numColores, numCapas, numAlgorit;
    //Vectores para la matriz de colores
    string color;
    vector<string> unColor;
    vector<vector<string>> todosLosColores;
    //Vectores para la matriz de notaciones
    string notacion;
    vector<string> unNotacion;
    vector<vector<string>> todasMisNotaciones;
    //Vectores para la matriz de algoritmos
    string algoritmo;
    vector<string> unAlgoritmo;
    vector<vector<string>> todosMisAlgoritmos;


    cout << endl;

    cout << "Que tipo de cubo es?: " << endl;
    cout << "1. Normal" << endl;               //Si eliges normal, es un cubo de toda la vida, por lo que no te pide el nombre.
    cout << "2. Modificacion" << endl;         //Si es una modificación, además te pide el nombre.
    cout << "3. Volver" << endl;               //Te lleva de vuelta al menú principal

    cin >> decision;

    if(decision < 1 || decision > 3){             //Si el número que has metido no es una opción valida.
        throw string {"No es un opcion valida"};

    }else{                                       //En el caso de que lo sea simplemente se hacen los switch-case
        switch(decision) {

        case 1: {

            cout << endl;

            cout << "Cuales son las dimensiones del cubo?: ";
            cin >> dim;

            cout << endl;

            cout << "Cuantos colores tiene tu cubo:? ";
            cin >> numColores;

            for(int i{0}; i < numColores; i++){
                cout << "Cual es el siguiente color?: ";
                cin >> color;

                unColor.push_back(color);
                todosLosColores.push_back(unColor);
                unColor.clear();
            }
            cout << endl;

            cout << "Cuantas capas tiene tu cubo? (Necesario para la notacion): ";
            cin >> numCapas;

            for(int j{0}; j < numCapas; j++){
                cout << "Meta la capa a la que se refiera, seguida de la letra utilizada para la notacion: ";
                cin >> notacion;

                unNotacion.push_back(notacion);
                todasMisNotaciones.push_back(unNotacion);
                unNotacion.clear();
            }

            cout << endl;

            cout << "Cuantos algoritmos tiene el cubo? Debe contar ademas con algoritmos de uso ocasional como los de paridadad: ";
            cin >> numAlgorit;

            cout << endl;

            cout << "Meta el algoritmo, ademas le recomendamos añadir antes de meter el algoritmo numerar o especificar el algoritmo." << endl;

            cout << "Ejemplo: " << endl;
            cout << "1.B,F,L,E,Rr,B" << endl;
            cout << "Paridad1.B'" << endl;

            cout << endl;

            for(int k{0}; k < numAlgorit; k++){

                cout << "Meta el algoritmo: ";
                cin >> algoritmo;

                unAlgoritmo.push_back(algoritmo);
                todosMisAlgoritmos.push_back(unAlgoritmo);
                unAlgoritmo.clear();

            }

            guardarFicheroNoMod(dim, todosLosColores, todasMisNotaciones, todosMisAlgoritmos);
            cout << "Se ha guardado todo correctamente." << endl;

            cout << "Quiere hacer alguna otra cosa?: ";
            mainMenu();

            break;
        }

        case 2: {

            cout << endl;

            cout << "Meta el nombre de la modificacion: ";
            cin >> nomMod;

            cout << endl;

            cout << "Cuales son las dimensiones del cubo?: ";
            cin >> dim;

            cout << endl;

            cout << "Cuantos colores tiene tu cubo:? ";
            cin >> numColores;

            for(int i{0}; i < numColores; i++){
                cout << "Cual es el siguiente color?: ";
                cin >> color;

                unColor.push_back(color);
                todosLosColores.push_back(unColor);
                unColor.clear();
            }
            cout << endl;

            cout << "Cuantas capas tiene tu cubo? (Necesario para la notacion): ";
            cin >> numCapas;

            for(int j{0}; j < numCapas; j++){
                cout << "Meta la capa a la que se refiera, seguida de la letra utilizada para la notacion: ";
                cin >> notacion;

                unNotacion.push_back(notacion);
                todasMisNotaciones.push_back(unNotacion);
                unNotacion.clear();
            }

            cout << endl;

            cout << "Cuantos algoritmos tiene el cubo? Debe contar ademas con algoritmos de uso ocasional como los de paridadad: ";
            cin >> numAlgorit;

            cout << endl;

            cout << "Meta el algoritmo, ademas le recomendamos añadir antes de meter el algoritmo numerar o especificar el algoritmo." << endl;

            cout << "Ejemplo: " << endl;
            cout << "1.B,F,L,E,Rr,B" << endl;
            cout << "Paridad1.B'" << endl;

            cout << endl;

            for(int k{0}; k < numAlgorit; k++){

                cout << "Meta el algoritmo: ";
                cin >> algoritmo;

                unAlgoritmo.push_back(algoritmo);
                todosMisAlgoritmos.push_back(unAlgoritmo);
                unAlgoritmo.clear();
            }
            guardarFicheroMod(nomMod, dim, todosLosColores, todasMisNotaciones, todosMisAlgoritmos);
            cout << "Se ha guardado todo correctamente." << endl;
            cout << "Quiere hacer alguna otra cosa?: ";
            cout << endl;
            mainMenu();
            break;
        }
        case 3:{
            cout << endl;
            mainMenu();
            break;
        }
        }
    }
}

void guardarFicheroMod(string nomMod, string dim, vector<vector<string>> color, vector<vector<string>> nota, vector<vector<string>> algorit){

    string nombreFichero{nomMod + dim + ".txt"};         //Le decimos que al ser una modificación, el nombre del Fichero sea el nombre del mod, más las dimensiones + txt
    ofstream miNuevoCubo(nombreFichero);                 //Creamos un fichero que tiene como nombre la suma descrita antes.

    miNuevoCubo << "Nombre de la modificacion: " << nomMod << endl;    //Metemos las cosas dentro del fichero.

    miNuevoCubo << "-----------------------------" << endl;           //Entre apartados, metemos esto para que sea más claro de ver y además facilite la impresión por pantalla.

    miNuevoCubo << "Dimensiones del cubo: " << dim << endl;

    miNuevoCubo << "-----------------------------" << endl;

    miNuevoCubo << "Colores de las caras del cubo: " << endl;

    for(unsigned int i{0}; i < color.size(); i++){                 //Recorremos nuestras matrices y les vamos metiendo los valores.
        for(unsigned int j{0}; j < color.at(i).size(); j++){
            miNuevoCubo << color.at(i).at(j);
            miNuevoCubo << " " << "|" << endl;                    //Además se le añade un barra al final de cada elemento para facilitar la impresión.
        }
    }

    miNuevoCubo << "-----------------------------" << endl;

    miNuevoCubo << "Notacion del cubo: " << endl;

    for(unsigned int ii{0}; ii < nota.size(); ii++){
        for(unsigned int jj{0}; jj < nota.at(ii).size(); jj++){
            miNuevoCubo << nota.at(ii).at(jj);
            miNuevoCubo << " " << "|" << endl;
        }
    }

    miNuevoCubo << "-----------------------------" << endl;

    miNuevoCubo << "Algoritmos del cubo: " << endl;

    for(unsigned int iii{0}; iii < algorit.size(); iii++){
        for(unsigned int jjj{0}; jjj < algorit.at(iii).size(); jjj++){
            miNuevoCubo << algorit.at(iii).at(jjj);
            miNuevoCubo << " " << "|" << endl;
        }
    }
    miNuevoCubo.close();

    documentosPush_Back(nombreFichero);         //Guardamos el nombre del nuevo fichero en el fichero de ficheros.
}

void guardarFicheroNoMod(string dim, vector<vector<string>> color, vector<vector<string>> nota, vector<vector<string>> algorit){

    string nombreFichero{dim + ".txt"};                        //Aquí es igual que antes, salvo que ahora el fichero tiene como nombre solo las dimensiones.
    ofstream miNuevoCubo(nombreFichero);                       //El resto es exactamente igual.

    miNuevoCubo << "Dimensiones del cubo: " << dim << endl;

    miNuevoCubo << "-----------------------------" << endl;

    miNuevoCubo << "Colores de las caras del cubo: " << endl;

    for(unsigned int i{0}; i < color.size(); i++){
        for(unsigned int j{0}; j < color.at(i).size(); j++){
            miNuevoCubo << color.at(i).at(j);
            miNuevoCubo << " " << "|" << endl;
        }
    }

    miNuevoCubo << "-----------------------------" << endl;

    miNuevoCubo << "Notacion del cubo: " << endl;

    for(unsigned int ii{0}; ii < nota.size(); ii++){
        for(unsigned int jj{0}; jj < nota.at(ii).size(); jj++){
            miNuevoCubo << nota.at(ii).at(jj);
            miNuevoCubo << " " << "|" << endl;
        }
    }

    miNuevoCubo << "-----------------------------" << endl;

    miNuevoCubo << "Algoritmos del cubo: " << endl;

    for(unsigned int iii{0}; iii < algorit.size(); iii++){
        for(unsigned int jjj{0}; jjj < algorit.at(iii).size(); jjj++){
            miNuevoCubo << algorit.at(iii).at(jjj);
            miNuevoCubo << " " << "|" << endl;
        }
    }
    miNuevoCubo.close();

    documentosPush_Back(nombreFichero);
}

void documentosPush_Back(string nombreFichero){

    ifstream misDatos ("todosMisDatos.txt"); //Este fichero es en el que se guardan todos los nombres de los ficheros con la información de los cubos. Se crea al entrar por primera vez.
    ofstream aux ("auxiliar.txt");           //Creamos un auxiliar donde meteremos los datos almacenados en el fichero de arriba, más el nuevo.
    string nombres;

    vector<string> ficheros;                //Un vector donde se van a guardar todos los nombres.

    while(!misDatos.eof()){                //Mientras esté lleno:

        misDatos >> nombres;               //Pasas el contenido del fichero a un string.

        ficheros.push_back(nombres);      //Guardas el contenido de esa iteración en un vector.
    }

    ficheros.push_back(nombreFichero);   //Cuando se termina el while, se le mete además el nombre del nuevo fichero.

    for(unsigned int i{0}; i < ficheros.size(); i++){    //Recorremos el vector.
        if(ficheros.at(i) == nombreFichero){             //Si fichero en el que estamos es el último, se mete en el fichero auxiliar sin salto de linea.
            aux << ficheros.at(i);                       //Esto es así ya que me dí cuenta de que el último elemento se duplicaba cuando quedaba un salto de línea al final del fichero.
        }else{
            aux << ficheros.at(i) << endl;              //Si no, se guarda con un salto de línea.
        }

    }
    //No hace falta meterno con saltos de línea ya que al imprimirlos no salen, pero si alguien quiere entrar en los archivos, que por lo menos quede bonito-

    misDatos.close();   //Cerramos los dos ficheros.
    aux.close();

    remove("todosMisDatos.txt");                  //Eliminamos el fichero viejo, ya tenemos sus elementos guardados en el otro fichero, además del nuevo.
    rename("auxiliar.txt", "todosMisDatos.txt");  //Cambiamos el nombre del fichero auxiliar al del fichero viejo, así siempre tiene el mismo nombre.

}

void eliminardeLista(string nombre){
    ifstream misDatos ("todosMisDatos.txt");     //Este es practicamente igual que el de antes, salvo por un par de cosas.
    ofstream aux("auxiliar.txt");
    string nombres;
    unsigned int count{0};

    vector<string> ficheros;

    while(!misDatos.eof()){
        misDatos >> nombres;

        ficheros.push_back(nombres);
    }                                           //Hasta aquí todo igual.

    for(unsigned int i{0}; i < ficheros.size(); i++){   //Hacemos un for en el que vamos a buscar el nombre del fichero que queremos eliminar, y lo vamos a borrar.
        if(ficheros.at(i) == nombre){
            ficheros.erase(ficheros.begin()+i);
        }
    }

    for(unsigned int j{0}; j < ficheros.size(); j++){ //Ahora metemos el vector sin el valor eliminado.
        count++;                                      //Esta vez lo he implementado con un contador ya que el parametro que le pasamos a la función ya no existe.
        if(count == ficheros.size()){                 //Si el contador es igual al tamaño de vector, lo guarda sin salto de línea para que no se duplique.
            aux << ficheros.at(j);
        }else{
            aux << ficheros.at(j) << endl;           //Si no pues con salto de línea.
        }
    }

    //Aquí también es igual que antes.
    misDatos.close();
    aux.close();

    remove("todosMisDatos.txt");
    rename("auxiliar.txt", "todosMisDatos.txt");

}

void eliminarMenu(){                     //Aqui tenemos el menú para eleminar cubos.
    ifstream datos("todosLosDatos.txt");
    string nombre;
    string misDatos;
    int decision;

    printFicheros(); //Sacamos por pantalla los ficheros que tiene el usuario guardado

    cout << "Que fichero desea eliminar?(Debe meter el nombre sin el .txt): "; //Le pedimos el nombre del fichero a eliminar.
    cin >> nombre;


    cout << endl;

    cout << "Esta seguro de que quiere eliminar el siguiente archivo?: "  << nombre + ".txt" << endl; //nos aseguramos de que el usuario lo quiera eliminar, para evitar problemas.
    cout << "1. No" << endl;
    cout << "2. Si" << endl;
    cin >> decision;

    cout << endl;

    if(decision < 1 || decision > 2){                   //En caso de que no sea una opcion valida.
        throw string {"No es una opcion valida"};
    }else{
        switch(decision){
        case 1:{

            cout << "Se le ha devuelto al menu princiapal" << endl;      //Si no quería eliminar el cubo, se le devuelva al menú principal.

            cout << endl;

            mainMenu();

            break;
        }

        case 2:{                    //si lo quería hacemos lo siguiente.
            const char *datName;    //Nos creamos un puntero de tipo char y le decimos que es una constante.

            nombre = nombre + ".txt";   //Convertimos el nombre que ha metído el usuario en el nombre del fichero.

            datName = nombre.c_str();   //Inicializamos el puntero a nombre convertido en chars.

            remove(datName);            //Eliminamos el archivo correspondiente al nombre que ha metido el usuario.

            eliminardeLista(nombre);    //Luego lo eliminamos del fichero de nombres de fichero.

            cout << "Su fichero ha sido eliminado" << endl;   //Se le comunica que el fichero se ha eliminado.

            cout << endl;

            mainMenu();  //Le devolvemos al menú principal.
        }

        }

    }

}

void printFicheros(){
    ifstream miDatos("todosMisDatos.txt"); //Abrimos el fichero con todos nuestros datos.
    string cubos;
    vector<string> comprobar;
    int count{0};   //Esto es para que cuando salga por pantalla, tenga un número a su lado, simplemente es para que quede bonito.

    while(!miDatos.eof()){
        count++;            //Por cada iteración, le sumamos uno.



        string s = to_string(count);   //Creamos un string y convertimos el número entero del contador a string.

        miDatos >> cubos;              //Pasamos los datos del fichero a cubos.

        comprobar.push_back(cubos);

        if(cubos.size() == 0){
            throw string {"No tienes ficheros"};
        }else{
            cout << s << ". " << cubos << endl; //Sacamos por pantalla el número, un punto y el nombre del fichero de nuestros cubos.
        }
    }


    miDatos.close();
}

void searchFicheros(){
    char volver;
    string nombreFichero;
    string datosDelCubo;
    int count{0};

    cout << "Estos son los cubos que tienes guardados: " << endl;

    cout << endl;

    printFicheros();   //Sacamos los nombres de los ficheros para que el usuario puede ver cuales tiene.

    cout << "Cual de los siguientes cubos quieres ver?(Debe meter el nombre sin el .txt): ";
    cin >> nombreFichero;                                  //Le pedimos que ponga el nombre del fichero.

    cout << endl;

    ifstream verCubo(nombreFichero + ".txt");         //Abrimos el fichero con el nombre que ha puesto el usuario + .txt
    //Esto lo hago para que el usuario no tenga que poner .txt cuando vaya a buscar algo.

    //Si el fichero tiene más de 4 caracteres, significa que es un mod, por lo que se imprime de otra forma.
    //La razón por la que es 4 y no 3 (3x3, 4x4, etc) es porque también existen cuboides (3x3x2, 4x3x2, etc)
    if(nombreFichero.size() > 4){
        while(!verCubo.eof()){

            verCubo >> datosDelCubo;

            //Aquí imprimimos todo lo del fichero pero de forma bonita.

            if(datosDelCubo != "-----------------------------"){   //Mientras no exista una separación.
                if(datosDelCubo == nombreFichero){                 //Si los datos del cubo son igual al nombre del fichero.
                    datosDelCubo = " ";                             //Lo convertimos a un espacio. Para que no se imprima con un salto de línea.
                }

                if(datosDelCubo == "|"){                           //Estas barritas son las que marcan que hay que hacer un salto de línea.
                    datosDelCubo = "";                             //Primero las borramos para que no se impriman y quede feo.
                    cout << endl;                                  //Luego hacemos el salto de línea.
                    cout << datosDelCubo;                          //Y las sacamos por pantalla para que no intefiera más abajo.
                }else{
                    cout << datosDelCubo << " ";                   //Si no es esa barrita, se imprimen los datos del fichero con un espacio entre medias.
                }

                if(datosDelCubo == "cubo:"){                       //Si la palabra en ese momento es "cubo" queremos un salto de línea.
                    if(count == 0){                                //Aquí esto no se útiliza mucho, es para que al encontrar la primera palabra cubo, no haga salto de línea.
                        count++;
                    }else{
                        cout << endl;                              //Si el contador no es cero, hacemos salto de línea.
                        cout << endl;
                        cout << "";
                    }
                }

            }else{
                cout << endl;                                     //En el caso de que exista una separación, hacemos un salto de línea
                cout << datosDelCubo << endl;                     //Imprimimos la separación y otro salto de línea.
            }

        }

        cout << endl;
        cout << endl;

        cout << "Cuando desee volver, pulse -v-" << endl;            //Si quiere volver el usuario debe pulsar la v y le devolverá al menú principal.
        cin >> volver;

        if(volver != 'v'){
            throw string {"No es una opcion valida"};

        }else{
            mainMenu();
        }

    }else{                                                         //En el caso de que no sea una modificación es casi igual, salvo por una cosa.

        while(!verCubo.eof()){

            verCubo >> datosDelCubo;

            if(datosDelCubo != "-----------------------------"){
                if(datosDelCubo == nombreFichero){
                    datosDelCubo = " ";
                }

                if(datosDelCubo == "|"){
                    datosDelCubo = "";
                    cout << endl;
                    cout << datosDelCubo;
                }else{
                    cout << datosDelCubo << " ";
                }

                if(datosDelCubo == "cubo:"){
                    if(count == 0){                               //Queremos que las dimensiones no salgan en otra línea, pura estetica.
                        count++;                                  //Así que si el contador es 0, significa que es la primera palabra cubo:
                        datosDelCubo = nombreFichero;             //Convertimos la palabra cubo: en la variable nombreFichero, por ejemplo, (2x2).
                        cout << datosDelCubo;                     //Sacamos por pantalla la palabra. Esto es así por la siguiente razón.
                    }else{                                        //Si sacamos por pantalla datosDelCubo sin cambiar el nombre saldría cubo: cubo:, pero al cambiarlo, sale cubo: 2x2.
                        cout << endl;                             //El resto es igual.
                        cout << endl;
                        cout << "";
                    }
                }

            }else{
                cout << endl;
                cout << datosDelCubo << endl;
            }

        }

        cout << endl;
        cout << endl;

        cout << "Cuando desee volver, pulse -v-" << endl;
        cin >> volver;

        if(volver != 'v'){
            throw string {"No es una opcion valida"};

        }else{
            mainMenu();
        }
    }

}

void eliminarUsuario(){
    int decision;
    string nombreUsuario, miUsuario;
    string nombreFicheros;
    const char *miData;
    cout << "Estas seguro de que quieres borrar tu usuario?: " << endl;
    cout << "1. No" << endl;
    cout << "2. Si" << endl;

    cin >> decision;

    if(decision < 1 || decision > 2){
        throw string {"No es una opcion valida"};
    }else{
        switch(decision){

        case 1:{
            cout << "Se te ha devuelto al menu principal" << endl;

            cout << endl;

            mainMenu();
            break;
        }

        case 2:{
            ifstream Usuario("Usuario.txt");
            ifstream misDatos("todosMisDatos.txt");

            if(!Usuario.eof()){
                Usuario >> miUsuario;
            }

            cout << "Debe meter antes lo siguiente: " << miUsuario << endl;
            cin >> nombreUsuario;

            if(nombreUsuario != miUsuario) {
                cout << "No es correcto, por favor, meta el nombre correcto: ";
                cin >> nombreUsuario;
            }

            while(!misDatos.eof()) {
                misDatos >> nombreFicheros;

                miData = nombreFicheros.c_str();

                remove(miData);            //Eliminamos el archivo correspondiente al nombre guardado en nuestro fichero de ficheros.
            }

            cout << "Se han eliminado todos los datos" << endl;

            Usuario.close();
            misDatos.close();

            remove("Usuario.txt");
            remove("todosMisDatos.txt");
        }
        }
    }
}

//CLASE USUARIO.
string Usuario::getNombre() const
{
    return nombre;
}

void Usuario::setNombre(const string &value)
{
    nombre = value;
}
