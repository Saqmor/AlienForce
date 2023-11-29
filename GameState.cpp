#include "GameState.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os,  Character& personage) {
    os << personage.name << std::endl <<
       "HP " << personage.hp << " " <<
       "isAlive " << personage.isAlive << " " <<
       "speed " << personage.speed <<std::endl;
    /*for(const auto& bomb : personage.bombs)
    os << "TypeBomb" << " " << bomb.first << " " << "Quantidade" << " " << bomb.second << " ";*/
    /*for () {
        os << "TypeBomb " << bomb.first << " Quantidade " << bomb.second<< std::endl;
    }*/
    for (int i = 0; i < 4; ++i) {
        os << "TypeBomb " << personage.grenades[i].type <<  " Quantidade " << personage.grenades[i].full << std::endl;
    }
    return os;
}


std::istream& operator>>(std::istream& is, Character& personage) {
    std::string nameCharacater, hp, isAlive, speed, typeBomb, Tbomb, quantBomb;
    int numBomb;
    is >> personage.name >>
       hp >> personage.hp >>
       isAlive >> personage.isAlive >>
       speed >> personage.speed;
    /*for (const auto& bomb : personage.Bombs){
        is >> typeBomb >> typeBomb >> quantBomb >> numBomb;
        personage.Bombs.push_back(typeBomb, numBomb);
    }*/
    //Grenade aux;
    for (int i = 0; i < 4; ++i) {
        is >> Tbomb >> personage.grenades[i].type >> quantBomb >> personage.grenades[i].full;
        //personage.grenades[i].type=aux.type;
    }

    return is;
}

void readSave(Character& ms, std::ifstream& is){
    is >> ms;
    std::cout << ms;
}

void  LoadSave(Character& ms, Character& hs){
    std::ifstream is;
    is.open("save.txt");

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
    os.open("save.txt", std::ios::out);

    if (os.is_open()) {
        writeSave(ms, os);
        writeSave(hs, os);
        os.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo.\n";
    }
}
std::size_t read_base(){
    std::ifstream is;
    int vertex;
    is.open("graph_input.txt");
    is>>vertex;
    is.close();
    return vertex;
}