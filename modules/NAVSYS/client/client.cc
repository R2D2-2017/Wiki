
/**
 * \file
 * \brief     Client side connection code for the NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"


Client::Client(sf::IpAddress ipAddress, uint16_t port): ipAddress(ipAddress), port(port){}



void Client::run(){
	sf::Socket::Status connectionStatus = socket.connect(ipAddress, port);
	if(connectionStatus != sf::Socket::Done){
		std::cout << "Connection failed" << std::endl;
	}


    std::string nodeFilePath = "../client/node.txt";
    std::string verticeFilePath = "../client/vertice.txt";
    // this loads the the files declared above with the database
    getDatabaseFromServer(nodeFilePath,verticeFilePath);

    //create the graph
    GraphFactory factory =  GraphFactory();
    Graph g = Graph();
    factory.createGraph(nodeFilePath,verticeFilePath, g);

    //create the window
    sf::RenderWindow  window{ sf::VideoMode{ 1000, 1000}, "SFML window" };
    GraphDrawer printOnScreen(window);


    sf::Packet receivedMessage;
    std::string messageString;

    //used to let the user know a knew request can be made
    bool printOptionsFlag =1;
    while(true){
        window.clear(sf::Color::Black);
	sf::sleep(sf::milliseconds(100));
        
        printOnScreen.reload(&g);
        printOnScreen.draw();


        if(printOptionsFlag){
            printOptionsFlag = 0;
            std::cout << "press Left to enter route information\n";
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            path nodes;
            std::cout << "name of start node>";
            std::cin >> nodes.startNode;
            std::cout << "name of end node>";
            std::cin >> nodes.endNode;

            requestPath(nodes);

            if(  socket.receive(receivedMessage) != sf::Socket::Done  ){
                std::cout << "Something went wrong with receiving" << std::endl;
            }
            else{
                receivedMessage >> messageString;
                std::cout << messageString << std::endl;

            }

            //used to let the user know a knew request can be made
            printOptionsFlag = 1;
        }

        if( window.isOpen()) {
            	sf::Event event;
            	while( window.pollEvent(event) ){
                    if( event.type == sf::Event::Closed ){
                        window.close();
                    }
                }
        }
    }
}


void Client::getDatabaseFromServer(std::string nodeFilePath, std::string verticeFilePath){

    sf::Packet receivedMessage;
    std::string messageString;

    std::ofstream nodeStream(nodeFilePath);

    requestNodes();

    if(socket.receive(receivedMessage) != sf::Socket::Done){
        std::cout << "Something went wrong with receiving" << std::endl;
    }
    else{
        receivedMessage >> messageString;
        nodeStream << messageString;
    }
    nodeStream.close();

    std::ofstream verticeStream(verticeFilePath);

    requestVertices();

    if(socket.receive(receivedMessage) != sf::Socket::Done){
        std::cout << "Something went wrong with receiving" << std::endl;
    }
    else{
        receivedMessage >> messageString;
        verticeStream << messageString;
    }

    verticeStream.close();

}


void Client::requestNodes(){
	sf::Packet p;
	p << command::requestNodes;
	if(socket.send(p) != sf::Socket::Done){
		std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
	}
}


void Client::requestVertices(){
	sf::Packet p;
	p << command::requestVertices;
	if(socket.send(p) != sf::Socket::Done){
		std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
	}
}

void Client::requestPath(path nodes){
    sf::Packet p;
    p << command::requestPath << nodes;
    if(socket.send(p) != sf::Socket::Done){
        std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
    }
}

