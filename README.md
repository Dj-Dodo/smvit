# SMVIT

Overview:


Cieľom tohto projektu je navrhnúť a zostrojiť vlastnú, cenovo dostupnú a univerzálnu meteorologickú stanicu pomocou 3D tlačených dielov, komponentov Arduino a niekoľkých ďalších senzorov a modulov. Meteorologická stanica bude zbierať údaje o rôznych parametroch prostredia a bude spolupracovať s aplikáciou Home Assistant, populárnou open-source platformou pre domácu automatizáciu. Integráciou s aplikáciou Home Assistant umožní stanica používateľom automatizovať úlohy v domácom prostredí na základe poveternostných podmienok v reálnom čase.

Komponenty projektu:
1. 3D tlačený kryt: Prispôsobiteľné puzdrá odolné voči poveternostným vplyvom pre senzory a dosku Arduino, navrhnuté tak, aby odolali vonkajším podmienkam.
2. Mikrokontrolér Arduino: Základná spracovateľská jednotka na zber údajov z rôznych snímačov a komunikáciu s domácim asistentom.
3. Senzory:
	* Snímač teploty a vlhkosti
	* Senzor dažďa
	* Snímač rýchlosti a smeru vetra
	* Snímač blesku
	* Snímač svetla

Projektové aplikácie a prípady použitia:
Meteorologická stanica bude generovať cenné údaje o prostredí, ktoré môžu spustiť automatizačné postupy prostredníctvom aplikácie Home Assistant, čím sa zvýši energetická účinnosť, bezpečnosť a pohodlie domova. Niektoré praktické príklady automatizácie zahŕňajú:

Ochrana drahých zariadení pred prepätím: Keď snímač blesku zistí blížiacu sa búrku, môže spustiť sekvenciu na odpojenie zariadení s vysokým výkonom, ako sú počítače a servery, čím sa zníži riziko poškodenia prepätím.

Automatické ovládanie žalúzií pre optimálne slnečné svetlo: Snímač svetla dokáže nastaviť žalúzie alebo rolety na základe úrovne slnečného svetla, čím pomáha prirodzene regulovať teplotu v interiéri alebo zabezpečiť rastlinám dostatok svetla.

Ovládanie zavlažovacieho systému podľa poveternostných podmienok: Ak dažďový senzor zistí nedávne zrážky, zavlažovací systém sa môže pozastaviť, aby sa zabránilo pretečeniu a šetrila sa voda.

Nastavenia HVAC pre úsporu energie: Teplota a vlhkosť môžu optimalizovať vykurovanie, vetranie a klimatizáciu, automaticky upravovať vnútorné podmienky na základe počasia vonku, znižovať spotrebu energie a udržiavať pohodlie.

Upozornenia na extrémne počasie: Pri zistení extrémnych podmienok, ako je napríklad vysoká rýchlosť vetra alebo nízka teplota, sa môžu používateľom posielať upozornenia do mobilných zariadení, aby mohli vykonať potrebné kroky, napríklad zabezpečiť vonkajšie predmety alebo sa pripraviť na nepriaznivé počasie.
