#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


template<typename Y>
void imprimirRelacion(vector<vector<Y>> relacion){
  cout<< "\n{";
  for(int i =0; i < relacion.size(); i++) cout << '(' << relacion[i][0] << ", " << relacion[i][1]<< ')'; 
  cout<< "}";
}

template<typename U>
void imprimirConjunto(vector<U> conjunto){
  cout<< "\n{";
  for(int i = 0; i<conjunto.size(); i++) cout<< conjunto[i] << ',';
  cout<< "}";
}

void generarConjuntos(vector<int> &numeros, 
                  vector<char> &letras, 
                  vector<vector<int>> &productoNumeros, 
                  vector<vector<char>> &productoLetras, 
                  int &tipo
  ){
  int n;
  do{
    cout<<"Ingrese el numero de elementos de su conjunto(entre 4 y 10): ";
    cin>>n;
  }while(n<4 || n>10);
  cout<<endl;
  do{
    cout<<"Ingrese el tipo de conjunto que desea ingresar \n1: numeros \n2: caracteres \n";
    cin>>tipo;
  }while(tipo!=1 && tipo!=2);

  if(tipo==1){
    for(int i=0; i<n;i++){
      int temp;
      cout<<"\nIngrese el elemento "<< i+1<<": ";
      cin>>temp;
      numeros.push_back(temp);
      cout<<"elemento ingresado: "<<numeros[i]<<endl;
    }
  }
  else{
    for(int i=0; i<n;i++){
      char temp;
      cout<<"Ingrese el elemento "<<i+1<<": ";
      cin>> temp;
      letras.push_back(temp);
      cout<<"\nelemento ingresado: "<<letras[i]<<endl;
    }
  }

  if(tipo==1){
    cout << "El conjunto es:\nA={ ";
  for(int i=0; i<n-1;i++){
    cout<< numeros[i]<<" , ";
    };
  cout << numeros[n-1] << "}" << endl;
  }
  else{
    cout << "\nEl conjunto es:\nA={ ";
  for(int i=0; i<n-1;i++){
    cout<< letras[i]<<" , ";
    };
  cout << letras[n-1] << "}" << endl;
  }

  if (tipo==1){
  cout<< "AxA = { ";
  for(int i=0; i<n;i++) {
    for(int j=0;j<n;j++){
      vector<int> par(2);
      par[0] = numeros[i];
      par[1] = numeros[j];
      productoNumeros.push_back(par);
      cout<<"("<< numeros[i]<<" , "<<numeros[j]<<")";
    }
  }
  cout<< " }";
  }
  else{
    cout<< "AxA = { ";
  for(int i=0; i<n;i++) {
    for(int j=0;j<n;j++){
      vector<char> par(2);
      par[0] = letras[i];
      par[1] = letras[j];
      productoLetras.push_back(par);
      cout<<"("<< letras[i]<<" , "<<letras[j]<<")";
    }
  }
  cout<< " }";
       }
}

template<typename T>
vector<vector<T>> armarRelacion(vector<vector<T>>producto){
  int n = 0;
  vector<vector<T>> relacion;
  cout<< "\nAhora creemos la relacion...";
  while(n>=0){
    //a y b representan a los elementos del par tal que (a,b)
    T a;
    T b;
    vector<T> par(2);
    cout<< "\nIngresa los numeros del par que quieras agreagar a la relacion separados por un espacio:";
    cin>>a;
    cin>>b;
    par[0] = a; par[1] = b;
    for(int i = 0; i < producto.size(); i++){
      if(producto[i] == par) {
        relacion.push_back(par);
        break;
      }
      if(producto.size() -1 == i) cout<< "\nEl par que ingresaste no existe, vuelve a intentar";
    }
    cout<<"\nAsi va tu relacion:";
    imprimirRelacion<T>(relacion);
    while(n>=0){
      
      char opcion;
      cout<< "\nAgregar otro par? (y/n)";
      cin>>opcion;
      if(opcion == 'y' || opcion == 'Y') break;
      else if(opcion == 'n' || opcion == 'N') n = -1;
    }
  }
  return relacion;
}

template <typename W>
bool comprobarSiRelacionDeOrden(vector<vector <W> > relacion){
  bool reflexiva = true;
  bool antisimetrica = true;
  bool transitiva = true;

  //crear un conjunto de todos loselementos que aparecen en la relacion sin repetirlos
  vector<W> elementos;

  for (int i = 0; i< relacion.size(); i++){
    for(int j = 0; j< 2; j++){
      if(i == 0 && j == 0) elementos.push_back(relacion[i][j]);
      else{
        bool agregar = true;
        for(int k = 0; k< elementos.size(); k++){
          if(elementos[k] == relacion[i][j]) agregar = false;
        }
        if(agregar) elementos.push_back(relacion[i][j]);
      }
    }
  }
  imprimirConjunto(elementos);
  //comprobar que la relacion es reflexiva
  for(int i = 0; i < elementos.size(); i++){
    bool cumple = false;
    for(int j = 0; j < relacion.size(); j++){
      if(elementos[i] == relacion[j][0] && relacion[j][0] == relacion[j][1]){ 
        if(j ==relacion.size() -1) cumple = true;
        break;
      }
      else if(j == relacion.size()-1) reflexiva = false;
    }
    if(!cumple && !reflexiva) {
      reflexiva = false;
      break;
    }
  }

  cout<< "\n" <<reflexiva;

  //comprobar que la relacion es antisimetrica
  for(int i = 0; i< relacion.size(); i++){
    if(relacion[i][0] != relacion[i][1]){
      bool falla = false;
      for(int j = i; j< relacion.size(); j++){
        vector<W> temp = {relacion[j][1], relacion[j][0]};
        if(relacion[i] == temp) falla = true;
      }
      if(falla) {
        antisimetrica = false;
        break;
      }
    }
  }
  cout<< "\n" << antisimetrica;
  
  //comprobar si es transitiva
  for(int i = 0; i< relacion.size(); i++){
    for(int j = 0; j< relacion.size(); j++){
      bool cumple = false;
      if(relacion[i][1] == relacion[j][0]){
        vector<W> temp = {relacion[i][0], relacion[j][1]};
        for(int k = 0; k<relacion.size(); k++){
          if(!std::count(relacion.begin(), relacion.end(), temp)){
            transitiva = false;
            break;
          }
        }
        if(!transitiva) break;
      }
    }
    if(!transitiva) break;
  }
  cout<< "\n" << transitiva;

  return (antisimetrica && transitiva && reflexiva);
}


int main() {
  int tipo;
  vector <int> numeros;
  vector <char> letras;
  vector<vector <int> > productoNumeros;
  vector<vector <char> > productoLetras;
  vector<vector <int> > relacionNumeros;
  vector<vector <char> > relacionLetras;
  

  generarConjuntos(numeros, letras, productoNumeros, productoLetras, tipo);

  if(tipo == 1) {
    relacionNumeros = armarRelacion <int> (productoNumeros);
    comprobarSiRelacionDeOrden <int> (relacionNumeros);
  }
  else {
    relacionLetras = armarRelacion<char>(productoLetras);
    comprobarSiRelacionDeOrden<char>(relacionLetras);
  }



  return 0;
}