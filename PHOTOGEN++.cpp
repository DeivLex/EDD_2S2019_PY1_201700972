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
				break;
			case 2:
				html="hola.html";
				css ="hola.scss";
				Escribirscss(css,ancho_imagen,alto_imagen,ancho_pixel,alto_pixel);
				EscribirHtml(html,css);
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

	archivo<<"body {";
    archivo<<"background: #333333;";      
    archivo<<"height: 100vh;";
    archivo<<"display: flex;";          
    archivo<<"justify-content: center;";
    archivo<<"align-items: center;";
    archivo<<"}";

    archivo<<".canvas {";
    archivo<<"width: "<< <<"px;";
    archivo<<"height: "<< <<"px;";
	archivo<<"}";

	archivo<<".pixel {";
    archivo<<"width: "<<ancho_imagen<<"px;";
    archivo<<"height: "<<alto_imagen<<"px;";
    archivo<<"float: left;";
    archivo<<"}";

	archivo<<".pixel:nth-child(0),";
	archivo<<".pixel:nth-child(9),";
	archivo<<".pixel:nth-child(10),";
	archivo<<".pixel:nth-child(14),";
	archivo<<".pixel:nth-child(15),";
	archivo<<".pixel:nth-child(16),";
	archivo<<".pixel:nth-child(17),";
	archivo<<".pixel:nth-child(20),";
	archivo<<".pixel:nth-child(21),";
	archivo<<".pixel:nth-child(22),";
	archivo<<".pixel:nth-child(23),";
	archivo<<".pixel:nth-child(27),";
	archivo<<".pixel:nth-child(28){";
    archivo<<"background: #000000;";
	archivo<<"}";

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








