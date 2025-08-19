public native class SplashScreenLoadingScreenLogicController extends ILoadingLogicController {
  public native let logoTrainWBBink: ResourceAsyncRef; // raRef<Bink>
  public native let logoTrainNamcoBink: ResourceAsyncRef; // raRef<Bink>
  public native let logoTrainStadiaBink: ResourceAsyncRef; // raRef<Bink>
  public native let logoTrainNoRTXBink: ResourceAsyncRef; // raRef<Bink>
  public native let logoTrainRTXBink: ResourceAsyncRef; // raRef<Bink>
  public native let introMessageBink: inkLocalizedBink;
  public native let trailerBink: ResourceAsyncRef; // raRef<Bink>
  public native let logosTrainAnimation: CName;
  public native let localizedMessageAnimation: CName;
  public native let gameIntroAnimation: CName;
  public native let longLogosTrainAnimation: CName;
  public native let stopIntroAudioEventName: CName;
  public native let afterSkipAnimation: CName;
  public native let videoPlayer: inkVideoRef;
  public native let skipButtonPanel: inkCompoundRef;
}
