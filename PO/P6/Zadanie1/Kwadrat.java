import java.io.Serializable;

public class Kwadrat extends Figury implements Serializable {
   double a;

   public Kwadrat(double a) {
      this.a = a;
   }

   @Override
   public double pole() {
      return a * a;
   }

   @Override
   public String toString() {
      String str = "Kwadrat o polu: " + pole();
      return str;
   }
}