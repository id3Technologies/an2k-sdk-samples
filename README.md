# An2K SDK samples

## Introduction

### Content

This repository contains basic samples for the **id3 Technologies** An2K SDK.

Going through those samples before trying to integrate it in your applications is strongly recommended.

### A word on version format

The version of this repository is made of 4 digits:
* The first 3 correspond to the version of the An2K SDK that is currently supported in this repository.
* The forth digit contains updates dedicated to the samples (evolutions, bug fixes, doc, etc).

This strategy is employed to ensure version consistency among the various supported languages. When updating the An2K SDK version, all the samples are updated as well.

For this release of the samples the version numbers are : 
* Samples version: **1.2.0.0**
* Required id3 An2K SDK version: **1.2.0**

## Getting started

### Step 1: Get a license and the SDK

To run any of the samples, you need to get a license from **id3 Technologies**. For that, you must contact us at the following e-mail address: contact@id3.eu.

Then, once your request will be accepted, you will receive both a license activation key and a ZIP archive containing the SDK itself. Once you are here, you can move forward to step 2.

### Step 2: Install the SDK and models

Once you have the SDK ZIP archive, you need to unzip it in the *sdk/* subfolder resulting in the following architecture.

    .
    ├── android
    ├── cpp
    ...
    ├── flutter
    ├── sdk
        ├── activation
        ├── bin
        ...
        └── README.md
    └── README.md

### Step 3: Activate a license

The id3 An2K SDK needs a license file to be used. To retrieve this license file you will need either:
- An id3 serial key (formatted as XXXX-XXXX-XXXX-XXXX): it allows activation (and further retrieval of the license file) on a single computer
- An id3 activation key (formatted as email-XXXXXXXX-XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX): it allows activations (and further retrievals of the license file) on several computers and can be re-credited upon request
- (A login / password / product reference) triplet: same behaviour as the activation key

This license file can be retrieved through different methods depending of your operating system:
- **On mobile systems:**
    - On most android and ios implementations, the system does not allow retrieval of a true unique hardware identifier to the application developers for privacy purposes. The side effect of this behavior is that you may get a different (but fixed) hardware code for each app you develop even on the same device.
    - As the hardware code you lock your id3 license on may be different on each app you need to retrieve the license through the app using the An2KLicense_Activate...() APIs
    - id3 recommends to run the activation at the first launch of the app and then store the license on the device for further uses, this is the behavior which is demonstrated in the mobile samples of this repository
    - For example the following code retrieves a license on android in Kotlin calling the Java API:
        ```kotlin
        val hardwareCode = License.getHostHardwareCode(LicenseHardwareCodeType.ANDROID)
        var licenseBuffer: ByteArray? = null
        licenseBuffer = License.activateSerialKeyBuffer(hardwareCode, "XXXX-XXXX-XXXX-XXXX", "Activated from Android")
        ```
    - Notes:
        - To use the activation APIs you must ensure that your application have the internet usage permission
        - When using the id3An2K Flutter wrapper, the android license activation and check must be performed from a native android class, this behavior is demonstrated in the flutter samples of this repository
- **On Windows or Linux systems:**
    - Using the command line interface tool in *sdk/activation/cli-tool*
        - For example on Windows you can run:
            - Serial key activation: `.\sdk\activation\cli-tool\windows\x64\id3LicenseActivationCLI.exe --activate .\data\id3An2K.lic --serialkey="XXXX-XXXX-XXXX-XXXX"`
            - Activation key activation: `.\sdk\activation\cli-tool\windows\x64\id3LicenseActivationCLI.exe --activate .\data\id3An2K.lic --activationkey="email-XXXXXXXX-XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX"`
            - Account activation: `.\sdk\activation\cli-tool\windows\x64\id3LicenseActivationCLI.exe --activate .\data\id3An2K.lic --login="login@domain.com" --password="myPassword" --reference="XXXXXXXX"`
        - Same examples on Linux:
            - Serial key activation: `./sdk/activation/cli-tool/linux/x64/id3LicenseActivationCLI --activate ./data/id3An2K.lic --serialkey="XXXX-XXXX-XXXX-XXXX"`
            - Activation key activation: `./sdk/activation/cli-tool/linux/x64/id3LicenseActivationCLI --activate ./data/id3An2K.lic --activationkey="email-XXXXXXXX-XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX"`
            - Account activation: `./sdk/activation/cli-tool/linux/x64/id3LicenseActivationCLI --activate ./data/id3An2K.lic --login="login@domain.com" --password="myPassword" --reference="XXXXXXXX"`
    - Using the An2KLicense_Activate...() APIs from the SDK:
        - For example the following code retrieves a license file using the C# API:
            ```c#
            string hardwareCode = id3.An2K.License.GetHostHardwareCode(id3.An2K.LicenseHardwareCodeType.WindowsOs);
            id3.An2K.License.ActivateSerialKey(hardwareCode,"XXXX-XXXX-XXXX-XXXX", "Activated through C# API", "data/id3An2K.lic");
            ```
        - Please see API documentation for more details about usage (retrieve license as file, as buffer, ...)
    - Using the License Manager tool in *sdk/activation/windows-tool* (only on Windows)

### Step 4: Play around with the samples

You are now ready to go straight to the directory of your favorite language/platform which will contain a readme file with additional information on how to run the samples.

Sample code is heavily commented in order to give you an overview of the id3 An2K SDK usage. We recommend you to read through the code while you run the samples.

## Troubleshooting

If you get stuck at any step of this procedure, please contact us: support@id3.eu.
