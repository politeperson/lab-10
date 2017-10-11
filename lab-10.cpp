#include <iostream>
using namespace std;
void crear(int **m,int x, int y, int i = 0){//esta funcion crea todas las filas de la matriz con sus columnas
  if(i == x){
    return;
  }
  *(m+i) = new int [y];
  crear(m,x,y,++i);
}
void eliminar(int **m, int x, int i = 0){
  if(i == x){//cuando se termine de eliminar las columnas elimino la matriz
    delete [] m;
    return;
  }
  delete [] *(m+i);
  return eliminar(m,x,++i);
}
int init(int **m, int x, int y, int i = 0, int j = 0){//funcion para ingresar los valores que tendra mi matriz
  if(i == x){
    return 0;
  }
  if(j == y){
    return init(m,x,y,++i,0);
  }
  cin >> *(*(m+i)+j);
  return init(m,x,y,i,++j);
}
bool comp(int x, int y){//comparo dos numeros y devuelvo un booleano
  return x > y;
}
int mayor(int **A, int **B, int **C,int x, int y, int i = 0, int j = 0){
  if(i == x)
    return 0;
  if(j == y){
    return mayor(A,B,C,x,y,++i,0);
  }
  if( comp(*(*(A+i)+j),*(*(B+i)+j)) ){//si comp me devuelve true agrego a ya que es el mayor
    *(*(C+i)+j) = *(*(A+i)+j);
  }
  else{
    *(*(C+i)+j) = *(*(B+i)+j);//sino agrego b ya que es el mayor
  }
  return mayor(A,B,C,x,y,i,++j);
}
int menor(int **A, int **B, int **C,int x, int y, int i = 0, int j = 0){
  if(i == x)
    return 0;
  if(j == y){
    return menor(A,B,C,x,y,++i,0);
  }
  if(comp(*(*(A+i)+j) , *(*(B+i)+j))){//si comp me develve true le agrego B ya que es el menor
    *(*(C+i)+j) = *(*(B+i)+j);
  }
  else{//sino agrego A ya que es el menor
    *(*(C+i)+j) = *(*(A+i)+j);
  }
  return menor(A,B,C,x,y,i,++j);
}
void promedio(int **A, int **B, int **C, int x, int y, int i = 0, int j = 0){
  if(i == x)
    return;
  if(j == y){
    return promedio(A,B,C,x,y,++i,0);
  }
  *(*(C+i)+j) = (*(*(B+i)+j) + *(*(A+i)+j))/2;//divido la suma de los dos valores entre dos ya que solo comparo 2 matrices, en caso de n matrices tendria que hacer una sumatoria, y luego dividir entre n 
  return promedio(A,B,C,x,y,i,++j);
}
void suma(int **A, int **B, int **C,int x, int y, int i = 0, int j = 0){
  if(i == x)
    return;
  if(j == y){
    return suma(A,B,C,x,y,++i,0);
  }
  *(*(C+i)+j) = *(*(B+i)+j) + *(*(A+i)+j);//sumo las posiciones (i,j) de la matriz A, con las (i,j) de la matriz B
  return suma(A,B,C,x,y,i,++j);
}
void resta(int **A, int **B, int **C,int x, int y, int i = 0, int j = 0){
  if(i == x)
    return;
  if(j == y){
    return resta(A,B,C,x,y,++i,0);
  }
  *(*(C+i)+j) = *(*(B+i)+j) - *(*(A+i)+j);//resto las posiciones (i,j) de la matriz A, con las (i,j) de la matriz B
  return resta(A,B,C,x,y,i,++j);
}
void mult(int **A, int **B, int **C,int x, int y, int l, int i = 0, int j = 0, int k = 0){
  if(i == x)//cuando el iterador i llegue al numero de filas de A, que es x se para la multiplicación
    return;
  else if(j == l){
    return mult(A,B,C,x,y,l,++i,0,0);//cuando el iterador j llegue al numero de columnas de la matriz B, sumo el iterador i e reinicio los iteradores j , k
  }
  else if(k == y){//cuando el iterador k llegue al numero  de columnas de la matriz A, aumento el iterador j, y reininio el iterador k
    return mult(A,B,C,x,y,l,i,++j,0);
  }
  else{//sino hago la operación correspondiente
    *(*(C+i)+j) += *(*(A+i)+k) * *(*(B+k)+j);//como C esta inicializado en NULL que es 0, a este le voy sumando la multiplicacion de A,B
    return mult(A,B,C,x,y,l,i,j,++k);//y por ultimo aumento el iterador K, este algoritmo tiene complejidad O(N^3)
  }
}
int mostrar(int **m, int x, int y, int i = 0, int j = 0){//bueno esta función muestra la matriz
  if(i == x)
    return 0;
  if(j == y){//cada vez que acabo de recorrer una fila, imprimo un salto de linea para hacer que la matriz se vea ordenada
    cout << endl;
    return mostrar(m,x,y,++i,0);
  }
  cout << *(*(m+i)+j) << " ";//impprimo un espacio para la estética
  return mostrar(m,x,y,i,++j);
}
void principal(int **A, int **B, int **C){
    int x, y;
    //punteros a funciones
    void (*p_crear)(int **, int, int, int);//apunto a mi funcion crear con mi función p_crear
    p_crear = &crear;
    int (*p_init)(int **, int, int, int, int);//puntero p_init
    p_init = &init;
    void (*p_eliminar)(int **, int, int);//puntero p_eliminar
    p_eliminar = &eliminar;
    int (*p_mostrar)(int **, int, int, int, int);//puntero p_mostrar
    p_mostrar = &mostrar;
    
    //ingreso numero de filas y columnas
    cout << "Ingrese el numero de filas y columnas[n*m]: ";
    cin >> x >> y;
    A = new int *[x];
    B = new int *[x];
    C = new int *[x];
    //creo matriz
    p_crear(A,x,y,0);
    p_crear(B,x,y,0);
    p_crear(C,x,y,0);
    //inicializo matriz
    cout << "Ingresa la matriz A, con orden n*m: " << endl;
    p_init(A,x,y,0,0);
    cout << "Ingresa la matriz B, con orden n*m: " << endl;
    p_init(B,x,y,0,0);
    //mayor
    cout << "La matriz mayor es: " << endl;
    mayor(A,B,C,x,y);
    p_mostrar(C,x,y,0,0);
    //menor
    cout << "La matriz menor es: " << endl;
    menor(A,B,C,x,y);
    p_mostrar(C,x,y,0,0);
    //promedio
    cout << "La matriz promedio es: " << endl;
    promedio(A,B,C,x,y);
    p_mostrar(C,x,y,0,0);
    //suma
    cout << "La matriz suma es: " << endl;
    suma(A,B,C,x,y);
    p_mostrar(C,x,y,0,0);
    //resta
    cout << "La matriz resta es: " << endl;
    resta(A,B,C,x,y);
    p_mostrar(C,x,y,0,0);
    //mult
    p_eliminar(A,x,0);
    p_eliminar(B,x,0);
    p_eliminar(C,x,0);
    int l;
    cout << "Ahora ingresa el orden de una matriz A y B para multiplicarlas, recuerda que el orden de la matriz A debe ser n * m, y el orden de la matriz B es m * l\n";
    cout << "Ingresa n: ";
    cin >> x;
    cout << "Ingresa m: ";
    cin >> y;
    cout << "Ingresa l: ";
    cin >> l;
    A = new int *[x];
    B = new int *[y];
    C = new int *[x];
    p_crear(A,x,y,0);
    p_crear(B,y,l,0);
    p_crear(C,x,l,0);
    cout << "Ingresa la matriz A, con orden n*m: " << endl;
    p_init(A,x,y,0,0);
    cout << "Ingresa la matriz B, con orden n*l: " << endl;
    p_init(B,y,l,0,0);
    mult(A,B,C,x,y,l);
    cout << "La matriz multiplicación es: " << endl;
    p_mostrar(C,x,l,0,0);
    //elimino el resto de matrices
    p_eliminar(A,x,0);
    p_eliminar(B,x,0);
    p_eliminar(C,x,0);
}
int main(){
  int **A,**B,**C;
  principal(A,B,C);
  return 0;
}
