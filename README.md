# Sssnake
Jest to najzwyklejsza oldschoolowa gra Snake. 
Została stworzona przy pomocy biblioteki 
Simple and Fast Multimedia Library - SFML.

### Rozgrywka
Gra jest (na ten moment) podzielona na 3 poziomy. Na każdy,
oprócz pierwszego dostajemy się poprzez zjedzenie siedmiu
jabłek na aktualnym poziomie. Wąż przyspiesza wraz z każdym
zjedzonym jabłkiem, dopiero po przejściu na kolejny poziom jego
prędkość zostaje resetowana. Gramy dopóki nasz wąż nie wykituje -
nie wejdzie w jakąś przeszkodę, albo nie ugryzie się w swój segment.

### Sterowanie:
- poruszamy się przy pomocy strzałek (Up, Down, Left, Right)
- z gry możemy wyjść na dwa sposoby - Escape lub zamykamy okienko naszej gry przy pomocy czerwonego X
- grę możemy zapauzować w dowolnej chwili przy pomocy Spacji
- jeżeli przegramy, a chcemy zagrać ponownie (od pierwszego poziomu) to
wciskamy Enter
