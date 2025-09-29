## Battery statictics (batstat)
> [!WARNING]
> This project isn’t complete, so it’s unstable and lacks many of the functionalities it should have.

A simple service for logging the real capacity of laptop batteries over time to monitor how quickly they degrade.
The service logs the battery’s real capacity every day when the laptop starts up.
### Installation
```
$ make
$ sudo make install
$ systemctl enable batstat.service
```
### Usage

*Show history*
```
$ batstat
```
*Show graph of history*
```
$ batstat --graph
```
