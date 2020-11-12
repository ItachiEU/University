package obliczenia;

public class Logarytm extends Operator2Arg {
   public Logarytm(Wyrazenie w1, Wyrazenie w2) {
      super(w1, w2);
   }

   public int oblicz() {
      return (int) (Math.log(arg1.oblicz()) / Math.log(arg2.oblicz()));
   }

   public String toString() {
      return "(logarytm z " + arg1 + " o podstawie " + arg2 + ")";
   }
}