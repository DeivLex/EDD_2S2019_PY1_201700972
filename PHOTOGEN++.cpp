#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string nombre;
string html;
string css;

string ancho_imagen;
string alto_imagen;
string ancho_pixel;
string alto_pixel;
void InsertarImagen(string nombre);
void AbrirConfig(string config);
void EscribirHtml(string html,string css);
void Escribirscss(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel);

int main ()
{
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
				html="hola.html";
				css ="hola.scss";
				Escribirscss(css,ancho_imagen,alto_imagen,ancho_pixel,alto_pixel);
				EscribirHtml(html,css);
				break;
			case 2:
				cout<< "Opcion2\n";
				break;
			case 3:
				cout<< "Opcion3\n";
				break;
			case 4:
				cout<< "Opcion4\n";
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
void InsertarImagen(string nombre){
	string config;
	ifstream infile(nombre.c_str());
	string line = "";
	vector<string> all_words;
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ';')){
		all_words.push_back(word);
	}
	}
	for (unsigned i = 0; i < all_words.size(); i++){
		cout << all_words.at(i)<< "\n";
		if (all_words.at(i) == "0"){
			int n = i+1;
			config = all_words.at(n);
		}
	    
	}
	AbrirConfig(config);
	cout<<"\nImagen insertada\n";
}

void AbrirConfig(string config){
	ifstream infile(config.c_str());
	string line = "";
	vector<string> all_words;
	while (getline(infile, line)){
		stringstream strstr(line);
		string word = "";
	while (getline(strstr,word, ';')){
		all_words.push_back(word);
	}
	}
	for (unsigned i = 0; i < all_words.size(); i++){
		cout << all_words.at(i)<< "\n";
		if(all_words.at(i)=="image_width"){
			ancho_imagen=all_words.at(i+1);
		}else if(all_words.at(i)=="image_height"){
			alto_imagen=all_words.at(i+1);
		}else if(all_words.at(i)=="pixel_width"){
			ancho_pixel=all_words.at(i+1);
		}else if(all_words.at(i)=="pixel_height"){
			alto_pixel=all_words.at(i+1);
		}
	}
}

void Escribirscss(string css,string ancho_imagen,string alto_imagen,string ancho_pixel,string alto_pixel){
	
	int altoactual = atoi(alto_imagen.c_str())*atoi(alto_pixel.c_str());
	int anchoactual = atoi(ancho_imagen.c_str())*atoi(ancho_pixel.c_str());
	
	ofstream archivo;
	string nombreArchivo,frase;
	char rpt;
	
	archivo.open(css.c_str(),ios::out); //Creamos el archivo
	
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

	archivo<<".pixel:nth-child(0),"<<endl;
	archivo<<".pixel:nth-child(9),"<<endl;
	archivo<<".pixel:nth-child(10),"<<endl;
	archivo<<".pixel:nth-child(14),"<<endl;
	archivo<<".pixel:nth-child(15),"<<endl;
	archivo<<".pixel:nth-child(16),"<<endl;
	archivo<<".pixel:nth-child(17),"<<endl;
	archivo<<".pixel:nth-child(20),"<<endl;
	archivo<<".pixel:nth-child(21),"<<endl;
	archivo<<".pixel:nth-child(22),"<<endl;
	archivo<<".pixel:nth-child(23),"<<endl;
	archivo<<".pixel:nth-child(27),"<<endl;
	archivo<<".pixel:nth-child(28){"<<endl;
    archivo<<"  background: #000000;"<<endl;
	archivo<<"}"<<endl;

	archivo.close(); //Cerramos el archivo
}

void EscribirHtml(string html, string css){
	ofstream archivo;
	string nombreArchivo,frase;
	char rpt;
	
	archivo.open(html.c_str(),ios::out); //Creamos el archivo
	
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
    
    for(int i = 0; i < 36; i++){
    archivo<<"<div class="<<(char)34<<"pixel"<<(char)34<<"></div>"<<endl;
	}
    archivo<<"</div>"<<endl;
	archivo<<"</body>"<<endl;
	archivo<<"</html>"<<endl;

	archivo.close(); //Cerramos el archivo
}
/* clase nodo */
class node{
public:
	int data;
	node* right;
	node* left;
	node* down;
	node* up;
	
	node(int data){
		this->data = data;
		right = NULL;
		left = NULL;
		down = NULL;
		up = NULL;
	}
};
/*clase matriz*/
class matrix{
public:
	node *head;
	matrix(){
		node *temp= new node(0);
		head = temp;
	}
	void add(int value, int x, int y){
		
		add_x_header(x);
		
		add_y_header(y);
		
		node *new_node = new node(value);
		add_x(new_node,x);
		add_y(new_node,y);		
	}
	
	void add_x(node *new_node, int x){
		node *temp = head;
		while(temp->data!=x){
			temp = temp->right;
		}
		if(temp->down == NULL){
			temp->down = new_node;
			new_node->up = temp;
		}
	}
	
	void add_y(node *new_node, int y){
		node *temp = head;
		while(temp->data!=y){
			temp = temp->down;
		}
		if(temp->right == NULL){
			temp->right = new_node;
			new_node->left = temp;
		}
	}
	
	void add_x_header(int x){
		if(head->right==NULL){
			node *temp = new node(x);
			head->right = temp;
			temp->left = head;
		}else{
			node *temp = head;
			while(temp->right!=NULL && temp->right->data<x){
				temp = temp->right;
			}
			if(temp->right==NULL){
				node *new_temp = new node(x);
				temp->right = new_temp;
				new_temp->left = temp;
			}else if(temp->right!=NULL && temp->right->data != x){
				node *new_temp = new node(x);
				node *der = temp->right;
				temp->right = new_temp;
				new_temp->left = temp;
				new_temp->right = der;
				der->left = new_temp;
			}
		}
	}
	void add_y_header(int y){
		if(head->down==NULL){
			node *temp = new node(y);
			head->down = temp;
			temp->up = head;
		}else{
			node *temp = head;
			while(temp->down!=NULL && temp->down->data<y){
				temp = temp->down;
			}
			if(temp->down==NULL){
				node *new_temp = new node(y);
				temp->down = new_temp;
				new_temp->up = temp;
			}else if(temp->down!=NULL && temp->down->data != y){
				node *new_temp = new node(y);
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
	void print_nodes_x(){
		node *temp = head->right;
		while(temp->right!=NULL){
			cout<<temp->data;
			cout<<"->";
			if(temp->down!=NULL){
				cout<<temp->down->data;
			}
			cout<<"\n";
			temp = temp->right;
	}
		cout<<temp->data;
		cout<<"->";
		cout<<temp->down->data;	
	}
	void print_nodes_y(){
		node *temp = head->down;
		while(temp->down!=NULL){
			cout<<temp->data;
			cout<<"->";
			if(temp->right!=NULL){
				cout<<temp->right->data;		
			}
			cout<<"\n";
			temp = temp->down;
	}
		cout<<temp->data;
		cout<<"->";
		cout<<temp->right->data;	
	}
};





