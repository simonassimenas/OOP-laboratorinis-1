# OOP - Pirmas laboratorinis darbas
## v0.4


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


## Pakeitimai v0.3->v0.4

 - Sugeneruojami studentų įrašų failai pasirenkant studentų kiekį.
 - Studentai padalinami į dvi kategorijas (du failus):
    - Galutinis balas < 5.0 - varšai ("vagsai.txt")
    - Galutinis balas >= 5.0 - šaunuoliai ("saunuoliai.txt")
 - Greičiau veikiantis failų skaitymas.
 - Pažymių vektorius perkeltas į struktūrą dėl greitesnio failo skaitymo.