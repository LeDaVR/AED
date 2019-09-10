#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "videoListType.h"

using namespace std;

void createVideoList(ifstream &infile, videoListType &videoList);

void letterEvent(string& w){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)&&w.size()>0){
		string temp=w;
		w="";
		for(int i=0;i<temp.size()-1;i++)
			w+=temp[i];
	}
	if(w.size()>50)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		w+= "a";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		w+= "b";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		w+= "c";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		w+= "d";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		w+= "e";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		w+= "f";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		w+= "g";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		w+= "h";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		w+= "i";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		w+= "j";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		w+= "k";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		w+= "l";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		w+= "m";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		w+= "n";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		w+= "o";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		w+= "p";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		w+= "q";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		w+= "r";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		w+= "s";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		w+= "t";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		w+= "u";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		w+= "v";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		w+= "w";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		w+= "x";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		w+= "y";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		w+= "z";
}

class Textarea{
	bool isWritable;
	bool isSelected;
	sf::Vector2f x1;
	sf::Vector2f x2;
	sf::Font font;
	sf::Text mensaje;
	string mensajecache;
	public:
		static sf::Vector2i CLICK_POSITION;
		Textarea(sf::Vector2f SupIz,sf::Vector2f InfDer){
			font.loadFromFile("arial.ttf");
			mensaje.setFont(font);
			mensaje.setPosition(SupIz);
			mensaje.setColor(sf::Color::Black);
			x1=SupIz;
			x2=InfDer;
			isWritable=true;
			isSelected=false;
			mensajecache="";
		}
		void event(){
			if(!isWritable)
				return;
			if(CLICK_POSITION.x>x1.x&&CLICK_POSITION.x<x2.x&&CLICK_POSITION.y<x2.y&&CLICK_POSITION.y>x1.y){
				isSelected=true;
			}else{
				isSelected=false;
			}
			if(isSelected){
				letterEvent(mensajecache);
				mensaje.setString(mensajecache);
			}
		}
		
		void disableUser(){
			isWritable=false;
		}
		
		void write(string mensaje){
			mensajecache=mensaje;
			this->mensaje.setString(mensajecache);
		}
		
		sf::Text getText(){
			return mensaje;
		}
		
		string getMensaje(){
			return mensajecache;
		}
		
		
};

sf::Vector2i Textarea::CLICK_POSITION = sf::Vector2i(0,0);



class Button{

	sf::Vector2f x1;
	sf::Vector2f x2;
	public:
		
	static sf::Vector2i CLICK_POSITION;
	Button(sf::Vector2f SupIz,sf::Vector2f InfDer){
		x1=SupIz;
		x2=InfDer;
	}
	bool event(){
		if(CLICK_POSITION.x>x1.x&&CLICK_POSITION.x<x2.x&&CLICK_POSITION.y<x2.y&&CLICK_POSITION.y>x1.y){
			CLICK_POSITION=sf::Vector2i(0,0);
			return true;
		}
		return false;
	}
};

sf::Vector2i Button::CLICK_POSITION = sf::Vector2i(0,0);


int main()
{
	videoListType videoList;
    char ch;
    ifstream infile;
    //open the input file
    infile.open("videoDat.txt");
    if (!infile)
    {
        cout << "The input file does not exist. "  << "The program terminates!!!" << endl;
        return 1;
    }
    //create the video list
    createVideoList(infile, videoList);
    infile.close();
    
	// inicilizacio cutre
    sf::RenderWindow window(sf::VideoMode(1600,900),"VIDEO STORE");
    sf::Texture textura;
    textura.loadFromFile("fondo.jpg");
	sf::Sprite fondo;
	fondo.setTexture(textura);
	fondo.setScale(1600.0f/1920.0f,900.0f/1080.0f);

	
	Button searchvideo(sf::Vector2f(40,136),sf::Vector2f(425,245));
	Button checkout(sf::Vector2f(40,264),sf::Vector2f(425,373));
	Button checkin(sf::Vector2f(40,392),sf::Vector2f(425,501));
	Button verify(sf::Vector2f(40,520),sf::Vector2f(425,629));
	Button showtitles(sf::Vector2f(40,648),sf::Vector2f(425,757));
	Button showvideos(sf::Vector2f(40,776),sf::Vector2f(425,885));
	Textarea UserCamp(sf::Vector2f(537,151), sf::Vector2f(1375,200));
	Textarea ResultsCamp(sf::Vector2f(544,315), sf::Vector2f(1373,850));
	ResultsCamp.disableUser();

	
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            	Button::CLICK_POSITION=sf::Mouse::getPosition(window);
            	Textarea::CLICK_POSITION=sf::Mouse::getPosition(window);
			}
            	
            
        }
        UserCamp.event();
        ResultsCamp.event();

		if(searchvideo.event()){
        	string mensaje="NOT FOUND";
        	if(videoList.videoSearch(UserCamp.getMensaje()))
        		mensaje="THE STORE CARRIES "+UserCamp.getMensaje();
        	ResultsCamp.write(mensaje);
		}
        if(checkout.event()){
        	if(videoList.videoSearch(UserCamp.getMensaje())){
        		if (videoList.isVideoAvailable(UserCamp.getMensaje()))
                {
                    videoList.videoCheckOut(UserCamp.getMensaje());
                    ResultsCamp.write("Enjoy your movie: "+UserCamp.getMensaje()+'\n');
                }
                else
                    ResultsCamp.write("Currently " +UserCamp.getMensaje()+" is out of stock."+'\n');
			}
			else
                ResultsCamp.write("The store does not carry "+UserCamp.getMensaje()+'\n');
        	
		}
        if(checkin.event()){
        	if(videoList.videoSearch(UserCamp.getMensaje())){
        		videoList.videoCheckIn(UserCamp.getMensaje());
                ResultsCamp.write("Thanks for returning "+UserCamp.getMensaje()+'\n');
			}
			else
				ResultsCamp.write( "The store does not carry "+UserCamp.getMensaje()+'\n');
		}

        if(verify.event())
        {
        	if(videoList.videoSearch(UserCamp.getMensaje())){
        		if (videoList.isVideoAvailable(UserCamp.getMensaje()))
                    ResultsCamp.write(UserCamp.getMensaje()+" is currently in "+"stock." +'\n');
                else
                    ResultsCamp.write(UserCamp.getMensaje()+" is currently out "+"of stock."+'\n');
			}
			else
                ResultsCamp.write("The store does not carry "+UserCamp.getMensaje()+'\n');
		}

        if(showtitles.event())
        {
        	ResultsCamp.write(videoList.videoGetTitle());
		}

        if(showvideos.event()){
        	ResultsCamp.write(videoList.get());
		}

        
        window.clear();
        window.draw(fondo);
        window.draw(UserCamp.getText());
        window.draw(ResultsCamp.getText());
        window.display();
    }

    return 0;
}

void createVideoList(ifstream &infile,
                     videoListType &videoList)
{
    string title;
    string star1;
    string star2;
    string producer;
    string director;
    string productionCo;
    char ch;
    int inStock;
    videoType newVideo;
    getline(infile, title);
    while (infile)
    {
        getline(infile, star1);
        getline(infile, star2);
        getline(infile, producer);
        getline(infile, director);
        getline(infile, productionCo);
        infile >> inStock;
        infile.get(ch);
        newVideo.setVideoInfo(title, star1, star2, producer,
                              director, productionCo, inStock);
        videoList.insertFirst(newVideo);
        getline(infile, title);
    } //end while
} //end createVideoList
