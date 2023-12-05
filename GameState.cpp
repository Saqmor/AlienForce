#include "GameState.h"

std::ostream& operator<<(std::ostream& os,  Character& personage) {
    os << personage.name << std::endl <<
       "HP " << personage.hp << " " <<
       "isAlive " << personage.isAlive << " " <<
       "speed " << personage.speed <<std::endl;
    for (int i = 0; i < 4; ++i) {
        os << "TypeBomb " << personage.grenades[i].type <<  " Quantidade " << personage.grenades[i].full << std::endl;
    }
    return os;
}


std::istream& operator>>(std::istream& is, Character& personage) {
    std::string nameCharacater, hp, isAlive, speed, typeBomb, Tbomb, quantBomb;
    is >> personage.name >>
       hp >> personage.hp >>
       isAlive >> personage.isAlive >>
       speed >> personage.speed;
    for (int i = 0; i < 4; ++i) {
        is >> Tbomb >> personage.grenades[i].type >> quantBomb >> personage.grenades[i].full;
    }

    return is;
}

void readSave(Character& ms, std::ifstream& is){
    is >> ms;
    std::cout << ms;
}

void  LoadSave(Character& ms, Character& hs){
    std::ifstream is;
    is.open("./System/save.txt");

    if (is.is_open()) {
        readSave(ms, is);
        readSave(hs, is);
        is.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo.\n";
    }
}

void writeSave(Character& ms, std::fstream& os) {
    os << ms;
}

void  CharactersSave(Character& ms, Character& hs){
    std::fstream os;
    os.open("./System/save.txt", std::ios::out);

    if (os.is_open()) {
        writeSave(ms, os);
        writeSave(hs, os);
        os.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo.\n";
    }
}
std::size_t readBase(){
    std::ifstream is;
    int vertex;
    is.open("./System/graph_input.txt");
    is>>vertex;
    is.close();
    return vertex;
}