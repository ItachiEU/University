package obliczenia;

public class Stala extends Wyrazenie {

   private final int wartosc;
   private final String nazwa;

   public Stala(int wartosc, String nazwa) {
      this.wartosc = wartosc;
      this.nazwa = nazwa;
   }

   @Override
   public int oblicz() {
      return wartosc;
   }

   public String toString() {
      return nazwa;
   }
}
