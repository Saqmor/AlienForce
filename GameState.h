#include "bossFight.h"
#include <fstream>

void readSave(Character& character, std::ifstream& is);
void writeSave(Character& character, std::fstream& os);
void CharactersSave(Character& ms, Character& hs);
void LoadSave(Character& ms, Character& hs);
std::size_t read_base();