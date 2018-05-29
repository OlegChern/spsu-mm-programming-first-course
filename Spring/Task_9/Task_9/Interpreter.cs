using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Threading;

namespace Task_9
{
    class Interpreter : IDisposable
    {
        private bool IsExit { get; set; }
        private Dictionary<string, object> Variables { get; }
        private string TmpDirPath { get; }

        public Interpreter()
        {
            IsExit = false;
            Variables = new Dictionary<string, object>();
            TmpDirPath = Directory.GetCurrentDirectory() + "\\Task9tmp";
            Directory.CreateDirectory(TmpDirPath);
        }

        public void Start()
        {
            Console.WriteLine("You can use:\n" +
                              "echo - display the argument (s)\n" +
                              "exit - exit the interpreter\n" +
                              "pwd - display the current working directory\n" +
                              "cat [FILENAME] - show the contents of a file on the screen\n" +
                              "wc [FILENAME] - show on the screen the number of lines, words and bytes in the file\n\n" +
                              "If your command is not recognized, an attempt will be made with cmd\n\n" +
                              "also you can use:\n" +
                              "operator $ - assignment and use of local session variables\n" +
                              "operator | - pipelining commands. The result of executing one command becomes an input for the other\n");
            do
            {
                Thread.Sleep(150);
                Console.Write("{0}>", Dns.GetHostName());
                string inputStr = Console.ReadLine();
                if (inputStr == "exit")
                {
                    IsExit = true;
                }
                else
                {
                    try
                    {
                        ExecuteInstructions(Parser.Parse(inputStr));
                    }


                    catch (VariableDefException e)
                    {
                        Console.WriteLine(e.Message);
                    }

                    catch (InvalidOperationException e)
                    {
                    }
                    catch (Exception e)
                    {
                        Console.Write(e.Message);
                    }
                }
            } while (!IsExit);
        }

        private void ExecuteInstructions(Instruction instructions)
        {
            switch (instructions.Type)
            {
                case InstructionType.VariableDef:
                {
                    Variables.Add(instructions.VariableName, instructions.VariableValue);
                    break;
                }
                case InstructionType.Command:
                {
                    for (int i = 0; i < instructions.Commands.Count - 1; ++i)
                    {
                        string tmpPath = ExecuteCommand(instructions.Commands[i], i);
                        instructions.Commands[i + 1].Arguments.Add(tmpPath);
                    }


                    if (instructions.Commands.Last().Type == CommandType.CmdCommand)
                    {
                        ExecuteCommand(instructions.Commands.Last(), instructions.Commands.Count - 1);
                    }
                    else
                    {
                        string lastTmpPath =
                            ExecuteCommand(instructions.Commands.Last(), instructions.Commands.Count - 1);

                        using (var reader = File.OpenText(lastTmpPath))
                        {
                            Console.WriteLine(reader.ReadToEnd());
                        }
                    }

                    foreach (var filePath in Directory.EnumerateFiles(TmpDirPath))
                    {
                        File.Delete(filePath);
                    }

                    break;
                }
            }
        }

        private string ExecuteCommand(Command command, int numberOfCommand)
        {
            switch (command.Type)
            {
                case CommandType.Pwd:
                {
                    string currentDirectory = Directory.GetCurrentDirectory();
                    string tmpPwdFile = TmpDirPath + "\\tmpCommandResult" + numberOfCommand + ".txt";
                    using (var writer = File.CreateText(tmpPwdFile))
                    {
                        writer.WriteLine(currentDirectory);
                        foreach (var fileName in Directory.EnumerateFileSystemEntries(currentDirectory))
                        {
                            writer.WriteLine(fileName);
                        }

                        return tmpPwdFile;
                    }
                }


                case CommandType.Echo:
                {
                    string tmpEchoFile = TmpDirPath + "\\tmpCommandResult" + numberOfCommand + ".txt";
                    using (var writer = File.CreateText(tmpEchoFile))
                    {
                        foreach (var arg in command.Arguments)
                        {
                            if (arg[0] == '$' && Variables.ContainsKey(arg.Remove(0, 1)))
                            {
                                writer.WriteLine(Variables[arg.Remove(0, 1)]);
                            }
                            else
                            {
                                writer.WriteLine(arg);
                            }
                        }
                    }

                    return tmpEchoFile;
                }

                case CommandType.Cat:
                {
                    string tmpCatFile = TmpDirPath + "\\tmpCommandResult" + numberOfCommand + ".txt";
                    File.Copy(command.Arguments[0], tmpCatFile);
                    return tmpCatFile;
                }

                case CommandType.Wc:
                {
                    string tmpWcFile = TmpDirPath + "\\tmpCommandResult" + numberOfCommand + ".txt";
                    int linesAmount = File.ReadAllLines(command.Arguments[0]).Length;
                    int wordsAmount = File.ReadAllText(command.Arguments[0]).Length;
                    int bytesAmount = File.ReadAllBytes(command.Arguments[0]).Length;
                    using (var writer = File.CreateText(tmpWcFile))
                    {
                        writer.WriteLine("In {0} {1} lines", command.Arguments[0], linesAmount);
                        writer.WriteLine("In {0} {1} words", command.Arguments[0], wordsAmount);
                        writer.WriteLine("In {0} {1} bytes", command.Arguments[0], bytesAmount);
                    }

                    return tmpWcFile;
                }

                case CommandType.CmdCommand:
                {
                    var process = new Process
                    {
                        StartInfo = new ProcessStartInfo
                        {
                            FileName = "cmd.exe",
                            RedirectStandardInput = true,
                            UseShellExecute = false,
                            Arguments = "/C " + command.Arguments[0]
                        }
                    };
                    process.Start();
                    return "";
                }
                default:
                {
                    throw new CommandException("Incorrect command work");
                }
            }
        }

        public void Dispose()
        {
            Directory.Delete(TmpDirPath);
        }
    }
}
