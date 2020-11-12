package obliczenia;

public class Reszta extends Operator2Arg {
   public Reszta(Wyrazenie w1, Wyrazenie w2) {
      super(w1, w2);
   }

   public int oblicz() {
      return (arg1.oblicz() + arg2.oblicz()) % arg2.oblicz();
   }

   public String toString() {
      return "(" + arg1 + " % " + arg2 + ")";
   }
}
