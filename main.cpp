#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



const int M = 20;
const int N = 10;

int rcol, rstr, rcolor, rstruct;
int punteggio = 0, start = 0, countclass = 0;

fstream fp; //settaggio file classifica

string uploadpunti, uploadpunti_a, uploadpunti_b, uploadpunti_c, puntitemp[100];

int classifica[100] = {0};

int campo[M][N];

struct Punto
{int x,y;} a[4], b[4], c[4];

int fig[7][4] = { //creazione blocchi
		
		3,5,7,6,	//J
		2,4,6,7,	//L
		1,3,5,7,	//|
		4,5,6,7,	//O
		3,5,4,6,	//Z
		2,4,5,7,	//S
		3,5,4,7,	//T
		
};

bool check() {
	for(int i=0; i<4; i++)
		if(a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
		else if(campo[a[i].y][a[i].x]) return 0;
	
	return 1;	
};

bool final() {
	for(int i=0; i<4; i++)
		if(campo[a[i].y][a[i].x]>0) return 0;
	
	return 1;
};

int main() {
	
	srand(time(0));
	
	//Inizializzazione finestra e sfondo
	sf::RenderWindow window(sf::VideoMode(1080,1080), "Tetris");
		
	window.clear();
	
	sf::RectangleShape sfondo(sf::Vector2f(1080.f,1080.f));
	sfondo.setFillColor(sf::Color::Black);
	sfondo.setPosition(0.f, 0.f);
	
	window.draw(sfondo);
	window.display();
	
	
	
	sf::Music music; //settaggio audio
	music.openFromFile("audio/soundtrack.wav");
	music.setLoop(true);
	


	//Settaggio Font
	sf::Font font;
	font.loadFromFile("file/arial.ttf");


	//Creazione testo, colorazione, settaggio font, settaggio carattere, settaggio stile	
	sf::Text testo_a, testo_b, testo_c, testo_d, crediti;
	
	testo_a.setString("TETRIS"); //titolo
	testo_a.setFont(font);
	testo_a.setCharacterSize(72);
	testo_a.setFillColor(sf::Color::White);
	testo_a.setStyle(sf::Text::Bold);
	testo_a.setPosition(450.f, 180.f);
	
	window.draw(testo_a);
	
	testo_b.setString("Clicca spazio per giocare"); //descrizioni
	testo_b.setFont(font);
	testo_b.setCharacterSize(36);
	testo_b.setFillColor(sf::Color::White);
	testo_b.setStyle(sf::Text::Bold);
	testo_b.setPosition(348.f, 360.f);
	
	window.draw(testo_b);
	
	testo_c.setString("Clicca A per attivare / disattivare la musica:");
	testo_c.setFont(font);
	testo_c.setCharacterSize(32);
	testo_c.setFillColor(sf::Color::Blue);
	testo_c.setStyle(sf::Text::Bold);
	testo_c.setPosition(48.f, 840.f);
	
	window.draw(testo_c);
	
	testo_d.setString("Disattivata");
	testo_d.setFont(font);
	testo_d.setCharacterSize(32);
	testo_d.setFillColor(sf::Color::Green);
	testo_d.setStyle(sf::Text::Bold);
	testo_d.setPosition(750.f, 840.f);
	
	window.draw(testo_d);
	
	crediti.setString("Made by Panca278"); //titolo
	crediti.setFont(font);
	crediti.setCharacterSize(24);
	crediti.setFillColor(sf::Color::White);
	crediti.setStyle(sf::Text::Bold);
	crediti.setPosition(840.f, 48.f);
	
	window.draw(crediti);
	window.display();
	
	window.clear();
	window.display();

	
	
	sf::Texture texture; //settaggio texture e creazione sprite
	
	texture.loadFromFile("image/color.png");
	
	sf::Sprite s;
	
	s.setTexture(texture);
	
	sf::Sprite r;
	
	r.setTexture(texture);
	
	
	
	sf::Texture background;
	
	background.loadFromFile("image/campo.png");
	
	sf::Sprite back;
	
	back.setTexture(background);
	
	
	
	sf::Text punti; //settaggio testo punteggio
	
	punti.setString("0");
	punti.setFont(font);
	punti.setCharacterSize(36);
	punti.setFillColor(sf::Color::Black);
	punti.setStyle(sf::Text::Bold);
	punti.setPosition(554.f, 99.f);
	
	window.draw(punti);
	window.display();
			
	
	
	sf::Clock clock; //settaggio timer
	
	int f=0, g=0, h=0, k=0, dx=0, rotazione=0, musica=0;
	float timer = 0, delay=0.7;
	rcol = 1+rand()%7;
	rcolor = 1+rand()%7;
	
	sf::Event event;
	
	//Cuore
	while(window.isOpen()) {
				
	  if(start==0) {
	  	
		while (window.pollEvent(event)) { //Eventi
			switch (event.type) {
				
				case sf::Event::Closed: //Chiusura finestra
					window.close();
					break;
					
				case sf::Event::Resized: //Resize sfondo quando la finestra viene allargata
					window.setSize(sf::Vector2u(1080.f,1080.f));
					window.display();
					break;
					
				case sf::Event::KeyPressed: //start
					if(event.key.code == sf::Keyboard::Space) { start++; sf::sleep(sf::milliseconds(1000)); }
					else if(event.key.code == sf::Keyboard::A) { if(musica==0) { musica++; testo_d.setString("Attivata"); } else {	musica--; testo_d.setString("Disattivata"); } window.draw(testo_a); window.draw(testo_b); window.draw(testo_c); window.draw(testo_d); window.draw(crediti); window.display();}
					
					break;
				
			}			
		}

	  } else if(start==1) {
	  	
	  	if(h==0) { h++; if(musica==1) { music.play(); } }
				
		srand(time(NULL));
		
		float tempo=clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=tempo;
    
		while (window.pollEvent(event)) { //Eventi
			switch (event.type) {
				
				case sf::Event::Closed: //Chiusura finestra
					music.stop();
					window.close();
					break;
					
				case sf::Event::Resized: //Resize sfondo quando la finestra viene allargata
					window.setSize(sf::Vector2u(1080.f,1080.f));
					window.display();
					break;
								
				case sf::Event::KeyPressed: //Pressione tasti tastiera
					if(event.key.code == sf::Keyboard::Space) rotazione++;  //rotazione
					else if(event.key.code == sf::Keyboard::Left) dx--; //sinistra
					else if(event.key.code == sf::Keyboard::Right) dx++; //destra
					else if(event.key.code == sf::Keyboard::Down) delay=0.07; //destra
											
					break;
					
				case sf::Event::KeyReleased: //Rilascio tasti tastiera
					if(event.key.code == sf::Keyboard::Down) delay=0.7;
					
					break;
				
			}				
		}
				
				
		
		for(int i=0; i<4; i++) { b[i]=a[i]; a[i].x+=dx; } //movimento
		if(!check()) for(int i=0; i<4; i++) a[i]=b[i];
		
		
			
		if(rotazione==1) { //rotazione
			for(int i=0; i<4; i++) {	
				int x = a[i].y - a[1].y;
				int y =	a[i].x - a[1].x;
				a[i].x = a[1].x - x;
				a[i].y = a[1].y + y;
			}			
			if(!check()) for(int i=0; i<4; i++) a[i]=b[i];
		}
		
		if(g==0) {
			if(f==0) {
				timer=0;
				g++;
			}	
		}
				
		if(delay<timer) { //caduta verticale figura
			f++;
			for(int i=0; i<4; i++) { b[i] = a[i]; a[i].y+=1;}
			
			if(!check()) {
				for(int i=0; i<4; i++) campo[b[i].y][b[i].x]=rcol;
				
				rcol = rcolor;	
				rcolor = 1+rand()%7;
				
				rstr = rstruct;	
				rstruct=rand()%7;
				if(rstr==2) {
					for(int i=0; i<4; i++) { //creazione figure
						a[i].x = fig[rstr][i] % 2 + 3;
						a[i].y = fig[rstr][i] / 2 + 1;
					}
				} else if(rstr==3) {
					for(int i=0; i<4; i++) {
						a[i].x = fig[rstr][i] % 2 + 4;
						a[i].y = fig[rstr][i] / 2 - 1;
					}
				} else {
					for(int i=0; i<4; i++) {
						a[i].x = fig[rstr][i] % 2 + 4;
						a[i].y = fig[rstr][i] / 2;
					}
				}
				
				if(rstruct==2) {
					for(int i=0; i<4; i++) { //creazione prossima figura
						c[i].x = fig[rstruct][i] % 2 + 12;
						c[i].y = fig[rstruct][i] / 2 + 3;
					}
				} else if(rstruct==3) {
					for(int i=0; i<4; i++) {
						c[i].x = fig[rstruct][i] % 2 + 13;
						c[i].y = fig[rstruct][i] / 2 + 2;
					}
				} else {
					for(int i=0; i<4; i++) {
						c[i].x = fig[rstruct][i] % 2 + 13;
						c[i].y = fig[rstruct][i] / 2 + 3;
					}
				}
				
			}
			
			timer=0;
		}
		
		
		
		int e=M-1; //controllo linee
		for(int i=M-1; i>0; i--) {
			
			int counter = 0;
			
			for(int z=0; z<N; z++) {
				if(campo[i][z])
				counter++;									
				campo[e][z] = campo[i][z];
			}
			
			if(counter<N) e--;		
		}
		
		if(e>0) { //aggiornamento punteggio
			punteggio+=100*e;
		}
		

		if(!final()) start++; //controllo finale
		
		
		
		dx=0; rotazione=0; //reset variabili
		
		window.clear(sf::Color::White);		
		for(int i=0; i<M; i++){ //posizionamento figure
			for(int z=0; z<N; z++) {
				if(campo[i][z]==0) continue;
				s.setTextureRect(sf::IntRect(campo[i][z]*42, 0, 42, 42));
				s.setPosition(z*42,i*42);
				s.move(42,42);
				window.draw(s);
			}
		}
		
		if(f==0) { //creazione prima figura
			rstr=rand()%7;
			if(rstr==2){
				for(int i=0; i<4; i++) {
					a[i].x = fig[rstr][i] % 2 + 3;
					a[i].y = fig[rstr][i] / 2 + 1;
				}
			} else if(rstr==3) {
				for(int i=0; i<4; i++) {
					a[i].x = fig[rstr][i] % 2 + 4;
					a[i].y = fig[rstr][i] / 2 - 1;
				}
			} else {
				for(int i=0; i<4; i++) {
					a[i].x = fig[rstr][i] % 2 + 4;
					a[i].y = fig[rstr][i] / 2;
				}
			}
			
			rstruct=rand()%7;
			if(rstruct==2) {
				for(int i=0; i<4; i++) { //creazione prima prossima figura
					c[i].x = fig[rstruct][i] % 2 + 12;
					c[i].y = fig[rstruct][i] / 2 + 3;
				}
			} else if(rstruct==3) {
				for(int i=0; i<4; i++) {
					c[i].x = fig[rstruct][i] % 2 + 13;
					c[i].y = fig[rstruct][i] / 2 + 2;
				}
			} else {
				for(int i=0; i<4; i++) {
					c[i].x = fig[rstruct][i] % 2 + 13;
					c[i].y = fig[rstruct][i] / 2 + 3;
				}
			}
		}
		
		for(int i=0; i<4; i++) { //stampa figure
			s.setTextureRect(sf::IntRect(rcol*42, 0, 42, 42));
			s.setPosition(a[i].x*42,a[i].y*42);
			s.move(42,42);
			r.setTextureRect(sf::IntRect(rcolor*42, 0, 42, 42));
			r.setPosition(c[i].x*42,c[i].y*42);
			r.move(42,42);
			window.draw(s);
			window.draw(r);
		}
		
		stringstream ss;
		ss<<punteggio;
		ss>>uploadpunti;
		punti.setString(uploadpunti);
		
		window.draw(back);
		window.draw(punti);
		window.display();
		
	  } else if(start==2) {
	  	
	  	if(k==0) { //preparazione schermata finale
	  	
	  		int max, t;
	  		
			sf::sleep(sf::milliseconds(3000)); k++; music.stop();
			
			
			
			fp.open("file/punteggio.txt", ios::app);
			fp << punteggio; //scrittura punteggio nel file
			fp << "\n";
			fp.close();
			
			fp.open("file/punteggio.txt", ios::in);
			stringstream rr[100]; //settaggio punti classifica
			while(getline(fp,puntitemp[countclass])) {
				rr[countclass]<<puntitemp[countclass];
				rr[countclass]>>punteggio;
				classifica[countclass] = punteggio;
				countclass++;
			}
		
			for(int i=0; i<countclass; i++) { //ordine decrescente punteggi		
				max=i;
			
				for (int z=i+1; z<countclass; z++) {
					if (classifica[z]>classifica[max]) {
						max=z;
					}
				}

				t = classifica[max];
				classifica[max] = classifica[i];
				classifica[i] = t;
					
			}
			
		}
	  	
	  	
	  	
	  	while (window.pollEvent(event)) { //Eventi
			switch (event.type) {
				
				case sf::Event::Closed: //Chiusura finestra
					window.close();
					break;
					
				case sf::Event::Resized: //Resize sfondo quando la finestra viene allargata
					window.setSize(sf::Vector2u(1080.f,1080.f));
					window.display();
					break;
					
				case sf::Event::KeyPressed: //end
					if(event.key.code == sf::Keyboard::Space) start++;
					
					break;
				
			}			
		}
					
		
		
	  	window.clear();
	
		sf::Text testo_e, testo_f, testo_g, classifica_a, classifica_b, classifica_c;
	
		testo_e.setString("Il tuo punteggio: "); //punteggio finale
		testo_e.setFont(font);
		testo_e.setCharacterSize(48);
		testo_e.setFillColor(sf::Color::White);
		testo_e.setStyle(sf::Text::Bold);
		testo_e.setPosition(270.f, 180.f);
	
		window.draw(testo_e);
	
		punti.setCharacterSize(48);
		punti.setFillColor(sf::Color::Green);
		punti.setStyle(sf::Text::Bold);
		punti.setPosition(690.f, 180.f);
	
		window.draw(punti);	
	
		testo_f.setString("Clicca spazio per terminare");
		testo_f.setFont(font);
		testo_f.setCharacterSize(48);
		testo_f.setFillColor(sf::Color::White);
		testo_f.setStyle(sf::Text::Bold);
		testo_f.setPosition(348.f, 360.f);
	
		window.draw(testo_f);
		
		testo_g.setString("Classifica:\n\tPrimo:\n\tSecondo:\n\tTerzo:");
		testo_g.setFont(font);
		testo_g.setCharacterSize(48);
		testo_g.setFillColor(sf::Color::White);
		testo_g.setStyle(sf::Text::Bold);
		testo_g.setPosition(180.f, 500.f);
	
		window.draw(testo_g);
		
	
		stringstream tt, uu, vv; //settaggio punti classifica
		tt<<classifica[0];
		tt>>uploadpunti_a;
		classifica_a.setString(uploadpunti_a);
		uu<<classifica[1];
		uu>>uploadpunti_b;
		classifica_b.setString(uploadpunti_b);
		vv<<classifica[2];
		vv>>uploadpunti_c;
		classifica_c.setString(uploadpunti_c);
		
		classifica_a.setFont(font);
		classifica_a.setCharacterSize(48);
		classifica_a.setFillColor(sf::Color::Red);
		classifica_a.setStyle(sf::Text::Bold);
		classifica_a.setPosition(480.f, 550.f);
	
		window.draw(classifica_a);
		
		classifica_b.setFont(font);
		classifica_b.setCharacterSize(48);
		classifica_b.setFillColor(sf::Color::Red);
		classifica_b.setStyle(sf::Text::Bold);
		classifica_b.setPosition(480.f, 600.f);
	
		window.draw(classifica_b);
		
		classifica_c.setFont(font);
		classifica_c.setCharacterSize(48);
		classifica_c.setFillColor(sf::Color::Red);
		classifica_c.setStyle(sf::Text::Bold);
		classifica_c.setPosition(480.f, 650.f);
	
		window.draw(classifica_c);
				
		window.display();
		
	  } else {
	  	
	  	fp.close();
	  	break;
	  	
	  }
	}
	


	window.clear();
	window.display();	
	
	return 0;
}
