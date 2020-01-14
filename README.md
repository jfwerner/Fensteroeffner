# Fensteröffner

## Zweck:
Auslesen der Temperatur und Luftfeuchtigkeit mithilfe des DHT22. Anzeige in human readable format in °C und %.
Nutzen der Werte und eines Telegram bots zur Steuerung eines 28BY Schrittmotors mit einem ULN2003 Motortreibers um ein Fenster zu öffnen und zu schließen.
![Schaltplan](https://i.imgur.com/qYhl0lE.png)

Mechatronik Projekt bei der HsKa bei Herrn Jürgen Walther.

## Wo kann ich das Programm herunterladen?
Bei den [Releases](https://github.com/jojo313/Fensteroeffner/releases) gibt es alle Versionen des Programms. Dort einfach die "tempdisp.ino" anklicken, und in der Arduino IDE öffnen.

## [Wiki](https://github.com/jojo313/Fensteroeffner/wiki)
mit genaueren Erklärungen, Beispielen und Screenshots
### [Beschreibung und Vorteile/Nachteil von Telegram](https://github.com/jojo313/Fensteroeffner/wiki/Features---Beschreibung-des-Projektes)
### [Komponenten und Breadboard](https://github.com/jojo313/Fensteroeffner/wiki/Komponenten-und-Breadboard)
Mit Erklärungen zur Verkabelung


## Features, Implementierung
- [x] Steuerung mit Telegram
- [x] 3D gedruckte Teile für den mechanischen Teil
- [x] Messung von Daten über den DHT22 Sensor
- [x] Anzeige auf einem OLED

### Verbesserungsideen
- [ ] Löten der Komponenten für ein schöneres und kompakteres Produkt
- [ ] Bessere Fixierung für den Motor
- [ ] Access Restriction bei Telegram



This work is licensed under a Creative Commons Attribution-NonCommercial 4.0 International License.
