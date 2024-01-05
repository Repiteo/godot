using System;

namespace Godot.Generate;

internal record ExtensionApi
{
    public record GodotConstant
    {
        public string Name { get; set; } = string.Empty;
        public long Value { get; set; }
        public string Description { get; set; } = string.Empty;
    }

    public record GodotEnum
    {
        public string Name { get; set; } = string.Empty;
        public bool IsBitfield { get; set; }
        public GodotConstant[] Values { get; set; } = Array.Empty<GodotConstant>();
    }

    public record GodotArgument
    {
        public string Name { get; set; } = string.Empty;
        public string Type { get; set; } = string.Empty;
        public string Meta { get; set; } = string.Empty;
        public string DefaultValue { get; set; } = string.Empty;
    }

    public record GodotSignal
    {
        public string Name { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public GodotArgument[] Arguments { get; set; } = Array.Empty<GodotArgument>();
    }

    public record GodotProperty
    {
        public string Name { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public string Type { get; set; } = string.Empty;
        public string Setter { get; set; } = string.Empty;
        public string Getter { get; set; } = string.Empty;
    }

    public record GodotReturnValue
    {
        public string Type { get; set; } = string.Empty;
        public string Meta { get; set; } = string.Empty;
    }

    public record GodotMethod
    {
        public string Name { get; set; } = string.Empty;
        public bool IsConst { get; set; }
        public bool IsVararg { get; set; }
        public bool IsStatic { get; set; }
        public bool IsVirtual { get; set; }
        public ulong Hash { get; set; }
        public ulong[] HashCompatibility { get; set; } = Array.Empty<ulong>();
        public GodotReturnValue ReturnValue { get; set; } = new();
        public GodotArgument[] Arguments { get; set; } = Array.Empty<GodotArgument>();
    }

    public record GodotClass
    {
        public string Name { get; set; } = string.Empty;
        public string BriefDescription { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public bool IsRefcounted { get; set; }
        public bool IsInstantiable { get; set; }
        public string Inherits { get; set; } = string.Empty;
        public string ApiType { get; set; } = string.Empty;
        public GodotEnum[] Enums { get; set; } = Array.Empty<GodotEnum>();
        public GodotMethod[] Methods { get; set; } = Array.Empty<GodotMethod>();
        public GodotSignal[] Signals { get; set; } = Array.Empty<GodotSignal>();
        public GodotProperty[] Properties { get; set; } = Array.Empty<GodotProperty>();
    }

    public GodotConstant[] GlobalConstants { get; init; } = Array.Empty<GodotConstant>();
    public GodotEnum[] GlobalEnums { get; init; } = Array.Empty<GodotEnum>();
    public GodotClass[] Classes { get; init; } = Array.Empty<GodotClass>();
}
