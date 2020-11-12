package obliczenia;

public class DoWhile extends Instrukcja {
   Wyrazenie warunek;
   Instrukcja polecenie;

   public DoWhile(Wyrazenie warunek, Instrukcja polecenie) throws IllegalArgumentException {
      if (warunek == null || polecenie == null)
         throw new IllegalArgumentException("Null arguments");

      this.warunek = warunek;
      this.polecenie = polecenie;
   }

   @Override
   public void wykonaj() {
      do {
         polecenie.wykonaj();
      } while (warunek.oblicz() != 0);
   }

}
