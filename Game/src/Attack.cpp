#include "Attack.h"

const std::string& Attack::getName() const { return name; }
const std::string& Attack::getType() const { return type; }
int Attack::getDamage() const { return damage; }
int Attack::getPrecision() const { return precision; }
int Attack::getUse() const { return use; }
void Attack::Used() { use -= 1; }
bool Attack::isSpecial() const { return special; }