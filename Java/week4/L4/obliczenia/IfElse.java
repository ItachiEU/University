package obliczenia;

public class IfElse extends Instrukcja {
   private Wyrazenie warunek;
   private Instrukcja polecenieTrue, polecenieFalse;

   public IfElse(Wyrazenie warunek, Instrukcja polecenieTrue, Instrukcja polecenieFalse)
         throws IllegalArgumentException {
      if (warunek == null || polecenieTrue == null || polecenieFalse == null)
         throw new IllegalArgumentException("Null argument");
      this.warunek = warunek;
      this.polecenieTrue = polecenieTrue;
      this.polecenieFalse = polecenieFalse;
   }

   @Override
   public void wykonaj() {
      if (warunek.oblicz() != 0)
         polecenieTrue.wykonaj();
      else
         polecenieFalse.wykonaj();
   }
}
