# Krok 4a - Podłączenie pompki wody przez tranzystor

W kroku 3a nauczyliśmy się sterować diodą LED przy pomocy tranzystora `2N2222A`.

Teraz zamiast diody LED podłączymy prawdziwą pompkę wody, która będzie używana do automatycznego podlewania roślin.

Nie używamy tutaj modułu przekaźnika, ponieważ w naszym układzie działał on niestabilnie. Zamiast tego wykorzystujemy tranzystor jako elektroniczny przełącznik.
Arduino będzie wysyłać tylko sygnał sterujący, a pompka będzie zasilana z osobnego źródła `5V`.

Też  potrzebne będą jeszcze dwa dodatkowe elementy:
- dioda 1N4007
- kondensator elektrolityczny 100µF

## Pompka wody

Pompka jest bardzo prosta w obsłudze.

Posiada dwa przewody:

- czerwony — zasilanie `5V`
- czarny — `GND`

Po podłączeniu zasilania pompka zaczyna pracować i pompuje wodę.

![Pompka](./images/step-04a-pump.png)

## Dlaczego potrzebujemy diody i kondensatora?


Do sterowania pompką nie wystarczy samo Arduino, bo pompka wody potrzebuje większego prądu niż może bezpiecznie dostarczyć pin Arduino. Dlatego nie podłączamy jej bezpośrednio do Arduino. Dzięki temu Arduino będzie mogło bezpiecznie włączać i wyłączać pompkę

Oprócz tranzystora `2N2222A`, który poznaliśmy w kroku 3a, potrzebne będą jeszcze dwa dodatkowe elementy:
- dioda `1N4007`
- kondensator elektrolityczny 100µF

Dioda `1N4007` służy do ochrony układu.
Pompka zawiera mały silnik, który podczas wyłączania może powodować krótkie przepięcia. Dioda pomaga zabezpieczyć tranzystor i Arduino przed takim przepięciem.

Kondensator elektrolityczny `100µF` pomaga stabilizować zasilanie pompki.
Podczas uruchamiania pompka może chwilowo pobrać większy prąd, co może spowodować krótki spadek napięcia. Kondensator pomaga zmniejszyć takie zakłócenia.


Dodatkowo dodamy diodę `1N4007`, która zabezpiecza układ przed przepięciami powstającymi podczas wyłączania silnika pompki.

## Wymagane elementy

- Arduino UNO
- Tranzystor `2N2222A`
- Pompka wody `5V`
- Dioda `1N4007`
- Kondensator elektrolityczny `100µF`
- Rezystor `1kΩ` dla bazy tranzystora
- Zewnętrzne źródło zasilania `5V`, na przykład powerbank
- Przewody połączeniowe
- Kabel USB

![Części](./images/step-04a-parts.png) 

## Schemat połączenia

### Piny tranzystora

Tranzystor `2N2222A` ma trzy nóżki:

- `E` — emitter / emiter
- `B` — base / baza
- `C` — collector / kolektor

W wielu wersjach `2N2222A`, gdy patrzymy na płaską stronę tranzystora i nóżki są skierowane w dół, kolejność może wyglądać tak:

```text
E B C
```

Ale uwaga: w zależności od producenta kolejność nóżek może być inna. Jeśli układ nie działa, należy sprawdzić dokumentację konkretnego tranzystora albo spróbować zamienić miejscami skrajne nóżki: `E` i `C`.

## Połączenia

Najważniejsze jest to, że masa Arduino i masa zewnętrznego zasilania muszą być połączone.

| Element | Połączenie |
|---|---|
| GND zewnętrznego zasilania | GND Arduino |
| E tranzystora | GND zewnętrznego zasilania |
| B tranzystora | D7 Arduino przez rezystor `1kΩ` |
| C tranzystora | Czarny przewód pompki |
| Czerwony przewód pompki | `+5V` zewnętrznego zasilania |

Czyli pompkę podłączamy tak:

```text
+5V zewnętrzne -> czerwony przewód pompki
czarny przewód pompki -> kolektor tranzystora
```

Tranzystor podłączamy tak:

```text
emiter tranzystora -> GND zewnętrznego zasilania
baza tranzystora -> rezystor 1kΩ -> pin D7 Arduino
```

Oraz koniecznie:

```text
GND zewnętrznego zasilania -> GND Arduino
```

## Dioda zabezpieczająca 1N4007

Pompka zawiera mały silnik, a silnik podczas wyłączania może generować krótkie przepięcia.

Aby zabezpieczyć tranzystor i Arduino, podłączamy diodę `1N4007` równolegle do pompki.

Diodę podłączamy tak:

| Dioda 1N4007 | Połączenie |
|---|---|
| Katoda, strona z paskiem | `+5V`, czerwony przewód pompki |
| Anoda | Czarny przewód pompki, kolektor tranzystora |

Schematycznie:

```text
        +5V
         |
         +---- katoda 1N4007, strona z paskiem
         |
       pompka
         |
         +---- anoda 1N4007
         |
     kolektor tranzystora
```

Dioda jest podłączona odwrotnie względem normalnego przepływu prądu. To jest poprawne — w normalnej pracy nie przewodzi, ale chroni układ w momencie wyłączenia pompki.

## Kondensator 100µF

Kondensator `100µF` podłączamy między `+5V` i `GND` zewnętrznego zasilania.

| Kondensator | Połączenie |
|---|---|
| `+` kondensatora | `+5V` zewnętrznego zasilania |
| `-` kondensatora | GND zewnętrznego zasilania |

Kondensator pomaga zmniejszyć krótkie spadki napięcia, które mogą pojawić się podczas uruchamiania pompki.

Uwaga: kondensator elektrolityczny ma polaryzację. Nie wolno podłączać go odwrotnie.

## Pełny opis połączenia

```text
+5V zewnętrzne ---------------- czerwony przewód pompki
                                  |
                                pompka
                                  |
czarny przewód pompki -------- kolektor 2N2222A

emiter 2N2222A ---------------- GND zewnętrznego zasilania
GND Arduino ------------------- GND zewnętrznego zasilania

Arduino D7 ---- rezystor 1kΩ ---- baza 2N2222A

1N4007:
katoda, strona z paskiem ------- +5V / czerwony przewód pompki
anoda -------------------------- czarny przewód pompki / kolektor

100µF:
+ ------------------------------ +5V zewnętrznego zasilania
- ------------------------------ GND zewnętrznego zasilania
```

## Jak to działa?

Arduino nie zasila pompki bezpośrednio.

Pin `D7` wysyła tylko mały sygnał sterujący do bazy tranzystora.
Gdy na pinie `D7` pojawi się stan `HIGH`, tranzystor zaczyna przewodzić prąd.
Wtedy prąd płynie z zewnętrznego źródła `5V` przez pompkę i tranzystor do masy.
Pompka zaczyna pracować.

Gdy na pinie `D7` pojawi się stan `LOW`, tranzystor przestaje przewodzić i pompka się wyłącza.

## Kod programu

Odpowiedni kod znajduje się w [src/step_04a](./../src/step_04a/step_04a.ino).

Przykładowa logika programu:

```cpp
const int pumpPin = 7;

void setup() {
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  digitalWrite(pumpPin, HIGH);
  delay(1000);

  digitalWrite(pumpPin, LOW);
  delay(3000);
}
```

## Wynik

Po uruchomieniu programu:

- pompka będzie okresowo się uruchamiać
- Arduino będzie sterować pompką przez tranzystor
- pompka będzie zasilana z zewnętrznego źródła `5V`

Przykład:

<video src="./images/step-04-result.MOV" controls width="350"></video>

## Uwagi

- Nigdy nie uruchamiaj pompki bez wody na dłuższy czas.
- Nie podłączaj pompki bezpośrednio do pinu Arduino.
- Pin Arduino służy tylko do sterowania tranzystorem.
- Rezystor `1kΩ` między pinem Arduino a bazą tranzystora jest obowiązkowy.
- Rezystor `330Ω` z poprzedniego kroku był potrzebny tylko dla diody LED. Przy pompce go nie używamy.
- Dioda `1N4007` powinna być podłączona równolegle do pompki.
- Pasek na diodzie `1N4007` powinien być po stronie `+5V`.
- Kondensator `100µF` musi być podłączony zgodnie z polaryzacją.
- GND Arduino i GND zewnętrznego źródła zasilania muszą być połączone.
- Jeśli pompka nie działa, sprawdź zasilanie `5V`, połączenia tranzystora i kolejność jego nóżek.
- Jeśli tranzystor szybko się nagrzewa, wyłącz układ i sprawdź, czy pompka nie pobiera zbyt dużego prądu.
