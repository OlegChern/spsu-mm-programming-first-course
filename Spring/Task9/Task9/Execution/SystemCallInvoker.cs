using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;

namespace Task9.Execution
{
    static class SystemCallInvoker
    {
        public static object Execute(string fullName, object[] args)
        {
            var names = new List<string>(fullName.Split(new[] {'.'}, StringSplitOptions.None));
            if (names.Count <= 1)
            {
                throw new TargetInvocationException(
                    $"Could not invoke '{fullName}': it should contain booth class name and method name sebarated by dot.",
                    null);
            }

            return FindAndInvoke(names, args);
        }

        static object FindAndInvoke(IList<string> names, object[] args)
        {
            // Finding bugs related with closures in linq was damn painful
            string mainName = names[0];
            names.RemoveAt(0);

            var types =
                from assembley in AppDomain.CurrentDomain.GetAssemblies()
                from type in assembley.GetExportedTypes()
                where type.Name == mainName
                select type;

            while (names.Count > 1)
            {
                string subtypeName = names[0];
                names.RemoveAt(0);

                types =
                    from type in types
                    from subtype in type.GetNestedTypes()
                    where subtype.Name == subtypeName
                    select subtype;
            }

            string methodName = names[0];
            var methods = new List<MethodInfo>(
                from type in types
                from method in type.GetMethods(BindingFlags.Public | BindingFlags.Static)
                where method.Name == methodName
                let parameters = method.GetParameters()
                where parameters.Length == args.Length
                where parameters
                    .Zip(args, (info, obj) => new {info, obj})
                    .All(pair => pair.info.ParameterType == pair.obj.GetType())
                select method
            );

            if (methods.Count == 0)
            {
                return "No such method found";
            }

            if (methods.Count > 1)
            {
                return methods.Aggregate("Ambiguous match: ", (previous, info) => previous + info.Name + " ");
            }

            object result;
            try
            {
                result = methods[0].Invoke(null, args);
            }
            catch (TargetInvocationException e)
            {
                return $"Could not invoke: {e.InnerException}";
            }

            return result;
        }
    }
}
