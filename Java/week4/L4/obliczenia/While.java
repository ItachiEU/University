package obliczenia;

public class While extends Instrukcja {
      Wyrazenie warunek;
      Instrukcja polecenie;

      public While(Wyrazenie warunek, Instrukcja polecenie) throws IllegalArgumentException {
            if (warunek == null || polecenie == null)
                  throw new IllegalArgumentException("Null arguments");

            this.warunek = warunek;
            this.polecenie = polecenie;
      }

      @Override
      public void wykonaj() {
            while (warunek.oblicz() != 0) {
                  polecenie.wykonaj();
            }
      }

}
