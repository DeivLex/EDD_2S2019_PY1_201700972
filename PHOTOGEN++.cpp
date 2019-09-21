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
vector<string>cubo_linea;
vector<string>Filtros;
vector<string>ArbolNombre;

string ReporteMatrix="";
string ReporteMatrix1="";
string ReporteMatrix2="";
int NumCapa = 0;

string GraficarArbol="";
string Inorden="";
string Preorden="";
string Postorden="";

string carpeta;
string nombre;
string html;
string css;

string ancho_imagen;
string alto_imagen;
string ancho_pixel;
string alto_pixel;

void SeleccionarImagen(string nombre,string carpeta);
void InsertarImagen(string nombre,string carpeta);
void AbrirConfig(string config,string carpeta);
void AbrirCapa(string capa,string ancho_imagen,string carpeta);
void EscribirHtml(string html,string css,string ancho_imagen,string alto_imagen);
void Escribirscss(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel);
void EscribirscssGris(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel);
void EscribirscssNegativo(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel);
void ReporteArbol();
void ReporteArbolInorden();
void ReporteArbolPreorden();
void ReporteArbolPostorden();
void ReporteMatriz();
void MenuReporte();
void MenuFiltros();

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
		for(int i=0;i<10000;i++){
		if(temp->down == NULL){
			temp->down = new_node;
			new_node->up = temp;
			i=10000;
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
		for(int i=0;i<10000;i++){
		if(temp->right == NULL){
			temp->right = new_node;
			new_node->left = temp;
			i=10000;
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
		int tot=0;
		int x = 0;
		int y = 7;
		node *temp = head;
		node *temp2 = head;
	while(temp->down!=NULL){
		temp= temp2;
		temp2 = temp2->down;
		x=0;
		y-=2;
		tot+=1;
		stringstream sx,sy,stot;
		sy<<y;
		stot<<tot;
		sx<<x;
		if(temp->data != "x"){
		ReporteMatrix = ReporteMatrix +" p"+stot.str()+"[label="+(char)34+"{<data>"+temp->data+"|<next>}"+(char)34+"pos="+char(34)+sx.str()+","+sy.str()+"!"+(char)34+"];";
		ReporteMatrix1 = ReporteMatrix1 + "p"+stot.str();
	}
		while(temp->right!=NULL){
			temp = temp->right;
			tot+=1;
			x+=2;
			stringstream sx,sy,stot;
			sy<<y;
			stot<<tot;
			sx<<x;
			if(temp->data != "x"){
			ReporteMatrix = ReporteMatrix +" p"+stot.str()+"[label="+(char)34+"{<data>"+temp->data+"|<next>}"+(char)34+"pos="+char(34)+sx.str()+","+sy.str()+"!"+(char)34+"];";
			ReporteMatrix1 = ReporteMatrix1 +" -> "+ "p"+stot.str();
			}
		}
		ReporteMatrix = ReporteMatrix + "\n";
		ReporteMatrix1 = ReporteMatrix1+"[dir=both];" + "\n";
	}
	}
	
	void print_nodes_full_down(){
		int log = 1+ atoi(ancho_imagen.c_str());
		int tot=0;
		int x = 0;
		int y = 0;
		node *temp = head;
		node *temp2 = head;
	while(temp->right!=NULL){
		temp= temp2;
		temp2 = temp2->right;
		y+=1;
		tot=y;
		stringstream stot;
		stot<<tot;
		if(temp->data != "x"){
		ReporteMatrix2 = ReporteMatrix2 + "p"+stot.str();
	}
		while(temp->down!=NULL){
			temp = temp->down;
			tot+=log;
			stringstream stot;
			stot<<tot;
			if(temp->data != "x"){
			ReporteMatrix2 = ReporteMatrix2 +" -> "+ "p"+stot.str();
	}
		}
		ReporteMatrix2 = ReporteMatrix2+"[dir=both];" + "\n";
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
void DesplegarCubo(int x);
void ClearCubo();
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

void DesplegarCubo(int x){
	nodo* actual = new nodo();
	actual = primero;
	int j = 0;
	if(primero != NULL){
		while(j!=x ){
			actual = actual->siguiente;
			j++;
			if(x==j){
			actual->dato.print_nodes_full();
			actual->dato.print_nodes_full_down();
			}
		}
	}else{
		cout  << "\nEl cubo disperso se encuentra vacio\n\n";
	}
}

void ClearCubo(){
	primero = NULL;
	ultimo = NULL;
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
    void Padre()  { Padre(root);};
    void Iinorder()  { Iinorder(root);};
    void Select()  { Select(root);};
    void inorder( Node* actual) ;
    void postorder( Node*actual);
    void preorder( Node* actual) ;
    void Padre( Node* actual) ;
    void Iinorder( Node* actual) ;
    void Select( Node* actual) ;
    
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

void tree :: Iinorder( Node *root) {
    if (root != NULL) {
        Iinorder(root -> n_izq);
        cout <<" - "<< root->data <<endl;
        Iinorder(root -> n_der);
    }
    
}

void tree :: Select( Node *root) {
    if (root != NULL) {
        Select(root -> n_izq);
        ArbolNombre.push_back(root->data);
		Select(root -> n_der);
    }
    
}

void tree :: inorder( Node *root) {
    if (root != NULL) {
        inorder(root -> n_izq);
        Inorden = Inorden +" -> "+ root->data;
        //cout <<" - "<< root->data <<endl;
        inorder(root -> n_der);
    }
    
}

void tree :: preorder( Node *root) {
    if (root != NULL) {
    	Preorden = Preorden +" -> "+ root->data;
        //cout << " " << root->data << " ->";
        preorder(root -> n_izq);
        preorder(root -> n_der);
    }
    
}


void tree :: postorder( Node *root) {
    if (root != NULL) {
        postorder(root -> n_izq);
        postorder(root -> n_der);
        Postorden = Postorden +" -> "+ root->data;
        //cout << " " << root->data << " ->";
        
    }    
}

void tree :: Padre( Node *root) {
    if (root != NULL) {
    	GraficarArbol = GraficarArbol +" -> "+ root->data;
        Padre(root -> n_izq);
        GraficarArbol= GraficarArbol +"\n"+ root->data;
        Padre(root -> n_der);
    }
}
/*Creacion del arbol*/
tree Arbol;
tree ArbolC;
/*Seleccionar*/
void SeleccionarImagen(string nombre,string carpeta){
	ClearCubo();
	cubo_lineal.clear();
	Filtros.clear();
	string config;
	string capa;
	string direccion = carpeta+"/"+nombre;
	ifstream infile(direccion.c_str());
	string line = "";
	vector<string>datos_csv;
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ',')){
		datos_csv.push_back(word);
	}
	}
	for (unsigned i = 1; i < datos_csv.size(); i+=2){
		if (i==3){
			config = datos_csv.at(i);
			AbrirConfig(config,carpeta);
		}else{
			capa = datos_csv.at(i);
			AbrirCapa(capa, ancho_imagen,carpeta);
		}
	}
	string token = nombre.substr(0, nombre.find(".csv"));
	html=token+".html";
	css =token+".scss";
	Escribirscss(css,ancho_imagen,alto_imagen,ancho_pixel,alto_pixel);
	EscribirHtml(html,css,ancho_imagen,alto_imagen);
}

/*Abrir primer csv*/
void InsertarImagen(string nombre,string carpeta){
	ClearCubo();
	cubo_lineal.clear();
	Filtros.clear();
	string config;
	string capa;
	string direccion = carpeta+"/"+nombre;
	ifstream infile(direccion.c_str());
	string line = "";
	vector<string>datos_csv;
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ',')){
		datos_csv.push_back(word);
	}
	}
	for (unsigned i = 1; i < datos_csv.size(); i+=2){
		if (i==3){
			config = datos_csv.at(i);
			AbrirConfig(config,carpeta);
		}else{
			capa = datos_csv.at(i);
			AbrirCapa(capa, ancho_imagen,carpeta);
		}
	}
	string token = nombre.substr(0, nombre.find(".csv"));
	Arbol.insert(token+"_Imagen_"+ancho_imagen+"X"+alto_imagen+"_Pixel_"+ancho_pixel+"X"+alto_pixel);
	ArbolC.insert(carpeta);
	html=token+".html";
	css =token+".scss";
	Escribirscss(css,ancho_imagen,alto_imagen,ancho_pixel,alto_pixel);
	EscribirHtml(html,css,ancho_imagen,alto_imagen);
	cout<<"\nImagen insertada\n";
}
/*abrir config */
void AbrirConfig(string config,string carpeta){
	string direccion = carpeta+"/"+config;
	ifstream infile(direccion.c_str());
	string line = "";
	vector<string> datos_config;
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ',')){
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
void AbrirCapa(string capa,string ancho_imagen,string carpeta){
	/*Cubo*/
	matrix *cubo = new matrix;
	int ancho = atoi(ancho_imagen.c_str());
	
	string direccion = carpeta+"/"+capa;
	ifstream infile(direccion.c_str());
	string line = "";
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ',')){
		cubo_lineal.push_back(word);
		cubo_linea.push_back(word);
	}
	}
	int x=1;
	int y=1;
	for (unsigned i = 0; i < cubo_linea.size(); i++){
		cubo->add(cubo_linea.at(i),x,y);
		x+=1;
		if(x==ancho+1){
			y+=1;
			x=1;
		}
	}
	InsertarMatriz(*cubo);
	cubo_linea.clear();
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
		int y=(0.2126*r)+(0.7152*g)+(0.0722*b);
		//RGB data = RGB(y, y, y);
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
	pintar.clear();
	value.clear();
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
/*Filtro grises*/
void EscribirscssGris(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel){
	
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
		//RGB data = RGB(r, g, b);
		int y=(0.2126*r)+(0.7152*g)+(0.0722*b);
		RGB data = RGB(y, y, y);
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
	pintar.clear();
	value.clear();
}

/*Filtro negativo*/
void EscribirscssNegativo(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel){
	
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
		int q =(255-r);
		int w =(255-g);
		int e =(255-b);
		RGB data = RGB(q, w, e);
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
	pintar.clear();
	value.clear();
}

/*Reporte Arbol binario*/
void ReporteArbol(){
	ofstream archivo;
	char rpt;

	archivo.open("arbol.dot",ios::out); //Creamos el archivo
	
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	archivo<<"digraph G {"<<endl;
	archivo<<"nodesep=2.0;"<<endl;
    archivo<<"ranksep=0.3;"<<endl;
    archivo<<"graph [ordering="<<(char)34<<"out"<<(char)34<<"];";
	archivo<<"Lista_De_Imagenes "<<GraficarArbol<<";"<<endl;
	archivo<<"}"<<endl;
	archivo.close(); //Cerramos el archivo
	
	system("dot -Tpng arbol.dot -o arbol.png");
	system("arbol.png" );
}
/*Reporte Arbol Inorden*/
void ReporteArbolInorden(){
	ofstream archivo;
	char rpt;

	archivo.open("arbol1.dot",ios::out); //Creamos el archivo
	
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	archivo<<"digraph G {"<<endl;
    archivo<<"rankdir=LR;"<<endl;
	archivo<<"Inorden "<<Inorden<<";"<<endl;
	archivo<<"}"<<endl;
	archivo.close(); //Cerramos el archivo
	
	system("dot -Tpng arbol1.dot -o arbol1.png");
	system("arbol1.png" );
}
/*Reporte Arbol Preorden*/
void ReporteArbolPreorden(){
	ofstream archivo;
	char rpt;

	archivo.open("arbol2.dot",ios::out); //Creamos el archivo
	
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	archivo<<"digraph G {"<<endl;
	archivo<<"rankdir=LR;"<<endl;
	archivo<<"Preorden "<<Preorden<<";"<<endl;
	archivo<<"}"<<endl;
	archivo.close(); //Cerramos el archivo
	
	system("dot -Tpng arbol2.dot -o arbol2.png");
	system("arbol2.png" );
}
/*Reporte Arbol Postorden*/
void ReporteArbolPostorden(){
	ofstream archivo;
	char rpt;

	archivo.open("arbol3.dot",ios::out); //Creamos el archivo
	
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	archivo<<"digraph G {"<<endl;
	archivo<<"rankdir=LR;"<<endl;
	archivo<<"Postorden "<<Postorden<<";"<<endl;
	archivo<<"}"<<endl;
	archivo.close(); //Cerramos el archivo
	
	system("dot -Tpng arbol3.dot -o arbol3.png");
	system("arbol3.png" );
}
//Reporte matriz
void ReporteMatriz(){
	DesplegarCubo(NumCapa);
	ofstream archivo;
	char rpt;

	archivo.open("capa.dot",ios::out); //Creamos el archivo
	
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	archivo<<"digraph G {"<<endl;
	archivo<<"node[shape=record];"<<endl;
    archivo<<"graph[pencolor=transparent];"<<endl;
    archivo<<"node [style=filled];";
	archivo<<ReporteMatrix<<endl;
	archivo<<ReporteMatrix1<<endl;
	archivo<<ReporteMatrix2<<endl;
    archivo<<"}"<<endl;
	archivo.close(); //Cerramos el archivo
	
	system("neato -Tpng capa.dot -o capa.png");
	system("capa.png" );
}
//reporte filtros
void ReporteFiltros(){
	ofstream archivo;
	char rpt;

	archivo.open("filtros.dot",ios::out); //Creamos el archivo
	
	if(archivo.fail()){ //Si a ocurrido algun error
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	
	archivo<<"digraph G {"<<endl;
	archivo<<"rankdir=LR"<<endl;
	archivo<<"node [shape=box]"<<endl;
	archivo<<"Filtros_Aplicados";
	for(int i=0;i<Filtros.size(); i++){
	archivo<<" -> "<<Filtros.at(i);	
	}
	archivo<<"-> Filtros_Aplicados";
	archivo<<"[dir=both];";
	archivo<<"}"<<endl;
	archivo.close(); //Cerramos el archivo
	
	system("dot -Tpng filtros.dot -o filtros.png");
	system("filtros.png" );
}
/*Menu reportes*/
void MenuReporte(){
	int a;
	do{
		cout<< "\n";
		cout<< "1. Arbol\n";
		cout<< "2. Arbol Inorden\n";
		cout<< "3. Arbol Preorden\n";
		cout<< "4. Arbol Postorden\n";
		cout<< "5. Cubo\n";
		cout<< "6. Filtros Aplicados\n";
		cout<< "7. Exit \n\n";
		cout<<"Option to select: "; 
		cin >> a ;
		cout<< "\n";
		
		switch (a)
		{
			case 1:
				cout<< "Arbol\n";
				Arbol.Padre();
				ReporteArbol();
				break;
			case 2:
				cout<< "Arbol Inorden\n";
				Arbol.inorder();
				ReporteArbolInorden();
				break;
			case 3:
				cout<< "Arbol Preorden\n";
				Arbol.preorder();
				ReporteArbolPreorden();
				break;
			case 4:
				cout<< "Arbol Postorden\n";
				Arbol.postorder();
				ReporteArbolPostorden();
				break;
			case 5:
				cout<<"Numero de capa: "; 
				cin >> NumCapa;
				cout<< "Cubo\n";
				ReporteMatrix="";
				ReporteMatrix1="";
				ReporteMatrix2="";
				ReporteMatriz();
				break;
			case 6:
				cout<< "Filtros aplicados\n";
				ReporteFiltros();
				break;				
			case 7:
				system("pause");
				return;
				break;
			default:
				break;
		}
	}
	while(a != 3);
}

void MenuFiltros(){
	int a;
	do{
		cout<< "\n";
		cout<< "1. Grises\n";
		cout<< "2. Negativo\n";
		cout<< "3. Exit \n\n";
		cout<<"Option to select: "; 
		cin >> a ;
		cout<< "\n";
		
		switch (a)
		{
			case 1:
				cout<< "Filtro gris aplicado\n";
				EscribirscssGris(css,ancho_imagen,alto_imagen,ancho_pixel,alto_pixel);
				Filtros.push_back("Grises");
				break;
			case 2:
				cout<< "Filtro negativo aplicado\n";
				EscribirscssNegativo(css,ancho_imagen,alto_imagen,ancho_pixel,alto_pixel);
				Filtros.push_back("Negativo");
				break;			
			case 3:
				system("pause");
				return;
				break;
			default:
				break;
		}
	}
	while(a != 3);
}
/*Main*/
int main ()
{
	string hola,hola1="";
	int NumImagen =0;
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
				cout<<"Carpeta del archivo: "; 
				cin>>carpeta;
				cout<<"Nombre del archivo: "; 
				cin>>nombre;
				InsertarImagen(nombre,carpeta);
				break;
			case 2:
				Arbol.Iinorder();
				cout<<"Numero de imagen: "; 
				cin>>NumImagen;
				ArbolC.Select();
				hola=ArbolNombre.at(NumImagen-1);
				hola1=hola+".csv";
				SeleccionarImagen(hola1,hola);
				break;
			case 3:
				cout<< "Menu filtros\n";
				MenuFiltros();
				break;
			case 4:
				cout<<"Funcion en proceso, Espere hasta la proxima version\n"; 
				break;
			case 5:
				cout<< "Imagen Exportada\n";
				break;
			case 6:
				MenuReporte();
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




