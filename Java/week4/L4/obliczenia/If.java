package obliczenia;

public class If extends Instrukcja {
   private Wyrazenie warunek;
   private Instrukcja polecenie;

   public If(Wyrazenie warunek, Instrukcja polecenie) throws IllegalArgumentException {
      if (warunek == null || polecenie == null)
         throw new IllegalArgumentException("Null argument");
      this.warunek = warunek;
      this.polecenie = polecenie;
   }

   @Override
   public void wykonaj() {
      if (warunek.oblicz() != 0)
         polecenie.wykonaj();
   }
}
