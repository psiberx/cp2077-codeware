@addMethod(GameInstance)
public static func GetSystemRequestsHandler() -> wref<inkISystemRequestsHandler> {
    return new inkMenuScenario().GetSystemRequestsHandler();
}
