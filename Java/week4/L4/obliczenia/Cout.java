package obliczenia;

public class Cout extends Instrukcja {
   private int val;

   public Cout(int val) {
      this.val = val;
   }

   @Override
   public void wykonaj() {
      System.out.println(val);
   }
}
