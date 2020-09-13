# LotniskoSanEscobar
[![Build Status](https://travis-ci.org/baaxymilian/LotniskoSanEscobar.svg?branch=master)](https://travis-ci.org/baaxymilian/LotniskoSanEscobar)

Wykorzystanie algorytmu Dijkstry w problemie matematycznym.

Temat: Lotnisko w San Escobar pęka w szwach! To oczywiście efekt ogromnego ruchu lotniczego
z Polski, jaki nastąpił po nawiązaniu stosunków dyplomatycznych między oboma krajami. Jako
minister transportu republiki postanowiłaś wybudować nowe lotnisko dla naszych narodowych
linii lotniczych El Niño i to natychmiast. W tym celu na pas startowy zostanie przerobiony jeden z
odcinków sieci autostrad w naszym kraju. Sieć autostrad na planach ma kształt grafu, a
wierzchołkami są poszczególne miasta. Napisz algorytm, który ustali, który odcinek sieci
autostrad należy poświęcić pod pas startowy, tak aby suma odległości ze stolicy kraju, Santo
Subito, do pozostałych miast pozostała jak najmniejsza.

## Wprowadzanie z pliku:

Program korzysta z pliku input.txt zapisanego według ścisłego klucza:

X Y Z 

A1 B1 C1

A2 B2 C3 … 

X – wierzchołek startowy – stolica 

Y – łączna liczba węzłów 

Z – łączna liczba krawędzi 

Ax Bx Cx – wprowadzanie krawędzi x

A – pierwszy wierzchołek 

B – drugi wierzchołek 

C – waga krawędzi

Kolejne wierzchołki powinny być wprowadzane inkrementalnie, tzn. jeśli w grafie jest 10 wierzchołków należy wykorzystać numerację od 1 do 10.

## Kompilator:

GCC, MinGW64
g++.exe -Wall -fexceptions -O2 -Wall  -c graph.cpp -o graph.o
g++.exe -Wall -fexceptions -O2 -Wall  -c main.cpp -o main.o
g++.exe -Wall -fexceptions -O2 -Wall  -c network.cpp -o network.o
g++.exe  -o lotnisko.exe graph.o main.o network.o  -static-libstdc++ -static-libgcc -static -lpthread -s  
