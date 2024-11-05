# Typeracer Game
## 1.Componente folosite :
- Arduino UNO (ATmega328P microcontroller)
- 1x LED RGB (pentru a semnaliza dacă cuvântul corect e scris greșit sau nu)
- 2x Butoane (pentru start/stop rundă și pentru selectarea dificultății)
- 5x Rezistoare (3x 330 ohm, 2x 2000 ohm)
- Breadbord
- Fire de legătură

## 2.Detalii Tehnice
- LED RGB - Indicator de stare: În starea de repaus, LED-ul va avea culoarea albă.La apăsarea butonului de start, LED-ul va clipi timp de 3 secunde, indicând o numărătoare inversă până la începerea rundei.În timpul unei runde: LED-ul va fi verde dacă textul introdus este corect și va deveni roșu în caz de greșeală.
  
- Butonul Start/Stop: Modul de repaus: Dacă jocul este oprit, apăsarea butonului inițiază o nouă rundă după o numărătoare inversă de 3 secunde. În timpul unei runde: Dacă runda este activă, apăsarea butonului o va opri imediat.
  
- Butonul de dificultate: Butonul de dificultate controlează viteza cu care apar cuvintele și poate fi folosit doar în starea de repaus. La fiecare apăsare, dificultatea se schimbă ciclind între: (Easy, Medium, Hard). La schimbarea dificultății, se trimite un mesaj prin serial: “Easy/Medium/Hard mode on!”.

- Generarea cuvintelor: Se va crea un dicționar de cuvinte. În timpul unei runde, cuvintele vor fi afișate în terminal într-o ordine aleatorie. Dacă cuvântul curent a fost scris corect, un cuvânt nou va fi afișat imediat. Dacă nu, un nou cuvânt va apărea după intervalul de timp stabilit în funcție de dificultate.

## 3. Video demonstrativ:
https://youtube.com/shorts/dEik2olXsSA?feature=share
