# (Very) simplified air traffic control modeling

The purpose of this project is to model an air traffic control. Depending on the
selected, this modeling concerns a territory at the scale of a country or
around aerodromes/airports.
The three main air traffic control organizations are (see
Wikipedia):

● Area Control Centers (ACCs) responsible for providing air traffic services to
air traffic services to aircraft in cruise (outside the proximity of the aerodrome).
aerodrome proximity).

● The approach control centers (APP) are in charge of providing air traffic services
air traffic services in the vicinity of an aerodrome, in a control zone
The size of the control area varies. The air traffic controllers are located either in the lookout
of a control tower or in a dedicated radar room.

● Aerodrome control towers (TWR) are in charge of providing air traffic control services to the air traffic controllers
.
For this project, it will be considered that air traffic controllers in aerodrome control towers will
control towers will only manage the approach and departure of aircraft before landing and during
and their take-off as well as their parking on the dedicated areas in the airport.

## Installation

Use your favourite package manager to install [nlohmann-JSON](https://github.com/nlohmann/json).

```bash
sudo pacman -S nlohmann-json
```

## Usage

In the files, create a folder called `build`. After, go inside this file by doing :
```bash
cd build/
```
Then, you need to initialize the `MakeFile` project by doing :
```bash
cmake ..
```
And to finish, execute the project by doing :
```bash
make && ./airport
```
or, if you want a clean console before executing :
```bash
make && clear && ./airport
```


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## Contact

You can contact us by sending an email to :
`tom.mullier@student.junia.com`
or
`maxime.declemy@student.junia.com`

## License

Copyrighted, do not distribute
Under license [Attribution-NonCommercial-NoDerivatives](https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode)