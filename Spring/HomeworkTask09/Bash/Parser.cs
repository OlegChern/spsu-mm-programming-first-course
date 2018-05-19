using Bash.Commands;

namespace Bash
{
    class Parser
    {
        /*private static Parser instance;

        public static Parser Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new Parser();
                }

                return instance;
            }
        }

        private Parser() { }*/

        public static bool Parse(string str, out ICommand command)
        {
            command = null;

            if (str.Length == 0)
            {
                return false;
            }

            string[] splitted = str.Split(' ');

            if (splitted.Length == 0)
            {
                return false;
            }

            // todo
            if (str[0] == '&')
            {

            }

            string arg = Concatenate(1, splitted);

            switch (splitted[0])
            {
                case "echo":
                    {
                        command = new Echo(arg);
                        return true;
                    }
                case "exit":
                    {
                        command = new Exit();
                        return true;
                    }
                case "pwd":
                    {
                        command = new Pwd();
                        return true;
                    }
                case "cat":
                    {
                        command = new Cat(arg);
                        return true;
                    }
                case "wc":
                    {
                        command = new Wc(arg);
                        return true;
                    }
            }

            command = new SystemProcess(Concatenate(0, splitted));
            return true;
        }

        private static string Concatenate(int startIndex, string[] strs)
        {
            string result = string.Empty;

            for (int i = startIndex; i < strs.Length; i++)
            {
                result += strs[i];
            }

            return result;
        }
    }
}
