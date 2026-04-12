# Fiber Optic Tester / LWL-Tester

[![GitHub](https://img.shields.io/badge/GitHub-Amirmobash%2Ffiber--optic--tester-blue?logo=github)](https://github.com/Amirmobash/fiber-optic-tester)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Amir%20Mobasheraghdam-0077B5?logo=linkedin)](https://www.linkedin.com/in/amirmobasher/)
[![Arduino](https://img.shields.io/badge/Arduino-Nano-00979D?logo=arduino)](https://www.arduino.cc/)
[![Python](https://img.shields.io/badge/Python-3.7%2B-3776AB?logo=python)](https://www.python.org/)
[![PyQt5](https://img.shields.io/badge/GUI-PyQt5-41CD52?logo=qt)](https://www.riverbankcomputing.com/software/pyqt/)

**Author:** Amir Mobasheraghdam (Amirmobash)  
**LinkedIn:** [https://www.linkedin.com/in/amirmobasher/](https://www.linkedin.com/in/amirmobasher/)

---

## Table of Contents / Inhaltsverzeichnis

- [English](#english)  
  - [Overview](#overview)  
  - [Features](#features)  
  - [Hardware Requirements](#hardware-requirements)  
  - [Wiring Diagram](#wiring-diagram)  
  - [Arduino Setup](#arduino-setup)  
  - [Windows GUI (PyQt5) Setup](#windows-gui-pyqt5-setup)  
  - [Usage Instructions](#usage-instructions)  
  - [How It Works](#how-it-works)  
  - [Troubleshooting](#troubleshooting)  
  - [License](#license)

- [Deutsch](#deutsch)  
  - [Überblick](#überblick)  
  - [Funktionen](#funktionen)  
  - [Hardware-Anforderungen](#hardware-anforderungen)  
  - [Verkabelungsplan](#verkabelungsplan)  
  - [Arduino Einrichtung](#arduino-einrichtung)  
  - [Windows GUI (PyQt5) Einrichtung](#windows-gui-pyqt5-einrichtung)  
  - [Bedienungsanleitung](#bedienungsanleitung)  
  - [Funktionsweise](#funktionsweise)  
  - [Fehlerbehebung](#fehlerbehebung)  
  - [Lizenz](#lizenz)

---

# English

## Overview

This **Fiber Optic Cable Tester** is a professional-grade tool for verifying the integrity of fiber optic cables with two independent channels (A and B). It consists of:

- **Arduino Nano** – controls LEDs (light sources) and reads LDR sensors (light detectors).
- **OLED Display (128×64, SSD1306)** – shows real-time test results and difference values.
- **Windows GUI (Python + PyQt5)** – provides a modern interface for logging, visual feedback, and extended analysis.

The device tests fiber paths **A→A** and **B→B** by emitting light through an LED and measuring the received light intensity with an LDR after passing through the fiber. The difference between ambient light and lit condition determines if the fiber is intact.

> **Perfect for:** Quality control, field testing, educational labs, and production line verification of fiber optic assemblies.

## Features

- ✅ **Two independent channels** (A & B) – test duplex fibers simultaneously.
- ✅ **OLED display** – shows per‑channel difference values, PASS/FAIL status, and adjustable sensitivity.
- ✅ **Adjustable sensitivity** – set threshold for reliable detection (default 15 LSB).
- ✅ **Welcome animation** – professional startup sequence with author credits.
- ✅ **Serial logging** – detailed debug output via USB Serial (9600 baud).
- ✅ **Windows GUI (PyQt5)** – 
  - Real‑time chart of light intensity
  - Save/load test logs (CSV)
  - One‑click retest
  - Visual pass/fail indicators
  - Automatic serial port detection
- ✅ **Open source** – fully customizable for your specific fiber types or LED/LDR combinations.

## Hardware Requirements

| Component               | Quantity | Notes                                  |
|-------------------------|----------|----------------------------------------|
| Arduino Nano            | 1        | Any ATmega328P based board works       |
| LED (visible red or IR) | 2        | 5mm, forward current ~20mA             |
| LDR (photoresistor)     | 2        | GL5528 or similar (resistance varies with light) |
| Resistor 10kΩ           | 2        | For voltage divider with LDR           |
| Resistor 220Ω           | 2        | Current limiting for LEDs              |
| OLED Display            | 1        | SSD1306, 128×64, I²C (address 0x3C)    |
| Breadboard & jumper wires | –      | For prototyping                        |
| Fiber optic cable       | 1        | With two independent fibers (A and B)  |

**Optional:** 3D printed enclosure, battery pack for portable use.

## Wiring Diagram

Connect components to the Arduino Nano as follows:

| Component          | Arduino Pin | Notes                          |
|--------------------|-------------|--------------------------------|
| LED_A (Channel A)  | A2 (digital) | Anode → A2, Cathode → GND via 220Ω |
| LED_B (Channel B)  | A3 (digital) | Anode → A3, Cathode → GND via 220Ω |
| LDR_A (Channel A)  | A0 (analog)  | One leg → A0, other leg → 5V. 10kΩ from A0 to GND (voltage divider) |
| LDR_B (Channel B)  | A1 (analog)  | Same as above                   |
| OLED SDA           | A4           | I²C data line                   |
| OLED SCL           | A5           | I²C clock line                  |
| OLED VCC           | 5V           |                                 |
| OLED GND           | GND          |                                 |

**Important:** Place the LDRs and LEDs facing each other with the fiber optic cable in between. Use opaque tubing to block ambient light.

## Arduino Setup

1. **Install Arduino IDE** (version 1.8.13+).
2. **Install required libraries** via Library Manager:
   - `Adafruit GFX Library`
   - `Adafruit SSD1306`
3. **Open** `fiber_tester.ino` from the `arduino/` folder.
4. **Select board:** Tools → Board → Arduino Nano (Processor: ATmega328P).
5. **Select port** (e.g., COM3 on Windows).
6. **Upload** the sketch.

### Customizing Parameters (in `fiber_tester.ino`)

```cpp
#define BLINK_DURATION 900    // LED on time (ms)
#define SENSITIVITY    15     // Detection threshold (LSB)
#define DELAY_BETWEEN  900    // Delay between testing A and B (ms)
#define DELAY_RESULT   3000   // How long to show results on OLED (ms)
```

Adjust `SENSITIVITY` if your ambient light is very high or low. Increase `BLINK_DURATION` for longer fibers that attenuate more.

## Windows GUI (PyQt5) Setup

The GUI communicates with the Arduino via Serial (USB) and provides a rich dashboard.

### Prerequisites

- **Python 3.7 or higher** (download from [python.org](https://www.python.org/))
- **PyQt5** and **pyserial** libraries

### Installation Steps

1. Clone or download this repository.
2. Open a command prompt (cmd) in the `software/` folder.
3. Install dependencies:

```bash
pip install pyqt5 pyserial
```

4. Run the GUI:

```bash
python fiber_gui.py
```

> **Note:** The Arduino must be connected and the sketch uploaded before starting the GUI. The GUI automatically scans for available serial ports – select the one matching your Arduino (e.g., COM3).

### GUI Features

- **Connect / Disconnect** – establish serial communication.
- **Start Test** – runs the same test cycle as the standalone Arduino (A then B).
- **Live Chart** – plots LDR values over time (ambient → lit → decay).
- **Result Table** – shows differential values and pass/fail status.
- **Export CSV** – saves all measurements with timestamps.
- **Sensitivity Slider** – adjust threshold on the fly (syncs with Arduino).
- **Retest Button** – quick repeat of the test.

## Usage Instructions

### Standalone Mode (OLED only)

1. Power the Arduino (USB or external 7–12V).
2. The OLED shows a welcome animation, then enters the main loop.
3. Insert the fiber optic cable between LED_A and LDR_A (and similarly for B).
4. The device automatically tests Channel A, waits, then tests Channel B.
5. Results are displayed on the OLED:
   - **A Diff:** difference value (higher = better light transmission)
   - **B Diff:** same for channel B
   - **A: OK / X** – indicates whether the fiber is intact.
6. The cycle repeats every few seconds.

### PC Mode (with GUI)

1. Connect Arduino via USB.
2. Launch the GUI (`python fiber_gui.py`).
3. Click **Connect** and select the correct COM port.
4. Click **Start Test** – the GUI will send a command to the Arduino to run the test.
5. View real‑time charts and logs. Save data as needed.

> **Pro tip:** Use the GUI for long‑term documentation or when testing many cables in a row.

## How It Works

1. **Ambient reading** – LDR measures light level without LED (background).
2. **Threshold calculation** – `threshold = ambient + SENSITIVITY`.
3. **LED turns on** for `BLINK_DURATION` ms.
4. **Second reading** – LDR measures light with LED active.
5. **Difference** = `after - before`.
6. **Decision** – if `after > threshold` → **OK** (fiber conducts light), else **FAIL**.
7. **OLED & Serial output** – shows difference, OK/FAIL, and sensitivity.
8. The same process runs for Channel B after a short delay.

The Windows GUI additionally records the raw analog values over time and allows CSV export for statistical analysis.

## Troubleshooting

| Problem                          | Likely Solution                                                                 |
|----------------------------------|---------------------------------------------------------------------------------|
| OLED stays blank                 | Check I²C connections (SDA→A4, SCL→A5). Verify address is 0x3C.                 |
| LED does not light               | Verify polarity (anode to pin, cathode to GND). Check resistor (220Ω).          |
| LDR always reads 0 or 1023      | Ensure voltage divider (10kΩ from LDR pin to GND). LDR should see changing light. |
| GUI cannot find serial port      | Install Arduino drivers (CH340 or FTDI). Close Serial Monitor in Arduino IDE.   |
| False negatives (FAIL when OK)   | Increase `SENSITIVITY` or `BLINK_DURATION` in the code.                         |
| Cross‑talk between channels      | Use opaque shielding between A and B paths.                                    |

## License

This project is open source under the **MIT License**. Feel free to use, modify, and distribute with attribution.

---

# Deutsch

## Überblick

Dieser **LWL-Kabeltester** (Lichtwellenleiter-Tester) ist ein professionelles Werkzeug zur Überprüfung der Integrität von Glasfaserkabeln mit zwei unabhängigen Kanälen (A und B). Er besteht aus:

- **Arduino Nano** – steuert LEDs (Lichtquellen) und liest LDR-Sensoren (Lichtdetektoren).
- **OLED-Display (128×64, SSD1306)** – zeigt Echtzeit-Ergebnisse und Differenzwerte an.
- **Windows GUI (Python + PyQt5)** – moderne Oberfläche für Protokollierung, visuelles Feedback und erweiterte Analyse.

Das Gerät testet die Faserpfade **A→A** und **B→B**, indem es Licht durch eine LED sendet und die empfangene Lichtintensität nach Durchlaufen der Faser mit einem LDR misst. Die Differenz zwischen Umgebungslicht und Beleuchtung bestimmt, ob die Faser intakt ist.

> **Ideal für:** Qualitätskontrolle, Feldtests, Ausbildungslabore und Produktionslinien zur Prüfung von LWL-Konfektionen.

## Funktionen

- ✅ **Zwei unabhängige Kanäle** (A & B) – testet Duplex-Fasern gleichzeitig.
- ✅ **OLED-Display** – zeigt Differenzwerte pro Kanal, BESTANDEN/FEHLGESCHLAGEN und einstellbare Empfindlichkeit.
- ✅ **Einstellbare Empfindlichkeit** – Schwellwert für zuverlässige Erkennung (Standard 15 LSB).
- ✅ **Begrüßungsanimation** – professioneller Start mit Autorenangaben.
- ✅ **Serielle Protokollierung** – detaillierte Debug-Ausgabe über USB-Seriell (9600 Baud).
- ✅ **Windows GUI (PyQt5)** – 
  - Echtzeit-Diagramm der Lichtintensität
  - Speichern/Laden von Testprotokollen (CSV)
  - Ein-Klick-Wiederholungstest
  - Visuelle Bestanden/Fehlgeschlagen-Anzeigen
  - Automatische Erkennung des seriellen Ports
- ✅ **Open Source** – vollständig anpassbar für Ihre spezifischen Fasertypen oder LED/LDR-Kombinationen.

## Hardware-Anforderungen

| Komponente               | Anzahl | Hinweise                                  |
|--------------------------|--------|-------------------------------------------|
| Arduino Nano             | 1      | Jedes ATmega328P-Board funktioniert       |
| LED (sichtbares Rot oder IR) | 2  | 5mm, Durchlassstrom ~20mA                 |
| LDR (Fotowiderstand)     | 2      | GL5528 o.ä. (Widerstand variiert mit Licht) |
| Widerstand 10kΩ          | 2      | Für Spannungsteiler mit LDR               |
| Widerstand 220Ω          | 2      | Strombegrenzung für LEDs                  |
| OLED-Display             | 1      | SSD1306, 128×64, I²C (Adresse 0x3C)       |
| Steckbrett & Jumper-Kabel | –     | Für Prototypen                            |
| LWL-Kabel                | 1      | Mit zwei unabhängigen Fasern (A und B)    |

**Optional:** 3D-gedrucktes Gehäuse, Akkupack für mobilen Einsatz.

## Verkabelungsplan

Verbinden Sie die Komponenten wie folgt mit dem Arduino Nano:

| Komponente           | Arduino-Pin | Hinweise                                   |
|----------------------|-------------|--------------------------------------------|
| LED_A (Kanal A)      | A2 (digital) | Anode → A2, Kathode → GND über 220Ω       |
| LED_B (Kanal B)      | A3 (digital) | Anode → A3, Kathode → GND über 220Ω       |
| LDR_A (Kanal A)      | A0 (analog)  | Ein Pin → A0, anderer Pin → 5V. 10kΩ von A0 nach GND (Spannungsteiler) |
| LDR_B (Kanal B)      | A1 (analog)  | Genau wie oben                             |
| OLED SDA             | A4           | I²C-Datenleitung                          |
| OLED SCL             | A5           | I²C-Taktleitung                           |
| OLED VCC             | 5V           |                                            |
| OLED GND             | GND          |                                            |

**Wichtig:** Platzieren Sie die LDRs und LEDs mit der Glasfaser dazwischen. Verwenden Sie undurchsichtige Schläuche, um Umgebungslicht abzuschirmen.

## Arduino Einrichtung

1. **Arduino IDE installieren** (Version 1.8.13+).
2. **Erforderliche Bibliotheken** über den Bibliotheksverwalter installieren:
   - `Adafruit GFX Library`
   - `Adafruit SSD1306`
3. **Öffnen** Sie `fiber_tester.ino` aus dem Ordner `arduino/`.
4. **Board auswählen:** Werkzeuge → Board → Arduino Nano (Prozessor: ATmega328P).
5. **Port auswählen** (z.B. COM3 unter Windows).
6. **Hochladen** des Sketches.

### Anpassen von Parametern (in `fiber_tester.ino`)

```cpp
#define BLINK_DURATION 900    // LED-Einschaltdauer (ms)
#define SENSITIVITY    15     // Erkennungsschwelle (LSB)
#define DELAY_BETWEEN  900    // Verzögerung zwischen Test A und B (ms)
#define DELAY_RESULT   3000   // Dauer der Ergebnisanzeige auf dem OLED (ms)
```

Passen Sie `SENSITIVITY` an, wenn Ihr Umgebungslicht sehr hoch oder niedrig ist. Erhöhen Sie `BLINK_DURATION` für längere Fasern, die mehr dämpfen.

## Windows GUI (PyQt5) Einrichtung

Die GUI kommuniziert über serielle Schnittstelle (USB) mit dem Arduino und bietet ein übersichtliches Dashboard.

### Voraussetzungen

- **Python 3.7 oder höher** (Download von [python.org](https://www.python.org/))
- **PyQt5** und **pyserial** Bibliotheken

### Installationsschritte

1. Dieses Repository klonen oder herunterladen.
2. Eine Eingabeaufforderung (cmd) im Ordner `software/` öffnen.
3. Abhängigkeiten installieren:

```bash
pip install pyqt5 pyserial
```

4. GUI starten:

```bash
python fiber_gui.py
```

> **Hinweis:** Der Arduino muss angeschlossen und das Sketch hochgeladen sein, bevor die GUI gestartet wird. Die GUI durchsucht automatisch verfügbare serielle Ports – wählen Sie den Port, der Ihrem Arduino entspricht (z.B. COM3).

### GUI-Funktionen

- **Verbinden / Trennen** – serielle Kommunikation aufbauen.
- **Test starten** – führt denselben Testzyklus aus wie der eigenständige Arduino (A dann B).
- **Live-Diagramm** – zeichnet LDR-Werte über die Zeit (Umgebungslicht → Beleuchtung → Abfall).
- **Ergebnistabelle** – zeigt Differenzwerte und Bestanden/Fehlgeschlagen-Status.
- **Export als CSV** – speichert alle Messungen mit Zeitstempeln.
- **Empfindlichkeitsregler** – Schwellwert live anpassen (synchronisiert mit Arduino).
- **Wiederholungstest** – schnelle Wiederholung des Tests.

## Bedienungsanleitung

### Eigenständiger Modus (nur OLED)

1. Arduino mit Strom versorgen (USB oder extern 7–12V).
2. Das OLED zeigt eine Begrüßungsanimation an und startet dann die Hauptschleife.
3. Das Glasfaserkabel zwischen LED_A und LDR_A (und entsprechend für B) einlegen.
4. Das Gerät testet automatisch Kanal A, wartet, dann Kanal B.
5. Ergebnisse werden auf dem OLED angezeigt:
   - **A Diff:** Differenzwert (höher = bessere Lichtübertragung)
   - **B Diff:** gleiches für Kanal B
   - **A: OK / X** – zeigt an, ob die Faser intakt ist.
6. Der Zyklus wiederholt sich alle paar Sekunden.

### PC-Modus (mit GUI)

1. Arduino über USB anschließen.
2. GUI starten (`python fiber_gui.py`).
3. Klicken Sie auf **Verbinden** und wählen Sie den richtigen COM-Port.
4. Klicken Sie auf **Test starten** – die GUI sendet einen Befehl an den Arduino, um den Test auszuführen.
5. Sehen Sie sich die Echtzeit-Diagramme und Protokolle an. Speichern Sie Daten bei Bedarf.

> **Profi-Tipp:** Verwenden Sie die GUI für eine langfristige Dokumentation oder wenn Sie viele Kabel hintereinander testen.

## Funktionsweise

1. **Umgebungsmessung** – LDR misst Lichtpegel ohne LED (Hintergrund).
2. **Schwellwertberechnung** – `Schwellwert = Umgebungswert + SENSITIVITY`.
3. **LED einschalten** für `BLINK_DURATION` ms.
4. **Zweite Messung** – LDR misst Licht bei aktiver LED.
5. **Differenz** = `nachher - vorher`.
6. **Entscheidung** – wenn `nachher > Schwellwert` → **OK** (Faser leitet Licht), sonst **FEHLER**.
7. **OLED- und serielle Ausgabe** – zeigt Differenz, OK/FEHLER und Empfindlichkeit.
8. Der gleiche Vorgang läuft nach einer kurzen Verzögerung für Kanal B.

Die Windows-GUI zeichnet zusätzlich die analogen Rohwerte über die Zeit auf und ermöglicht den CSV-Export für statistische Analysen.

## Fehlerbehebung

| Problem                            | Wahrscheinliche Lösung                                                              |
|------------------------------------|-------------------------------------------------------------------------------------|
| OLED bleibt dunkel                 | I²C-Verbindungen prüfen (SDA→A4, SCL→A5). Adresse 0x3C bestätigen.                 |
| LED leuchtet nicht                 | Polarität prüfen (Anode an Pin, Kathode an GND). Widerstand (220Ω) kontrollieren.  |
| LDR liest immer 0 oder 1023        | Spannungsteiler sicherstellen (10kΩ vom LDR-Pin zu GND). LDR muss Lichtänderungen sehen. |
| GUI findet keinen seriellen Port   | Arduino-Treiber installieren (CH340 oder FTDI). Seriellen Monitor in Arduino IDE schließen. |
| Falsche Fehler (FAIL obwohl OK)    | Erhöhen Sie `SENSITIVITY` oder `BLINK_DURATION` im Code.                           |
| Übersprechen zwischen Kanälen      | Verwenden Sie undurchsichtige Abschirmung zwischen A- und B-Pfaden.                |

## Lizenz

Dieses Projekt ist Open Source unter der **MIT-Lizenz**. Sie können es frei nutzen, ändern und unter Nennung des Autors weiterverbreiten.

---

**Developed with ❤️ by Amir Mobasheraghdam (Amirmobash)**  
[GitHub](https://github.com/Amirmobash) | [LinkedIn](https://www.linkedin.com/in/amirmobasher/)
```
