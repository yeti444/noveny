# Automata öntöző rendszer fejlesztői dokumentációja 

### Tervezési fázis

Alapvetően nem volt ötletünk, hogy milyen szerkezetet kellene megvalósítani, de aztán az egyik ‘Kertészeti alapismeretek’ óráról kilépve arra jöttünk rá, hogy milyen menő lenne egy automata locsoló rendszer. És ez milyen jó ötlet volt. Kinek van kedve hajolgatni és vizet hordani minden egyes nap, mert van egy élőlény(parazita) aki meghal a segítségünk nélkül. A modulok beszerzése bonyolult volt elsőre, mivel az Arduino ami nekünk kellett (WIFI modulos) az hiányban volt, de a további modulok, amik szükségesek voltak az öntözéshez (pumpa, cső, relé stb.), azok már könnyebben beszerezhetőek voltak.

### Futtatási környezet

Arduino IDE 2.0.1 futtatására alkalmas operációs rendszer: 

- Windows:
  - Window 10, vagy újabb
- Linux:
  - AppImage 64 bits (X86-64) 
- MacOS: 
  - 10.14: “Mojave” vagy újabb, 64 bit 

### Periféria követelmények

- Billentyűzet
- Egér
- Monitor

### A fejlesztői környezet

Én az Arduino Nano RP2040 Connect felprogramozásához az Arduino IDE 2.0.1 nevű programozási környezetet használtuk, mely C++ programozási nyelvet használ, és én Windows 11-et használtam, mivel az volt telepítve a számítógépemre. Továbbá, az felhasznált Arduino modul hátrányaiból kimenően, nem voltunk képesek CSV fájlokat tárolni az apró meghajtóján, szóval ez miatt az Arduino Cloud – IOT Cloud szolgáltatását vettük igénybe, ami lehetővé tette azt nekünk, hogy adatokat tároljunk az nedvességérzékelő állapotáról, továbbá telefonon is meg lehet tekinteni egy alkalmazáson keresztül, amit az Arduino fejlesztett. 

### Arduino Cloud – IOT Cloud

<!-- Sok kép nem később ki kell fejteni -->

### Felhasznált modulok

- Arduino Nano RP2040 Connect 
- RELC-1CH-5V-UNI 
- AD20P-1230C 
- WTRH-TR-811 
- RC-40-20/MF 
- SA-27 
- OBO A11 

## Fontosabb modulok leírása

### Arduino Nano RP2040 Connect 

Az Arduino Nano RP2040 Connect az az Arduino Nano családba tartozó WIFI és Bluetooth modullal felszerelt mikrovezérlő. Képes az Internetre csatlakozni (ami szükséges) és továbbá, ha szükség lenne rá most a növény locsoló rendszerhez, akkor Bluetooth segítségével a közelében lévő Bluetooth eszközöket is tudnánk vezérelni. Egy a mikroszámítógép továbbá támogatja az Arduino Cloud fejlesztői felületet, és az integrálását. 

A mikrovezérlőnek van 3.3 és 5V outputja (az utóbbi forrasztás után érhető el), amik képesek feszültséggel táplálni a ‘RELC-1CH-5V-UNI' relét, és a ‘SA-27’ vízérzékelőt. 

### RELC-1CH-5V-UNI 

Ez egy 1 csatornás 5 Voltos opcionális vezérlésű relé optocsatolóval. Ez a legjobb relé, amit találtunk és úgy gondoljuk, hogy teszi a dolgát. Ahogy az elején le lett írva, 5V feszültséggel lehet kapcsolni és alacsony, illetve magas vezérlő jel opcióban is lehet vezérelni, de most a mi projektünknél magas feszültség beállításban lesz. 

A relé képes átkapcsolni 30V feszültséget egyenáramon, és 250V feszültséget váltakozó áramon, ami egy picit erős a mi kis 12V feszültségű vízpumpánkhoz, de a túlzás sose árt. 

Mérete apró: 26x50x20 mm, és ez miatt könnyen belefér a ‘OBO A11’ kis tároló dobozban a többi központi modullal együtt. 

Hozzáadott bónusz az, hogy led-del van felszerelve, és így lehet látni, ha be van kapcsolva, vagy ha ki van kapcsolva. 

