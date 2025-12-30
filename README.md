# Overview 
This is a remake of one of my previous projects: [SilentWaifu](https://github.com/TomasAndrijevskis/SilentWaifu). Project was built in Unreal Engine 5.4 using C++.
This remake exists because of two reasons:
- I wanted to rebuild the project using C++ instead of relying primarily on Blueprints. Since I am still learning C++, this was a good opportunity to practice by remaking a project I had already created, rather than copying mechanics from other projects or games.
- I wanted to redesign parts of the project that were poorly implemented in the original version, particularly the overall UI and the save system.
## Removed
- Localization for different languages was not implemented. The game is available only in English. Since the game will not be shipped, I decided there was no point in adding localization.
- Promo codes were also removed for the same reason.
- The loading screen was removed. 
- The settings menu previously contained buttons for social media. These buttons still exist but are not clickable, as the social media pages no longer exist.

## Reworked
- Two out of three premium characters were converted into legendary characters and can now be purchased in the shop. The last one became an event character because I could not find the images for the previous event character. As a result, the premium character purchase menu was removed as well.
- Ability cooldown was reworked. Previously all cooldowns for each character on the main screen were displayed in an additional money panel. Now, cooldowns are shown above each character. To display them player needs to click on character. Second click or waiting a few seconds will hide the cooldown.
- The UI was completely redesigned. Previously, every screen (shop, storage, etc.) was implemented inside a single Blueprint file. Now, each screen is separated into its own file.
- The save system was completely reworked. Previously, the save file contained an array with pre-added empty elements, where each element represented a character ID. If new characters were added later and exceeded the array size, old accounts could not save them because the array size could not be increased after the save file was created. Now, the arrays are fully dynamic.
- The process of how characters gain coins was slightly reworked. Previously, when a character was placed on the main screen, the earning timer started. If the player left the game before the timer finished, offline earnings would restart the timer from zero instead of continuing from the remaining time. The same issue occurred when the player rejoined the game. Now, the remaining time is saved and correctly handled for both online and offline earnings.
