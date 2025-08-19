@addField(inkISystemRequestsHandler)
public native let SavesForSaveReady: inkSystemRequesResult;

@addField(inkISystemRequestsHandler)
public native let SavesForLoadReady: inkSystemRequesResult;

@addField(inkISystemRequestsHandler)
public native let SaveMetadataReady: inkSaveMetadataRequestResult;

@addField(inkISystemRequestsHandler)
public native let GogLoginStatusChanged: inkOnGogLoginStatusChangedResult;

@addField(inkISystemRequestsHandler)
public native let SaveDeleted: inkDeleteRequestResult;

@addField(inkISystemRequestsHandler)
public native let SaveTransferUpdate: inkSaveTransferRequestUpdate;

@addField(inkISystemRequestsHandler)
public native let ServersSearchResult: inkSystemServerRequesResult;

@addField(inkISystemRequestsHandler)
public native let AdditionalContentPurchaseResult: inkAdditionalContentPurchaseCallback;

@addField(inkISystemRequestsHandler)
public native let AdditionalContentInstallationRequestResult: inkAdditionalContentInstallRequestedCallback;

@addField(inkISystemRequestsHandler)
public native let AdditionalContentInstallationResult: inkAdditionalContentInstalledCallback;

@addField(inkISystemRequestsHandler)
public native let AdditionalContentStatusUpdateResult: inkAdditionalContentStatusUpdateCallback;

@addField(inkISystemRequestsHandler)
public native let AdditionalContentDataReloadProgressCallback: inkAdditionalContentDataReloadProgress;

@addField(inkISystemRequestsHandler)
public native let ToggleBreachingCallback: inkToggleBreachingCallback;

@addField(inkISystemRequestsHandler)
public native let UserChanged: inkUserIdResult;

@addField(inkISystemRequestsHandler)
public native let UserIdResult: inkUserIdResult;

@addField(inkISystemRequestsHandler)
public native let TrialVersionRemainingTimeUpdated: inkTrialVersionRemainingTimeUpdate;

@addField(inkISystemRequestsHandler)
public native let BoughtFullGame: inkTrialOnBuyFullGame;

@addField(inkISystemRequestsHandler)
public native let CloudSavesQueryStatusChanged: inkCloudSavesQueryStatusChange;

@addField(inkISystemRequestsHandler)
public native let CloudSaveUploadFinish: inkCloudSaveUploadFinish;

@addField(inkISystemRequestsHandler)
public native let ScreenshotsForLoadReady: inkGameScreenshotsRequestResult;

@addField(inkISystemRequestsHandler)
public native let FavoritesLoadedReady: inkFavoriteLoadResult;

@addField(inkISystemRequestsHandler)
public native let DeleteSreenshotComplete: inkDeleteScreenshotResult;

@addField(inkISystemRequestsHandler)
public native let MarketingConsentPopupTypeResult: inkMarketingConsentPopupTypeResult;
