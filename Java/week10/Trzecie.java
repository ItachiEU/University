import java.util.HashMap;
import java.util.Map;

public class Trzecie {

   enum Pierwiastki {
      H(1, "Wodór", 1.008), He(2, "Hel", 4.003), Li(3, "Lit", 6.941), Be(4, "Beryl", 9.0121831), B(5, "Bor", 10.806),
      C(6, "Węgiel", 12.010), N(7, "Azot", 14.00643), O(8, "Tlen", 15.999), F(9, "Fluor", 18.9984032),
      Ne(10, "Neon", 20.1797), Na(11, "Sód", 22.989769), Mg(12, "Magnez", 24.305), Al(13, "Glin", 26.981539),
      Si(14, "Krzem", 28.0855), P(15, "Fosfor", 30.973762), S(16, "Siarka", 32.066), Cl(17, "Chlor", 35.4527),
      Ar(18, "Argon", 39.948);

      private static class Holder {
         static Map<Integer, Pierwiastki> map = new HashMap<Integer, Pierwiastki>();
      }

      private final int atomicNumber;
      private final String fullName;
      private final double atomicMass;

      private Pierwiastki(int atomicNumber, String fullName, double atomicMass) {
         this.atomicNumber = atomicNumber;
         this.fullName = fullName;
         this.atomicMass = atomicMass;
         Holder.map.put(atomicNumber, this);
      }

      public static Pierwiastki forAtomicNumber(int atomicNumber) {
         return Holder.map.get(atomicNumber);
      }

      public int getAtomicNumber() {
         return atomicNumber;
      }

      public String getFullName() {
         return fullName;
      }

      public double getAtomicMass() {
         return atomicMass;
      }

      public String toString() {
         return "[ " + atomicNumber + " " + fullName + " " + atomicMass + " ]";
      }
   }

   public static void main(String[] args) {
      for (Pierwiastki element : Pierwiastki.values()) {
         System.out.println(element);
      }
   }
}