# Yet Another Speedometer Mod for GTA V
A simple speedometer mod with basic customization features.

# How to Install
## Dependencies
- [Microsoft Visual C++ Redistributable for Visual Studio 2022 x64](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170#latest-microsoft-visual-c-redistributable-version)
- [Script Hook V](https://www.dev-c.com/gtav/scripthookv/)

## Downloads & Installation
Download the latest release from the [Releases](https://github.com/rikkamus/yasm/releases) page on GitHub and extract `YetAnotherSpeedometerMod.asi` and `YetAnotherSpeedometerMod.ini` from the downloaded archive into your GTA V installation directory.

## Configuration Options
The following table lists all available configuration options that can be set in the `YetAnotherSpeedometerMod.ini` file. Keys, enum values and units are case-insensitive.

| Key                   | Type / Possible values                                      | Default                            | Notes                                                                                                                                                                                                                                                                                                                                                            |
| --------------------- | ----------------------------------------------------------- | ---------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Format                | string                                                      | `<font size='60'>%mph ~b~mph`      | You can use `%mph`, `%kph` and `%mps` to include speed values in the format text. Percent sign can be escaped using `%%`. Supports [formatting codes](https://docs.fivem.net/docs/game-references/text-formatting/#rockstar-formatting-codes).                                                                                                                   |
| Anchor                | One of: `TopLeft`, `TopRight`, `BottomLeft`, `BottomRight`  | `BottomRight`                      | The anchor also affects text justification (`TopLeft` and `BottomLeft` cause the text to be left-justified and `TopRight` and `BottomRight` cause the text to be right-justified).                                                                                                                                                                               |
| OffsetX               | &lt;float&gt;&lt;unit&gt;                                   | `15vh`                             | Supported units are: `px`, `vw`, `vh`. They work just like their [CSS counterparts](https://developer.mozilla.org/en-US/docs/Learn_web_development/Core/Styling_basics/Values_and_units#numbers_lengths_and_percentages). Offsets represent the distance of the speedometer from the anchor (offsets should be positive values).                                 |
| OffsetY               | &lt;float&gt;&lt;unit&gt;                                   | `15vh`                             | Supported units are: `px`, `vw`, `vh`. They work just like their [CSS counterparts](https://developer.mozilla.org/en-US/docs/Learn_web_development/Core/Styling_basics/Values_and_units#numbers_lengths_and_percentages). Offsets represent the distance of the speedometer from the anchor (offsets should be positive values).                                 |
| Font                  | integer                                                     | `0`                                | Uses GTA V's [font IDs](https://wiki.rage.mp/wiki/Fonts_and_Colors#DrawText_Fonts).                                                                                                                                                                                                                                                                              |
| Opacity               | float                                                       | `1.0`                              | Must be between 0.0 and 1.0.                                                                                                                                                                                                                                                                                                                                     |
| Scale                 | float                                                       | `1.0`                              | Must be a positive value.                                                                                                                                                                                                                                                                                                                                        |
| HideVehicleName       | boolean                                                     | `true`                             | If true, hides the vehicle name in the bottom-right corner of the HUD.                                                                                                                                                                                                                                                                                           |
| HideWhenUsingPhone    | boolean                                                     | `true`                             | If true, hides the speedometer while the player is using their phone.                                                                                                                                                                                                                                                                                            |

## Example Configuration File
**Note:** The following configuration was tested on a 2560x1440 display. The configuration may need to be modified in order to achieve the same result on screens with a different resolution.

### Configuration
```ini
Format = <font size='30'>~w~%kph ~c~kph~n~~w~%mps ~c~mps~n~<font size='65'>~w~%mph ~r~mph~n~
Anchor = BottomLeft
OffsetX = 17vw
OffsetY = 15vh
Font = 3
Opacity = 0.8
HideVehicleName = false
HideWhenUsingPhone = false
```

### Result
![Example](https://github.com/rikkamus/yasm/raw/refs/heads/main/screenshots/example.jpg)

## Default Configuration
This is what the speedometer looks like in its default configuration:

![Example](https://github.com/rikkamus/yasm/raw/refs/heads/main/screenshots/default.jpg)

# How to Compile
In order to compile the source code, you must first download the [Script Hook V SDK](https://www.dev-c.com/gtav/scripthookv/) and extract the contents of the downloaded archive into the [sdk directory](https://github.com/rikkamus/yasm/tree/main/sdk).
