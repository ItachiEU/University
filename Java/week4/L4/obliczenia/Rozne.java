package obliczenia;

public class Rozne extends Operator2Arg {
   public Rozne(Wyrazenie w1, Wyrazenie w2) {
      super(w1, w2);
   }

   public int oblicz() {
      return arg1.oblicz() == arg2.oblicz() ? 0 : 1;
   }

   public String toString() {
      return "(" + arg1 + " != " + arg2 + ")";
   }
}
