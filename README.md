# OOP - Pirmas laboratorinis darbas
## v0.1


## Aprašymas

Ši programa paėma naudotojo įvestus įrašus, kuriuos sudaro: studento vardas, pavardė, namų darbų rezultatai ir egzamino rezultatas, ir apskaičiuoja galutinį studento balą.

Galutinis balas skaičiuojamas dvejais būdais:
1. Pasitelkiant namų darbų pažymių vidurkį.
  GalutinisVid = 0.4 * vidurkis + 0.6 * egzaminas
  ![CodeCogsEqn](https://user-images.githubusercontent.com/116019627/220766715-8a46ad0d-f470-46d2-bc3c-42a8ba354050.png)

2. Pasitelkiant namų darbų pažymių vidurkį medianą.
  GalutinisVid = 0.4 * mediana + 0.6 * egzaminas
  ![CodeCogsEqn-2](https://user-images.githubusercontent.com/116019627/220768370-a02e423c-92d2-4747-945d-c0f46beee986.png)


Apskaičiavus gautinius įvestų studentų balus, programa išspausdinus studentų vardus, pavardes bei galutinius balus, kurie apskaičiuoti pasitelkiant vidurkį arba medianą.


## Failai

 - mylib.h - failas, kuriame saugomos naudojamos bibliotekos bei deklaruotos naudojamos funkcijos.
 - c_masyvas_main.cpp - programos failas, kuriame saugomas programos kodas. Duomenų talpinimui naudojami **C masyvai**.
 - main.cpp - programos failas, kuriame saugomas programos kodas. Duomenų talpinimui naudojami **vektoriai**.


## Instrukcija

1. Paleista programa paklausia naudotojo ar bus skaičiuojamas vidurkis, ar mediana.
2. Naudotojas pasirenka ar nori pildyti įrašą. Pasirinkus nepradėti programa sustabdoma.
3. Naudotojas įveda studento vardą ir pavardę.
4. Programa paklausia naudotojo ar jis norėtų studento pažymius įvesti ranka, ar sugeneruoti automatiškai. Leidžiami įvesti pažymiai turi būti intervale nuo 0 iki 10. "0" reiškia, jog darbas nebuvo atsiskaitytas.
  - Pasirinkus rankinį įvedimą naudotojas įvedą namų darbų pažymius. Kiekvienas įvedimas turi būti atskirtas klavišo "Enter" paspaudimu. Įvedimą užbaigti galima įvedus "33" ir paspaudus "Enter" klavišą. Baigus namų darbų įvedimą naudotojas įveda studento egzamino pažymį.
  - Pasirinkus automatinį pažymių generavimą programa paprašo naudotojo įvesti pažymių skaičių(į šį skaičių neįeina egzamino pažymys).
5. Programa išveda, jog duomenys buvo įrašyti irpaklausia naudotojo ar jis norėtų pildyti dar vieną įrašą.
  - Pasirinkus "Ne" programa stabdoma ir išvedami įvesti įrašų duomenys.
  - Pasirinkus "Taip" grįžtama į 3 instrukcijos žingsnį.
