using System;
using System.IO;
using System.Reflection;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace Godot.Generate;

internal class Program
{
    static string AssemblyDirectory = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location)!;
    static string GodotSharpPath = $"{AssemblyDirectory}/../../../../GodotSharp";
    static string GodotSharpEditorPath = $"{AssemblyDirectory}/../../../../GodotSharpEditor";

    // Replace with JsonNamingPolicy.SnakeCaseLower when we switch to .NET 8
    public class PascalToSnake : JsonNamingPolicy
    {
        public override string ConvertName(string name)
        {
            if (name.Length < 2)
            {
                return name;
            }
            var sb = new StringBuilder();
            sb.Append(char.ToLowerInvariant(name[0]));
            for (int i = 1; i < name.Length; ++i)
            {
                char c = name[i];
                if (char.IsUpper(c))
                {
                    sb.Append('_');
                    sb.Append(char.ToLowerInvariant(c));
                }
                else
                {
                    sb.Append(c);
                }
            }
            return sb.ToString();
        }
        public static JsonSerializerOptions Serializer = new() { PropertyNamingPolicy = new PascalToSnake() };
    }
    public static void Main(string[] args)
    {
        if (args == null || args.Length == 0)
        {
            throw new ArgumentException(null, nameof(args));
        }
        string apiFile = args[0];
        if (!File.Exists(apiFile))
        {
            throw new FileNotFoundException(null, nameof(apiFile));
        }
        ExtensionApi? extensionApi = JsonSerializer.Deserialize<ExtensionApi>(File.ReadAllText(apiFile), PascalToSnake.Serializer);
        ArgumentNullException.ThrowIfNull(extensionApi, nameof(extensionApi));
        //Console.WriteLine(AssemblyDirectory);
        //Console.WriteLine(extensionApi.Classes.Length);

        Parallel.ForEach(extensionApi.Classes, (godotClass, localSum, i) =>
        {
            string fileName = $"{AssemblyDirectory}/Generated/{godotClass.Name}.cs";
            File.WriteAllText(fileName, BindingsGenerator.GenerateFile(godotClass));
            Console.WriteLine($"Generated {fileName} ...");
        });
    }
}
