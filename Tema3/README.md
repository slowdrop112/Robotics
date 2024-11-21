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

  
 ![alt text](https://github.com/slowdrop112/Robotics/blob/main/Tema3/Capture.PNG)

## 2.Detalii Tehnice
- LED RGB -Fiecare jucător are 3 butoane asociate cu LED-uri de culori diferite. La începutul fiecărei runde, LED-ul RGB al jucătorului activ va lumina într-o culoare corespunzătoare unui buton. Jucătorul trebuie să apese butonul corespunzător cât mai rapid pentru a câștiga puncte. LED-ul RGB se va stinge în afara rundei jucătorului activ.
  
- Butoane: Fiecare jucător are câte 3 butoane asociate fiecărui LED.
La apăsarea unui buton corespunzător culorii LED-ului activ, jucătorul câștigă puncte.
Un buton suplimentar dedicat pentru pornirea jocului poate fi adăugat.
Multiplexarea butoanelor cu rezistențe poate fi utilizată pentru economisirea pinilor.

-LCD: LCD-ul va afisa punctajul celor 2 jucători pe parcursul jocului.
La finalul jocului, LCD-ul va afișa câștigătorul și scorul final pentru câteva secunde, apoi va reveni la ecranul de start cu mesajul de bun venit.

-Servomotor: Servomotorul va începe la 0 grade și se va mișca în sens anticlockwise pentru a marca timpul scurs.
Poziția sa finală va indica sfârșitul jocului.

-SPI: Comunicarea între cele două plăci Arduino se va face prin SPI. Arduino-ul Master va controla LCD-ul și servomotorul, iar Arduino-ul Slave va gestiona butoanele și LED-urile. Mesajele vor fi schimbate între cele două plăci pentru sincronizarea stării jocului.

## 3.Cum functioneaza:
Jocul începe cu afișarea unui mesaj de bun venit pe LCD. Jucătorii vor apăsa butoanele pentru a porni jocul.
Fiecare jucător va avea 3 butoane și un LED RGB, care vor corespunde unei culori.
La fiecare rundă, LED-ul RGB al jucătorului activ va aprinde o culoare asociată cu unul dintre butoanele acestuia.
Jucătorul va trebui să apese butonul corespunzător cât mai rapid pentru a câștiga puncte.
Scorurile vor fi actualizate și afișate pe LCD pe parcursul jocului.
La final, se va anunța câștigătorul și scorul final.

## 4. Video demonstrativ:
https://youtube.com/shorts/dEik2olXsSA?feature=share

## 5. Poze ale circuitului:
 ![alt text](https://github.com/slowdrop112/Robotics/blob/main/Tema3/POZA_CIRCUIT.JPEG)

