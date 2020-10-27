package figury;

public interface Figura {
   void translacja(Wektor v);

   void obrot(Punkt p, double kat);

   void odbij(Prosta l);
}
