public abstract class Codeware {
    public static func Version() -> String = "1.0.0"

    public static func Require(version: String) ->  Bool {
        return Equals(version, Codeware.Version()); // TODO: Parse version
    }
}