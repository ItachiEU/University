package obliczenia;

public class Deklaracja extends Instrukcja {
   private final String nazwa;
   private final int wartosc;
   private Integer stara_wartosc;

   public Deklaracja(String n) throws IllegalArgumentException {
      if (n == null)
         throw new IllegalArgumentException("Nazwa nie moze byc nullem.");
      this.nazwa = n;
      this.wartosc = 0;
      this.stara_wartosc = null;
   }

   public Deklaracja(String n, int v) throws IllegalArgumentException {
      if (n == null)
         throw new IllegalArgumentException("Nazwa nie moze byc nullem.");
      this.nazwa = n;
      this.wartosc = v;
      this.stara_wartosc = null;
   }

   public Deklaracja(String n, Wyrazenie w) {
      this.nazwa = n;
      this.wartosc = w.oblicz();
      this.stara_wartosc = null;
   }

   @Override
   public void wykonaj() {
      if (Zmienna.istnieje(nazwa)) {
         stara_wartosc = (int) Zmienna.szukaj(nazwa).getValue();
      }
      Zmienna.ustaw(nazwa, wartosc);
   }

   public void usun() {
      if (stara_wartosc != null) {
         Zmienna.ustaw(nazwa, stara_wartosc);
      } else {
         Zmienna.usun(nazwa);
      }
   }
}
