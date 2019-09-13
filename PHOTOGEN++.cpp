#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <direct.h>
using namespace std;



vector<string>cubo_lineal;

string nombre;
string html;
string css;

string ancho_imagen;
string alto_imagen;
string ancho_pixel;
string alto_pixel;

void InsertarImagen(string nombre);
void AbrirConfig(string config);
void AbrirCapa(string capa,string ancho_imagen);
void EscribirHtml(string html,string css,string ancho_imagen,string alto_imagen);
void Escribirscss(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel);


/* clase nodo */
class node{
public:
	string data;
	node* right;
	node* left;
	node* down;
	node* up;
	
	node(string data){
		this->data = data;
		right = NULL;
		left = NULL;
		down = NULL;
		up = NULL;
	}
};
/*Clase matriz*/
class matrix{
public:
	node *head;
	matrix(){
		node *temp= new node("0");
		head = temp;
	}
	void add(string value, int x, int y){
		
		add_x_header(x);
		
		add_y_header(y);
		
		node *new_node = new node(value);
		add_x(new_node,x);
		add_y(new_node,y);		
	}
	
	void add_x(node *new_node, int x){
		node *temp = head;
		stringstream ss;
		ss << x;
		while(temp->data!=ss.str()){
			temp = temp->right;
		}
		for(int i=0;i<1000;i++){
		if(temp->down == NULL){
			temp->down = new_node;
			new_node->up = temp;
			i=1000;
			}else{
			temp = temp->down;	
			}
		}
	}
	
	void add_y(node *new_node, int y){
		node *temp = head;
		stringstream ss;
		ss << y;
		while(temp->data!=ss.str()){
			temp = temp->down;
		}
		for(int i=0;i<1000;i++){
		if(temp->right == NULL){
			temp->right = new_node;
			new_node->left = temp;
			i=1000;
			}else{
			temp = temp->right;	
			}
		}
	}
	
	void add_x_header(int x){
		stringstream ss;
		ss << x;
		if(head->right==NULL){	
			node *temp = new node(ss.str());
			head->right = temp;
			temp->left = head;
		}else{
			node *temp = head;
			
			while(temp->right!=NULL && atoi(temp->right->data.c_str())<x){
				temp = temp->right;
			}
			if(temp->right==NULL){
				node *new_temp = new node(ss.str());
				temp->right = new_temp;
				new_temp->left = temp;
			}else if(temp->right!=NULL && atoi(temp->right->data.c_str())!= x){
				node *new_temp = new node(ss.str());
				node *der = temp->right;
				temp->right = new_temp;
				new_temp->left = temp;
				new_temp->right = der;
				der->left = new_temp;
			}
		}
	}
	void add_y_header(int y){
		stringstream ss;
		ss << y;
		if(head->down==NULL){
			node *temp = new node(ss.str());
			head->down = temp;
			temp->up = head;
		}else{
			node *temp = head;
			while(temp->down!=NULL && atoi(temp->down->data.c_str())<y){
				temp = temp->down;
			}
			if(temp->down==NULL){
				node *new_temp = new node(ss.str());
				temp->down = new_temp;
				new_temp->up = temp;
			}else if(temp->down!=NULL && atoi(temp->down->data.c_str()) != y){
				node *new_temp = new node(ss.str());
				node *der = temp->down;
				temp->down = new_temp;
				new_temp->up = temp;
				new_temp->down = der;
				der->up = new_temp;
			}
		}
	}
	void print_headers(){
		print_x_header();
		print_y_header();
	}
	
	void print_y_header(){
		node *temp = head->down;
		while(temp->down!=NULL){
			cout<<temp->data;
			cout<<"\n";
			temp = temp->down;
	}
		cout<<temp->data;
		cout<<"\n";	
	}
	void print_x_header(){
		node *temp = head;
		while(temp->right!=NULL){
			cout<<temp->data;
			cout<<"->";
			temp = temp->right;
	}
		cout<<temp->data;
		cout<<"\n";	
	}
	void print_nodes_full(){
		node *temp = head;
		node *temp2 = head;
	while(temp->down!=NULL){
		temp= temp2;
		temp2 = temp2->down;
		cout<<temp->data;
		while(temp->right!=NULL){
			temp = temp->right;
			cout<<"->";
			cout<<temp->data;
		}
		cout<<"\n";
	}
	}
};
/*Cubo disperso*/
/*clase nodo cubo disperso*/
struct nodo{
	matrix dato;
	nodo* siguiente;
} *primero, *ultimo;

void InsertarMatriz(matrix n);
void DesplegarCubo();
/*Metodos del cubo*/
void InsertarMatriz(matrix n){
	nodo* nuevo = new nodo();
	nuevo->dato = n;
	
	if(primero == NULL){
		primero = nuevo;
		primero->siguiente = NULL;
		ultimo = nuevo;
	}else{
		ultimo->siguiente = nuevo;
		nuevo->siguiente = NULL;
		ultimo = nuevo;
	}
}

void DesplegarCubo(){
	nodo* actual = new nodo();
	actual = primero;
	if(primero != NULL){
		
		while(actual != NULL){
			actual->dato.print_headers();  
			cout<< endl;
			actual = actual->siguiente;
		}
		
	}else{
		cout  << "\nEl cubo disperso se encuentra vacio\n\n";
	}
}

/*RGB to Hexa*/
class RGB
{
public:
	unsigned char R;
	unsigned char G;
	unsigned char B;

	RGB(unsigned char r, unsigned char g, unsigned char b)
	{
		R = r;
		G = g;
		B = b;
	}

	bool Equals(RGB rgb)
	{
		return (R == rgb.R) && (G == rgb.G) && (B == rgb.B);
	}
};

static string DecimalToHexadecimal(int dec) {
	if (dec < 1) return "00";

	int hex = dec;
	string hexStr = "";

	while (dec > 0)
	{
		hex = dec % 16;

		if (hex < 10)
			hexStr = hexStr.insert(0, string(1, (hex + 48)));
		else
			hexStr = hexStr.insert(0, string(1, (hex + 55)));

		dec /= 16;
	}

	return hexStr;
}

static string RGBToHexadecimal(RGB rgb) {
	string rs = DecimalToHexadecimal(rgb.R);
	string gs = DecimalToHexadecimal(rgb.G);
	string bs = DecimalToHexadecimal(rgb.B);

	return '#' + rs + gs + bs;
}
/*Arbol binario*/
class Node {
public:
    Node *n_der,*n_izq;
    string data;
    Node (string num) {
        data = num;
        n_izq = n_der = NULL;
    }
};

class tree {
public:
    Node* root;
    tree () {root = NULL; }
    bool insert(string data) { 
        return insert(data,root); 
    };
    bool insert(string item, Node* raiz_actual);
    void inorder()  { inorder(root);};
    void postorder()  { postorder(root);};
    void preorder()  { preorder(root);};
    void inorder( Node* actual) ;
    void postorder( Node*actual);
    void preorder( Node* actual) ;
    
    
};

bool tree :: insert(string item, Node *raiz_actual) {
	
    if (root == NULL) {
        root = new Node(item);
        return true;
    }else if (item < raiz_actual->data) {
        if (raiz_actual->n_izq == NULL) {
            raiz_actual->n_izq = new Node(item);
            return true;
        }
        else {
            return insert(item, raiz_actual->n_izq);
        }
    }else if (item > raiz_actual->data) {
        if (raiz_actual->n_der == NULL) {
            raiz_actual->n_der = new Node(item);
            return true;
        }
        else {
            return insert(item, raiz_actual->n_der);
        }
    }else {
        return false;
    }
}

void tree :: inorder( Node *root) {
    if (root != NULL) {
        inorder(root -> n_izq);
        cout <<" - "<< root->data <<endl;
        inorder(root -> n_der);
    }
    
}

void tree :: preorder( Node *root) {
    if (root != NULL) {
        cout << " " << root->data << " ->";
        preorder(root -> n_izq);
        preorder(root -> n_der);
    }
    
}

void tree :: postorder( Node *root) {
    if (root != NULL) {
        postorder(root -> n_izq);
        postorder(root -> n_der);
        cout << " " << root->data << " ->";
        
    }
    
}
/*Creacion del arbol*/
tree Arbol;
/*Abrir primer csv*/
void InsertarImagen(string nombre){
	string config;
	string capa;
	ifstream infile(nombre.c_str());
	string line = "";
	vector<string>datos_csv;
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ';')){
		datos_csv.push_back(word);
	}
	}
	for (unsigned i = 1; i < datos_csv.size(); i+=2){
		//cout<<datos_csv.at(i)<<endl;
		if (i==3){
			config = datos_csv.at(i);
			AbrirConfig(config);
		}else{
			capa = datos_csv.at(i);
			AbrirCapa(capa, ancho_imagen);
		}
	}
	string token = nombre.substr(0, nombre.find(".csv"));
	Arbol.insert(token+", Dimensiones Imagen: "+ancho_imagen+"X"+alto_imagen+", Dimensiones Pixel: "+ancho_pixel+"X"+alto_pixel);
	html=token+".html";
	css =token+".scss";
	Escribirscss(css,ancho_imagen,alto_imagen,ancho_pixel,alto_pixel);
	EscribirHtml(html,css,ancho_imagen,alto_imagen);
	cout<<"\nImagen insertada\n";
}
/*abrir config */
void AbrirConfig(string config){
	ifstream infile(config.c_str());
	string line = "";
	vector<string> datos_config;
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ';')){
		datos_config.push_back(word);
	}
	}
	for (unsigned i = 0; i < datos_config.size(); i++){
		//cout << datos_config.at(i)<< "\n";
		if(datos_config.at(i)=="image_width"){
			ancho_imagen=datos_config.at(i+1);
		}else if(datos_config.at(i)=="image_height"){
			alto_imagen=datos_config.at(i+1);
		}else if(datos_config.at(i)=="pixel_width"){
			ancho_pixel=datos_config.at(i+1);
		}else if(datos_config.at(i)=="pixel_height"){
			alto_pixel=datos_config.at(i+1);
		}
	}
}
/*abrir capas */
void AbrirCapa(string capa,string ancho_imagen){
	/*Cubo*/
	matrix *cubo = new matrix;
	
	int ancho = atoi(ancho_imagen.c_str());
	
	ifstream infile(capa.c_str());
	string line = "";
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ';')){
		cubo_lineal.push_back(word);
	}
	}
	int x=1;
	int y=1;
	for (unsigned i = 0; i < cubo_lineal.size(); i++){
		cubo->add(cubo_lineal.at(i),x,y);
		x+=1;
		if(x==ancho+1){
			y+=1;
			x=1;
		}
	}
	InsertarMatriz(*cubo);
}
/*Escribir css*/
void Escribirscss(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel){
	
	
	
	int altoactual = atoi(alto_imagen.c_str())*atoi(alto_pixel.c_str());
	int anchoactual = atoi(ancho_imagen.c_str())*atoi(ancho_pixel.c_str());
	
	int AltoPorAncho = atoi(ancho_imagen.c_str())*atoi(alto_imagen.c_str());
	
	vector<int>pintar;
	vector<string>value;
	
	
	for(int i=0; i<pintar.size();i++){
		cout<<pintar.at(i)<<"->";
	}
	
	ofstream archivo;
	string nombreArchivo,frase;
	char rpt;
	
	string token = nombre.substr(0, nombre.find(".csv"));
	string direccion = "Exports/"+token;
	mkdir(direccion.c_str());
	string nombrecss = direccion+"/"+css;
	
	archivo.open(nombrecss.c_str(),ios::out); //Creamos el archivo
	
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}

	archivo<<"body {"<<endl;
    archivo<<"  background: #333333;"<<endl;      
    archivo<<"  height: 100vh;"<<endl;
    archivo<<"  display: flex;"<<endl;          
    archivo<<"  justify-content: center;"<<endl;
    archivo<<"  align-items: center;"<<endl;
    archivo<<"}"<<endl;

    archivo<<".canvas {"<<endl;
    archivo<<"  width: "<<anchoactual<<"px;"<<endl;
    archivo<<"  height: "<<altoactual<<"px;"<<endl;
	archivo<<"}"<<endl;

	archivo<<".pixel {"<<endl;
    archivo<<"  width: "<<ancho_pixel<<"px;"<<endl;
    archivo<<"  height: "<<alto_pixel<<"px;"<<endl;
    archivo<<"  float: left;"<<endl;
    archivo<<"}"<<endl;
	int K=0;
	for (int i=0; i<cubo_lineal.size(); i++){
	
		if(K==AltoPorAncho){
			K=0;
		}
	if(cubo_lineal.at(i)!="x"){
		pintar.push_back(K+1);
		//metodo de split
		string hola = cubo_lineal.at(i);
		char str[hola.size()+1];
		strcpy(str,hola.c_str());
		char* point;
		point = strtok(str,"-");
	    
	    int r = atoi(point);
		point = strtok(NULL,"-");
		int g = atoi(point);
		point = strtok(NULL,"-");
		int b = atoi(point);
		point = strtok(NULL,"-");
		//pasar valores
		RGB data = RGB(r, g, b);
		value.push_back(RGBToHexadecimal(data));
	}
	K+=1;
	}

	for(int i=0; i<pintar.size();i++){
		archivo<<".pixel:nth-child("<<pintar.at(i)<<")"<<endl;
		archivo<<"  {background: "<<value.at(i)<<";"<<endl;
	archivo<<"}"<<endl;
	}
	
	archivo.close(); //Cerramos el archivo
}
/*Escrbir html*/
void EscribirHtml(string html, string css,string ancho_imagen,string alto_imagen){
	ofstream archivo;
	string nombreArchivo,frase;
	char rpt;
	
	int divs = atoi(alto_imagen.c_str())*atoi(ancho_imagen.c_str());
	
	string token = nombre.substr(0, nombre.find(".csv"));
	string direccion = "Exports/"+token;
	mkdir(direccion.c_str());
	string nombrehtml = direccion+"/"+html;
	archivo.open(nombrehtml.c_str(),ios::out); //Creamos el archivo
	
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}

	archivo<<"<!DOCTYPE html>"<<endl;
	archivo<<"<html>"<<endl;
	archivo<<"<head>"<<endl;
    archivo<<"<link rel="<<(char)34<<"stylesheet"<<(char)34<<" href="<<(char)34<<css.c_str()<<(char)34<<">"<<endl;
    archivo<<"</head>"<<endl;
    archivo<<"<body>"<<endl;
    archivo<<"<div class="<<(char)34<<"canvas"<<(char)34<<">"<<endl;
    
    for(int i = 0; i < divs; i++){
    archivo<<"<div class="<<(char)34<<"pixel"<<(char)34<<"></div>"<<endl;
	}
    archivo<<"</div>"<<endl;
	archivo<<"</body>"<<endl;
	archivo<<"</html>"<<endl;

	archivo.close(); //Cerramos el archivo
}

/*Main*/
int main ()
{
	string parametrox;
	string parametroy;
	string parametroz;
	string parametrocolor;
	int a;
	do{
		cout<< "\n";
		cout<< "1. Insert image\n";
		cout<< "2. Select image\n";
		cout<< "3. Apply filrtes\n";
		cout<< "4. Manual editing\n";
		cout<< "5. Export image\n";
		cout<< "6. Reports\n";
		cout<< "7. Exit \n\n";
		cout<<"Option to select: "; 
		cin >> a ;
		cout<< "\n";
		
		switch (a)
		{
			case 1:
				cout<<"Nombre del archivo: "; 
				cin>>nombre;
				InsertarImagen(nombre);
				break;
			case 2:
				Arbol.inorder();
				break;
			case 3:
				cout<< "Opcion3\n";
				break;
			case 4:
				cout<<"Coordenada x: "; 
				cin>>parametrox;
				cout<<"Coordenada y: "; 
				cin>>parametroy;
				cout<<"Numero de capa: "; 
				cin>>parametroz;
				cout<<"Color R-G-B: "; 
				cin>>parametrocolor;
				cout<<parametrox+","+parametroy+","+parametroz+","+parametrocolor;
				break;
			case 5:
				cout<< "Opcion5\n";
				break;
			case 6:
				cout<< "Opcion6\n";
				break;				
			case 7:
				system("pause");
				return 0;
				break;
			default:
				return main();
				break;
		}
	}
	while(a != 3);
	return main();
}




