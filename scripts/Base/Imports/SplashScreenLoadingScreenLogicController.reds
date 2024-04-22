public native class SplashScreenLoadingScreenLogicController extends ILoadingLogicController {
  native let logoTrainWBBink: ResourceAsyncRef; // raRef<Bink>
  native let logoTrainNamcoBink: ResourceAsyncRef; // raRef<Bink>
  native let logoTrainStadiaBink: ResourceAsyncRef; // raRef<Bink>
  native let logoTrainNoRTXBink: ResourceAsyncRef; // raRef<Bink>
  native let logoTrainRTXBink: ResourceAsyncRef; // raRef<Bink>
  native let introMessageBink: inkLocalizedBink;
  native let trailerBink: ResourceAsyncRef; // raRef<Bink>
  native let logosTrainAnimation: CName;
  native let localizedMessageAnimation: CName;
  native let gameIntroAnimation: CName;
  native let longLogosTrainAnimation: CName;
  native let stopIntroAudioEventName: CName;
  native let afterSkipAnimation: CName;
  native let videoPlayer: inkVideoRef;
  native let skipButtonPanel: inkCompoundRef;
}
