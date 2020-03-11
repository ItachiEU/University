using System;

namespace Zadanie1
{
    class IntStream
    {
        public int curr_int;
        public int limit;
        public IntStream()
        {
            curr_int = 0;
            limit = (1 << 32) - 1;
        }
        public virtual int next()
        {
            return ++curr_int;
        }
        public virtual bool eos()
        {
            if (curr_int == limit)
            {
                return true;
            }
            return false;
        }
        public virtual void reset()
        {
            curr_int = 0;
        }
    }
    class PrimeStream : IntStream
    {
        public PrimeStream()
        {
            curr_int = 1;
            limit = 2147483647;
        }
        private bool isPrime(int a)
        {
            int dzielniki = 0;
            for(int i=2; i*i < a; i++)
            {
                if (a % i == 0)
                    if(i*i == a)
                        dzielniki++;
                    else
                    {
                        dzielniki += 2;
                    }
            }
            return dzielniki == 0 ? true : false;
        }
        public override bool eos()
        {
            return curr_int == limit;
        }
        public override int next()
        {
            curr_int++;
            while (!this.isPrime(curr_int))
            {
                curr_int++;
            }
            return curr_int;
        }
        public override void reset()
        {
            curr_int = 1;
        }

    }
    class RandomStream : IntStream
    {
        Random rnd;
        public RandomStream()
        {
            curr_int = 0;
            limit = (1 << 32) - 1;
            rnd = new Random();
        }
        public override bool eos()
        {
            return false;
        }
        public override int next()
        {
            curr_int = rnd.Next();
            return curr_int;
        }
        public override void reset()
        {
            curr_int = 0;
        }
    }
    class RandomWordStream
    {
        public IntStream length;
        public RandomStream rnd;
        public RandomWordStream()
        {
            length = new IntStream();
            length.next();
            rnd = new RandomStream();
        }
        public string next()
        {
            string result = "";
            int temp = length.next();
            for (int i = 0; i < temp; i++)
            {
                result += (char)(rnd.next() % 26 + 97);
            }
            return result;
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            IntStream intS = new IntStream();
            Console.WriteLine("Int stream: ");
            Console.WriteLine(intS.next());
            Console.WriteLine(intS.next());
            Console.WriteLine(intS.next());
            Console.WriteLine(intS.eos());
            intS.reset();
            Console.WriteLine(intS.next());
            Console.WriteLine("Prime stream: ");
            PrimeStream primeS = new PrimeStream();
            Console.WriteLine(primeS.next());
            Console.WriteLine(primeS.next());
            Console.WriteLine(primeS.next());
            Console.WriteLine(primeS.eos());
            primeS.reset();
            Console.WriteLine(primeS.next());
            RandomStream randomS = new RandomStream();
            Console.WriteLine("Random stream: ");
            Console.WriteLine(randomS.next());
            Console.WriteLine(randomS.next());
            Console.WriteLine(randomS.next());
            Console.WriteLine(randomS.eos());
            primeS.reset();
            Console.WriteLine(randomS.next());
            RandomWordStream rws = new RandomWordStream();
            Console.WriteLine("Random Word Stream: ");
            Console.WriteLine(rws.next());
            Console.WriteLine(rws.next());
            Console.WriteLine(rws.next());
            Console.WriteLine(rws.next());
        }
    }
}
