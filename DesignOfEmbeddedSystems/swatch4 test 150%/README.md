# How to use
Open the project with Eclipse for ErikaOS 2.8, found at http://www.erika-enterprise.com/index.php/download/erika-v2.x.html . Import this project. Menu -> Project -> Clean... -> Build it after cleaning.

cd University/DesignOfEmbeddedSystems/swatch4 test 150%/swatch4
st-flash write Debug/c_mX.bin 0x8000000

st-flash must be downloaded from https://github.com/texane/stlink and installed manually. Windows users can also use the utility provided by ST, but you have to register on their website.
