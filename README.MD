# Hash generatoriu

Galimi parametrai:
* `--string { string }`,
* `--files { filename1 ... filenameN }`,
* `--time { filename }`,
* `--compare { filename }`.

Perduoti parametrą **būtina**, tačiau nuskaitomas tik pirmas perduotas parametras.

## --string

Šis parametras skirtas perduoti simbolių eilutei, kurią programa apdoroja maišos funkcija ir išveda rezultatą į `outputs/string.txt` failą.

Pvz.: `g++ main.cpp -o main.out && ./main.out --string lietuva`.

## --files

Šis parametras skirtas perduoti failų masyvui, kurių turiny skaito kaip simbolių eilutę ir išveda rezultatus į `outputs/files.txt` failą, kiekvienam įvestam failui, išvedama viena eilutė į išvesties failą.

Pvz.: `g++ main.cpp -o main.out && ./main.out --files test-data/1-1.txt test-data/1-2.txt test-data/2-1.txt test-data/2-2.txt test-data/3-1.txt test-data/3-2.txt`.

## --measure

Šis parametras skirtas išmatuoti per kiek laiko "užhash'uojama" kiekviena failo eilutė. Rezultatas išvedamas į `outputs/measured.txt` failą.

Pvz.: `g++ main.cpp -o main.out && ./main.out --measure test-data/konstitucija.txt`.

## --compare

Šis parametras skirtas palyginti simbolių eilučių poras ar jų maišos funkcijos išvestys nesutampa bei apskaičiuojamas procentinis maišos funkcijos išvesčių "skirtingumas".

Pvz.: `g++ main.cpp -o main.out && ./main.out --compare test-data/string-pairs-2.txt`.


# Testinių failų pavyzdžių rezultatai:

| Failo pavadinimas      | Išvesties rezultatas                                             |
|------------------------|------------------------------------------------------------------|
| oneletter1.txt         | 1576200dab1dbf74da6ebd449414a92af40797706af58787549e26ba5d9acc4c |
| oneletter2.txt         | 7aa806b75f69e4d22255fcd703607adcede990f76dd522124526967202f9f171 |
| testBigString1.txt     | 7a7bba5ab2bb332ebf36d2767a5ed48b302407fd0ae0b1ecbd1b58c7f7ad4d48 |
| testBigString2.txt     | 51ea18e2e3b2cff79e39854e69fc6da2734dcf2517c4d04ed7049e092962887e |
| testBigStringDiff1.txt | 7a7bba5ab2bb332ebf36d2767a5ed48b302407fd0ae0b1ecbd1b58c7f7ad4d48 |
| testBigStringDiff2.txt | 55020de8b2f1c63d81f304a8446ec4937f9d9ec2bdae531c948080a2b1e86e80 |


# Hash funkcijos efektyvumas

Funkcijos veikimo laikas hash'uojant kiekvieną eilutę iš `konstitucija.txt` failo: `0.208 sec.`

# Simbolių eilučių porų lyginimas

| Failas | Simbolių eilučių porų skaičius | Rezultatas Bits Lygmuo |  Rezultatas Char Lygmuo |
| ------ |:------------------------------:|:----------:|:----------:|
| test100k-pairs-diff.txt | 100 000 | Avg Diff % 47.201<br>Max Diff % 63.2812<br>Min Diff % 37.5 | Avg Diff % 91.9215<br>Max Diff % 100<br>Min Diff % 78.125 |


Failas `test1m-pairs.txt` su 1 milijonu eilučių neturi sutapusių išvesties rezultatų.