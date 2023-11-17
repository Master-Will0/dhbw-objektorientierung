# Spielname

### ToDo's :

- [ ] Arena unten füllen (mit einem Bild, in der Größe vieleicht?)

- [x] Hintergrund hinzufügen

- [x] Arena erstellen

- [x] Auto-Klasse erstellen

- [ ] Plattformen einfügen

- [x] Beschleunigung der Autos

- [x] verkleinern der Autos

- [ ] Schaden hinzufügen (Labensbalken)

- [ ] Autos interagieren miteinander

## Beschreibung der Spielkomponenten

| Objekt                  | Beschreibung                                                                                                                                                                                      |
| ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Auto                    | zwei verschiedene Farben, wenig Details, Pixel-Art                                                                                                                                                |
| Arena                   | links und rechts einer Parabel und in der Mitte eine horizontale Linie                                                                                                                            |
| Plattformen             | simple, Pixel-Art, klein, fliegend                                                                                                                                                                |
| Auto-Klasse             | ``private(Geschwindigkeitx,y; Positionx,y; Rotation; bool mirrored [Fahrtrichtung]); public(Funktionen set; get; accelerate[Geschwindigkeitsänderung]; move[Positionsänderung]; rotate; mirror)`` |
| Bewegungen vom Auto     | realistisches Beschleunigen  mit entsprechender Richtung, evtl. fliegen; ``move function in draw(); accerlate function in update() mit rechts/links gedrückt``                                    |
| Interaktionen der Autos | Schaden, aufeinandertreffen                                                                                                                                                                       |
|                         |                                                                                                                                                                                                   |
|                         |                                                                                                                                                                                                   |
