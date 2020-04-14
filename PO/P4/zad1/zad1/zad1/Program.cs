using System;
using System.Text;
using System.Linq;
using System.Collections;               
using System.Collections.Generic;

namespace zad1
{
    class Program
    {
        static void Main(string[] args)
        {
            LazyList list = new LazyList();
            int test = list[17];
            int count = 0;
            foreach(int liczba in list)
            {
                Console.WriteLine(liczba);
                count++;
            }
            Console.WriteLine("====================");
            Console.WriteLine(list[3]);
            Console.WriteLine(list[5]);

        }
    }

    interface MyList
    {
        int Element(int i);
        int Size();
    }

    public class LazyListEnum : IEnumerator
    {
        List<int> int_list;
        int index;

        public LazyListEnum(List<int> int_list)
        {
            this.int_list = int_list;
            index = -1;
        }

        public bool MoveNext()
        {
            index++;
            return (index < int_list.Count);
        }

        public void Reset()
        {
            index = -1;
        }

        public int Current
        {
            get
            {
                return int_list[index];
            }
        }

        object IEnumerator.Current
        {
            get
            {
                return Current;
            }
        }
    }
    class LazyList : MyList, IEnumerable
    {
        private int licz_elem;
        List<int> int_list;
        Random random;

        public int Size()
        {
            return this.licz_elem;
        }
        public LazyList()
        {
            this.licz_elem = 0;
            this.int_list = new List<int>();
            this.random = new Random();
        }

        public int Element(int i)
        {
            if (i > this.licz_elem)
            {
                int brakuje = i - this.licz_elem;
                this.FillList(brakuje);
                this.licz_elem = i;
            }
            return this.int_list[i - 1];
        }
        void FillList(int ile)
        {
            while( ile > 0)
            {
                this.int_list.Add(random.Next(-Int32.MaxValue, Int32.MaxValue));
                ile--;
            }
        }

        public int this[int index]
        {
            get
            {
                return Element(index + 1);
            }
        }
        public override string ToString()
        {
            if (licz_elem == 0)
                return null;
            return int_list[licz_elem - 1].ToString();
        }

        public IEnumerator GetEnumerator()
        {
            return new LazyListEnum(int_list);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new LazyListEnum(int_list);
        }
    }
    class Prime: MyList
    {
        private int licz_elem;
        List<int> primesL;
        int dummy;
        private bool IsPrime(int test)
        {
            for (int i = 2; i < test; i++)
            {
                if (test % i == 0)
                    return false;
            }
            return true;
        }
        public int Size()
        {
            return this.licz_elem;
        }
        public Prime()
        {
            this.primesL = new List<int>();
            this.dummy = 2;
        }
        void FillList(int ile)
        {
            while(ile > 0)
            {
                if (IsPrime(dummy) == true)
                {
                    this.primesL.Add(this.dummy);
                    ile--;
                }
                this.dummy++;
            }
        }
        public int Element(int i)
        {
            if (i > licz_elem)
            {
                int brakuje = i - licz_elem;
                this.FillList(brakuje);
                licz_elem = i;
            }
            return this.primesL[i - 1];
        }
    }
}