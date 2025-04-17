@addField(inkISystemRequestsHandler)
native let SavesForSaveReady: inkSystemRequesResult;

@addField(inkISystemRequestsHandler)
native let SavesForLoadReady: inkSystemRequesResult;

@addField(inkISystemRequestsHandler)
native let SaveMetadataReady: inkSaveMetadataRequestResult;

@addField(inkISystemRequestsHandler)
native let GogLoginStatusChanged: inkOnGogLoginStatusChangedResult;

@addField(inkISystemRequestsHandler)
native let SaveDeleted: inkDeleteRequestResult;

@addField(inkISystemRequestsHandler)
native let SaveTransferUpdate: inkSaveTransferRequestUpdate;

@addField(inkISystemRequestsHandler)
native let ServersSearchResult: inkSystemServerRequesResult;

@addField(inkISystemRequestsHandler)
native let AdditionalContentPurchaseResult: inkAdditionalContentPurchaseCallback;

@addField(inkISystemRequestsHandler)
native let AdditionalContentInstallationRequestResult: inkAdditionalContentInstallRequestedCallback;

@addField(inkISystemRequestsHandler)
native let AdditionalContentInstallationResult: inkAdditionalContentInstalledCallback;

@addField(inkISystemRequestsHandler)
native let AdditionalContentStatusUpdateResult: inkAdditionalContentStatusUpdateCallback;

@addField(inkISystemRequestsHandler)
native let AdditionalContentDataReloadProgressCallback: inkAdditionalContentDataReloadProgress;

@addField(inkISystemRequestsHandler)
native let ToggleBreachingCallback: inkToggleBreachingCallback;

@addField(inkISystemRequestsHandler)
native let UserChanged: inkUserIdResult;

@addField(inkISystemRequestsHandler)
native let UserIdResult: inkUserIdResult;

@addField(inkISystemRequestsHandler)
native let TrialVersionRemainingTimeUpdated: inkTrialVersionRemainingTimeUpdate;

@addField(inkISystemRequestsHandler)
native let BoughtFullGame: inkTrialOnBuyFullGame;

@addField(inkISystemRequestsHandler)
native let CloudSavesQueryStatusChanged: inkCloudSavesQueryStatusChange;

@addField(inkISystemRequestsHandler)
native let CloudSaveUploadFinish: inkCloudSaveUploadFinish;

@addField(inkISystemRequestsHandler)
native let ScreenshotsForLoadReady: inkGameScreenshotsRequestResult;

@addField(inkISystemRequestsHandler)
native let FavoritesLoadedReady: inkFavoriteLoadResult;

@addField(inkISystemRequestsHandler)
native let DeleteSreenshotComplete: inkDeleteScreenshotResult;

@addField(inkISystemRequestsHandler)
native let MarketingConsentPopupTypeResult: inkMarketingConsentPopupTypeResult;
