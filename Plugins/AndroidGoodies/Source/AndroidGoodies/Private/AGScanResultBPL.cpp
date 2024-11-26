#include "AGScanResultBPL.h"
#if PLATFORM_ANDROID
#include "Android/Utils/AGMethodCallUtils.h"

void UAGScanResultBPL::Init(jobject ScanResultObject)
{
	BSSID = AGMethodCallUtils::CallStringMethod(ScanResultObject, "getBSSID", "()Ljava/lang/String;");
	SSID = AGMethodCallUtils::CallStringMethod(ScanResultObject, "getSSID", "()Ljava/lang/String;");
	Capabilities = AGMethodCallUtils::CallStringMethod(ScanResultObject, "getCapabilities", "()Ljava/lang/String;");
	OperatorFriendlyName = AGMethodCallUtils::CallStringMethod(ScanResultObject, "getOperatorFriendlyName", "()Ljava/lang/String;");
	VenueName = AGMethodCallUtils::CallStringMethod(ScanResultObject, "getVenueName", "()Ljava/lang/String;");
	CenterFreq0 = AGMethodCallUtils::CallIntMethod(ScanResultObject, "getCenterFreq0", "()I");
	CenterFreq1 = AGMethodCallUtils::CallIntMethod(ScanResultObject, "getCenterFreq1", "()I");
	ChannelWidth = AGMethodCallUtils::CallIntMethod(ScanResultObject, "getChannelWidth", "()I");
	Frequency = AGMethodCallUtils::CallIntMethod(ScanResultObject, "getFrequency", "()I");
	Level = AGMethodCallUtils::CallIntMethod(ScanResultObject, "getLevel", "()I");
	Timestamp = AGMethodCallUtils::CallLongMethod(ScanResultObject, "getTimestamp", "()J");
}
#endif