import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public abstract class Figury implements Comparable<Figury> {
   public static void main(String[] args) {
      List<Figury> figury = new ArrayList<Figury>();
      figury.add(new Kwadrat(6.0));
      figury.add(new Prostokat(3.0, 5.0));
      figury.add(new Kolo(5.0));
      figury.add(new Trojkat(3.0, 4.0, 5.0));
      Collections.sort(figury);
      for (Figury figura : figury) {
         System.out.println(figura);
      }
   }

   public abstract double pole();

   @Override
   public int compareTo(Figury o) {
      return (int) Math.signum(pole() - o.pole());
   }
}