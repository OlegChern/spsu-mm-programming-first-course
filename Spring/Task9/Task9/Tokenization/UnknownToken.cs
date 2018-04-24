using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Task9.Parsing;

namespace Task9.Tokenization
{
    public sealed class UnknownToken : Token
    {
        public override TokenType TokenType => TokenType.Unknown;
        public override object Value => Representation;

        public string Representation { get; }

        public override object Execute(IEnumerable<object> args, Context context, ExecutionType executionType)
        {
            var argsArray = args.ToArray();
            if (executionType == ExecutionType.Argument)
            {
                if (argsArray.Any())
                {
                    throw new InvalidSyntaxException(
                        $"Unknown token '{Representation}' is used as argument but was given arguments itself");
                }

                return Representation;
            }
            
            // Call system methods
            var methodsQuery =
                from assembly in AppDomain.CurrentDomain.GetAssemblies()
                from type in assembly.GetExportedTypes()
                from method in type.GetMethods()
                where method.IsStatic && method.GetParameters().Length == argsArray.Length
                select method;
            
            var methodsArray = methodsQuery.ToList();

            if (methodsArray.Count > 1)
            {
                return "Ambiguous match";
            }

            object result;
            try
            {
                result = methodsArray[0].Invoke(null, argsArray);
            }
            catch (ArgumentException)
            {
                return "Could not invoke :(";
            }

            return result;
        }

        public UnknownToken(string representation)
        {
            Representation = representation;
        }
    }
}
