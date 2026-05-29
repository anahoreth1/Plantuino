# Krok 3a - Tranzystor 2N2222A dla diody LED

Czasami przekaźnik działa niestabilnie, nie przełącza się poprawnie, może powodować zakłócenia albo reagować inaczej niż oczekujemy.

Dlatego zamiast przekaźnika użyjemy tranzystora `2N2222A`, który może działać jak elektroniczny przełącznik.
Arduino nie będzie zasilać pompki bezpośrednio, tylko wyśle mały sygnał sterujący do tranzystora.
Tranzystor włączy lub wyłączy osobny obwód zasilania.

Zanim jednak podłączymy prawdziwą pompkę, najpierw nauczymy się obsługi tranzystora na prostym i bezpiecznym przykładzie: będziemy sterować diodą LED.

## Co to jest tranzystor?

Tranzystor `2N2222A` może działać jak elektroniczny przełącznik. Ma on trzy nóżki:

- `E` — emitter / emiter
- `B` — base / baza
- `C` — collector / kolektor

W wielu wersjach `2N2222A`, gdy patrzymy na płaską stronę tranzystora i nóżki są skierowane w dół, kolejność może wyglądać tak:


<image src="./images/step-03a-tranzystor.png" controls width="350"></video>

Ale uwaga: w zależności od producenta kolejność nóżek może być inna. Jeśli układ nie działa, należy sprawdzić dokumentację konkretnego tranzystora albo spróbować zamienić miejscami skrajne nóżki: `E` i `C`.




Arduino wysyła sygnał na bazę tranzystora, a tranzystor pozwala przepłynąć prądowi przez podłączony element, na przykład diodę LED albo pompkę.

Dzięki temu możemy sterować urządzeniami wymagającymi większego prądu niż może dostarczyć pojedynczy pin Arduino.

## Wymagane elementy

- Arduino UNO
- Tranzystor `2N2222A`
- Dioda LED
- Rezystor `330Ω` dla diody LED
- Rezystor `1kΩ` dla bazy tranzystora
- Zewnętrzne źródło zasilania `5V`, na przykład powerbank
- Przewody połączeniowe
- Kabel USB

## Schemat połączenia

Najważniejsze jest to, że masa Arduino i masa zewnętrznego zasilania muszą być połączone.


| Element                    | Połączenie                                            |
| -------------------------- | ----------------------------------------------------- |
| GND zewnętrznego zasilania | GND Arduino                                           |
| E tranzystora              | GND zewnętrznego zasilania                            |
| B tranzystora              | D13 Arduino przez rezystor `1kΩ`                       |
| C tranzystora              | Katoda LED                                            |
| Anoda LED                  | Rezystor `330Ω`, a potem `+5V` zewnętrznego zasilania |


Czyli diodę LED podłączamy tak:

```text
+5V zewnętrzne -> rezystor 330Ω -> anoda LED -> katoda LED -> kolektor tranzystora
```

Tranzystor podłączamy tak:

```text
emiter tranzystora -> GND zewnętrznego zasilania
baza tranzystora -> rezystor 1kΩ -> pin D13 Arduino
```

Oraz koniecznie:

```text
GND zewnętrznego zasilania -> GND Arduino
```

<image src="./images/step-03a-connection.png" controls width="350"></video>


## Jak to działa?

Arduino nie zasila diody LED bezpośrednio.

Pin `D13` wysyła tylko mały sygnał sterujący do bazy tranzystora.
Gdy na pinie `D13` pojawi się stan `HIGH`, tranzystor zaczyna przewodzić prąd.
Wtedy prąd płynie z zewnętrznego źródła `5V` przez rezystor, diodę LED i tranzystor do masy.
Dioda LED zapala się.

Gdy na pinie `D13` pojawi się stan `LOW`, tranzystor przestaje przewodzić i dioda LED gaśnie.

## Kod programu

Odpowiedni kod znajduje się w [src/step_03a](./../src/step_03a/step_03a.ino).

## Wynik

Po uruchomieniu programu:

- dioda LED będzie migać co sekundę
- tranzystor będzie działał jak przełącznik
- Arduino będzie sterować obwodem z zewnętrznym zasilaniem

## Uwagi

- Pin Arduino służy tylko do sterowania tranzystorem.
- Rezystor `1kΩ` między pinem Arduino a bazą tranzystora jest obowiązkowy.
- Rezystor `330Ω` jest potrzebny tylko dla diody LED.
- GND Arduino i GND zewnętrznego źródła zasilania muszą być połączone.
- Jeśli LED nie miga, sprawdź kolejność nóżek tranzystora.
- W Kroku 4a zamiast diody LED podłączymy pompkę wody.
