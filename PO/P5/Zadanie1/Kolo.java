
public class Kolo extends Figury {
   double r;

   public Kolo(double r) {
      this.r = r;
   }

   @Override
   public double pole() {
      return r * r * 3.14159265359;
   }

   @Override
   public String toString() {
      String str = "Kolo o polu: " + pole();
      return str;
   }
}