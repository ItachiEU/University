package obliczenia;

public class WiekszeRowne extends Operator2Arg {
   public WiekszeRowne(Wyrazenie w1, Wyrazenie w2) {
      super(w1, w2);
   }

   public int oblicz() {
      return arg1.oblicz() >= arg2.oblicz() ? 1 : 0;
   }

   public String toString() {
      return "(" + arg1 + " >= " + arg2 + ")";
   }
}
