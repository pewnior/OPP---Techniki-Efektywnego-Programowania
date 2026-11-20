# C-OPP
Zbiór projektów zrealizowanych w ramach kursu **Techniki Efektywnego Programowania** na Politechnice Wrocławskiej. Repozytorium prezentuje praktyczne zastosowanie paradygmatu programowania obiektowego, ręcznego zarządzania pamięcią oraz przeciążania operatorów w czystym standardzie **C++98**.

## 1. `CNumber` — Arytmetyka dużych liczb i przeciążanie operatorów

Implementacja klasy `CNumber` przeznaczonej do przechowywania i wykonywania obliczeń na liczbach całkowitych o dowolnej długości (nawet rzędu kilku tysięcy cyfr), wykraczających poza zakres wbudowanych typów liczbowych.

### Kluczowe funkcjonalności
* **Dynamiczna reprezentacja cyfr:** Kolejne cyfry liczby przechowywane są w dynamicznie alokowanej tablicy liczb całkowitych (`int*`), zarządzanej przez klasę.
* **Bezpieczne kopiowanie głębokie:** Własny `operator=(const CNumber&)` oraz konstruktor kopiujący eliminują błędy płytkiej kopii, zapobiegając współdzieleniu wskaźników oraz błędom podwójnego zwalniania pamięci w destruktorze.
* **Arytmetyka wielocyfrowa:** Przeciążone operatory `+`, `-`, `*` oraz `/` realizują obliczenia bezpośrednio na tablicach cyfr (bez niedozwolonej konwersji do typu `int`).
* **Obsługa znaków i dzielenie całkowite:** Klasa wspiera liczby ujemne, a operator `/` zwraca część całkowitą wyniku dzielenia.
* **Konwersja i inicjalizacja:** Przeciążony `operator=(const int)` umożliwia bezpośrednie przypisywanie standardowych wartości całkowitych, a metoda `sToStr()` zwraca tekstową reprezentację liczby w obiekcie `std::string`.

### Przykład użycia w kodzie

```cpp
CNumber c_num_0, c_num_1, c_result;
c_num_0 = 368;
c_num_1 = 1567;

// Głębokie kopiowanie bez wycieków pamięci
c_num_0 = c_num_1;

// Złożone wyrażenia arytmetyczne z zachowaniem kolejności działań
c_result = (c_num_0 / c_num_1) * c_num_0 + c_num_1;
std::cout << c_result.sToStr() << std::endl;
```

---

## 2. `CTree` & `CNode` — Parser i ewaluator wyrażeń w Notacji Polskiej

Obiektowy silnik służący do wczytywania, automatycznej naprawy, łączenia oraz obliczania wartości formuł matematycznych zapisanych w postaci prefiksowej (Notacji Polskiej, niewymagającej stosowania nawiasów).

### Architektura i rozwiązania algorytmiczne
* **Dekompozycja obiektowa (`CTree`, `CNode`):** Klasa `CTree` zarządza całą strukturą drzewa i stanowi punkt styku z warstwą interfejsu użytkownika, natomiast klasa `CNode` odpowiada za pojedynczy węzeł oraz jego dowolną liczbę potomków (drzewo ogólne, nieograniczone do struktury binarnej).
* **Rekurencyjne parsowanie bez stosu:** Wczytywanie formuły ze zmiennej `std::string` odbywa się w pełni obiektowo — kolejne węzły samodzielnie analizują swój token na podstawie przekazywanego przesunięcia (offsetu) w ciągu znaków i delegują parsowanie argumentów do tworzonych dzieci, bez użycia zewnętrznego stosu.
* **Automatyczna naprawa błędnych formuł:**
  * *Brakujące argumenty:* Niekompletne wyrażenia (np. `+++` lub `+ a`) są automatycznie uzupełniane domyślnymi wartościami stałymi (np. `1`), dzięki czemu żaden z wprowadzonych operatorów nie zostaje utracony.
  * *Nadmiarowe symbole:* Tokeny występujące po wczytaniu kompletnego, poprawnego drzewa (np. `2` w wyrażeniu `+ 1 1 2`) są ignorowane, o czym program informuje użytkownika.
* **Obsługiwane symbole i walidacja:**
  * Operatory dwuargumentowe: `+`, `-`, `*`, `/`.
  * Funkcje jednoargumentowe: `sin`, `cos`.
  * Stałe (dodatnie liczby całkowite) oraz zmienne (ciągi liter i cyfr zawierające co najmniej jedną literę; niedozwolone znaki specjalne, np. `$`, są usuwane z komunikatem ostrzegawczym).
* **Łączenie drzew przez przeciążone operatory:** Zaimplementowane operatory `+` oraz `=` umożliwiają zapis `c_sum = c_a + c_b`, który tworzy nowe drzewo poprzez zastąpienie jednego z liści drzewa `c_a` kopią korzenia drzewa `c_b`, pozostawiając oba drzewa wejściowe niezmienione.

### Polecenia interfejsu konsolowego (CLI)

| Polecenie | Opis działania |
| :--- | :--- |
| `enter <formula>` | Parsuje wyrażenie w notacji prefiksowej do nowego drzewa, w razie potrzeby naprawia je i wypisuje ostateczną postać formuły. |
| `vars` | Wypisuje listę unikalnych nazw zmiennych występujących w aktualnym drzewie. |
| `print` | Wyświetla aktualnie przechowywane drzewo w postaci prefiksowej. |
| `comp <v0> <v1>...` | Oblicza wartość formuły dla podanych wartości zmiennych (zgodnie z kolejnością zwracaną przez `vars`) oraz weryfikuje liczbę argumentów. |
| `join <formula>` | Tworzy nowe drzewo na podstawie podanej formuły i dołącza je w miejsce jednego z liści aktualnego drzewa przy użyciu operatorów `+` i `=`. |

### Przykładowa sesja w konsoli

```text
> enter + a
Błąd w wyrażeniu. Naprawiona formuła: + a 1

> enter * + a b 8
Przetwarzana formuła: * + a b 8

> vars
a b

> comp 2 3
Wynik: 40

> join sin x
Połączona formuła: * + a b sin x
```

---
# Kompilacja zadania z drzewami wyrażeń (CTree / CNode)
g++ -std=c++98 -Wall -Wextra -pedantic *.cpp -o ctree_app
```
