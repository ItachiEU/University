using System;
using System.Collections.Generic;


namespace zadanie4
{
    public class ListaLeniwa
    {
        public List<int> list;
        public ListaLeniwa()
        {
            list = new List<int>();
        }
        public int size()
        {
            return list.Count;
        }
        public virtual int element(int index)
        {
            if(index < this.size())
            {
                int count = 1;
                foreach(int var in list)
                {
                    if (count == index)
                        return var;
                    count++;
                }
            }
            else
            {
                Random rnd = new Random();
                int brakuje = index - this.size();
                int item = 0;
                while(brakuje > 0)
                {
                    item = rnd.Next(200);
                    list.Add(item);
                    brakuje--;
                }
                return item;
            }
            return -1;
        }
        public void dodaj(int a)
        {
            list.Add(a);
        }
    }
    public class Pierwsze : ListaLeniwa
    {
        int last;
        public Pierwsze()
        {
            list = new List<int>();
            list.Add(2);
            last = 2;
        }
        public bool isPrime(int a)
        {
            int dzielniki = 0;
            for (int i = 2; i * i <= a; i++)
            {
                if (a % i == 0)
                {
                    if (i * i == a)
                        dzielniki++;
                    else
                        dzielniki += 2;
                }
            }
            return dzielniki == 0 ? true : false;
        }
        public override int element(int index)
        {
            if (index < this.size())
            {
                int count = 1;
                foreach (int var in list)
                {
                    if (count == index)
                        return var;
                    count++;
                }
            }
            else
            {
                int brakuje = index - this.size();
                int item = 0;
                while (brakuje > 0)
                {
                    item = last + 1;
                    while (!this.isPrime(item))
                    {
                        item++;
                    }
                    list.Add(item);
                    last = item;
                    brakuje--;
                }
                return item;
            }
            return -1;
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            ListaLeniwa lst = new ListaLeniwa();
            Console.WriteLine("Lista Leniwa: ");
            Console.WriteLine(lst.size());
            lst.element(20);
            Console.WriteLine(lst.size());
            Console.WriteLine("Pierwsze: ");
            Pierwsze primes = new Pierwsze();
            Console.WriteLine(primes.element(3));
            Console.WriteLine(primes.element(2));
            Console.WriteLine(primes.element(5));
            Console.WriteLine(primes.size());
        }
    }
}
