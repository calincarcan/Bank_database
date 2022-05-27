Carcan Calin si Stefan Darius - CTI Anul 1 314 CD

Ideea proiectului este implementarea simplista a unei baze de date bancare inspirata de primele 2 teme de la SDA.
Pentru a stoca utilizatorii bancii am format o structura User care va fi stocata ca informatie utila in interiorul unui 
arbore AVL. 
Cheia fiecarui arbore va fi id ul utilizatorului atribuit la crearea contului utilizatorului. 
Pentru a tine contul tuturor tranzactiilor pe care utilizatorii le vor face, fiecare din ei va pastra stocata in nodul
propriu 2 liste dublu inlantuite care reprezinta sumele de bani primite si sumele de bani trimise.
Utilizatorii pot fi eliminati din baza de date a bancii daca acestia doresc sa isi inchida contul, iar atunci toate
componentele nodului lor vor fi sterse insa intrarile din listele de tranzactii ale celorlalti utilizatori de la sau
catre utilizatorul sters vor continua sa existe. 
