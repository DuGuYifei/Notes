# Mongo_Operations

## Task Example
1. Tasks
```
For collection "cities" write queries (note that connections between cities are unidirectional):

1. find the distance from Kałużów to Pacynków,
2. add a connection from Pacynków to Pacynków with a distance of 40,
3. calculate a combined population of cities reachable from Pacynków.

For collection "albums" write queries:

1. find artists that had "Big Bad" as a guest,
2. add "Bonjo" as a guest artist in the track "100m",
3. calculate the combined length of the tracks performed by "Bonjo" (both his as well as guest performances).
```
2.  Data:
* "cities" collection:
```BSON
{
 city: "Arnoldów",
 population: 345,
 reachable_from:
 [
  {city: "Arnoldów", distance:34},
  {city: "Kałużów", distance:2}
 ]
},
{
 city: "Pacynków",
 population: 2,
 reachable_from:
 [
  {city: "Arnoldów", distance:5},
  {city: "Kałużów", distance:17},
  {city: "Mrzawków", distance:4}
 ]
},
{
 city: "Kałużów",
 population: 100000,
 reachable_from:
 [
  {city: "Mrzawków", distance: 12},
  {city: "Pacynków", distance: 23}
 ]
},
{
 city: "Mrzawków",
 population: 6727,
 reachable_from:
 [
  {city: "Pacynków", distance:11}
 ]
}
```
* "albums" collection:
```BSON
{
 artist: "Bonjo",
 album: "Banjo",
 tracks:
 [
  {title: "bip", length: 3.45},
  {title: "bop", length: 2.17, guest: "Rock"},
  {title: "bap", length: 4.05, guest: "Short"}
 ]
},
{
 artist: "Rock",
 album: "Roll",
 tracks:
 [
  {title: "Jail", length: 4.56, guest: "Big Bad"},
  {title: "House", length: 8.97},
  {title: "Rock", length: 2.34}
 ]
},
{
 artist: "Big Bad",
 album: "Wolf",
 tracks:
 [
  {title: "Little", length: 1.11, guest: "Bonjo"},
  {title: "Red", length: 2.77},
  {title: "Riding", length: 5.13},
  {title: "Hood", length: 4.05}
 ]
},
{
 artist: "Short",
 album: "Track",
 tracks:
 [
  {title: "100m", length: 10.00},
  {title: "200m", length: 20.00, guest: "Big Bad"}
 ]
}
```
3. Queris:
  1. find the distance from Kałużów to Pacynków,
    ```bash
    test> db.cities.find({city:"Pacynków","reachable_from.city":"Kałużów"},{_id:0,city:1,"reachable_from.$":1})
    [
      {
        city: 'Pacynków',
        reachable_from: [ { city: 'Kałużów', distance: 17 } ]
      }
    ]
    ```
  2. add a connection from Pacynków to Pacynków with a distance of 40
   ```bash
   
   ```
