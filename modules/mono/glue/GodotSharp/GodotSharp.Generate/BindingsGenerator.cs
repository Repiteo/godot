using System.Text;

namespace Godot.Generate;

internal static class BindingsGenerator
{
    public class BindingsBuilder
    {
        StringBuilder builder = new();
        int indent = 0;

        public BindingsBuilder BeginIndent()
        {
            AppendLine("{");
            indent++;
            return this;
        }
        public BindingsBuilder EndIndent()
        {
            indent--;
            AppendLine("}");
            return this;
        }
        public BindingsBuilder AppendLine()
        {
            builder.Append('\n');
            return this;
        }
        public BindingsBuilder AppendLine(string value)
        {
            builder.Append(new string(' ', 4 * indent)).Append(value).Append('\n');
            return this;
        }
        public override string ToString() => builder.ToString();
    }

    public static string GenerateFile(ExtensionApi.GodotClass godotClass)
    {
        BindingsBuilder file = new();

        file.AppendLine("using System;");
        file.AppendLine("using System.ComponentModel;");
        file.AppendLine("using System.Diagnostics;");
        file.AppendLine("using Godot.NativeInterop;");
        file.AppendLine();
        file.AppendLine("#nullable enable");
        file.AppendLine();
        file.AppendLine("namespace Godot;");
        file.AppendLine();
        file.AppendLine($"public partial class {godotClass.Name}");
        file.BeginIndent();
        file.AppendLine("// meme");
        file.EndIndent();

        return file.ToString();
    }
}
