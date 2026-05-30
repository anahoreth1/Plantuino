# Plantuino

Plantuino to prosty system monitorowania i podlewania roślin oparty na Arduino.

Celem projektu jest stopniowe zbudowanie urządzenia, które potrafi mierzyć wilgotność gleby, wyświetlać dane na ekranie OLED oraz automatycznie sterować pompką wody.

Projekt został przygotowany w formie kolejnych kroków. W każdym kroku dodawany jest nowy element systemu, dzięki czemu można łatwo zrozumieć zarówno podłączenie podzespołów, jak i działanie programu.

Do realizacji projektu wykorzystamy między innymi czujnik wilgotności gleby, wyświetlacz OLED, potencjometr, przekaźnik oraz pompkę wody.

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

Projekt został podzielony na dwie części.

### Część 1 - Monitorowanie stanu rośliny

W tej części nauczymy się odczytywać dane z czujników i prezentować je użytkownikowi.

- Krok 1. Podłączenie czujnika wilgotności gleby do Arduino
- Krok 2. Podłączenie wyświetlacza OLED i wyświetlanie danych
- Krok 3. Dodanie potencjometru: możliwość regulacji progu wilgotności bez zmiany kodu

### Część 2 - Sterowanie pompką

W drugiej części zajmiemy się automatycznym podlewaniem roślin. Najpierw poznamy różne sposoby sterowania urządzeniami zewnętrznymi, a następnie podłączymy pompkę i dodamy ręczne sterowanie.

- Krok 4. Nauka działania przekaźnika (na przykładzie LED) 
- Krok 5. Podłączenie pompki wody przez przekaźnik 
- Krok 6. Dodanie przycisku do ręcznego sterowania pompką


### Przekaźnik czy tranzystor?

W projekcie jako główny sposób sterowania pompką wykorzystamy przekaźnik.

Przekaźnik jest prosty w użyciu i pozwala łatwo zrozumieć zasadę sterowania urządzeniami zewnętrznymi za pomocą Arduino.

W praktyce podobny efekt można osiągnąć również przy pomocy tranzystora, na przykład popularnego `2N2222A` oraz MOSFET.

Dlatego dla zainteresowanych przygotowano dodatkowe kroki:

- Krok 4a. Sterowanie diodą LED przy pomocy tranzystora 2N2222A
- Krok 5a. Sterowanie pompką przy pomocy tranzystora 2N2222A

Te kroki są opcjonalne i pokazują alternatywne rozwiązanie bez użycia przekaźnika.
