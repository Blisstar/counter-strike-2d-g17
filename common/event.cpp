#include "event.h"

void Event::show() const {
    std::string event = (type == ENEMYDEAD) ? "Un enemigo ha muerto" : "Un enemigo ha revivido";
    std::cout << event << ". " << enemiesAliveCnt << " vivo(s) y " << enemiesDeadCnt
              << " muerto(s)." << std::endl;
}
