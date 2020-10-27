import figury.*;

public class Main {
   public static void main(String args[]) {
      // Trojkat t = new Trojkat(new Punkt(0, 0), new Punkt(1, 1), new Punkt(2, 2));
      // Niepoprawny input do Trojkata ^^^^^

      Odcinek o = new Odcinek(new Punkt(3, -3), new Punkt(1, 3));
      o.odbij(new Prosta(-1, 2, -1));

      System.out.println(
            "(" + o.start.getX() + ", " + o.start.getY() + ") <-> (" + o.koniec.getX() + ", " + o.koniec.getY() + ")");

      o.translacja(new Wektor(1, 1));
      System.out.println(o.start.getX() + " " + o.start.getY() + " -> " + o.koniec.getX() + " " + o.koniec.getY());

      Trojkat t = new Trojkat(new Punkt(0, 1), new Punkt(4, 1), new Punkt(3, 5));
      t.odbij(new Prosta(0, 1, 0));
      System.out.println(t.a.getX() + " " + t.a.getY() + " -> " + t.b.getX() + " " + t.b.getY() + " -> " + t.c.getX()
            + " " + t.c.getY());

      t.obrot(new Punkt(1, 1), 2.0);
      System.out.println(t.a.getX() + " " + t.a.getY() + " -> " + t.b.getX() + " " + t.b.getY() + " -> " + t.c.getX()
            + " " + t.c.getY());

      Prosta p1 = new Prosta(5, 1, 14), p2 = new Prosta(-0.2, 1, -12);
      if (Prosta.prostopadle(p1, p2))
         System.out.println("Są prostopadłe");
      else
         System.out.println("Nie są prostopadłe");

      Punkt p3 = Prosta.przeciecie(p1, p2);
      System.out.println("Punkt przeciecia p1 i p2: (" + p3.getX() + ", " + p3.getY() + ")");

   }
}