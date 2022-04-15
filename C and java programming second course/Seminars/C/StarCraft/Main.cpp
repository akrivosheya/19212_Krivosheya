#include <memory>

int main(int argc, char* argv[]){
  if (argc < 2) return -1;
  
  std::unique_ptr<Unit> u (Factory<Unit, std::string, Unit* (*)()>::getInstance->makeUnit(argv[1]));//смарт поинтер
}
