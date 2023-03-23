# OOP - Pirmas laboratorinis darbas
## v0.5


## Aprašymas

Ši programa skaito studentų įrašų arba paėma naudotojo įvestus įrašus, kuriuos sudaro: studento vardas, pavardė, namų darbų rezultatai ir egzamino rezultatas, ir apskaičiuoja galutinį studento balą.

Galutinis balas skaičiuojamas dvejais būdais:
1. Pasitelkiant namų darbų pažymių vidurkį.
  > GalutinisVid = 0.4 * vidurkis + 0.6 * egzaminas
  >>![CodeCogsEqn](https://user-images.githubusercontent.com/116019627/220766715-8a46ad0d-f470-46d2-bc3c-42a8ba354050.png)

2. Pasitelkiant namų darbų pažymių vidurkį medianą.
  > GalutinisMed = 0.4 * mediana + 0.6 * egzaminas
  >>![CodeCogsEqn-2](https://user-images.githubusercontent.com/116019627/220768370-a02e423c-92d2-4747-945d-c0f46beee986.png)


Apskaičiavus gautinius įvestų studentų balus, programa išveda duomenis į failą arba išspausdina studentų vardus, pavardes bei galutinius balus, kurie apskaičiuoti pasitelkiant vidurkį arba medianą.


## Failai

 - mylib.h - antraščių failas, kuriame saugomos naudojamos bibliotekos bei deklaruotos naudojamos funkcijos.
 - main.cpp - programos failas, kuriame saugomas programos kodas. Duomenų talpinimui naudojami **vektoriai**.
 - addFunctions.h - antraščių failas, kuriame saugomi naudojamų pridėtinių funkcijų prototipai.
 - addFunctions.cpp - programos failas, kuriame saugomos naudojamos pridėtinės funkcijos skirtos įvesties patikrinimui, random skaičių generavimui ir išvedimui.
 - makefile - aprašytos komandos naudojamos kompiliavimui ar failų valimui.


## Instrukcija

1. Paleista programa paklausia naudotojo ar norima skaityti failą(a) ar įvesti duomenis(b).

2.a. Naudotojas pasirenka ar nori generuoti failą.
 > - Pasirinkus "Ne" programa toliau pereina į 4 instrukcijos žingsnį.
 > - Pasirinkus "Taip" programa toliau pereina į 3 instrukcijos žingsnį.
 
3.a. Naudotojas įveda norimų sugeneruoti studentų skaičių ir paspaudžia "enter" klavišą.
 > - Programa paklausia ar naudotojas nori sugeneruoti dar vieną failą, jei taip grįžtama į 3 instrukcijos žingsnį.
 
4.a. Naudotojas įveda failo pavadinimą ir paspaudžia "enter" klavišą.

5.a. Programa išveda kiekvieno etapo laiką bei išveda kada duomenys buvo perskaityti, surūšiuoti ir įrašyti.
 > - Nepavykus atidaryti failo programa stabdoma ir į ekraną išvedama, jog nepavyko atidaryti failo.


2.b. Paleista programa paklausia naudotojo ar bus skaičiuojamas vidurkis, ar mediana.

3.b. Naudotojas pasirenka ar nori pildyti įrašą. Pasirinkus nepradėti programa sustabdoma.

4.b. Naudotojas įveda studento vardą ir pavardę.

5.b. Programa paklausia naudotojo ar jis norėtų studento pažymius įvesti ranka, ar sugeneruoti automatiškai. Leidžiami įvesti pažymiai turi būti intervale nuo 0 iki 10. "0" reiškia, jog darbas nebuvo atsiskaitytas.
 > - Pasirinkus rankinį įvedimą naudotojas įvedą namų darbų pažymius. Kiekvienas įvedimas turi būti atskirtas klavišo "Enter" paspaudimu. Įvedimą užbaigti galima įvedus "33" ir paspaudus "Enter" klavišą. Baigus namų darbų įvedimą naudotojas įveda studento egzamino pažymį.
 > - Pasirinkus automatinį pažymių generavimą programa paprašo naudotojo įvesti pažymių skaičių(į šį skaičių neįeina egzamino pažymys).
 
6.b. Programa išveda, jog duomenys buvo įrašyti irpaklausia naudotojo ar jis norėtų pildyti dar vieną įrašą.
 > - Pasirinkus "Ne" programa stabdoma ir išvedami įvesti įrašų duomenys.
 > - Pasirinkus "Taip" grįžtama į 3 instrukcijos žingsnį.


## Makefile

 - "make main" - paruošia programos vykdomąjį failą.
 - "make addFunctions" - sukompiliuoja pridėtinių funkcijų failą.
 - "make clean" - išvalo "make main" ir "make addFunctions" sukurtus failus bei "vargasi.txt" ir "saunuoliai.txt".
 - "make txt" - išvalo visus .txt failus.


## Veikimo greitis

 - Bandymams naudotas namų darbų skaicius - 10.

  ### Programos veikimo greitis

  | Įrašų kiekis 	| Etapas                                           	| Trukmė (s) 	|
  |--------------	|--------------------------------------------------	|------------	|
  | 1000         	| Failo nuskaitymas                                	| 0.007856   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.000013   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.000369   	|
  |              	| Rašymas į failus                                 	| 0.001619   	|
  |              	| Bendras laikas                                   	| 0.009857   	|
  |              	|                                                  	|            	|
  | 10000        	| Failo nuskaitymas                                	| 0.052215   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.000198   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.002544   	|
  |              	| Rašymas į failus                                 	| 0.009154   	|
  |              	| Bendras laikas                                   	| 0.064111   	|
  |              	|                                                  	|            	|
  | 100000       	| Failo nuskaitymas                                	| 0.399489   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.001401   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.036410   	|
  |              	| Rašymas į failus                                 	| 0.091424   	|
  |              	| Bendras laikas                                   	| 0.528724   	|
  |              	|                                                  	|            	|
  | 1000000      	| Failo nuskaitymas                                	| 3.807240   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.013938   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.368861   	|
  |              	| Rašymas į failus                                 	| 0.857484   	|
  |              	| Bendras laikas                                   	| 5.047523   	|
  |              	|                                                  	|            	|
  | 10000000     	| Failo nuskaitymas                                	| 39.56331   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.137143   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 4.590920   	|
  |              	| Rašymas į failus                                 	| 7.691110   	|
  |              	| Bendras laikas                                   	| 51.98248   	|

  ### Failu generavimo laikas

  | Įrašų kiekis 	| Etapas            	| Trukmė (s) 	|
  |--------------	|-------------------	|------------	|
  | 1000         	| Failo generavimas 	| 0.005660   	|
  |              	|                   	|            	|
  | 10000        	| Failo generavimas 	| 0.033800   	|
  |              	|                   	|            	|
  | 100000       	| Failo generavimas 	| 0.263591   	|
  |              	|                   	|            	|
  | 1000000      	| Failo generavimas 	| 2.229450   	|
  |              	|                   	|            	|
  | 10000000     	| Failo generavimas 	| 21.74790   	|

### Greičio testavimai - skirtingos duomenų struktūros

  #### Testavimo sistemos parametrai

  - Ram: 16 GB (VSCode paskirta - 4GB), 2133 MHz DDR3
  - Procesorius: 2,4 GHz Quad-Core Intel Core i5
  - Diskas: SSD


  #### Vector

  | Įrašų kiekis 	| Etapas                                           	| Trukmė (s) 	|
  |--------------	|--------------------------------------------------	|------------	|
  | 1000         	| Failo nuskaitymas                                	| 0.007856   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.000013   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.000369   	|
  |              	|                                                  	|            	|
  | 10000        	| Failo nuskaitymas                                	| 0.052215   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.000198   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.002544   	|
  |              	|                                                  	|            	|
  | 100000       	| Failo nuskaitymas                                	| 0.399489   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.001401   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.036410   	|
  |              	|                                                  	|            	|
  | 1000000      	| Failo nuskaitymas                                	| 3.807240   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.013938   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.368861   	|
  |              	|                                                  	|            	|
  | 10000000     	| Failo nuskaitymas                                	| 39.56331   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.137143   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 4.590920   	|

  #### Deque

  | Įrašų kiekis 	| Etapas                                           	| Trukmė (s) 	|
  |--------------	|--------------------------------------------------	|------------	|
  | 1000         	| Failo nuskaitymas                                	| 0.008772   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.000020   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.000390   	|
  |              	|                                                  	|            	|
  | 10000        	| Failo nuskaitymas                                	| 0.055995   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.000158   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.003236   	|
  |              	|                                                  	|            	|
  | 100000       	| Failo nuskaitymas                                	| 0.413631   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.001855   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.048346   	|
  |              	|                                                  	|            	|
  | 1000000      	| Failo nuskaitymas                                	| 4.084060   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.022699   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0 458764   	|
  |              	|                                                  	|            	|
  | 10000000     	| Failo nuskaitymas                                	| 40.5219   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.175214   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 6.06296   	|

  #### List

  | Įrašų kiekis 	| Etapas                                           	| Trukmė (s) 	|
  |--------------	|--------------------------------------------------	|------------	|
  | 1000         	| Failo nuskaitymas                                	| 0.006860   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.000090   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.000308   	|
  |              	|                                                  	|            	|
  | 10000        	| Failo nuskaitymas                                	| 0.059444   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.001317   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.003786   	|
  |              	|                                                  	|            	|
  | 100000       	| Failo nuskaitymas                                	| 0.582805   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.042608   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.051172   	|
  |              	|                                                  	|            	|
  | 1000000      	| Failo nuskaitymas                                	| 5.678090   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 0.711688   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 0.590938   	|
  |              	|                                                  	|            	|
  | 10000000     	| Failo nuskaitymas                                	| 57.23360   	|
  |              	| Atskyrimas ir rūšiavimas (pagal galutinį pažymį) 	| 11.44320   	|
  |              	| Rūšiavimas (dvi grupės - vardais)                	| 6.814410   	|

  #### Testavimo rezultatai

  Vektoriaus duomenų struktūra naudojimas šiai programai efektyviausias, kadangi testuojant atitinkamus šios programos etapus ji atliko darbą greičiausiai.

  Verta paminėti, jog programos kodas pirma buvo rašytas nadojant **vektorius**, tad atitinkami metodai pritaikyti greitesniam vektoriaus veikimui.

  * Pastaba: sąrašo(list) naudojimas labai stipriai sulėtina programos spausdinimą į failus, tačiau tai gali būti dėl blogo iteratorių cikluose pritaikymo.

  Pagal greitį:
  1. Vector
  2. Deque
  3. List 

## Pakeitimai v0.4->v0.5

 - Pridėti deque.cpp ir list.cpp failai.
 - Palygintas greitis naudojant skirtingas duomenų struktūras: vector, deque ir list.
