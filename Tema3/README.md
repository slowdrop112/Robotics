# Quick Time Game
## 1.Componente folosite :
- 2x Arduino UNO (ATmega328P microcontroller)
- 2x LED RGB (pentru a semnaliza dacă cuvântul corect e scris greșit sau nu)
- 6x Butoane (pentru start/stop rundă și pentru selectarea dificultății)
- 20x Rezistoare (13x 330 Ohm, 7x 1K Ohm )
- 1x Breadbord Mediu, 1x Breadbord Mare
- O TONA DE Fire de legătură
- 1x LCD
- 1x Servomotor
- 1x Potentiometru

  
 ![alt text](https://github.com/slowdrop112/Robotics/blob/main/Tema2/poza_circuit2.png)

## 2.Detalii Tehnice
- LED RGB -Fiecare jucător are 3 butoane asociate cu LED-uri de culori diferite. La începutul fiecărei runde, LED-ul RGB al jucătorului activ va lumina într-o culoare corespunzătoare unui buton. Jucătorul trebuie să apese butonul corespunzător cât mai rapid pentru a câștiga puncte. LED-ul RGB se va stinge în afara rundei jucătorului activ.
  
- Butonul Start/Stop: Modul de repaus: Dacă jocul este oprit, apăsarea butonului inițiază o nouă rundă după o numărătoare inversă de 3 secunde. În timpul unei runde: Dacă runda este activă, apăsarea butonului o va opri imediat.
  
- Butonul de dificultate: Butonul de dificultate controlează viteza cu care apar cuvintele și poate fi folosit doar în starea de repaus. La fiecare apăsare, dificultatea se schimbă ciclind între: (Easy, Medium, Hard). La schimbarea dificultății, se trimite un mesaj prin serial: “Easy/Medium/Hard mode on!”.

- Generarea cuvintelor: Se va crea un dicționar de cuvinte. În timpul unei runde, cuvintele vor fi afișate în terminal într-o ordine aleatorie. Dacă cuvântul curent a fost scris corect, un cuvânt nou va fi afișat imediat. Dacă nu, un nou cuvânt va apărea după intervalul de timp stabilit în funcție de dificultate.

## 3.Cum functioneaza:
La incept intra in starea default, adica dificultatea nu este setata iar ledul este alb. Avem 2 butoane, unul de start/stop, iar celalalt de selectare a dificultatii. Dupa ce selectam dificultatea incepe insiruirea de cuvinte random. Cand ghicim un cuvant, se trece la urmatorul iar daca nu il ghicim se aprinde led-ul rosu. Runda se opreste dupa 30 de secunde sau dupa apasarea butonului de start/stop.La finalul rundei se va afisa cate cuvinte ai ghicit, si se va reveni la starea default.

Spor la joaca :3


## 4. Video demonstrativ:
https://youtube.com/shorts/dEik2olXsSA?feature=share
