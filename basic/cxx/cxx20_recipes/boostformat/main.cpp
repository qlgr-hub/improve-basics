#include <iostream>
#include "LocalizationManager.h"
#include <boost/format.hpp>

using namespace std;

int main()
{
    Localization::Manager localizationManager;
    
    string color{ localizationManager.GetString(Localization::STRING_COLOR) };
    cout << "EN_US localized string: " << color.c_str() << endl;

    string flavor{ localizationManager.GetString(Localization::STRING_FLAVOR) };
    cout << "EN_US localized string: " << flavor.c_str() << endl;

    localizationManager.SetLanguage(Localization::Languages::EN_GB);

    color = localizationManager.GetString(Localization::STRING_COLOR);
    cout << "EN_GB localized string: " << color.c_str() << endl;

    flavor = localizationManager.GetString(Localization::STRING_FLAVOR);
    cout << "EN_GB localized string: " << flavor.c_str() << endl;

    color = localizationManager.GetString(3);
    cout << color.c_str() << endl;

    cout << "Enter your first name: " << endl;
    string firstName;
    cin >> firstName;

    cout << "Enter your surname: " << endl;
    string surname;
    cin >> surname;

    localizationManager.SetLanguage(Localization::Languages::EN_US);
    string formatedName{ localizationManager.GetString(Localization::STRING_NAME) };
    formatedName = str( boost::format(formatedName) % firstName % surname );
    cout << "You said your name is: " << formatedName << endl;

    localizationManager.SetLanguage(Localization::Languages::EN_GB);
    formatedName = localizationManager.GetString(Localization::STRING_NAME);
    formatedName = str( boost::format(formatedName) % firstName % surname );
    cout << "You said your name is: " << formatedName << endl;

    return 0;
}
