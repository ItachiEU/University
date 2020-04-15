import java.io.Serializable;

public class Trojkat extends Figury implements Serializable {
   double a;
   double b;
   double c;

   public Trojkat(double a, double b, double c) {
      this.a = a;
      this.b = b;
      this.c = c;
   }

   @Override
   public double pole() {
      double p = (a + b + c) / 2.0;
      return Math.sqrt(p * (p - a) * (p - b) * (p - c));
   }

   @Override
   public String toString() {
      String str = "Trojkat o polu: " + pole();
      return str;
   }
}