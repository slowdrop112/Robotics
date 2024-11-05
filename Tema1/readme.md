În această temă trebuie să simulați o stație de încărcare pentru un vehicul electric, folosind mai multe LED-uri și butoane. În cadrul acestui task trebuie să țineți cont de stările butonului și să folosiți debouncing, dar și să coordonați toate componentele ca într-un scenariu din viața reală. Componente: 7x 220 ohm rezistoare 2x 1k ohm rezistoare 4x LED-uri (pentru a simula procentul de încărcare) 1x LED RGB (pentru starea de liber sau ocupat) 2x Butoane (pentru start încărcare și stop încărcare) Breadboard Linii de legătură

Led-ul RGB reprezintă disponibilitatea stației. Dacă stația este liberă led-ul va fi verde, iar dacă stația este ocupată se va face roșu.

Led-urile simple reprezintă gradul de încărcare al bateriei, pe care îl vom simula printr-un loader progresiv (L1 = 25%, L2 = 50%, L3 = 75%, L4 = 100%). Loader-ul se încărca prin aprinderea succesivă a led-urilor, la un interval fix de 3s. LED-ul care semnifică procentul curent de încărcare va avea starea de clipire, LED-urile din urma lui fiind aprinse continuu, iar celelalte stinse.

Apăsarea scurtă a butonului de start va porni încărcarea. Apăsarea acestui buton în timpul încărcării nu va face nimic.

Apăsarea lungă a butonului de stop va opri încărcarea forțat și va reseta stația la starea liberă. Apăsarea acestui buton cat timp stația este liberă nu va face nimic.

https://youtube.com/shorts/gnvC7Rnd-WE?feature=share