// TEMP SELFTEST R19 (macOS port only, not part of Codeware). A scripted class whose OnConstruct sets a field, so the Mac
// self-test (macos/MacR19.cpp) can check that the CClass::CreateInstance hook calls OnConstruct for scripted classes.
// CodewareMacSelfTest is a native class of the Mac plugin (macos/MacR13.cpp); Log prints a line to stderr.
public abstract native class CodewareMacSelfTest {
  public static native func Log(text: String) -> Void;
  public static native func PostKey(keyCode: Int32) -> Bool;
  public static native func PostKeys(keyCode: Int32, intervalMs: Int32, count: Int32) -> Bool;
  public static native func StopKeys() -> Void;
  public static native func DumpObject(object: ref<ISerializable>, maxDepth: Int32, arrayCap: Int32, label: String) -> Void;
  public static native func DumpScriptable(object: ref<IScriptable>, maxDepth: Int32, arrayCap: Int32, label: String) -> Void;
}

public class CodewareMacConstructTest extends IScriptable {
  public let constructed: Bool;

  public func OnConstruct() -> Void {
    CodewareMacSelfTest.Log("[selftest] R19 script OnConstruct enter");
    this.constructed = true;
    CodewareMacSelfTest.Log("[selftest] R19 script OnConstruct set the field");
  }
}
