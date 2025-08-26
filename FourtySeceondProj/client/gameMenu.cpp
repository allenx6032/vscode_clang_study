#include "gameMenu.hpp"

MenuM::MenuM(gameEngine::RenderWindow &window) : window(window){
    winclose = new gameEngine::RectangleShape();
    font = new gameEngine::Font();
    image = new gameEngine::Texture();
    bg = new gameEngine::Sprite();
    set_values();
}

MenuM::~MenuM(){
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void MenuM::set_values(){

    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("r-type.ttf");
    image->loadFromFile("menuM.png");

    bg->setTexture(*image);
    bg->setScale(1.5, 1.5);

    pos_mouse = {0,0};
    mouse_coord = {0, 0};

    options = {"R TYPE", "Multiplayer", "R Type Maker", "About", "Quit"};
    texts.resize(5);
    coords = {{910,70},{880,300},{880,440},{880,560},{880,690}};
    sizes = {28,22,22,24,24};

    for (std::size_t i{}; i < texts.size(); ++i){
        texts[i].setFont(*font); 
        texts[i].setString(options[i]); 
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(gameEngine::Color::Black);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(4);
    pos = 1;

    winclose->setSize(gameEngine::Vector2f(23,26));
    winclose->setPosition(1178,39);
    winclose->setFillColor(gameEngine::Color::Transparent);

}

void MenuM::loop_events(){
    gameEngine::Event event;
    while(window.pollEvent(event)){
        if( event.type == gameEngine::Event::Closed){
            window.close();
        }

        pos_mouse = gameEngine::Mouse::getPosition(window);
        mouse_coord = window.mapPixelToCoords(pos_mouse);

        if(gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Down) && !pressed){
            if( pos < 4){
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if(gameEngine::Keyboard::isKeyPressed(gameEngine::Keyboard::Up) && !pressed){
            if(pos > 1) {
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
        }
        }
        
        if (event.type == gameEngine::Event::KeyReleased && event.key.code == gameEngine::Keyboard::Enter) {
            theselect = true;
            if (pos == 1) {
                GameClient cli(window);
                cli.connectionScreen();
            }
            else if (pos == 2) {
                LevelEditor le(window);
                le.run();
            }
            else if (pos == 3) {
                std::cout << "About" << std::endl;
            }
            else if( pos == 4) {
                window.close();
            }
            std::cout << options[pos] << '\n';
        }
    }

    if(gameEngine::Mouse::isButtonPressed(gameEngine::Mouse::Left)){
        if(winclose->getGlobalBounds().contains(mouse_coord)){
            window.close();
        }
    }
}

void MenuM::draw_all(){
    window.clear();
    window.draw(*bg);
    for(auto t : texts){
        window.draw(t); 
    }
    window.display();
}

void MenuM::run_menu(){
  while(window.isOpen()){
    loop_events();
    draw_all();
  }
}


void startGame() {

    gameEngine::Event event;
    gameEngine::RenderWindow window;
    window.create(gameEngine::VideoMode(1920, 1080), "R-Type");
    MainMenu menu = MainMenu(window);
    while (window.isOpen()) {
        window.clear();
        while (window.pollEvent(event)) {
            if (event.type == gameEngine::Event::Closed)
                window.close();
            if (event.type == gameEngine::Event::KeyReleased) {
                menu.setState(4);
            }
        }

        if (menu.getState() != 3)
            menu.cinematic();
        else if (menu.getState() == 3) {
            menu.update();
        }
        
        if (menu.getState() == 4) {
            break;
        }
        
        
        window.display();
    }
    MenuM menuM(window);
    menuM.run_menu();

}