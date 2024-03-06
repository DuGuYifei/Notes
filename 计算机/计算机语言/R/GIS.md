# GIS

## ggmap
[Google_ggmap](Google_ggmap.md)

## leaflet
## 添加圆和popup
```R
# install.packages("ggmap",lib = "./")
# install.packages("leaflet", lib = "./")
library(ggmap, lib.loc = "./")
library(leaflet, lib.loc = "./")
library(leaflet.providers, lib.loc = "./")
register_google(apiKey)

## Get the long-lat of each Voivodoship

locs <- c('Małopolskie', 'Śląskie', 'Wielkopolskie', 'Zachodniopomorskie', 'Lubuskie', 'Dolnośląskie', 'Opolskie', 'Kujawsko-pomorskie', 'Warmińsko-mazurskie', 'Pomorskie', 'Łódzkie', 'Świętokrzyskie', 'Lubelskie', 'Podkarpackie', 'Podlaskie', 'Mazowiecki')
locations<-geocode(locs)
locations

## Prepare dataset
unemployment <- c(4.6, 4.4, 3.2, 7.1, 5.0, 4.9, 6.0, 7.7, 8.6, 5.3, 5.8, 7.3, 7.1, 8.1, 7.0, 8.6)
dataset <- data.frame(locs, locations, unemployment)

## Map
### 1. Create leaflet map with circles. Circle sizes should be based on unemployment ratio (the higher unemployment ratio, the bigger circle)
### 2. Add popup and on popup Voivodoship name and unemployment rate should be visible.

pl_coordinates <- c(52.93046841624075, 18.913610940888134)

leaflet() %>%
  setView(lng = pl_coordinates[2], lat = pl_coordinates[1], zoom = 5) %>%
  addProviderTiles("OpenStreetMap.Mapnik") %>%
  addCircles(
    data = dataset,
    radius = dataset$unemployment * 5000,
    color = "#0073e6",
    fillColor = "#0073e6",
    fillOpacity = 0.3,
    popup = paste0(
      "<b>Voivodoship: </b>", dataset$locs, "<br>",
      "<b>unemployment(%): </b>", dataset$unemployment, "<br>"
    )
  ) 

```