using System;
using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using JetBrains.Annotations;
using Task9.Tokenization;

namespace Task9.Parsing
{
    public static class Executer
    {
        [Pure]
        public static object Echo(IEnumerable<object> args)
        {
            return args.Aggregate(new StringBuilder(),
                (builder, arg) => builder.Append(arg is Variable v ? v.Compute() : arg),
                builder => builder.ToString());
        }

        [Pure]
        public static object Exit()
        {
            throw new ExecutionFinishedException();
        }

        [Pure]
        public static object Pwd(IEnumerable<object> args, Context context)
        {
            if (args.Any())
            {
                throw new SyntaxErrorException("PWD cannot accept any arguments");
            }

            var result = new StringBuilder();

            result.Append(context.Path);

            Directory.EnumerateDirectories(context.Path)
                .ForEach(dir => result.Append($"{Environment.NewLine}\t<dir> {dir}"));
            Directory.EnumerateFiles(context.Path)
                .ForEach(file => result.Append($"{Environment.NewLine}\t{file}"));

            return result.ToString();
        }

        [Pure]
        public static object Cat(IEnumerable<object> args, Context context)
        {
            string result = null;
            foreach (var arg in args)
            {
                if (result != null)
                {
                    throw new InvalidSyntaxException("cat expected only one argument");
                }

                Stream stream = null;
                StreamReader reader = null;
                try
                {
                    stream = new FileStream(arg.ToString(), FileMode.Open);
                    reader = new StreamReader(stream);
                    result = reader.ReadToEnd();
                }
                catch (IOException)
                {
                    return "Could not access file";
                }
                finally
                {
                    stream?.Dispose();
                    reader?.Dispose();
                }
            }

            if (result != null)
            {
                return result;
            }

            throw new InvalidSyntaxException("cat expected at least one argument");
        }

        public static object Wc(IEnumerable<object> args, Context context)
        {
            string result = null;

            foreach (var arg in args)
            {
                if (result != null)
                {
                    throw new InvalidSyntaxException("cat expected only one argument");
                }

                string fullPath = Path.Combine(context.Path, arg.ToString());
                
                if (!File.Exists(fullPath))
                {
                    return "No such file";
                }

                try
                {
                    // What a costly operation, huh?
                    // I don't care
                    result = $"{arg}:{Environment.NewLine}" +
                             $"\t{File.ReadAllLines(fullPath).Length} lines{Environment.NewLine}" +
                             $"\t{GetWordsCount(File.ReadAllText(fullPath))} words{Environment.NewLine}" +
                             $"\t{File.ReadAllBytes(fullPath).Length} bytes{Environment.NewLine}";
                }
                catch (IOException)
                {
                    Console.WriteLine("Could not access file");
                }
            }

            if (result != null)
            {
                return result;
            }

            throw new InvalidSyntaxException("wc expected at least one argument");
        }

        [Pure]
        static int GetWordsCount(string text)
        {
            int wordCount = 0;
            int index = 0;

            while (index < text.Length)
            {
                // check if current char is part of a word
                while (index < text.Length && !char.IsWhiteSpace(text[index]))
                    index++;

                wordCount++;

                // skip whitespace until next word
                while (index < text.Length && char.IsWhiteSpace(text[index]))
                    index++;
            }

            return wordCount;
        }
    }
}
