# Plantuino

Plantuino - system monitorowania życiem roślin,  oparty na Arduino.  
Celem projektu jest stopniowe budowanie prostego systemu do kontroli warunków roślin.

TODO: części i etapy z "a"

## Struktura projektu

```text
project/
│
├── docs/
│   ├── step_01.md
│   ├── step_02.md
│   ├── step_03.md
│   ....
│
├── src/
│   ├── step_01/
│   ├── step_02/
│   ├── step_03/
│   ....
│
└── README.md
```

## Etapy projektu

- Krok 1. Podłączenie czujnika wilgotności gleby do Arduino
- Krok 2. Podłączenie wyświetlacza OLED i wyświetlanie danych
- Krok 3. Nauka działania przekaźnika (na przykładzie LED)
- Krok 3a - Tranzystor 2N2222A dla diody LED
- Krok 4. Podłączenie pompki wody przez przekaźnik
- Krok 5. Dodanie przycisku do ręcznego sterowania pompką
- Krok 6. Integracja systemu:
    * czujnik + OLED + przekaźnik
    * automatyczne uruchamianie pompki po przekroczeniu progu
    * nadal działa przycisk ręczny
-  Krok 7. Dodanie potencjometru: możliwość regulacji progu wilgotności bez zmiany kodu
