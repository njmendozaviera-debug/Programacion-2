#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

struct Pokemon{
    int numeroPokedex;
    string nombre;
    string tipo1;
    string tipo2;
    int total;
    int hp;
    int ataque;
    int defensa;
    int ataqueEsp;
    int defensaEsp;
    int velocidad;
    int generacion;
    bool legendario;
};

void limpiar(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausarylimpiar(){
    cout << "\nPresiona Enter para continuar...";
    cin.get();
    limpiar();
}

Pokemon* cargarPokemonDinamico(const string& nombreArchivo, int& cantidadTotal){
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()){
        cout << "Error: no se pudo abrir el archivo " << nombreArchivo << endl;
        cantidadTotal = 0;
        return nullptr;
    }

    int capacidad = 20;
    int contador = 0;

    Pokemon* lista = new Pokemon[capacidad];

    string linea;

    getline(archivo, linea);

    while(getline(archivo, linea)){
        if (linea.empty()) continue;

        if (contador >= capacidad){
            capacidad *= 2;
            Pokemon* nuevaLista = new Pokemon[capacidad];

            for (int i = 0; i < contador; i++){
                nuevaLista[i] = lista[i];
            }

            delete[] lista;
            lista = nuevaLista;
        }

        stringstream ss(linea);
        Pokemon p;
        string temp;

        getline(ss, temp, ','); p.numeroPokedex = stoi(temp);
        getline(ss, p.nombre, ',');
        getline(ss, p.tipo1, ',');
        getline(ss, p.tipo2, ',');

        if (p.tipo2.empty()){
            p.tipo2 = "Ninguno";
        }

        getline(ss, temp, ','); p.total = stoi(temp);
        getline(ss, temp, ','); p.hp = stoi(temp);
        getline(ss, temp, ','); p.ataque = stoi(temp);
        getline(ss, temp, ','); p.defensa = stoi(temp);
        getline(ss, temp, ','); p.ataqueEsp = stoi(temp);
        getline(ss, temp, ','); p.defensaEsp = stoi(temp);
        getline(ss, temp, ','); p.velocidad = stoi(temp);
        getline(ss, temp, ','); p.generacion = stoi(temp);
        getline(ss, temp, ','); p.legendario = (temp == "True" || temp == "1");

        *(lista + contador) = p;
        contador++;
    }

    archivo.close();
    cantidadTotal = contador;
    return lista;
}

void mostrarTodos(const Pokemon* lista, int cantidad){
    pausarylimpiar();
    if (cantidad == 0){
        cout << "No hay Pokemon registrados para mostrar." << endl;
        return;
    }

    cout << "\n==========================================================================================" << endl;
    cout << "                                 LISTADO COMPLETO DE POKEMON                               " << endl;
    cout << "==========================================================================================" << endl;

    cout << "Nº Pokedex | Nombre               | Tipo 1      | Tipo 2      | Total | HP  | Ataque | Defensa" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < cantidad; i++){
        cout << "#" << (lista + i)->numeroPokedex;
        if ((lista + i)->numeroPokedex < 10) cout << "         | ";
        else if ((lista + i)->numeroPokedex < 100) cout << "        | ";
        else cout << "       | ";
        string nom = (lista + i)->nombre;
        cout << nom;
        for (int k = nom.length(); k < 18; k++) cout << " ";
        cout << "| ";
        
        string t1 = (lista + i)->tipo1;
        cout << t1;
        for (int k = t1.length(); k < 11; k++) cout << " ";
        cout << "| ";
        
        string t2 = (lista + i)->tipo2;
        cout << t2;
        for (int k = t2.length(); k < 11; k++) cout << " ";
        cout << "| ";
        
        cout << (lista + i)->total;
        if ((lista + i)->total < 100) cout << "   | ";
        else if ((lista + i)->total < 1000) cout << "  | ";
        else cout << " | ";
        
        cout << (lista + i)->hp;
        if ((lista + i)->hp < 10) cout << "   | ";
        else if ((lista + i)->hp < 100) cout << "  | ";
        else cout << " | ";

        cout << (lista + i)->ataque;
        if ((lista + i)->ataque < 10) cout << "    | ";
        else if ((lista + i)->ataque < 100) cout << "   | ";
        else cout << "  | ";

        cout << (lista + i)->defensa << endl;
    }
    cout << "==========================================================================================" << endl;
    cout << "Total de registros mostrados: " << cantidad << endl;
}

void buscarPorNumero(const Pokemon* lista, int cantidad, int num){
    pausarylimpiar();
    bool encontrado = false;

    for (int i = 0; i < cantidad; i++){
        if ((lista + i)->numeroPokedex == num){
            cout << "\n========================================" << endl;
            cout << "   POKEMON ENCONTRADO (Nº " << (lista + i)->numeroPokedex << ")" << endl;
            cout << "========================================" << endl;
            cout << "Nombre: " << (lista + i)->nombre << endl;
            cout << "Tipo 1: " << (lista + i)->tipo1 << " | Tipo 2: " << (lista + i)->tipo2 << endl;
            cout << "Estadisticas: " << endl;
            cout << "  -HP: " << (lista + i)->hp << " | Ataque: " << (lista + i)->ataque << " | Defensa: " << (lista + i)->defensa << endl;
            cout << "  -Atq. Esp: " << (lista + i)->ataqueEsp << " | Def. Esp: " << (lista +i)->defensaEsp << " | Vel: " << (lista + i)->velocidad << endl;
            cout << "Total: " << (lista + i)->total << " | Legendario: " << ((lista + i)->legendario ? "Si" : "No") << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado){
        cout << "\n No se encontro ningun Pokemon con el numero #" << num << endl;
    }
}

void buscarPorNombre(const Pokemon* lista, int cantidad, const string& nombreBuscado){
    pausarylimpiar();

    bool encontrado = false;

    for (int i = 0; i < cantidad; i++){
        if ((lista + i)->nombre == nombreBuscado){
            cout << "\n========================================" << endl;
            cout << "   POKEMON ENCONTRADO: " << (lista + i)->nombre << endl;
            cout << "========================================" << endl;
            cout << "Nº Pokedex: #" << (lista + i)->numeroPokedex << endl;
            cout << "Tipo 1: " << (lista + i)->tipo1 << " | Tipo 2: " << (lista + i)->tipo2 << endl;
            cout << "Estadisticas: " << endl;
            cout << "  -HP: " << (lista + i)->hp << " | Ataque: " << (lista + i)->ataque << " | Defensa: " << (lista + i)->defensa << endl;
            cout << "  -Atq. Esp: " << (lista + i)->ataqueEsp << " | Def. Esp: " << (lista +i)->defensaEsp << " | Vel: " << (lista + i)->velocidad << endl;
            cout << "Total: " << (lista + i)->total << " | Legendario: " << ((lista + i)->legendario ? "Si" : "No") << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado){
        cout << "\nNo se encontro al Pokemon con el nombre: " << nombreBuscado << endl;
    }
}

void mostrarPorTipo(const Pokemon* lista, int cantidad, const string& tipoBuscado){
    pausarylimpiar();
    cout << "\n--- LISTA DE POKEMON DE TIPO " << tipoBuscado << " ---" << endl;
    int contador = 0;

    for(int i = 0; i < cantidad; i++){
        if ((lista + i)->tipo1 == tipoBuscado || (lista + i)->tipo2 == tipoBuscado){
            cout << "#" << (lista + i)->numeroPokedex << " - "
                 << (lista + i)->nombre << " (Tipo 1: " << (lista + i)->tipo1
                 << " | Tipo 2: "<< (lista + i)->tipo2 << ")" << endl;
                 contador++;
        }
    }

    if (contador == 0){
        cout << "No se encontraron Pokemon con el tipo '" << tipoBuscado << "'." << endl;
    }else{
        cout << "Total encontrados: " << contador << endl;
    }
}

void mostrarTop3(const Pokemon* lista, int cantidad){
    pausarylimpiar();
    if (cantidad == 0) return;

    Pokemon* copia = new Pokemon[cantidad];
    for (int i = 0; i < cantidad; i++){
        copia[i] = lista[i];
    }

    for (int i = 0; i < cantidad - 1; i++){
        for (int j = 0; j < cantidad - i - 1; j++){
            if ((copia + j)->total < (copia + j + 1)->total){
                Pokemon temp = *(copia +j);
                *(copia + j) = *(copia + j + 1);
                *(copia + j + 1) = temp;
            }
        }
    }

    cout << "\n========================================" << endl;
    cout << "       TOP 3 POKEMON MAS FUERTES        " << endl;
    cout << "========================================" << endl;
    for (int i = 0; i < 3 && i < cantidad; i++){
        cout << i + 1 << ". #" << (copia + i)->numeroPokedex << " "
             << (copia + i )->nombre << " | Total: " << (copia + i)->total << endl;
    }

    cout << "\n========================================" << endl;
    cout << "        TOP 3 POKEMON MAS DEBILES       " << endl;
    cout << "========================================" << endl;
    for(int i = 0; i < 3 && i < cantidad; i++){
        Pokemon p = *(copia + cantidad - 1 - i);
        cout << i + 1 << ". #" << p.numeroPokedex << " "
             << p.nombre << " | Total: " << p.total << endl;
    }

    delete[] copia;
}

int main(){
    int totalPokemon = 0;
    string archivoCSV = "pokemon_150_registros.csv";

    Pokemon* lista = cargarPokemonDinamico(archivoCSV, totalPokemon);

    if (lista == nullptr || totalPokemon == 0){
        cout << "No se pudo iniciar el programa debido a un error con el archivo." << endl;
        return 1;
    }

    int opcion;
    do{
        cout << "\n==========================================" << endl;
        cout << "          POKEDEX - MENU PRINCIPAL        " << endl;
        cout << "==========================================" << endl;
        cout << "1. Ver TODOS los Pokemon (con encabezado)" << endl;
        cout << "2. Ver info de Pokemon por numero de Pokedex" << endl;
        cout << "3. Buscar Pokemon por nombre" << endl;
        cout << "4. Ver Pokemon por Tipo" << endl;
        cout << "5. Ver Top 3 mas Fuertes y mas Debiles" << endl;
        cout << "6. Salir" << endl;
        cout << "==========================================" << endl;
        cout << "Seleccione una opcion (1-6): ";
        cin >> opcion;

        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
            pausarylimpiar();
            continue;
        }

        switch (opcion){
            case 1:
                mostrarTodos(lista, totalPokemon);
                break;
            case 2: {
                int num;
                cout << "\nIngrese el numero de Pokedex a buscar: ";
                cin >> num;
                buscarPorNumero(lista, totalPokemon, num);
                break;
            }

            case 3:{
                string nombre;
                cout << "\nIngrese el nombre exacto del Pokemon: ";
                cin >> nombre;
                buscarPorNombre(lista, totalPokemon, nombre);
                break;
            }

            case 4: {
                string tipo;
                cout << "\nIngrese el tipo (ejemplo: Fire, Water, Grass): ";
                cin >> tipo;
                mostrarPorTipo(lista, totalPokemon, tipo);
                break;
            }

            case 5:
                mostrarTop3(lista, totalPokemon);
                break;
            
            case 6: 
                cout << "\nSaliendo del programa..." << endl;
                break;
            
            default:
                cout << "\nOpcion no valida. intente nuevamente" << endl;
                break;
        }
        if (opcion != 6){
            pausarylimpiar();
        }
    }while (opcion !=6);

    delete[] lista;
    lista = nullptr;

    cout << "Memoria liberada correctamente. Nos vemos en el proyecto o el proyecto 2 idk" << endl;
    return 0;
}